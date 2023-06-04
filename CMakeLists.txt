cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(polinom)

include(cmake/function.cmake)

add_subdirectory(lib)
add_subdirectory(main)

add_subdirectory(gtest)
add_subdirectory(test)
