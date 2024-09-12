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

    Implements `SimulatorBaseClass`, which is the base class to all simulator
    blocks.

*/

#include <oddf/simulator/common/backend/SimulatorBlockBase.h>

#include "ISimulatorBlockMapping.h"

#include <oddf/Exception.h>

#include <iostream>

namespace oddf::simulator::common::backend {

void SimulatorBlockBase::InitialiseInputsAndOutputs(size_t numberOfInputs, size_t numberOfOutputs)
{
	m_inputs.reserve(numberOfInputs);
	for (size_t i = 0; i < numberOfInputs; ++i)
		m_inputs.emplace_back(*this, i);

	m_outputs.reserve(numberOfOutputs);
	for (size_t i = 0; i < numberOfOutputs; ++i)
		m_outputs.emplace_back(*this, i);
}

SimulatorBlockBase::SimulatorBlockBase(design::blocks::backend::IDesignBlock const &designBlock) :
	m_designBlockReference(&designBlock),
	m_inputs(),
	m_outputs()
{
	InitialiseInputsAndOutputs(
		designBlock.GetInputsList().GetSize(),
		designBlock.GetOutputsList().GetSize());
}

SimulatorBlockBase::SimulatorBlockBase(size_t numberOfInputs, size_t numberOfOutputs) :
	m_designBlockReference(nullptr),
	m_inputs(),
	m_outputs()
{
	InitialiseInputsAndOutputs(numberOfInputs, numberOfOutputs);
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

void SimulatorBlockBase::DisconnectAll()
{
	// Disconnect all inputs
	auto inputsEnumerator = GetInputsList().GetEnumerator();
	for (inputsEnumerator.Reset(); inputsEnumerator.MoveNext();) {

		auto &input = inputsEnumerator.GetCurrent();
		if (input.IsConnected())
			input.Disconnect();
	}

	// Disconnect all outputs
	auto outputsEnumerator = GetOutputsList().GetEnumerator();
	for (outputsEnumerator.Reset(); outputsEnumerator.MoveNext();) {

		auto &output = outputsEnumerator.GetCurrent();
		output.DisconnectAll();
	}
}

bool SimulatorBlockBase::HasConnections() const
{
	// Check if inputs are connected
	auto inputsEnumerator = GetInputsList().GetEnumerator();
	for (inputsEnumerator.Reset(); inputsEnumerator.MoveNext();)
		if (inputsEnumerator.GetCurrent().IsConnected())
			return true;

	// Disconnect all outputs
	auto outputsEnumerator = GetOutputsList().GetEnumerator();
	for (outputsEnumerator.Reset(); outputsEnumerator.MoveNext();)
		if (!outputsEnumerator.GetCurrent().GetTargetsCollection().IsEmpty())
			return true;

	return false;
}

void SimulatorBlockBase::MapConnections(ISimulatorBlockMapping const &blockMapping)
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
