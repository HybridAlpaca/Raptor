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
include CMakeFiles/Renderer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Renderer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Renderer.dir/flags.make

CMakeFiles/Renderer.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Renderer/Utils/Window.cpp.o: CMakeFiles/Renderer.dir/flags.make
CMakeFiles/Renderer.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Renderer/Utils/Window.cpp.o: /home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Renderer/Utils/Window.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cellman123/Desktop/Raptor/Engine/Build/CMake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Renderer.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Renderer/Utils/Window.cpp.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Renderer.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Renderer/Utils/Window.cpp.o -c /home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Renderer/Utils/Window.cpp

CMakeFiles/Renderer.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Renderer/Utils/Window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Renderer.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Renderer/Utils/Window.cpp.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Renderer/Utils/Window.cpp > CMakeFiles/Renderer.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Renderer/Utils/Window.cpp.i

CMakeFiles/Renderer.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Renderer/Utils/Window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Renderer.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Renderer/Utils/Window.cpp.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Renderer/Utils/Window.cpp -o CMakeFiles/Renderer.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Renderer/Utils/Window.cpp.s

CMakeFiles/Renderer.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Renderer/Utils/Window.cpp.o.requires:

.PHONY : CMakeFiles/Renderer.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Renderer/Utils/Window.cpp.o.requires

CMakeFiles/Renderer.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Renderer/Utils/Window.cpp.o.provides: CMakeFiles/Renderer.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Renderer/Utils/Window.cpp.o.requires
	$(MAKE) -f CMakeFiles/Renderer.dir/build.make CMakeFiles/Renderer.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Renderer/Utils/Window.cpp.o.provides.build
.PHONY : CMakeFiles/Renderer.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Renderer/Utils/Window.cpp.o.provides

CMakeFiles/Renderer.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Renderer/Utils/Window.cpp.o.provides.build: CMakeFiles/Renderer.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Renderer/Utils/Window.cpp.o


# Object files for target Renderer
Renderer_OBJECTS = \
"CMakeFiles/Renderer.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Renderer/Utils/Window.cpp.o"

# External object files for target Renderer
Renderer_EXTERNAL_OBJECTS =

libRenderer.a: CMakeFiles/Renderer.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Renderer/Utils/Window.cpp.o
libRenderer.a: CMakeFiles/Renderer.dir/build.make
libRenderer.a: CMakeFiles/Renderer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cellman123/Desktop/Raptor/Engine/Build/CMake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libRenderer.a"
	$(CMAKE_COMMAND) -P CMakeFiles/Renderer.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Renderer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Renderer.dir/build: libRenderer.a

.PHONY : CMakeFiles/Renderer.dir/build

CMakeFiles/Renderer.dir/requires: CMakeFiles/Renderer.dir/home/cellman123/Desktop/Raptor/Engine/Source/Runtime/Renderer/Utils/Window.cpp.o.requires

.PHONY : CMakeFiles/Renderer.dir/requires

CMakeFiles/Renderer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Renderer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Renderer.dir/clean

CMakeFiles/Renderer.dir/depend:
	cd /home/cellman123/Desktop/Raptor/Engine/Build/CMake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cellman123/Desktop/Raptor/Engine/Build /home/cellman123/Desktop/Raptor/Engine/Build /home/cellman123/Desktop/Raptor/Engine/Build/CMake /home/cellman123/Desktop/Raptor/Engine/Build/CMake /home/cellman123/Desktop/Raptor/Engine/Build/CMake/CMakeFiles/Renderer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Renderer.dir/depend

