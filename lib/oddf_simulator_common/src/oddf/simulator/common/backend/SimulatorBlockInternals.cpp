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

#include "SimulatorBlockInternals.h"

#include <oddf/Exception.h>

#include <iostream>

namespace oddf::simulator::common::backend {

SimulatorBlockBase::Internals::Internals(SimulatorBlockBase &owningBlock, design::blocks::backend::IDesignBlock const &designBlock) :
	m_component(nullptr),
	m_visiting(false),
	m_designBlockReference(&designBlock),
	m_inputs(),
	m_outputs()
{
	InitialiseInputsAndOutputs(
		owningBlock,
		designBlock.GetInputsList().GetSize(),
		designBlock.GetOutputsList().GetSize());
}

SimulatorBlockBase::Internals::Internals(SimulatorBlockBase &owningBlock, size_t numberOfInputs, size_t numberOfOutputs) :
	m_component(nullptr),
	m_visiting(false),
	m_designBlockReference(nullptr),
	m_inputs(),
	m_outputs()
{
	InitialiseInputsAndOutputs(owningBlock, numberOfInputs, numberOfOutputs);
}

void SimulatorBlockBase::Internals::InitialiseInputsAndOutputs(SimulatorBlockBase &owningBlock, size_t numberOfInputs, size_t numberOfOutputs)
{
	m_inputs.reserve(numberOfInputs);
	for (size_t i = 0; i < numberOfInputs; ++i)
		m_inputs.emplace_back(owningBlock, i);

	m_outputs.reserve(numberOfOutputs);
	for (size_t i = 0; i < numberOfOutputs; ++i)
		m_outputs.emplace_back(owningBlock, i);
}

void SimulatorBlockBase::Internals::MapConnections(ISimulatorBlockMapping const &blockMapping)
{
	if (!m_designBlockReference)
		throw oddf::Exception(oddf::ExceptionCode::IllegalMethodCall);

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

				auto &simDriver = simDrivingBlock->m_internals->m_outputs[driverIndex];
				simInput.ConnectTo(simDriver);
			}
			else {

				std::cout << "Block '" << m_designBlockReference->GetPath().ToString() << "': driving block '" << designDrivingBlock.GetPath().ToString() << "' not found\n";
			}
		}

		designInputEnumerator.MoveNext();
	}
}

} // namespace oddf::simulator::common::backend
