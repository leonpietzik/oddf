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

#include "../SimulatorCore.h"

#include <oddf/Exception.h>

#include <vector>
#include <memory>
#include <cassert>
#include <iostream>

namespace oddf::simulator::common::backend {

namespace {

class ElaborationContext : public ISimulatorElaborationContext {

public:

	std::unique_ptr<SimulatorBlockBase> *m_currentBlockUniquePtr;
	size_t m_currentBlockIndex;

	std::vector<std::unique_ptr<SimulatorBlockBase>> m_newBlocks;

	void AddSimulatorBlock(std::unique_ptr<SimulatorBlockBase> &&block) override
	{
		assert(block);
		m_newBlocks.push_back(std::move(block));
	}

	void RemoveThisBlock() override
	{
		if ((*m_currentBlockUniquePtr)->HasConnections())
			throw oddf::Exception(oddf::ExceptionCode::IllegalMethodCall, "ISimulatorElaborationContext::RemoveThisBlock(): block cannot be removed if it has connections to other blocks.");

		m_currentBlockUniquePtr->reset();
	}
};

} // namespace

void SimulatorCore::ElaborateBlocks()
{
	std::cout << "\n";
	std::cout << "-- Elaborating blocks --\n";
	std::cout << "\n";

	size_t current = 0;
	size_t size = m_blocks.size();

	do {

		auto context = ElaborationContext();

		for (; current < size; ++current) {

			assert(m_blocks[current]);

			context.m_currentBlockUniquePtr = &m_blocks[current];
			m_blocks[current]->Elaborate(context);
		}

		m_blocks.reserve(size + context.m_newBlocks.size());
		std::move(std::begin(context.m_newBlocks), std::end(context.m_newBlocks), std::back_inserter(m_blocks));

		size = m_blocks.size();

	} while (current < size);
}

} // namespace oddf::simulator::common::backend
