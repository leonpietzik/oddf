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

#include <oddf/Exception.h>

namespace oddf::simulator::common::backend {

SimulatorBlockOutput::SimulatorBlockOutput(SimulatorBlockBase const &owningBlock, size_t index) :
	m_owningBlock(owningBlock),
	m_targets(),
	m_index(index)
{
}

SimulatorBlockOutput::SimulatorBlockOutput(SimulatorBlockOutput &&other) :
	m_owningBlock(other.m_owningBlock),
	m_targets(),
	m_index(0)
{
	// Since the address of an output object must never change, it must not be moved.
	throw oddf::Exception(oddf::ExceptionCode::Unexpected);
}

SimulatorBlockBase const &SimulatorBlockOutput::GetOwningBlock() const
{
	return m_owningBlock;
}

size_t SimulatorBlockOutput::GetIndex() const
{
	return m_index;
}

utility::CollectionView<SimulatorBlockInput const &> SimulatorBlockOutput::GetTargetsCollection() const
{
	return utility::MakeCollectionView<SimulatorBlockInput const &>(m_targets);
}

utility::CollectionView<SimulatorBlockInput &> SimulatorBlockOutput::GetTargetsCollection()
{
	return utility::MakeCollectionView<SimulatorBlockInput &>(m_targets);
}

void SimulatorBlockOutput::DisconnectAll()
{
	auto targets = GetTargetsCollection();

	while (!targets.IsEmpty())
		targets.GetFirst().Disconnect();
}

} // namespace oddf::simulator::common::backend
