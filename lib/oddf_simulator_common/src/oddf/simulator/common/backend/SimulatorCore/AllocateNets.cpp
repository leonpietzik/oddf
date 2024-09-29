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

void SimulatorCore::AllocateNets()
{
/*
	AllocateNets
	------------

	Dies geschieht automatisch, die Blöcke selbst werden nicht involviert.

	Zunächst werden keine Adressen vergeben, da nicht bekannt ist, wie viele
	man braucht. Das läuft erst über Indizes, diese beschreiben einen
	Byte-Offset ab dem Beginn des Speicherblockes, der dann am Schluss
	reserviert wird. Abschließend werden alle Blöcke nochmals durchgegangen
	und die Indizes durch Addressen ersetzt.

	Addressen müssen aligned sein. Wenn Adressen übersprungen werden müssen,
	so werden diese als freie Adressen in anderen Listen vermerkt.

	Zum Beispiel: Es wurde ein Byte reserviert und dann ein Double. Die sieben
	freien Plätze werden vermerkt als
	    1 Byte mit Alignment 1, 1 Wort mit Alignnent 2 und 1 Dopplewort mit
	    Alignment 4

	Referenzzählung implementieren --> Addressen wiederverwenden.


	SimulatorOutput::DeclareExclusiveAccess() --> Es wird eine exklusive
	Addresse für den Output reserviert, sodass auch außerhalb des normelen
	Execution-Flows Werte dort abgefragt bzw. gesetzt werden können.
	 - Auch für Konstanten verwendbar?

*/
	std::cout << "\n";
	std::cout << "--- Allocating nets ---\n";
	std::cout << "\n";

}

} // namespace oddf::simulator::common::backend
