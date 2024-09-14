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

#include <iostream>

namespace oddf::simulator::common::backend {

void SimulatorCore::TranslateDesign(design::IDesign const &design)
{
	std::cout << "\n";
	std::cout << "--- Translating design ---\n";
	std::cout << "\n";

	{
		auto blockMapping = MapBlocks(design);

		MapConnections(*blockMapping);
	}

	ElaborateBlocks();

	BuildComponents();

	for (auto const &block : m_blocks) {

		if (!block) {

			std::cout << "[block was removed]\n\n";
			continue;
		}

		std::cout << "<" << block.get() << ">: " << block->DebugString() << "\n";

		auto inputsList = block->GetInputsList();

		for (size_t i = 0; i < inputsList.GetSize(); ++i) {

			auto const &input = inputsList[i];

			std::cout << "  input[" << i << "]: ";

			if (input.IsConnected()) {

				auto *drivingBlock = &input.GetDriver().GetOwningBlock();
				std::cout << "driven by <" << drivingBlock << ">: " << drivingBlock->DebugString();
			}
			else {

				std::cout << "unconnected";
			}

			std::cout << "\n";
		}

		auto outputsList = block->GetOutputsList();

		for (size_t i = 0; i < outputsList.GetSize(); ++i) {

			auto const &output = outputsList[i];

			std::cout << "  output[" << i << "]: ";

			auto targetsCollection = output.GetTargetsCollection();

			if (targetsCollection.GetSize() > 0) {

				std::cout << "driving inputs of";
				auto targetsEnumerator = targetsCollection.GetEnumerator();
				targetsEnumerator.Reset();
				while (targetsEnumerator.MoveNext())
					std::cout << " <" << &targetsEnumerator.GetCurrent().GetOwningBlock() << ">";
			}
			else {

				std::cout << "unconnected";
			}

			std::cout << "\n";
		}

		std::cout << "\n";
	}

	/*

	BuildComponents
	AllocateNets
	    - Speicher für outputs von Blöcken
	    - Speicher für interne knoten wiederverwenden können?
	    - Was ist mit Speicher für delay, memory --> landet in ComponentObjects
	GenerateCode

	*/
}

} // namespace oddf::simulator::common::backend
