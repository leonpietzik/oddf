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

#include <oddf/design/blocks/backend/IDesignBlock.h>

#include <oddf/simulator/common/backend/ISimulatorElaborationContext.h>

#include "SimulatorBlockInput.h"
#include "SimulatorBlockOutput.h"

#include <oddf/utility/ListView.h>

#include <vector>
#include <string>

namespace oddf::simulator::common::backend {

class SimulatorBlockBase {

private:

	design::blocks::backend::IDesignBlock const *m_designBlockReference;

	std::vector<SimulatorBlockInput> m_inputs;
	std::vector<SimulatorBlockOutput> m_outputs;

	void PrepareConnections(size_t numberOfInputs, size_t numberOfOutputs);

public:

	SimulatorBlockBase(design::blocks::backend::IDesignBlock const &designBlock);
	SimulatorBlockBase(size_t numberOfInputs, size_t numberOfOutputs);

	utility::ListView<SimulatorBlockInput const &> GetInputsList() const;
	utility::ListView<SimulatorBlockInput &> GetInputsList();

	utility::ListView<SimulatorBlockOutput const &> GetOutputsList() const;
	utility::ListView<SimulatorBlockOutput &> GetOutputsList();

	void MapConnections(class ISimulatorBlockMapping const &blockMapping);

	virtual void Elaborate(ISimulatorElaborationContext &context);

	virtual std::string DebugString() const = 0;

	virtual ~SimulatorBlockBase() { }
};

} // namespace oddf::simulator::common::backend
