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

#include "../SimulatorImpl.h"

namespace oddf::simulator::common::backend {

void SimulatorImpl::TranslateDesign(design::IDesign const &design)
{
	auto blockMapping = MapBlocks(design);
	MapConnections(*blockMapping);

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

} // namespace oddf::simulator::common::backend
