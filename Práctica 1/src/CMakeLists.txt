﻿# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_BUILD_TYPE Debug)

project ("FileManagerDistr")
add_subdirectory ("FileManagerDistr")

project ("FileManagerMain")
add_subdirectory ("FileManagerMain")

project ("MultMatrixDistr")
add_subdirectory ("MultMatrixDistr")

project ("MultMatrixLocal")
add_subdirectory ("MultMatrixLocal")

project ("MultMatrixMain")
add_subdirectory ("MultMatrixMain")