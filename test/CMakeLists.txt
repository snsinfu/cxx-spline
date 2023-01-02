cmake_minimum_required(VERSION 3.8.0)

set(CMAKE_CXX_STANDARD 11)

if (MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wconversion -Wextra -pedantic -Wsign-conversion -Wshadow)
endif()

enable_testing()

include_directories(..)

add_library(Catch INTERFACE)

add_library(catchmain catchmain.cpp)

target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

add_executable(natural natural.cpp)
target_link_libraries(natural Catch catchmain)
add_test(Natural natural)

add_executable(not-a-knot not-a-knot.cpp)
target_link_libraries(not-a-knot Catch catchmain)
add_test(Not-a-knot not-a-knot)

add_executable(default-behav default-behav.cpp)
target_link_libraries(default-behav Catch catchmain)
add_test(Default-behaviour default-behav)

add_executable(errors errors.cpp)
target_link_libraries(errors Catch catchmain)
add_test(Provoking-errors errors)

add_executable(repeated repeated.cpp)
target_link_libraries(repeated Catch catchmain)
add_test(Repeated-spline-calc repeated)
