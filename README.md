# FractalApp

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

![ubuntu-gnu](https://github.com/dmfrodrigues/fractal-app/workflows/ubuntu-gnu/badge.svg)
![windows-msvc](https://github.com/dmfrodrigues/fractal-app/workflows/windows-msvc/badge.svg)

Provides an easy interface to plot fractals.

This project makes use of the [wxWidgets](https://www.wxwidgets.org/) library, version [3.0.4](https://www.wxwidgets.org/downloads/).

## Compiling

The project is guaranteed to compile with:
* **GNU G++** under Ubuntu
* **Microsoft Visual C++** under Microsoft Windows
* **MinGW-W64** under Microsoft Windows

To compile using [GNU G++](.github/workflows/ubuntu-gnu) or [Microsoft Visual C++](.github/workflows/windows-msvc) check their respective workflow files.

### Under MinGW-W64

This particular case is very useful, given this package's wide reputation. However, because SourceForge sucks, I was not able to automate testing for this package.

Nevertheless, here are the instructions to compile this project using MinGW-W64:
- Download wxWidgets binaries for the latest stable release from the [downloads page](https://www.wxwidgets.org/downloads/), following [these instructions](https://docs.wxwidgets.org/trunk/plat_msw_binaries.html), namely:
    - In the downloads page choose a MinGW-w64 version and choose the 32bit or 64bit version.
    - For that version and bit size, download the header files, development files and release DLLs to the same folder.
    - Unzip all of them in the same directory, ending up with two folders: `include` and `lib`.
- Install [MinGW-W64 from SourceForge](https://sourceforge.net/projects/mingw-w64/files/)
    - Using the [executable](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe) to download a compatible version; you should match the version numbers (if the wxWidgets binaries you downloaded were made using MinGW-w64 8.1 you're going to download version `8.1.x`) and take into consideration the following details:
        - For 64bit wxWidgets, the MinGW-W64 package must be of architecture `x86_64`, with `posix` threads and `seh` exceptions
        - For 32bit wxWidgets, the MinGW-W64 package must be of architecture `i686`, with `posix` threads and `sjlj` exceptions
    -  By simply downloading the binaries [`x86_64-posix-seh`](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/8.1.0/threads-posix/seh/x86_64-8.1.0-release-posix-seh-rt_v6-rev0.7z) and unzipping them
- Look for the `bin` folder and include it in `PATH`
- Now you can compile the project; in the project base directory, create a folder `build`, `cd` to it and run `cmake .. -G "MinGW Makefiles"`

It is likely that (just as it happened to me) `cmake` fails to find the library, giving an error like:

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

you can run `cmake .. -G "MinGW Makefiles" -DwxWidgets_LIB_DIR:PATH=C:\wx\3.0.5\lib\gcc810_x64_dll`.

## Using the project

To use this project, you need to do two things:

1. Create your own class and inherit it from [FractalBitmap](include/FractalBitmap.h) (you should follow the orientations in [FractalBitmap.h](include/FractalBitmap.h) documentation)

2. Create a main source file similar to [FractalApp.cpp](FractalApp.cpp).

Documentation is available in the header/source where needed, or will be added soon.

You can check [dmfrodrigues/Mandelbrot](https://github.com/dmfrodrigues/Mandelbrot) for a working sample using FractalApp.
