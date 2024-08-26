add_library(oddf_simulator_common
	src/simulator/common/Simulator.cpp
	src/simulator/common/backend/blocks/DelaySimulatorBlock.cpp
	src/simulator/common/backend/SimulatorCore/EnsureValid.cpp
	src/simulator/common/backend/SimulatorCore/GetSimulatorObjectInterface.cpp
	src/simulator/common/backend/SimulatorCore/MapBlocks.cpp
	src/simulator/common/backend/SimulatorCore/MapConnections.cpp
	src/simulator/common/backend/SimulatorCore/RegisterDefaultBlockFactories.cpp
	src/simulator/common/backend/SimulatorCore/RegisterSimulatorBlockFactory.cpp
	src/simulator/common/backend/SimulatorCore/TranslateDesign.cpp
	src/simulator/common/backend/SimulatorBlockBase.cpp
	src/simulator/common/backend/SimulatorBlockInput.cpp
	src/simulator/common/backend/SimulatorBlockOutput.cpp
	src/simulator/common/backend/SimulatorCore.cpp
)

target_include_directories(oddf_simulator_common PUBLIC include)

target_compile_features(oddf_simulator_common PUBLIC cxx_std_17)

target_link_libraries(oddf_simulator_common PUBLIC oddf_core)
