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

namespace oddf::simulator::common::backend {

class SimulatorBlockOutput;
class SimulatorBlockBase;

class SimulatorBlockInput {

private:

	friend SimulatorBlockOutput;

	SimulatorBlockBase const &m_owningBlock;
	SimulatorBlockOutput *m_driver;
	size_t m_index;

public:

	SimulatorBlockInput(SimulatorBlockBase const &owningBlock, size_t index);
	SimulatorBlockInput(SimulatorBlockInput const &) = delete;
	SimulatorBlockInput(SimulatorBlockInput &&);

	SimulatorBlockBase const &GetOwningBlock() const;
	size_t GetIndex() const;

	bool IsConnected() const;
	SimulatorBlockOutput const &GetDriver() const;
	SimulatorBlockOutput &GetDriver();

	void ConnectTo(SimulatorBlockOutput &output);
	void Disconnect();
};

} // namespace oddf::simulator::common::backend
