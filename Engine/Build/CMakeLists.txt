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

set (CMAKE_CXX_COMPILER /usr/bin/g++)
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")

set (RAPTOR_ROOT_DIR ${CMAKE_SOURCE_DIR}/../../)
set (ENGINE_ROOT_DIR ${CMAKE_SOURCE_DIR}/../)
set (SOURCE_ROOT_DIR ${ENGINE_ROOT_DIR}/Source/)
set (RUNTIME_ROOT_DIR ${SOURCE_ROOT_DIR}/Runtime/)

###
# set include and linking directories
###

include_directories (${RUNTIME_ROOT_DIR})
include_directories (${SOURCE_ROOT_DIR}/External)

###
# load shared libraries
###

add_library (GLFW SHARED IMPORTED)
set_target_properties (GLFW PROPERTIES IMPORTED_LOCATION ${ENGINE_ROOT_DIR}/Binaries/Libraries/Shared/libglfw.so.3.2)

add_library (Glad SHARED
	${SOURCE_ROOT_DIR}/External/glad/glad.c
)
set_target_properties(Glad PROPERTIES LINKER_LANGUAGE CXX)

install (TARGETS Glad DESTINATION ${ENGINE_ROOT_DIR}/Binaries/Libraries/Shared)

###
# load static libraries
###

add_library (Core STATIC
	${RUNTIME_ROOT_DIR}/Core/Async/ThreadPool.cpp
	${RUNTIME_ROOT_DIR}/Core/Math/Vector.cpp
)
target_include_directories (
	Core PRIVATE ${RUNTIME_ROOT_DIR}/Core/
)

install (TARGETS Core DESTINATION ${ENGINE_ROOT_DIR}/Binaries/Libraries/Static)

###
# build the final executable
###

add_executable (Raptor ${RUNTIME_ROOT_DIR}/main.cpp)
target_link_libraries (Raptor Core GLFW)

install (TARGETS Raptor DESTINATION ${ENGINE_ROOT_DIR}/Binaries)