# Hexadecimal Conversion Benchmarks

<img src="data:image/svg+xml;base64,CjxpbWcgc3R5bGU9IndpZHRoOiA1MDBweDsgaGVpZ2h0OiBhdXRvOyBmbG9hdDogbGVmdDsiIHNyYz0iLy9jZG4ub25saW5ld2ViZm9udHMuY29tL3N2Zy9pbWdfNTQ1OTQyLnBuZyIgYWx0PSJTZW8gQmVuY2htYXJrIEdyYXBoIENoYXJ0IFN0YXRpY3MgQW5hbHlzaXMgUGVyZm9ybWFuY2UiPgogIA==" width="128" height="128" align="left">

[![C++](https://img.shields.io/badge/language-c%2B%2B-blue.svg)](https://isocpp.org/)
[![qbs](https://img.shields.io/badge/built-qbs-brightgreen.svg)](http://doc.qt.io/qbs/)

Benchmarks of various methods of conversion of long hexadecimal strings into binary data.

## Rationale

One of problems I recently face is the necessity of processing large amount of incoming data in form of hexadecimal strings which need to be converted to bytes for extraction of message data. I've realized methods used so far are inefficient, especially on a small embedded system.

I've built this project for myself to produce quantitative results of performance comparison between different methods of conversion. I knew which function is going to be the fastest one from the beginning, however real numbers I received actually surprised me.

## Results

### Preliminary

This is quick summary of results I got from various executions based on 1024 characters to convert:

| Function                         |    x64 MSVC |  x64 L/GCC | x64 F/CLang |   RPI 3 GCC |
|----------------------------------|------------:|-----------:|:-----------:|------------:|
| convert_hex_string_naive_sscanf  | 185.7700 us | 50.1654 μs |             | 504.7270 μs |
| convert_hex_string_naive_strtoul |  33.8518 us |  9.4807 μs |             |  82.0596 μs |
| convert_hex_string_naive_lookup  |   6.0036 us |  2.2786 μs |             |  22.5882 μs |
| convert_hex_string_calculated    |   7.9937 us |  5.0399 μs |             |  38.5360 μs |

Legend:

* **MSVC**: Visual Studio 2017
* **L/GCC**: GCC on Linux
* **F/CLang**: CLang on FreeBSD
* **RPi3**: Raspberry Pi 3

One conclusion I clearly see is that Raspberry Pi 3 is only 10 times slower than my i7 notebook :smile:

### Detailed

Detailed report in preparation.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

#### Linux

These are minimal versions I personally tested the code with, there is slight possibility it may work with lower versions either:

* gcc >= 6.3.0
* qbs >= 1.7.0
* boost-dev >= 1.62.0

#### Windows

* msvc >= 14.11.25503 || cl >= 19.11.25547
* qbs >= 1.12.1
* boost >= 1.68.0

### Building and execution

#### Linux

```sh
qbs setup-toolchains --detect
qbs build profile:gcc
```

If you're using [clang](https://clang.llvm.org/) instead of gcc, after changing the above profile building should be possible. This hasn't been tested yet.

#### Windows

Build (including tests):

```sh
qbs setup-toolchains --detect
qbs build profile:MSVC2017-x86_x64
```

#### Common

Basic executions if you wish to run benchmark:

```sh
qbs run --products hexstringconvertbenchmark
```

Some extras if you with to run unit tests:

```sh
qbs run --products tests
qbs run --products tests-generator
```

## 3rd Party Tools

Special thanks for great tools used in this projects goes to:

* [Catch 2](https://github.com/catchorg/Catch2)
* [Nonius](https://github.com/libnonius/nonius/)

## Contributing

## Versioning

Versioning is not yet established.

## License

The content of this project itself is licensed under the [Creative Commons Attribution 4.0 International](https://creativecommons.org/licenses/by/4.0/) license, and the underlying source code used to prepare results for that content is licensed under [Creative Commons Zero 1.0](http://creativecommons.org/publicdomain/zero/1.0/) license.

* Documentation & Results: [![CC-BY 4.0](https://i.creativecommons.org/l/by/4.0/80x15.png)](https://creativecommons.org/licenses/by/4.0/)
* Source Code: [![CC0](https://licensebuttons.net/p/zero/1.0/80x15.png)]("http://creativecommons.org/publicdomain/zero/1.0/)
