cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_STANDARD 11)

if (MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wconversion -Wextra -pedantic -Wsign-conversion -Wshadow)
endif()

enable_testing()

include_directories(..)

add_library(Catch INTERFACE)

target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

add_executable(test_spline test_spline.cc)
target_link_libraries(test_spline Catch)
