project (RaptorEntry)

add_executable (Raptor Main.cpp)

target_link_libraries (Raptor
PRIVATE
	Kernel
)

target_include_directories (Raptor
PRIVATE
	../Kernel
)

target_compile_features (Raptor PUBLIC cxx_std_17)
set_target_properties (Raptor PROPERTIES CXX_EXTENSIONS OFF)

install (TARGETS Raptor DESTINATION ${ENGINE_PATH}/Binaries/Debug)
