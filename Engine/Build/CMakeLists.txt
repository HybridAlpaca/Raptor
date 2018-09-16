#####################################
#                                   #
#      (c) 2018 HybridAlpaca        #
#                                   #
#            CMake v.3.5            #
#                                   #
# See README for Build Instructions #
#                                   #
#####################################

cmake_minimum_required (VERSION 3.5)

project (RaptorEngine LANGUAGES CXX)

######################
# Extern CMake Files #
######################

include (GNUInstallDirs)

######################
# Options and Params #
######################

# set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set (CMAKE_CXX_COMPILER /usr/bin/g++-8)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -fno-exceptions")

set (RAPTOR_ROOT_DIR ${CMAKE_SOURCE_DIR}/../..)
set (ENGINE_ROOT_DIR ${CMAKE_SOURCE_DIR}/..)
set (SOURCE_ROOT_DIR ${ENGINE_ROOT_DIR}/Source)
set (RUNTIME_ROOT_DIR ${SOURCE_ROOT_DIR}/Runtime)

if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE Release)
endif (NOT CMAKE_BUILD_TYPE)
if (CMAKE_BUILD_TYPE STREQUAL Debug)
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif ()

######################
# Inlcudes & Linking #
######################

include_directories ("${SOURCE_ROOT_DIR}/External")

link_directories ("${ENGINE_ROOT_DIR}/Binaries")

################
# Dependancies #
################

# opengl

find_package (OpenGL REQUIRED)
if (OPENGL_FOUND)
	include_directories (${OPENGL_INCLUDE_DIRS})
endif ()

# glew

find_package (GLEW REQUIRED)
if (GLEW_FOUND)
	include_directories (${GLEW_INCLUDE_DIRS})
endif()

####################
# Static Libraries #
####################

# raptor standard library

# add_library (LibRaptor STATIC
	# ${RUNTIME_ROOT_DIR}/Raptor/Private/POSIX/Console.cpp
# )
# target_include_directories (LibRaptor PUBLIC
	# ${RUNTIME_ROOT_DIR}/Raptor/Private
	# ${RUNTIME_ROOT_DIR}/Raptor/Public/Raptor
# )

include_directories (${RUNTIME_ROOT_DIR}/Raptor/Public)

# Core

add_library (Core STATIC
	${RUNTIME_ROOT_DIR}/Core/Private/Plugins.cpp
)
target_include_directories (Core PUBLIC
	${RUNTIME_ROOT_DIR}/Core/Private
	${RUNTIME_ROOT_DIR}/Core/Public/Core
)

include_directories (${RUNTIME_ROOT_DIR}/Core/Public)

# graphics

# add_library (Graphics STATIC
	# ${RUNTIME_ROOT_DIR}/Graphics/Private/GL/RenderDevice.cpp
	# ${RUNTIME_ROOT_DIR}/Graphics/Private/GL/Display.cpp
# )
# target_include_directories (Graphics PUBLIC
	# ${RUNTIME_ROOT_DIR}/Graphics/Private
	# ${RUNTIME_ROOT_DIR}/Graphics/Public/Graphics
# )
include_directories (${RUNTIME_ROOT_DIR}/Graphics/Public)

install (TARGETS Core DESTINATION ${ENGINE_ROOT_DIR}/Binaries)

#####################
# Create Executable #
#####################

add_executable (Raptor ${RUNTIME_ROOT_DIR}/main.cpp)
target_link_libraries (Raptor
	# LibRaptor
	Core
	# Graphics
	# assimp
	${OPENGL_gl_LIBRARY}
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
	v8
	glfw
	X11
	pthread
	Xrandr
	Xi
	dl
)

install (TARGETS Raptor DESTINATION ${ENGINE_ROOT_DIR}/Binaries)
