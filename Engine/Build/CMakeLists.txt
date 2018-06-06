###
#
# CMake AutoBuild v.3.5
#
# (c) 2018 HybridAlpaca
#
# See README for build instructions
#
###

cmake_minimum_required (VERSION 3.5)

project (RaptorEngine LANGUAGES CXX)

###
# include external cmake files
###

include (GNUInstallDirs)

###
# set parameters and options
###

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set (CMAKE_CXX_COMPILER /usr/bin/g++-8)
set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")

set (RAPTOR_ROOT_DIR ${CMAKE_SOURCE_DIR}/../..)
set (ENGINE_ROOT_DIR ${CMAKE_SOURCE_DIR}/..)
set (SOURCE_ROOT_DIR ${ENGINE_ROOT_DIR}/Source)
set (RUNTIME_ROOT_DIR ${SOURCE_ROOT_DIR}/Runtime)

if (NOT CMAKE_BUILD_TYPE) 
    set (CMAKE_BUILD_TYPE Release)
endif (NOT CMAKE_BUILD_TYPE)

###
# set include and linking directories
###

include_directories (${RUNTIME_ROOT_DIR})
include_directories (${SOURCE_ROOT_DIR}/External)

###
# load shared libraries
###

# opengl  

find_package (OpenGL REQUIRED)
if (OPENGL_FOUND)
	include_directories (${OPENGL_INCLUDE_DIRS})
	link_libraries (${OPENGL_gl_LIBRARY} ${OPENGL_LIBRARIES})
endif ()

# glew

find_package (GLEW REQUIRED)
if (GLEW_FOUND)
	include_directories (${GLEW_INCLUDE_DIRS})
	link_libraries (${GLEW_LIBRARIES})
endif()

# SDL2

find_package (SDL2 REQUIRED)
if (SDL2_FOUND)
	string (STRIP ${SDL2_INCLUDE_DIRS} SDL2_INCLUDE_DIRS)
	string (STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
	include_directories (${SDL2_INCLUDE_DIRS})
	link_libraries (${SDL2_LIBRARIES})
endif()

###
# load static libraries
###

# core

add_library (Core STATIC
	${RUNTIME_ROOT_DIR}/Core/ECS/Component.cpp
)
target_include_directories (Core PRIVATE
	${RUNTIME_ROOT_DIR}/Core/
)

# graphics

add_library (Graphics STATIC
	${RUNTIME_ROOT_DIR}/Graphics/Renderer/Primitive.cpp
	${RUNTIME_ROOT_DIR}/Graphics/Device/Display.cpp
	${RUNTIME_ROOT_DIR}/Graphics/Utils/Shader.cpp
)
target_include_directories (Graphics PRIVATE
	${RUNTIME_ROOT_DIR}/Graphics/
)
target_link_libraries (Graphics
	SDL2
)

# install

install (TARGETS Core Graphics DESTINATION ${ENGINE_ROOT_DIR}/Binaries)

###
# build the final executable
###

add_executable (Raptor ${RUNTIME_ROOT_DIR}/main.cpp)
target_link_libraries (Raptor Core Graphics)

install (TARGETS Raptor DESTINATION ${ENGINE_ROOT_DIR}/Binaries)
