# Vigenère Cryptanalysis

Project developed for the Systems Security discipline of the Software Engineering course at PUCRS in 2021/2.

This project aims to find a clear text from a ciphertext using the Index of Coincidence, chi-squared and OpenMP.

## OpenMP

OpenMP is a set of compiler directives as well as an API for programs written in C, C++ that provides support for parallel programming in a shared-memory environment.

When OpenMP encounters a directive such as `#pragma omp parallel for` it creates as many threads as available in the host system and simultaneously execute the parallel region.

## Prerequisites

- OpenMP
  - `brew install libomp`
- CMake

# Benchmark

Test bench:
- MacBook Pro M1 (2020)
- 16GB RAM
- CLion 2021.2.1
- CMake 3.20
- MacOS 11.5.2
- libomp 12.0.1

File input: `cipher31.txt`

Result:`Elapsed time in milliseconds: 719 ms`

File input: `20201-teste2.txt`

Result:`Elapsed time in milliseconds: 8 ms`
