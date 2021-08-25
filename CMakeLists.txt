cmake_minimum_required(VERSION 3.20)
project(Vigenere_IC)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME Vigenere_IC)
set (source "${CMAKE_SOURCE_DIR}/resources")
set (destination "${CMAKE_CURRENT_BINARY_DIR}/resources")

find_package(OpenMP)

if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_executable(Vigenere_IC src/main.cpp src/io.cpp src/io.h src/main.h)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination}
        DEPENDS ${destination}
        COMMENT "symbolic link resources folder from ${source} => ${destination}"
)

target_link_libraries(Vigenere_IC PRIVATE OpenMP::OpenMP_CXX)
