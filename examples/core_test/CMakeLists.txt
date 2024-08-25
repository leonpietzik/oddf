add_executable(core_test
	main.cpp
	testing/Uid.cpp
	testing/utility/CollectionView.cpp
	testing/utility/ListView.cpp
	testing/design/blocks/backend/DesignBlockClass.cpp
	testing/simulator/ISimulator.cpp
)

target_link_libraries(core_test PRIVATE oddf_core)
