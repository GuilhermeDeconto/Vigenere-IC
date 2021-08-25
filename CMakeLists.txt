cmake_minimum_required(VERSION 3.20)
project(Vigenere_IC)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP)

if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_executable(Vigenere_IC main.cpp)

target_link_libraries(Vigenere_IC PRIVATE OpenMP::OpenMP_CXX)
