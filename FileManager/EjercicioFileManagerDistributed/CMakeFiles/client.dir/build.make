# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/perryplatypus/shared/distributed-systems/FileManager/EjercicioFileManagerDistributed

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/perryplatypus/shared/distributed-systems/FileManager/EjercicioFileManagerDistributed

# Include any dependencies generated for this target.
include CMakeFiles/client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/client.dir/flags.make

CMakeFiles/client.dir/client.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/client.cpp.o: client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/perryplatypus/shared/distributed-systems/FileManager/EjercicioFileManagerDistributed/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/client.dir/client.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/client.cpp.o -c /home/perryplatypus/shared/distributed-systems/FileManager/EjercicioFileManagerDistributed/client.cpp

CMakeFiles/client.dir/client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/perryplatypus/shared/distributed-systems/FileManager/EjercicioFileManagerDistributed/client.cpp > CMakeFiles/client.dir/client.cpp.i

CMakeFiles/client.dir/client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/perryplatypus/shared/distributed-systems/FileManager/EjercicioFileManagerDistributed/client.cpp -o CMakeFiles/client.dir/client.cpp.s

CMakeFiles/client.dir/FileManager.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/FileManager.cpp.o: FileManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/perryplatypus/shared/distributed-systems/FileManager/EjercicioFileManagerDistributed/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/client.dir/FileManager.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/FileManager.cpp.o -c /home/perryplatypus/shared/distributed-systems/FileManager/EjercicioFileManagerDistributed/FileManager.cpp

CMakeFiles/client.dir/FileManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/FileManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/perryplatypus/shared/distributed-systems/FileManager/EjercicioFileManagerDistributed/FileManager.cpp > CMakeFiles/client.dir/FileManager.cpp.i

CMakeFiles/client.dir/FileManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/FileManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/perryplatypus/shared/distributed-systems/FileManager/EjercicioFileManagerDistributed/FileManager.cpp -o CMakeFiles/client.dir/FileManager.cpp.s

CMakeFiles/client.dir/FileManagerImp.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/FileManagerImp.cpp.o: FileManagerImp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/perryplatypus/shared/distributed-systems/FileManager/EjercicioFileManagerDistributed/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/client.dir/FileManagerImp.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/FileManagerImp.cpp.o -c /home/perryplatypus/shared/distributed-systems/FileManager/EjercicioFileManagerDistributed/FileManagerImp.cpp

CMakeFiles/client.dir/FileManagerImp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/FileManagerImp.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/perryplatypus/shared/distributed-systems/FileManager/EjercicioFileManagerDistributed/FileManagerImp.cpp > CMakeFiles/client.dir/FileManagerImp.cpp.i

CMakeFiles/client.dir/FileManagerImp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/FileManagerImp.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/perryplatypus/shared/distributed-systems/FileManager/EjercicioFileManagerDistributed/FileManagerImp.cpp -o CMakeFiles/client.dir/FileManagerImp.cpp.s

CMakeFiles/client.dir/FileManagerStub.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/FileManagerStub.cpp.o: FileManagerStub.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/perryplatypus/shared/distributed-systems/FileManager/EjercicioFileManagerDistributed/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/client.dir/FileManagerStub.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/FileManagerStub.cpp.o -c /home/perryplatypus/shared/distributed-systems/FileManager/EjercicioFileManagerDistributed/FileManagerStub.cpp

CMakeFiles/client.dir/FileManagerStub.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/FileManagerStub.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/perryplatypus/shared/distributed-systems/FileManager/EjercicioFileManagerDistributed/FileManagerStub.cpp > CMakeFiles/client.dir/FileManagerStub.cpp.i

CMakeFiles/client.dir/FileManagerStub.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/FileManagerStub.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/perryplatypus/shared/distributed-systems/FileManager/EjercicioFileManagerDistributed/FileManagerStub.cpp -o CMakeFiles/client.dir/FileManagerStub.cpp.s

CMakeFiles/client.dir/Utils.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/Utils.cpp.o: Utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/perryplatypus/shared/distributed-systems/FileManager/EjercicioFileManagerDistributed/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/client.dir/Utils.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/Utils.cpp.o -c /home/perryplatypus/shared/distributed-systems/FileManager/EjercicioFileManagerDistributed/Utils.cpp

CMakeFiles/client.dir/Utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/Utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/perryplatypus/shared/distributed-systems/FileManager/EjercicioFileManagerDistributed/Utils.cpp > CMakeFiles/client.dir/Utils.cpp.i

CMakeFiles/client.dir/Utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/Utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/perryplatypus/shared/distributed-systems/FileManager/EjercicioFileManagerDistributed/Utils.cpp -o CMakeFiles/client.dir/Utils.cpp.s

# Object files for target client
client_OBJECTS = \
"CMakeFiles/client.dir/client.cpp.o" \
"CMakeFiles/client.dir/FileManager.cpp.o" \
"CMakeFiles/client.dir/FileManagerImp.cpp.o" \
"CMakeFiles/client.dir/FileManagerStub.cpp.o" \
"CMakeFiles/client.dir/Utils.cpp.o"

# External object files for target client
client_EXTERNAL_OBJECTS =

client: CMakeFiles/client.dir/client.cpp.o
client: CMakeFiles/client.dir/FileManager.cpp.o
client: CMakeFiles/client.dir/FileManagerImp.cpp.o
client: CMakeFiles/client.dir/FileManagerStub.cpp.o
client: CMakeFiles/client.dir/Utils.cpp.o
client: CMakeFiles/client.dir/build.make
client: CMakeFiles/client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/perryplatypus/shared/distributed-systems/FileManager/EjercicioFileManagerDistributed/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/client.dir/build: client

.PHONY : CMakeFiles/client.dir/build

CMakeFiles/client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/client.dir/clean

CMakeFiles/client.dir/depend:
	cd /home/perryplatypus/shared/distributed-systems/FileManager/EjercicioFileManagerDistributed && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/perryplatypus/shared/distributed-systems/FileManager/EjercicioFileManagerDistributed /home/perryplatypus/shared/distributed-systems/FileManager/EjercicioFileManagerDistributed /home/perryplatypus/shared/distributed-systems/FileManager/EjercicioFileManagerDistributed /home/perryplatypus/shared/distributed-systems/FileManager/EjercicioFileManagerDistributed /home/perryplatypus/shared/distributed-systems/FileManager/EjercicioFileManagerDistributed/CMakeFiles/client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/client.dir/depend

