# XCReader

## Introduction

QC starts using a new format of XBL config since 8450 platforms. The new format designed for it is to store some
important configurations like `XBL DTB`, `CPR`, and `DCB`.  
This tool is aim to extract those files from the XBL config.
:::tip
This tool only works on SM8450 and subsequent platforms.
:::

## How to use

- Just run it in a terminal will be fine.
- xbl_config.img is also acceptable.

```
Usage: <Path to xbl_config.elf> <Output Directory>
```

## Build
- Need cmake and C toolchain.
```
git clone https://github.com/woa-msmnile/XBLConfigReader --depth=1
cd XBLConfigReader
mkdir build && cd build
cmake -S .. && cmake --build .
```