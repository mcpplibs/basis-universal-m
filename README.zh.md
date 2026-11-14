# basis_universal

> Basis Universal 的转码器——把 KTX2 与 `.basis` 纹理转成像素或 GPU 自己的压缩格式——以 C++23 模块提供。

[English](README.md) · **简体中文** · [上游](https://github.com/BinomialLLC/basis_universal) · [发布](https://github.com/mcpplibs/basis-universal-m/releases) · [mcpp](https://github.com/mcpp-community/mcpp) · [索引](https://github.com/mcpplibs/mcpp-index)

[![C++23](https://img.shields.io/badge/C%2B%2B-23-blue.svg)](https://en.cppreference.com/w/cpp/23)
[![License](https://img.shields.io/badge/license-Apache--2.0-blue.svg)](LICENSE)
[![mcpp-community](https://img.shields.io/badge/mcpp--community-mwrap-blue)](https://github.com/mcpp-community)
[![CI](https://github.com/mcpplibs/basis-universal-m/actions/workflows/ci.yml/badge.svg?branch=main)](https://github.com/mcpplibs/basis-universal-m/actions/workflows/ci.yml)

上游的 C++ API 不变：`basist::ktx2_transcoder`、`basist::basisu_transcoder`、
`basist::transcoder_texture_format` 等都是上游的实体，位于上游声明它们的命名空间。
转码器源码逐字节取自 v2_50 发布，由本包按上游默认构建方式编译——全部格式、KTX2、
以及由上游随附的解码器提供的 Zstandard——只多两项选择：关闭浮点收缩；在每个目标上
都启用不透明块的较大 ASTC 表（上游在 Emscripten 下关闭它，那里的 ASTC 块会与原生构建
不同）。同一个文件在 CI 构建的每个平台上以及编译为 WebAssembly 时给出相同的像素和相同的
BC7、ETC2、ASTC 块（测试中固定了哈希）。封装修订 2.50.1 加入第二项选择，2.50 没有。
本包不含编码器。

## 模块

- `import mcpplibs.mwrap.basis_universal;`：`<transcoder/basisu_transcoder.h>` 在 `basist`、`basisu` 及其内部命名空间的命名空间作用域声明的每个名字——148 个类型、273 个函数、70 个对象、112 个无作用域枚举的枚举项

> 更多模块 API -> [上游 README](upstream/basis_universal/README.md)

## 快速开始

```sh
mcpp new texture --template mcpplibs.mwrap.basis_universal@2.50.1
cd texture
mcpp run -- a-texture.ktx2
```

默认模板说明一个 KTX2 文件是什么（尺寸、层级、编码），并把它的第一幅图读成 RGBA
像素；不给文件时列出转码器能写出的格式。

```toml
[dependencies]
mcpplibs.mwrap.basis_universal = "2.50.1"
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

块格式的取法相同：`cTFBC7_RGBA`、`cTFETC2_RGBA`、`cTFASTC_4x4_RGBA` ……，
把像素数换成该层级的块数（`ktx2_image_level_info::m_total_blocks`）。

## 常量与宏

头文件在命名空间作用域有 139 个标量常量是 `const` 而不是 `inline`
（`const uint32_t COLOR5_PAL0_PREV_HI = 9;`）：它们是内部链接（每个包含者各有一份），
模块无法导出。它们以原名、原类型、原值放在
`mcpplibs::mwrap::basis_universal::<所在命名空间>` 下
（`mcpplibs::mwrap::basis_universal::basist::COLOR5_PAL0_PREV_HI`）。
头文件的宏（`BASISD_SUPPORT_KTX2`、`BASISU_LIB_VERSION_KEY_NAME`、KTX2 的键名）
用于配置构建或命名字符串；没有 `.macros` 模块，需要的程序包含头文件即可。

## 包装了什么、没有包装什么

- 已包装：头文件在 `basist`、`basisu` 及其内部命名空间的每个名字（共 742 个，含上面改写的常量）。该头文件会带入上游的内部头文件，所以构成转码器的表和辅助函数也在其中，与包含头文件的程序所见一致。
- 不在模块中（11 个内部链接、无法重新给出的名字——`static` 函数、常量表、不是常量表达式的 `const float`）：`basist::MAX_HALF_FLOAT`, `basist::MIN_DENORM_HALF_FLOAT`, `basist::MIN_HALF_FLOAT`, `basist::astc_ldr_t::DEADZONE_ALPHA`, `basist::astc_ldr_t::SCALED_WEIGHT_BASE_CODING_SCALE`, `basisu::byteswap16`, `basisu::byteswap32`, `basisu::g_huffman_sorted_codelength_codes`, `basisu::read_le_dword`, `basisu::read_le_word`, `basisu::write_le_dword`。包含 `<transcoder/basisu_transcoder.h>` 的翻译单元（把 `upstream/basis_universal` 加入包含路径）可以使用它们，并且看到的实体与模块的相同（`tests/header_mix_test.cpp`）。
- 不包含：编码器（`encoder/`）、命令行工具、C／Python／WebAssembly 绑定、示例。
- Zstandard 用的是上游随附的解码器（`zstd/zstddeclib.c`），编译进本包；它的名字是 C 的，不导出。

## 验证

- `mcpp test`：上游自己的 KTX2 测试文件是什么（尺寸、层级、编码、alpha）；一张 ETC1S 照片转成 RGBA 像素以及 BC7、ETC2、ASTC 块，两次结果字节相同，各平台相同（固定哈希）；同一幅 XUASTC 图分别用 Zstandard 和算术编码打包，得到同一幅图；噪声、在四处截断的文件、被改动的标识符都被拒绝；头文件与模块在同一翻译单元混用。
- `python3 tools/check_exports.py`：模块与 `tools/surface.json` 完全一致；给出 clang++ 时（CI 的 LLVM 行必须给出）按编译器读到的头文件重新推导记录并比较。
- `python3 tools/test_template.py`：从已安装副本执行 `mcpp new`，严格构建并运行生成的工程。
- CI：Linux（GCC 16、LLVM 23）、macOS 与 Windows（LLVM 23）。

## 许可

包装部分为 Apache-2.0（mcpp-community）。Basis Universal 为 Apache-2.0，
© 2016-2026 Binomial LLC（“Basis Universal”是其商标）；它随附的 Zstandard 解码器
为 BSD 许可，© Facebook, Inc.。上游的 README、LICENSE、NOTICE 以及 Zstandard 的
LICENSE 保存在 `upstream/basis_universal/`，并随程序的许可文件一起部署。测试图像
来自上游的 `test_files/`，上游声明并不拥有它们。来源记录：`upstream/documents.json`。
