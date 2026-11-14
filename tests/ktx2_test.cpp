// The transcoder through the module: upstream's own KTX2 test files (tests/data,
// from the release's test_files/) read, their pictures as pixels and as a GPU's
// blocks — the same bytes on every platform and compiler the package is built
// for — and what is not a KTX2 file refused.
#include <gtest/gtest.h>

import std;
import mcpplibs.mwrap.basis_universal;

namespace {

std::vector<std::uint8_t> file(const char* name) {
    std::ifstream in(std::filesystem::path("tests/data") / name, std::ios::binary);
    return {std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>()};
}
std::uint64_t fnv(std::span<const std::uint8_t> bytes) {
    std::uint64_t hash = 14695981039346656037ull;
    for (const std::uint8_t byte : bytes) hash = (hash ^ byte) * 1099511628211ull;
    return hash;
}
// A level of a file in a format: its bytes (empty: refused).
std::vector<std::uint8_t> transcoded(const std::vector<std::uint8_t>& bytes, basist::transcoder_texture_format format, std::uint32_t level = 0) {
    basist::ktx2_transcoder transcoder;
    if (!transcoder.init(bytes.data(), static_cast<std::uint32_t>(bytes.size())) || !transcoder.start_transcoding()) return {};
    basist::ktx2_image_level_info info;
    if (!transcoder.get_image_level_info(info, level, 0, 0)) return {};
    const bool blocks = !basist::basis_transcoder_format_is_uncompressed(format);
    const std::uint32_t count = blocks ? info.m_total_blocks : info.m_orig_width * info.m_orig_height;
    std::vector<std::uint8_t> out(std::size_t{count} * basist::basis_get_bytes_per_block_or_pixel(format));
    if (!transcoder.transcode_image_level(level, 0, 0, out.data(), count, format)) return {};
    return out;
}

class Ktx2 : public ::testing::Test {
protected:
    static void SetUpTestSuite() { basist::basisu_transcoder_init(); }
};

}  // namespace

TEST_F(Ktx2, WhatAFileIs) {
    EXPECT_TRUE(basist::basisu_transcoder_supports_ktx2());
    EXPECT_TRUE(basist::basisu_transcoder_supports_ktx2_zstd());
    const std::vector<std::uint8_t> bytes = file("kodim23.ktx2");
    ASSERT_FALSE(bytes.empty());
    basist::ktx2_transcoder transcoder;
    ASSERT_TRUE(transcoder.init(bytes.data(), static_cast<std::uint32_t>(bytes.size())));
    EXPECT_EQ(transcoder.get_width(), 768u);
    EXPECT_EQ(transcoder.get_height(), 512u);
    EXPECT_EQ(transcoder.get_levels(), 1u);
    EXPECT_EQ(transcoder.get_faces(), 1u);
    EXPECT_TRUE(transcoder.is_etc1s());
    EXPECT_TRUE(transcoder.is_ldr());
    EXPECT_FALSE(transcoder.get_has_alpha());
    ASSERT_TRUE(transcoder.start_transcoding());
    basist::ktx2_image_level_info info;
    ASSERT_TRUE(transcoder.get_image_level_info(info, 0, 0, 0));
    EXPECT_EQ(info.m_orig_width, 768u);
    EXPECT_EQ(info.m_orig_height, 512u);
    EXPECT_EQ(info.m_total_blocks, 192u * 128u);
    EXPECT_FALSE(transcoder.get_image_level_info(info, 1, 0, 0)) << "a level the file has not";

    const std::vector<std::uint8_t> other = file("base_xuastc_zstd.ktx2");
    basist::ktx2_transcoder second;
    ASSERT_TRUE(second.init(other.data(), static_cast<std::uint32_t>(other.size())));
    EXPECT_EQ(second.get_width(), 512u);
    EXPECT_EQ(second.get_height(), 512u);
    EXPECT_TRUE(second.is_xuastc_ldr());
    EXPECT_FALSE(second.is_etc1s());
}

