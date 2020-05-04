#####################
# Core Build Script #
#####################

cmake_minimum_required (VERSION 3.8)

project (RaptorCore VERSION 0.0.1 LANGUAGES CXX)

#######################
# Options & Variables #
#######################

set (ENGINE_PATH ${CMAKE_CURRENT_LIST_DIR}/..)
set (EXTERN_PATH ${CMAKE_CURRENT_LIST_DIR}/External)
set (SOURCE_PATH ${CMAKE_CURRENT_LIST_DIR})

if (WIN32)
	set (PLATFORM_WIN32 TRUE)
	message ("[General] (win32) :: Found target platform")
endif (WIN32)

if (APPLE)
	set (PLATFORM_APPLE TRUE)
	message ("[General] (apple) :: Found target platform")
endif (APPLE)

if (UNIX AND NOT APPLE)
	set (PLATFORM_LINUX TRUE)
	message ("[General] (linux) :: Found target platform")
endif (UNIX AND NOT APPLE)

################
# Core Modules #
################

include_directories (Common)

add_subdirectory (Kernel)
add_subdirectory (Graphics)
add_subdirectory (Entry)
