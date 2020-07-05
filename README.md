# FractalApp

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

![ubuntu-gnu](https://github.com/dmfrodrigues/fractal-app/workflows/ubuntu-gnu/badge.svg)
![windows-msvc](https://github.com/dmfrodrigues/fractal-app/workflows/windows-msvc/badge.svg)
![windows-mingw](https://github.com/dmfrodrigues/fractal-app/workflows/windows-mingw/badge.svg)

Provides an easy interface to plot fractals.

This project makes use of the [wxWidgets](https://www.wxwidgets.org/) library, version [3.0.4](https://www.wxwidgets.org/downloads/).

## Compiling

The project is guaranteed to compile with:
* [TDM-GCC-64 5.1.0](http://tdm-gcc.tdragon.net/download)

To compile using `make`, please edit `WXLIB`, `IFLAGS` and `LFLAGS` so the paths to the library correspond to your owns'.

After that, all you will need is the file *libfractalapp.a*, which will be at *./lib/*. For using it in your project, make sure the compiler can find *libfractalapp.a* by including the path to it using -Lpath/to/FractalApp/lib/ and the flag -lfractalapp

## Using the project

To use this project, you need to do two things:

1. Create your own class and inherit it from [FractalBitmap](include/FractalBitmap.h) (you should follow the orientations in [FractalBitmap.h](include/FractalBitmap.h) documentation)

2. Create a main source file similar to [FractalApp.cpp](FractalApp.cpp).

Documentation is available in the header/source where needed, or will be added soon.

You can check [dmfrodrigues/Mandelbrot](https://github.com/dmfrodrigues/Mandelbrot) for a working sample using FractalApp.
