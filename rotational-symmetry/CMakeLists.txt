cmake_minimum_required(VERSION 3.16)
project(rotational-symmetry)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(../SDL build EXCLUDE_FROM_ALL)
add_subdirectory(src)
