add_library(oddf_simulator_common
	src/simulator/common/Simulator.cpp
	src/simulator/common/backend/blocks/DelaySimulatorBlock.cpp
	src/simulator/common/backend/SimulatorImpl/EnsureValid.cpp
	src/simulator/common/backend/SimulatorImpl/GetSimulatorObjectInterface.cpp
	src/simulator/common/backend/SimulatorImpl/MapBlocks.cpp
	src/simulator/common/backend/SimulatorImpl/MapConnections.cpp
	src/simulator/common/backend/SimulatorImpl/RegisterDefaultBlockFactories.cpp
	src/simulator/common/backend/SimulatorImpl/RegisterSimulatorBlockFactory.cpp
	src/simulator/common/backend/SimulatorImpl/TranslateDesign.cpp
	src/simulator/common/backend/SimulatorBlockBase.cpp
	src/simulator/common/backend/SimulatorBlockInput.cpp
	src/simulator/common/backend/SimulatorBlockOutput.cpp
	src/simulator/common/backend/SimulatorImpl.cpp
)

target_include_directories(oddf_simulator_common PUBLIC include)

target_compile_features(oddf_simulator_common PUBLIC cxx_std_17)

target_link_libraries(oddf_simulator_common PUBLIC oddf_core)
