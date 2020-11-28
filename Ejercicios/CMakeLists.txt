# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_BUILD_TYPE Release)

project ("FileManager")
add_subdirectory ("FileManager")

project ("MultMatrix")
add_subdirectory ("MultMatrix")
