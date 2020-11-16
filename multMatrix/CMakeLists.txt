cmake_minimum_required (VERSION 2.8.11)
set(CMAKE_BUILD_TYPE "Debug")
project (multMatrix)

add_executable (multMatrix main_multMatrix.cpp multmatrix.cpp multmatrix.h)
