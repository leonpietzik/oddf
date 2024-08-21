add_library(oddf_core INTERFACE
	)

target_include_directories(oddf_core INTERFACE include)

target_compile_features(oddf_core INTERFACE cxx_std_17)

# target_precompile_headers(oddf_core PRIVATE src/global.h)
