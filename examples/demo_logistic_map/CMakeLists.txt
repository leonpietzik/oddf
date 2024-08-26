add_executable(demo_logistic_map
	main.cpp
)

target_link_libraries(demo_logistic_map PRIVATE oddf)
target_link_libraries(demo_logistic_map PRIVATE verilog)
