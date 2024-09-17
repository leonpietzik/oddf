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

#include <list>

namespace oddf::simulator::common::backend {

class SimulatorComponent {

public:

	std::list<SimulatorBlockBase *> m_blocks;

	SimulatorComponent();
	SimulatorComponent(SimulatorComponent const &) = default;
	SimulatorComponent(SimulatorComponent &&) = default;

	void AddBlock(SimulatorBlockBase &block);
	void MoveAppendFromOther(SimulatorComponent &other);
	void MovePrependFromOther(SimulatorComponent &other);

	bool IsEmpty() const;
	size_t GetSize() const;
};

} // namespace oddf::simulator::common::backend
