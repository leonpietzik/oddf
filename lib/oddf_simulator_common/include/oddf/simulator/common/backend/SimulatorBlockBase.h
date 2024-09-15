/*

    ODDF - Open Digital Design Framework
    Copyright Advantest Corporation

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

/*

    Defines `SimulatorBaseClass`, which is the base class to all simulator
    blocks.

*/

#pragma once

#include <oddf/design/blocks/backend/IDesignBlock.h>

#include <oddf/simulator/common/backend/ISimulatorElaborationContext.h>

#include "SimulatorBlockInput.h"
#include "SimulatorBlockOutput.h"

#include <oddf/utility/ListView.h>

#include <vector>
#include <string>

namespace oddf::simulator::common::backend {

class SimulatorCore;

/*
    Base class to all simulator blocks.
*/
class SimulatorBlockBase {

private:

	friend SimulatorCore;

	// Pointer to the original design block, if the constructor accepting a design block reference was used. `nullptr` otherwise.
	design::blocks::backend::IDesignBlock const *const m_designBlockReference;

	// Vector of block inputs. Initialised by `InitialiseInputsAndOutputs()`. Reallocations must not occur afterwards.
	std::vector<SimulatorBlockInput> m_inputs;

	// Vector of block outputs. Initialised by `InitialiseInputsAndOutputs()`. Reallocations must not occur afterwards.
	std::vector<SimulatorBlockOutput> m_outputs;

	// Initialises members `m_inputs` and `m_outputs`.
	void InitialiseInputsAndOutputs(size_t numberOfInputs, size_t numberOfOutputs);

public:

	// Constructs the simulator block based on the given design block.
	SimulatorBlockBase(design::blocks::backend::IDesignBlock const &designBlock);

	// Constructs the simulator block with given numbers of inputs and outputs.
	SimulatorBlockBase(size_t numberOfInputs, size_t numberOfOutputs);

	// Returns a ListView into the list of inputs of this block.
	utility::ListView<SimulatorBlockInput const &> GetInputsList() const;

	// Returns a ListView into the list of inputs of this block.
	utility::ListView<SimulatorBlockInput &> GetInputsList();

	// Returns a ListView into the list of outputs of this block.
	utility::ListView<SimulatorBlockOutput const &> GetOutputsList() const;

	// Returns a ListView into the list of outputs of this block.
	utility::ListView<SimulatorBlockOutput &> GetOutputsList();

	// Returns whether the block has connections to other block.
	bool HasConnections() const;

	// Disconnects all inputs and outputs from all other blocks.
	void DisconnectAll();

	// Will map the connections to other blocks if the block was created from a design block.
	void MapConnections(class ISimulatorBlockMapping const &blockMapping);

	// Elaborates the block. Default implementation does nothing.
	virtual void Elaborate(ISimulatorElaborationContext &context);

	// Returns a short, descriptive string. Used during debugging print outs.
	virtual std::string DebugString() const = 0;

	virtual ~SimulatorBlockBase() { }
};

} // namespace oddf::simulator::common::backend
