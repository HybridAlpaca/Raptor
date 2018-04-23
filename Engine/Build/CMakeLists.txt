cmake_minimum_required (VERSION 3.5)

project (RaptorEngine LANGUAGES CXX)

include (GNUInstallDirs)

set (CMAKE_CXX_COMPILER /usr/bin/g++)
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")

set (RAPTOR_ROOT_DIR ${CMAKE_SOURCE_DIR}/../../)
set (ENGINE_ROOT_DIR ${CMAKE_SOURCE_DIR}/../)
set (SOURCE_ROOT_DIR ${ENGINE_ROOT_DIR}/Source/)
set (RUNTIME_ROOT_DIR ${SOURCE_ROOT_DIR}/Runtime/)

include_directories (${RUNTIME_ROOT_DIR})

add_library (Core STATIC
	${RUNTIME_ROOT_DIR}/Core/Async/Thread.cpp
	${RUNTIME_ROOT_DIR}/Core/Async/ThreadPool.cpp
	${RUNTIME_ROOT_DIR}/Core/Math/Vector.cpp
)
target_include_directories (
	Core PRIVATE ${RUNTIME_ROOT_DIR}/Core/
)

install(TARGETS Core DESTINATION ${ENGINE_ROOT_DIR}/Binaries/Libraries/Static)

add_executable (Raptor ${RUNTIME_ROOT_DIR}/main.cpp)
target_link_libraries (Raptor Core)

install(TARGETS Raptor DESTINATION ${ENGINE_ROOT_DIR}/Binaries)