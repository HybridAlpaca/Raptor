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
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread -Wl,-R -Wl,/home/cellman123/Desktop/Raptor/Engine/Binaries")

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

include_directories (${RUNTIME_ROOT_DIR})
include_directories ("${SOURCE_ROOT_DIR}/External/Include")

# TODO: Remove this once build system is configured
include_directories ("${SOURCE_ROOT_DIR}/External")

link_directories ("${ENGINE_ROOT_DIR}/Binaries")

####################
# Shared Libraries #
####################

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

# glfw

find_library (GLFW3 glfw3 "${ENGINE_ROOT_DIR}/Binaries")

####################
# Static Libraries #
####################

# core

add_library (Core STATIC
	${RUNTIME_ROOT_DIR}/Core/Backend/Display.cpp
	${RUNTIME_ROOT_DIR}/Core/ECS/Component.cpp
)
target_include_directories (Core PRIVATE
	${RUNTIME_ROOT_DIR}/Core/
)

# graphics

add_library (Graphics STATIC
	${RUNTIME_ROOT_DIR}/Graphics/Model/Geometry.cpp
	${RUNTIME_ROOT_DIR}/Graphics/Renderer/Primitive.cpp
	${RUNTIME_ROOT_DIR}/Graphics/Utils/Shader.cpp
)
target_include_directories (Graphics PRIVATE
	${RUNTIME_ROOT_DIR}/Graphics/
)

# install

install (TARGETS Core Graphics DESTINATION ${ENGINE_ROOT_DIR}/Binaries)

#####################
# Create Executable #
#####################

add_executable (Raptor ${RUNTIME_ROOT_DIR}/main.cpp)
target_link_libraries (Raptor
	Core
	Graphics
	${OPENGL_gl_LIBRARY}
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
	${GLFW3}
	rt
	m
	dl
	Xrandr
	Xinerama
	Xxf86vm
	Xext
	Xcursor
	Xrender
	Xfixes
	X11
	pthread
	xcb
	Xau
	Xdmcp
)

install (TARGETS Raptor DESTINATION ${ENGINE_ROOT_DIR}/Binaries)
