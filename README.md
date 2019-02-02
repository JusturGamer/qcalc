# QCalc

QCalc is a multiple-precision GUI calculator.

![qcalc](https://user-images.githubusercontent.com/33803413/52157862-d3ae3180-2692-11e9-849f-04f46c99adaf.png)

## Prerequisites

* [CMake](https://cmake.org/)
* [Git](https://git-scm.com/)
* [MPIR](http://mpir.org/)
* [MPFR](https://www.mpfr.org/)
* [Qt5](https://www.qt.io/)

## Building

``` shell
cmake . -Bbuild
cmake --build build
```

### `MPIR_ROOT` and `MPFR_ROOT`

You may need to specify patches to MPIR and MPFR root directories by setting `MPIR_ROOT` and `MPFR_ROOT` variables.

You can do that using CMake `-D` option or by setting environment variables.

For example:

``` shell
cmake . -Bbuild -DMPIR_ROOT="C:\MPIR" -DMPFR_ROOT="C:\MPFR"
```

### Visual Studio

To create solution for Visual Studio correctly, you may need to specify [CMake Generator](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html).

For example, to create solution for Visual Studio 2017 on 64-bit Windows, enter the following in [Developer Command Prompt](https://docs.microsoft.com/en-us/dotnet/framework/tools/developer-command-prompt-for-vs):

``` shell
cmake -G"Visual Studio 15 Win64" . -Bbuild
```
