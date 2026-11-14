# basis_universal

> Basis Universal's transcoder — KTX2 and `.basis` textures to pixels or to a GPU's own compressed format — through C++23 modules.

**English** · [简体中文](README.zh.md) · [Upstream](https://github.com/BinomialLLC/basis_universal) · [Releases](https://github.com/mcpplibs/basis-universal-m/releases) · [mcpp](https://github.com/mcpp-community/mcpp) · [Index](https://github.com/mcpplibs/mcpp-index)

[![C++23](https://img.shields.io/badge/C%2B%2B-23-blue.svg)](https://en.cppreference.com/w/cpp/23)
[![License](https://img.shields.io/badge/license-Apache--2.0-blue.svg)](LICENSE)
[![mcpp-community](https://img.shields.io/badge/mcpp--community-mwrap-blue)](https://github.com/mcpp-community)
[![CI](https://github.com/mcpplibs/basis-universal-m/actions/workflows/ci.yml/badge.svg?branch=main)](https://github.com/mcpplibs/basis-universal-m/actions/workflows/ci.yml)

The upstream C++ API is unchanged: `basist::ktx2_transcoder`,
`basist::basisu_transcoder`, `basist::transcoder_texture_format` and the rest
are the upstream entities, in the namespaces upstream declares them in. The
transcoder's sources are vendored byte for byte from the v2_50 release and
built by this package as upstream's default build does — every format, KTX2,
and Zstandard by the decoder upstream ships beside it — with one choice:
floating-point contraction off. The same file gives the same pixels and the
same BC7, ETC2 and ASTC blocks on every platform CI builds (pinned hashes in
the tests). The encoder is not in this package.

## Modules

- `import mcpplibs.mwrap.basis_universal;`: every name `<transcoder/basisu_transcoder.h>` declares at namespace scope in `basist`, `basisu` and the namespaces inside them — 148 types, 273 functions, 70 objects and 112 enumerators of unscoped enumerations

> More Modules API -> [upstream's README](upstream/basis_universal/README.md)

## Getting started

```sh
mcpp new texture --template mcpplibs.mwrap.basis_universal@2.50
cd texture
mcpp run -- a-texture.ktx2
```

The default template says what a KTX2 file is (its size, levels, codec) and
reads its first picture as RGBA pixels; with no file it lists what the
transcoder can write.

```toml
[dependencies]
mcpplibs.mwrap.basis_universal = "2.50"
```

```cpp
import std;
import mcpplibs.mwrap.basis_universal;

std::vector<std::uint8_t> pixels_of(std::span<const std::uint8_t> ktx2) {
    basist::basisu_transcoder_init();  // once a program
    basist::ktx2_transcoder transcoder;
    if (!transcoder.init(ktx2.data(), static_cast<std::uint32_t>(ktx2.size())) || !transcoder.start_transcoding()) return {};
    const std::uint32_t pixels = transcoder.get_width() * transcoder.get_height();
    std::vector<std::uint8_t> out(std::size_t{pixels} * 4);
    if (!transcoder.transcode_image_level(0, 0, 0, out.data(), pixels, basist::transcoder_texture_format::cTFRGBA32)) return {};
    return out;
}
```

A block format is asked the same way: `cTFBC7_RGBA`, `cTFETC2_RGBA`,
`cTFASTC_4x4_RGBA` …, with the level's block count
(`ktx2_image_level_info::m_total_blocks`) in place of the pixel count.

## Constants and macros

139 scalar constants at namespace scope in the header are `const` and not
`inline` (`const uint32_t COLOR5_PAL0_PREV_HI = 9;`): they have internal
linkage (each includer has its own) and a module cannot export them. They are
under `mcpplibs::mwrap::basis_universal::<their namespace>` with their names,
types and values (`mcpplibs::mwrap::basis_universal::basist::COLOR5_PAL0_PREV_HI`).
The header's macros (`BASISD_SUPPORT_KTX2`, `BASISU_LIB_VERSION_KEY_NAME`, the
KTX2 key names) configure the build or name strings; there is no `.macros`
module, and a program that needs one includes the header.

## What is and is not wrapped

- Wrapped: every name of the header in `basist`, `basisu` and their inner namespaces (742 in all, the adapted constants among them). The header brings upstream's internal header with it, so the tables and helpers a transcoder is built from are there too, as they are for a program that includes it.
- Not in the module (11 names of internal linkage that cannot be given again — `static` functions, constant tables, `const float`s that are no constant expressions): `basist::MAX_HALF_FLOAT`, `basist::MIN_DENORM_HALF_FLOAT`, `basist::MIN_HALF_FLOAT`, `basist::astc_ldr_t::DEADZONE_ALPHA`, `basist::astc_ldr_t::SCALED_WEIGHT_BASE_CODING_SCALE`, `basisu::byteswap16`, `basisu::byteswap32`, `basisu::g_huffman_sorted_codelength_codes`, `basisu::read_le_dword`, `basisu::read_le_word`, `basisu::write_le_dword`. A translation unit that includes `<transcoder/basisu_transcoder.h>` (add `upstream/basis_universal` to its include path) has them, and sees the same entities as the module's (`tests/header_mix_test.cpp`).
- Not here: the encoder (`encoder/`), the command line tool, the C, Python and WebAssembly bindings, the samples.
- Zstandard is upstream's own copy of the decoder (`zstd/zstddeclib.c`), compiled into this package; its names are C's and are not exported.

## Verification

- `mcpp test`: what upstream's own KTX2 test files are (size, levels, codec, alpha); an ETC1S photograph as RGBA pixels and as BC7, ETC2 and ASTC blocks, the same bytes twice and on every platform (pinned); one XUASTC picture packed by Zstandard and by the arithmetic coder is one picture; noise, a file cut at four places and a changed identifier are refused; header and module mixed in one translation unit.
- `python3 tools/check_exports.py`: the module is exactly `tools/surface.json`; given a clang++ (required on CI's LLVM row) the record is derived again from the header as the compiler reads it, and compared.
- `python3 tools/test_template.py`: `mcpp new` from an installed copy, a strict build, and a run of the generated project.
- CI: Linux (GCC 16, LLVM 23), macOS and Windows (LLVM 23).

## License

The wrapper is Apache-2.0 (mcpp-community). Basis Universal is Apache-2.0,
© 2016-2026 Binomial LLC ("Basis Universal" is its trademark); the Zstandard
decoder it ships is BSD-licensed, © Facebook, Inc. Upstream's README, LICENSE
and NOTICE and Zstandard's LICENSE are kept in `upstream/basis_universal/` and
deployed with a program's licenses. The test images are from upstream's
`test_files/`, which upstream states it does not own. Provenance:
`upstream/documents.json`.
