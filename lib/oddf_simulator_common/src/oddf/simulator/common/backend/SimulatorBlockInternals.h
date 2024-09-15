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

    <no description>

*/

#pragma once

#include <oddf/simulator/common/backend/SimulatorBlockBase.h>

#include "ISimulatorBlockMapping.h"

#include <vector>

namespace oddf::simulator::common::backend {

class SimulatorBlockBase::Internals {

public:

	// Pointer to the original design block, if the constructor accepting a design block reference was used. `nullptr` otherwise.
	design::blocks::backend::IDesignBlock const *const m_designBlockReference;

	// Vector of block inputs. Initialised by `InitialiseInputsAndOutputs()`. Reallocations must not occur afterwards.
	std::vector<SimulatorBlockInput> m_inputs;

	// Vector of block outputs. Initialised by `InitialiseInputsAndOutputs()`. Reallocations must not occur afterwards.
	std::vector<SimulatorBlockOutput> m_outputs;

	Internals(SimulatorBlockBase &owningBlock, design::blocks::backend::IDesignBlock const &designBlock);
	Internals(SimulatorBlockBase &owningBlock, size_t numberOfInputs, size_t numberOfOutputs);

	// Initialises members `m_inputs` and `m_outputs`.
	void InitialiseInputsAndOutputs(SimulatorBlockBase &owningBlock, size_t numberOfInputs, size_t numberOfOutputs);

	// Will map the connections to other blocks if the block was created from a design block.
	void MapConnections(ISimulatorBlockMapping const &blockMapping);
};

} // namespace oddf::simulator::common::backend
