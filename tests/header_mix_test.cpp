// A translation unit that includes the header and imports the module sees one
// set of entities: a transcoder made through the header is a transcoder to the
// module's names, and what the module cannot export (a table of internal
// linkage) is there through the header beside it.
#include <transcoder/basisu_transcoder.h>

#include <gtest/gtest.h>

import mcpplibs.mwrap.basis_universal;

TEST(HeaderMix, TheSameEntities) {
    static_assert(std::is_same_v<basist::ktx2_transcoder, ::basist::ktx2_transcoder>);
    static_assert(mcpplibs::mwrap::basis_universal::basist::COLOR5_PAL0_PREV_HI == ::basist::COLOR5_PAL0_PREV_HI);
    EXPECT_EQ(sizeof(::basisu::g_huffman_sorted_codelength_codes), std::size_t{::basisu::cHuffmanTotalSortedCodelengthCodes});
    EXPECT_EQ(basist::basis_get_bytes_per_block_or_pixel(basist::transcoder_texture_format::cTFRGBA32), 4u);
    EXPECT_STREQ(basist::basis_get_format_name(basist::transcoder_texture_format::cTFBC7_RGBA), ::basist::basis_get_format_name(::basist::transcoder_texture_format::cTFBC7_RGBA));
}
