# Kernel

add_library (Kernel
STATIC
	./Private/ThreadPool.cpp
)

target_include_directories (Kernel
PUBLIC
	./Kernel
PRIVATE
	./Private
)

target_link_libraries (Kernel pthread)

target_compile_features (Kernel PUBLIC cxx_std_17)
set_target_properties (Kernel PROPERTIES CXX_EXTENSIONS OFF)
