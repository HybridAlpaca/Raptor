#####################
# Core Build Script #
#####################

cmake_minimum_required (VERSION 3.5)

project (Raptor VERSION 1.0 LANGUAGES CXX)

#######################
# Options & Variables #
#######################

# configure compiler to use

set (CMAKE_CXX_COMPILER /usr/bin/g++-8)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -Wall -fno-exceptions")

# configure userul directory aliases

set (MODULE_PATH ${CMAKE_SOURCE_DIR}/..)
set (ENGINE_PATH ${CMAKE_SOURCE_DIR}/../..)
set (EXTERN_PATH ${CMAKE_SOURCE_DIR}/../Source/External)
set (SOURCE_PATH ${CMAKE_SOURCE_DIR}/../Source/Runtime)

#################
# External Libs #
#################

set (GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set (GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set (GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory (${EXTERN_PATH}/glfw ${EXTERN_PATH}/glfw/Temp EXCLUDE_FROM_ALL)

################
# Core Modules #
################

add_library (Kernel STATIC
	${SOURCE_PATH}/Kernel/Private/Kernel.cpp
)
target_include_directories (Kernel PUBLIC
	${SOURCE_PATH}/Kernel/Private
	${SOURCE_PATH}/Kernel/Public/Kernel
)

include_directories (${SOURCE_PATH}/Kernel/Public)

add_library (IO STATIC
	${SOURCE_PATH}/IO/Private/Window.cpp
)
target_include_directories (IO PUBLIC
	${SOURCE_PATH}/IO/Private
	${SOURCE_PATH}/IO/Public/IO
)

include_directories (${SOURCE_PATH}/IO/Public)

target_link_libraries (IO glfw)

####################
# Build Executable #
####################

add_executable (Raptor ${SOURCE_PATH}/Entry/Private/Main.cpp)

target_link_libraries (Raptor Kernel IO)

# Install to appropriate binaries directory

install (TARGETS Raptor DESTINATION ${ENGINE_PATH}/Binaries/Debug)
