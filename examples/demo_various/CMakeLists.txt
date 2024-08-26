add_executable(demo_various
	main.cpp
)

target_link_libraries(demo_various PRIVATE oddf)
target_link_libraries(demo_various PRIVATE verilog)
