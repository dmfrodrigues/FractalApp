# FractalApp

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

[![ubuntu-gnu](https://github.com/dmfrodrigues/fractal-app/workflows/ubuntu-gnu/badge.svg)](.github/workflows/ubuntu-gnu)
[![win-msvc](https://github.com/dmfrodrigues/fractal-app/workflows/win-msvc/badge.svg)](.github/workflows/win-msvc)
[![win-mingw32](https://github.com/dmfrodrigues/fractal-app/workflows/win-mingw32/badge.svg)](.github/workflows/win-mingw32)
[![win-mingw64](https://github.com/dmfrodrigues/fractal-app/workflows/win-mingw64/badge.svg)](.github/workflows/win-mingw64)

Provides an easy interface to plot fractals.

This project makes use of the [wxWidgets](https://www.wxwidgets.org/) library, version [3.0.5](https://www.wxwidgets.org/downloads/).

## Compiling

This library has a CMake file that can be used to compile it using whichever compiler you prefer. It is guaranteed to work with:

| Workflow | Compiler suite | wxWidgets version |
|----------|----------------|-------------------|
| [![ubuntu-gnu](https://github.com/dmfrodrigues/fractal-app/workflows/ubuntu-gnu/badge.svg)](.github/workflows/ubuntu-gnu) **GNU G++** under Debian/Ubuntu | Latest version of *GNU GCC* available via `apt` ([GNU GCC 7.5.0](https://gcc.gnu.org/gcc-7/)) | Latest version of *wxGTK3.0* available via `apt` ([*wxWidgets 3.0.5*](https://www.wxwidgets.org/downloads/) ported to GTK, corresponding to package `libwxgtk3.0-dev`). |
| [![win-msvc](https://github.com/dmfrodrigues/fractal-app/workflows/win-msvc/badge.svg)](.github/workflows/win-msvc) **Microsoft Visual C++** under Microsoft Windows | Latest version of *MSVC* made available by GitHub Actions (*Visual Studio 16 2019*, compiler identification `MSVC 19.26.28806.0`) | Corresponding version of *wxMSW3.0* binaries available at the [official website](https://www.wxwidgets.org/) ([*wxWidgets 3.0.5*](https://www.wxwidgets.org/downloads/) ported to MSW). Since we use VS2019 (and apparently CMake defaults to a 64bit version), we downloaded the VS2019 64-Bit (`x86_64`) [developer files](https://github.com/wxWidgets/wxWidgets/releases/download/v3.0.5/wxMSW-3.0.5_vc142_x64_Dev.7z) and [release DLLs](https://github.com/wxWidgets/wxWidgets/releases/download/v3.0.5/wxMSW-3.0.5_vc142_x64_ReleaseDLL.7z). | 
| [![win-mingw32](https://github.com/dmfrodrigues/fractal-app/workflows/win-mingw32/badge.svg)](.github/workflows/win-mingw32) **MinGW32** under Microsoft Windows | MinGW-W64 8.1, architecture `i686` (32bit), `posix` threads and `sjlj` exceptions, from [here](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/8.1.0/threads-posix/sjlj/i686-8.1.0-release-posix-sjlj-rt_v6-rev0.7z). | Corresponding version of *wxMSW3.0* binaries available at the [official website](https://www.wxwidgets.org/) ([*wxWidgets 3.0.5*](https://www.wxwidgets.org/downloads/) ported to MSW). Although we use MinGW-W64 32bit, only *MinGW-w64 64-Bit* worked so we downloaded those [developer files](https://github.com/wxWidgets/wxWidgets/releases/download/v3.0.5/wxMSW-3.0.5_gcc810_x64_Dev.7z) and [release DLLs](https://github.com/wxWidgets/wxWidgets/releases/download/v3.0.5/wxMSW-3.0.5_gcc810_x64_ReleaseDLL.7z). |
| [![win-mingw64](https://github.com/dmfrodrigues/fractal-app/workflows/win-mingw64/badge.svg)](.github/workflows/win-mingw64) **MinGW64** under Microsoft Windows | MinGW-W64 8.1, architecture `x86_64` (64bit), `posix` threads and `seh` exceptions, from [here](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/8.1.0/threads-posix/seh/x86_64-8.1.0-release-posix-seh-rt_v6-rev0.7z). | Corresponding version of *wxMSW3.0* binaries available at the [official website](https://www.wxwidgets.org/) ([*wxWidgets 3.0.5*](https://www.wxwidgets.org/downloads/) ported to MSW). Since we use MinGW-W64 64bit, and the settings we chose (`posix` threads and `seh` exceptions) are [compatible](https://github.com/wxWidgets/wxWidgets/releases/tag/v3.0.5/) with *wxMSW MinGW-w64 64-Bit* (`x86_64`) binary files, we downloaded the *MinGW-w64 64-Bit* [developer files](https://github.com/wxWidgets/wxWidgets/releases/download/v3.0.5/wxMSW-3.0.5_gcc810_x64_Dev.7z) and [release DLLs](https://github.com/wxWidgets/wxWidgets/releases/download/v3.0.5/wxMSW-3.0.5_gcc810_x64_ReleaseDLL.7z). |

To install MinGW-W64 you can also use the [installer](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe) and select the appropriate settings (32/64bit, threads and exceptions).

If you use MinGW-W64, it is likely that (just as it happened to me) `cmake` fails to find the library, giving an error like:

```
CMake Error at C:/cmake-3.17.3-win64-x64/share/cmake-3.17/Modules/FindPackageHandleStandardArgs.cmake:164 (message):
  Could NOT find wxWidgets (missing: wxWidgets_LIBRARIES
  wxWidgets_INCLUDE_DIRS core base)
Call Stack (most recent call first):
  C:/cmake-3.17.3-win64-x64/share/cmake-3.17/Modules/FindPackageHandleStandardArgs.cmake:445 (_FPHSA_FAILURE_MESSAGE)
  C:/cmake-3.17.3-win64-x64/share/cmake-3.17/Modules/FindwxWidgets.cmake:1008 (find_package_handle_standard_args)
  src/CMakeLists.txt:8 (find_package)


-- Configuring incomplete, errors occurred!
See also "D:/dmfro/projects/fractals/fractal-app/build/CMakeFiles/CMakeOutput.log".
```

Assuming:
- wxWidgets version 3.0.5 is in `C:\wx\3.0.5`
- you downloaded the MinGW-w64 8.1 64bit binaries for wxWidgets, and unzipped them so that the `C:\wx\3.0.5\lib` folder now has a folder `gcc810_x64_dll` inside it
- You used the `x86_64-posix-seh` binaries

you can run `cmake .. -G "MinGW Makefiles" -DWX_ROOT_DIR:PATH=C:\wx\3.0.5 -DwxWidgets_LIB_DIR:PATH=C:\wx\3.0.5\lib\gcc810_x64_dll` (or alternatively run `cmake .. -G "MinGW Makefiles" -DwxWidgets_LIB_DIR:PATH=C:\wx\3.0.5\lib\gcc810_x64_dll` twice so as to appreciate the arbitrary workings of `FindwxWidgets`).

For further information on how to compile using a certain environment, click the respective badge.

## Using

To use this project, you need to:

1. Create your own class and inherit it from [FractalBitmap](include/FractalBitmap.h), implementing the pure virtual functions so your class can be instantiated (follow the guidelines in [FractalBitmap.h](include/FractalBitmap.h) documentation blocks)

2. Create a main source file similar to [FractalApp.cpp](FractalApp.cpp).

You can check [dmfrodrigues/mandelbrot](https://github.com/dmfrodrigues/mandelbrot) for a working sample using FractalApp.
