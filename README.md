# Vigenère Cryptanalysis

Project developed for the Systems Security discipline of the Software Engineering course at PUCRS in 2021/2.

This project aims to find a clear text from a ciphertext using the Index of Coincidence, chi-squared and OpenMP.

## OpenMP

OpenMP is a set of compiler directives as well as an API for programs written in C, C++ that provides support for parallel programming in a shared-memory environment.

When OpenMP encounters a directive such as `#pragma omp parallel for` it creates as many threads as available in the host system and simultaneously execute the parallel region.

## Prerequisites

- OpenMP 5.0+
  - `brew install libomp`
- CLion 2021.2.1+
- CMake 3.10+
  - *CMake should come bundled with CLion*

**Note:** This software was tested with the versions above, if any error occurs check the versions before opening any issue regarding build and/or compile errors.

## Build and Running Instructions

In order to run and debug this software it is recommended to use CLion and CMake. You can open the folder in CLion and run the application as you normally would.

If you don't want to use an IDE like CMake, please run the following commands:

1. `cmake -Bbuild -H.`
2. `cmake --build build --target all`
3. `cd build`
4. `./Vigenere_IC <absolute-path-to-file-to-be-decrypted> <language>`

Where language can be one of the following options:

1. `eng`, this option refers to english language.
2. `pt`, this option refers to portuguese language.

### Notes

1. The `build` folder is the directory, where CMake will generate temporary files and the build artifacts.
2. The -H. option tells CMake, where the CMakeLists.txt file is located, which in this case is the current working directory.

# Benchmark

Test bench:
- MacBook Pro M1 (2020)
- 16GB RAM
- CLion 2021.2.1
- CMake 3.20
- MacOS 11.5.2
- libomp 12.0.1

File input: `cipher31.txt`

Result:`Elapsed time in milliseconds: 685 ms`

File input: `cipherpt.txt`

Result:`Elapsed time in milliseconds: 3 ms`
