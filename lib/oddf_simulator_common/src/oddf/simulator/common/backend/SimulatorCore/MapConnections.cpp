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

#include "../SimulatorBlockInternals.h"

#include <cassert>
#include <iostream>

namespace oddf::simulator::common::backend {

void SimulatorCore::MapConnections(ISimulatorBlockMapping const &blockMapping)
{
	std::cout << "\n";
	std::cout << "-- Mapping connections --\n";
	std::cout << "\n";

	for (auto &pBlock : m_blocks) {

		assert(pBlock);
		pBlock->m_internals->MapConnections(blockMapping);
	}
}

} // namespace oddf::simulator::common::backend
