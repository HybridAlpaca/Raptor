# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/cellman123/Desktop/Raptor/Engine/Build

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cellman123/Desktop/Raptor/Engine/Build/CMake

# Include any dependencies generated for this target.
include CMakeFiles/Core.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Core.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Core.dir/flags.make

CMakeFiles/Core.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Core/Math/Vector.cpp.o: CMakeFiles/Core.dir/flags.make
CMakeFiles/Core.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Core/Math/Vector.cpp.o: /home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Core/Math/Vector.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cellman123/Desktop/Raptor/Engine/Build/CMake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Core.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Core/Math/Vector.cpp.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Core.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Core/Math/Vector.cpp.o -c /home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Core/Math/Vector.cpp

CMakeFiles/Core.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Core/Math/Vector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Core.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Core/Math/Vector.cpp.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Core/Math/Vector.cpp > CMakeFiles/Core.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Core/Math/Vector.cpp.i

CMakeFiles/Core.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Core/Math/Vector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Core.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Core/Math/Vector.cpp.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Core/Math/Vector.cpp -o CMakeFiles/Core.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Core/Math/Vector.cpp.s

CMakeFiles/Core.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Core/Math/Vector.cpp.o.requires:

.PHONY : CMakeFiles/Core.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Core/Math/Vector.cpp.o.requires

CMakeFiles/Core.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Core/Math/Vector.cpp.o.provides: CMakeFiles/Core.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Core/Math/Vector.cpp.o.requires
	$(MAKE) -f CMakeFiles/Core.dir/build.make CMakeFiles/Core.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Core/Math/Vector.cpp.o.provides.build
.PHONY : CMakeFiles/Core.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Core/Math/Vector.cpp.o.provides

CMakeFiles/Core.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Core/Math/Vector.cpp.o.provides.build: CMakeFiles/Core.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Core/Math/Vector.cpp.o


# Object files for target Core
Core_OBJECTS = \
"CMakeFiles/Core.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Core/Math/Vector.cpp.o"

# External object files for target Core
Core_EXTERNAL_OBJECTS =

libCore.a: CMakeFiles/Core.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Core/Math/Vector.cpp.o
libCore.a: CMakeFiles/Core.dir/build.make
libCore.a: CMakeFiles/Core.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cellman123/Desktop/Raptor/Engine/Build/CMake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libCore.a"
	$(CMAKE_COMMAND) -P CMakeFiles/Core.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Core.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Core.dir/build: libCore.a

.PHONY : CMakeFiles/Core.dir/build

CMakeFiles/Core.dir/requires: CMakeFiles/Core.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Core/Math/Vector.cpp.o.requires

.PHONY : CMakeFiles/Core.dir/requires

CMakeFiles/Core.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Core.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Core.dir/clean

CMakeFiles/Core.dir/depend:
	cd /home/cellman123/Desktop/Raptor/Engine/Build/CMake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cellman123/Desktop/Raptor/Engine/Build /home/cellman123/Desktop/Raptor/Engine/Build /home/cellman123/Desktop/Raptor/Engine/Build/CMake /home/cellman123/Desktop/Raptor/Engine/Build/CMake /home/cellman123/Desktop/Raptor/Engine/Build/CMake/CMakeFiles/Core.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Core.dir/depend

