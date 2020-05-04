# Kernel

add_library (Kernel STATIC)

target_sources (Kernel
PRIVATE
	./Private/ThreadPool.cpp
	./Private/POSIX/SharedLib.cpp
)

target_include_directories (Kernel
PUBLIC
	./Kernel
PRIVATE
	./Private
)

if (PLATFORM_LINUX OR PLATFORM_APPLE)
	target_link_libraries (Kernel PRIVATE pthread dl)
elseif (PLATFORM_WIN32)
	message (FATAL_ERROR "[Kernel] (win32) :: Target platform not supported")
endif ()

target_compile_features (Kernel PUBLIC cxx_std_17)
set_target_properties (Kernel PROPERTIES CXX_EXTENSIONS OFF)
