# XCReader

## Description

Qualcomm makes use of a eXtended Boot Loader configuration binary (`xbl_config`) starting with SM8450 and later hardware platforms.

The eXtended Boot Loader configuration binary is intended to store important configuration data, previously found on older platforms within plain text cfg files, such as:

- `XBL DTB`
- `CPR`
- `DCB`

This tool allows the extraction of the eXtended Boot Loader configuration data for these hardware platforms, using the `xbl_config` ELF or partition binary as input.

> [!TIP]
> This tool only works on SM8450+ based platforms.

## Usage

- Command Line Tool only, run it from a Terminal or Console Application.
- Provide the path to `xbl_config.elf`, please note that `xbl_config.img` (partition copy of `xbl_config.elf` with extra blank padding) is also handled fine by the tool.

```bash
Usage: <Path to xbl_config.elf> <Output Directory>
```

## Build

Prerequisites:

- `CMake`
- `C Toolchain`.

```bash
git clone https://github.com/woa-msmnile/XBLConfigReader --depth=1
cd XBLConfigReader
mkdir build && cd build
cmake -S .. && cmake --build .
```
