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

#include <oddf/simulator/common/backend/SimulatorBlockBase.h>

#include "ISimulatorBlockMapping.h"

#include <cassert>
#include <iostream>

namespace oddf::simulator::common::backend {

SimulatorBlockBase::SimulatorBlockBase(design::blocks::backend::IDesignBlock const &designBlock) :
	m_designBlockReference(&designBlock),
	m_inputs(),
	m_outputs()
{
	auto numberOfInputs = designBlock.GetInputsList().GetSize();
	m_inputs.reserve(numberOfInputs);
	for (size_t i = 0; i < numberOfInputs; ++i)
		m_inputs.emplace_back(*this, i);

	auto numberOfOutputs = designBlock.GetOutputsList().GetSize();
	m_outputs.reserve(numberOfOutputs);
	for (size_t i = 0; i < numberOfOutputs; ++i)
		m_outputs.emplace_back(*this, i);
}

utility::ListView<SimulatorBlockInput const &> SimulatorBlockBase::GetInputsList() const
{
	return utility::MakeListView<SimulatorBlockInput const &>(m_inputs);
}

utility::ListView<SimulatorBlockInput &> SimulatorBlockBase::GetInputsList()
{
	return utility::MakeListView<SimulatorBlockInput &>(m_inputs);
}

utility::ListView<SimulatorBlockOutput const &> SimulatorBlockBase::GetOutputsList() const
{
	return utility::MakeListView<SimulatorBlockOutput const &>(m_outputs);
}

utility::ListView<SimulatorBlockOutput &> SimulatorBlockBase::GetOutputsList()
{
	return utility::MakeListView<SimulatorBlockOutput &>(m_outputs);
}

void SimulatorBlockBase::MapConnections(ISimulatorBlockMapping const &blockMapping)
{
	assert(m_designBlockReference);

	auto designInputEnumerator = m_designBlockReference->GetInputsList().GetEnumerator();
	designInputEnumerator.Reset();

	for (auto &simInput : m_inputs) {

		auto &designInput = designInputEnumerator.GetCurrent();

		if (designInput.IsConnected()) {

			auto &designDriver = designInput.GetDriver();
			auto &designDrivingBlock = designDriver.GetOwningBlock();
			auto driverIndex = designDriver.GetIndex();

			auto *simDrivingBlock = blockMapping.DesignBlockToSimulatorBlock(designDrivingBlock);
			if (simDrivingBlock) {

				auto &simDriver = simDrivingBlock->m_outputs[driverIndex];
				simInput.ConnectTo(simDriver);
			}
			else {

				std::cout << "Block '" << m_designBlockReference->GetPath().ToString() << "': driving block '" << designDrivingBlock.GetPath().ToString() << "' not found\n";
			}
		}

		designInputEnumerator.MoveNext();
	}
}

void SimulatorBlockBase::Elaborate(ISimulatorElaborationContext & /* context */)
{
	// Default implementation does nothing.
}

} // namespace oddf::simulator::common::backend
