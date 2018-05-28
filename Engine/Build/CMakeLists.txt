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

set (CMAKE_CXX_COMPILER /usr/bin/g++)
set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")

set (RAPTOR_ROOT_DIR ${CMAKE_SOURCE_DIR}/../..)
set (ENGINE_ROOT_DIR ${CMAKE_SOURCE_DIR}/..)
set (SOURCE_ROOT_DIR ${ENGINE_ROOT_DIR}/Source)
set (RUNTIME_ROOT_DIR ${SOURCE_ROOT_DIR}/Runtime)

set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,${ENGINE_ROOT_DIR}/Binaries")

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

# glfw

add_library (glfw SHARED IMPORTED)
set_target_properties (glfw PROPERTIES IMPORTED_LOCATION ${ENGINE_ROOT_DIR}/Binaries/libglfw.so.3)

###
# load static libraries
###

# core

add_library (Core STATIC
	${RUNTIME_ROOT_DIR}/Core/Async/Scheduler.cpp
	${RUNTIME_ROOT_DIR}/Core/Async/Thread.cpp
	${RUNTIME_ROOT_DIR}/Core/Memory/BlobLoader.cpp
	${RUNTIME_ROOT_DIR}/Core/Memory/GlobalStore.cpp
	${RUNTIME_ROOT_DIR}/Core/Containers/SLinkedList.cpp
)
target_include_directories (Core PRIVATE
	${RUNTIME_ROOT_DIR}/Core/
)

# renderer

add_library (Renderer STATIC
	${RUNTIME_ROOT_DIR}/Renderer/Pipeline/Primitive.cpp
	${RUNTIME_ROOT_DIR}/Renderer/Utils/Window.cpp
	${RUNTIME_ROOT_DIR}/Renderer/Utils/Shader.cpp
)
target_include_directories (Renderer PRIVATE
	${RUNTIME_ROOT_DIR}/Renderer/
)
target_link_libraries (Renderer
	glfw
)

# install

install (TARGETS Core Renderer DESTINATION ${ENGINE_ROOT_DIR}/Binaries)

###
# build the final executable
###

add_executable (Raptor ${RUNTIME_ROOT_DIR}/main.cpp)
target_link_libraries (Raptor Core Renderer)

install (TARGETS Raptor DESTINATION ${ENGINE_ROOT_DIR}/Binaries)