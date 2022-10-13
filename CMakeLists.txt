cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_STANDARD 14)

project(cxx-spline)

add_subdirectory(test)
enable_testing ()

add_subdirectory(demo)

add_library(cxx-spline INTERFACE)

target_include_directories(cxx-spline INTERFACE .)
