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

	do {

		auto context = ElaborationContext();

		while (current < m_blocks.size()) {

			assert(m_blocks[current]);

			context.m_currentBlockUniquePtr = &m_blocks[current];
			m_blocks[current]->Elaborate(context);

			if (m_blocks[current])
				++current;
			else {

				/*
				    The block has been removed by a call to `RemoveThisBlock()`.
				    Swap places with the last block of the list, pop the now
				    empty last block from the list, and continue elaboration
				    without incrementing `current`.
				*/

				std::swap(m_blocks[current], m_blocks.back());
				m_blocks.pop_back();
			}
		}

		// Append the newly created blocks at the end of the main list...
		m_blocks.reserve(m_blocks.size() + context.m_newBlocks.size());
		std::move(std::begin(context.m_newBlocks), std::end(context.m_newBlocks), std::back_inserter(m_blocks));

		// ... and continue elaboration with the newly appended blocks.

	} while (current < m_blocks.size());
}

} // namespace oddf::simulator::common::backend
