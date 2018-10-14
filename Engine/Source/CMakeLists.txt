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

################
# Core Modules #
################

include_directories (Common)

add_subdirectory (Kernel)
add_subdirectory (Entry)
