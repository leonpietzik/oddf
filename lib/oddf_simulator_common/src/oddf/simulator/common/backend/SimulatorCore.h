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

#include "IBlockMapping.h"

#include <oddf/simulator/common/backend/ISimulatorBlockFactory.h>
#include <oddf/simulator/backend/ISimulatorAccess.h>

#include <oddf/design/IDesign.h>
#include <oddf/design/blocks/backend/DesignBlockClass.h>

#include <map>
#include <memory>
#include <vector>

namespace oddf::simulator::common::backend {

class SimulatorCore : public simulator::backend::ISimulatorAccess {

private:

	std::vector<std::unique_ptr<SimulatorBlockBase>> m_blocks;

	std::map<design::blocks::backend::DesignBlockClass, std::unique_ptr<ISimulatorBlockFactory>> m_simulatorBlockFactories;

	void RegisterDefaultBlockFactories();

	std::unique_ptr<IBlockMapping const> MapBlocks(design::IDesign const &design);
	void MapConnections(IBlockMapping const &blockMapping);

public:

	SimulatorCore();
	~SimulatorCore();

	bool RegisterSimulatorBlockFactory(design::blocks::backend::DesignBlockClass const &designBlockClass,
		std::unique_ptr<ISimulatorBlockFactory> &&simulatorBlockFactory);

	void TranslateDesign(design::IDesign const &design);

	//
	// simulator::backend::ISimulatorAccess members
	//

	virtual void EnsureValid() override;

	virtual void *GetSimulatorObjectInterface(ResourcePath const &path, Uid const &iid) override;
};

} // namespace oddf::simulator::common::backend
