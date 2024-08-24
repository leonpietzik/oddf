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

#include "SimulatorImpl.h"
#include <oddf/simulation/backend/IBlockMapping.h>

#include <cassert>

namespace oddf {
namespace simulation {
namespace internal {

SimulatorImpl::SimulatorImpl()
{
	RegisterDefaultBlockFactories();
}

SimulatorImpl::~SimulatorImpl()
{
}

bool SimulatorImpl::RegisterSimulatorBlockFactory(design::blocks::backend::DesignBlockClass const &designBlockClass,
	std::unique_ptr<backend::SimulatorBlockFactoryBase> &&simulatorBlockFactory)
{
	m_simulatorBlockFactories[designBlockClass] = std::move(simulatorBlockFactory);
	return true;
}

void SimulatorImpl::TranslateDesign(design::backend::IDesign const &design)
{
	class BlockMapping : public backend::IBlockMapping {

		std::unordered_map<design::blocks::backend::IDesignBlock const *, backend::SimulatorBlockBase *> m_blockMapping;

	public:

		void AddBlockMapping(design::blocks::backend::IDesignBlock const &fromDesignBlock, backend::SimulatorBlockBase &toSimulatorBlock)
		{
			assert(m_blockMapping.find(&fromDesignBlock) == m_blockMapping.end());
			m_blockMapping[&fromDesignBlock] = &toSimulatorBlock;
		}

		virtual backend::SimulatorBlockBase *DesignBlockToSimulatorBlock(design::blocks::backend::IDesignBlock const &designBlock) const override
		{
			auto designBlockIt = m_blockMapping.find(&designBlock);

			if (designBlockIt != m_blockMapping.end())
				return designBlockIt->second;
			else
				return nullptr;
		}
	};

	BlockMapping blockMapping;

	auto designBlocks = design.GetBlockCollection();

	//
	// Map blocks
	//

	m_blocks.reserve(designBlocks.GetSize());
	auto designBlocksEnumerator = designBlocks.GetEnumerator();

	for (designBlocksEnumerator.Reset(); designBlocksEnumerator.MoveNext();) {

		auto const &designBlock = designBlocksEnumerator.GetCurrent();

		auto blockClass = designBlock.GetClass();

		auto blockFactory = m_simulatorBlockFactories.find(blockClass);
		if (blockFactory != m_simulatorBlockFactories.end()) {

			m_blocks.push_back(blockFactory->second->CreateFromDesignBlock(designBlock));
			blockMapping.AddBlockMapping(designBlock, *m_blocks.back());
		}
		else {

			std::cout << "WARNING: do not know how to handle design block '"
					  << designBlock.GetPath().ToString()
					  << "' of class '" << blockClass.ToString() << "'.\n";
		}
	}

	//
	// Map connections
	//

	for (auto &pBlock : m_blocks) {

		assert(pBlock);
		auto &block = *pBlock;

		block.MapConnections(blockMapping);
	}

	//
	// Refine blocks / ElaborateBlocks -- for all blocks that implement the IElaborate interface (which is passed an IElaborationContext)
	//

	/*
	     Blocks created in a previous step may be converted to new blocks, that better support certain combinations of
	     input and output types. For example, a sum taking an integer and a double as inputs may be converted to a
	     block that sums doubles preceded by a type-conversion block for the integer input. Another example is where
	     operations on busses are individualised.
	*/

	/*

	BuildComponents
	AllocateNets
	    - Speicher für outputs von Blöcken
	    - Speicher für interne knoten wiederverwenden können?
	    - Was ist mit Speicher für delay, memory
	GenerateCode

	*/
}

} // namespace internal
} // namespace simulation
} // namespace oddf
