# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("EjercicioFileManager")

# Include sub-projects.
add_subdirectory ("EjercicioFileManager")



project ("EjercicioFileManagerDistributed")

# Include sub-projects.
add_subdirectory ("EjercicioFileManagerDistributed")