TEST_F(Ktx2, PixelsTheSameEverywhere) {
    // ETC1S (the photograph), as pixels and as three GPUs' blocks.
    const std::vector<std::uint8_t> photograph = file("kodim23.ktx2");
    const std::vector<std::uint8_t> pixels = transcoded(photograph, basist::transcoder_texture_format::cTFRGBA32);
    ASSERT_EQ(pixels.size(), std::size_t{768} * 512 * 4);
    EXPECT_EQ(fnv(pixels), 13856374787171296120ull);
    EXPECT_EQ(pixels, transcoded(photograph, basist::transcoder_texture_format::cTFRGBA32)) << "again: the same bytes";
    for (std::size_t pixel = 0; pixel < pixels.size() / 4; ++pixel) ASSERT_EQ(pixels[pixel * 4 + 3], 255) << "no alpha in the file: every pixel whole";
    const std::vector<std::uint8_t> bc7 = transcoded(photograph, basist::transcoder_texture_format::cTFBC7_RGBA);
    const std::vector<std::uint8_t> etc2 = transcoded(photograph, basist::transcoder_texture_format::cTFETC2_RGBA);
    const std::vector<std::uint8_t> astc = transcoded(photograph, basist::transcoder_texture_format::cTFASTC_4x4_RGBA);
    ASSERT_EQ(bc7.size(), std::size_t{192} * 128 * 16);
    ASSERT_EQ(etc2.size(), std::size_t{192} * 128 * 16);
    ASSERT_EQ(astc.size(), std::size_t{192} * 128 * 16);
    EXPECT_EQ(fnv(bc7), 15766935376129529535ull);
    EXPECT_EQ(fnv(etc2), 3619060494117872028ull);
    EXPECT_EQ(fnv(astc), 17062277099759253142ull);

    // XUASTC: one picture packed two ways (Zstandard, and the arithmetic coder) is one picture.
    const std::vector<std::uint8_t> by_zstd = transcoded(file("base_xuastc_zstd.ktx2"), basist::transcoder_texture_format::cTFRGBA32);
    const std::vector<std::uint8_t> by_arith = transcoded(file("base_xuastc_arith.ktx2"), basist::transcoder_texture_format::cTFRGBA32);
    ASSERT_EQ(by_zstd.size(), std::size_t{512} * 512 * 4);
    EXPECT_EQ(fnv(by_zstd), 12946497234108996751ull);
    EXPECT_EQ(by_zstd, by_arith);
}

TEST_F(Ktx2, WhatIsNotAFileIsRefused) {
    const std::vector<std::uint8_t> bytes = file("kodim23.ktx2");
    ASSERT_GT(bytes.size(), std::size_t{1000});
    basist::ktx2_transcoder transcoder;
    const std::vector<std::uint8_t> noise(4096, 0x5a);
    EXPECT_FALSE(transcoder.init(noise.data(), static_cast<std::uint32_t>(noise.size())));
    EXPECT_FALSE(transcoder.init(bytes.data(), 40)) << "cut inside its header";
    // Cut anywhere, a file is refused at some step or gives a picture: it never reads past its end.
    for (const std::size_t kept : {std::size_t{80}, std::size_t{200}, bytes.size() / 2, bytes.size() - 1}) {
        const std::vector<std::uint8_t> cut(bytes.begin(), bytes.begin() + static_cast<std::ptrdiff_t>(kept));
        const std::vector<std::uint8_t> out = transcoded(cut, basist::transcoder_texture_format::cTFRGBA32);
        EXPECT_TRUE(out.empty()) << kept;
    }
    // A byte of the header changed: the identifier no longer says KTX2.
    std::vector<std::uint8_t> other = bytes;
    other[1] ^= 0xff;
    EXPECT_FALSE(transcoder.init(other.data(), static_cast<std::uint32_t>(other.size())));
}
