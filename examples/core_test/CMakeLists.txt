add_executable(core_test
	main.cpp
	testing/utility/CollectionView.cpp
	testing/utility/ListView.cpp
)

target_link_libraries(core_test PRIVATE oddf_core)
