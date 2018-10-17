# Graphics

add_library (Graphics SHARED)

target_sources (Graphics
PRIVATE
	./Private/DrawContext.cpp
)

target_include_directories (Graphics
PUBLIC
	./Graphics
PRIVATE
	./Private
)

target_compile_features (Graphics PUBLIC cxx_std_17)
set_target_properties (Graphics PROPERTIES CXX_EXTENSIONS OFF)

install (TARGETS Graphics DESTINATION ${ENGINE_PATH}/../Binaries/Debug)
