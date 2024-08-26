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

#include "ISimulatorAccess.h"

#include <oddf/simulator/backend/ISimulatorAccess.h>

#include "../../Expect.h"

#include <memory>

namespace oddf::testing::simulator::backend {

class ITestObjectInterface {

public:

	static constexpr Uid IID = { 0x5ece6339, 0x1045, 0x46ec, 0x8f, 0x68, 0x94, 0x2f, 0xe6, 0x55, 0xaf, 0x56 };

	virtual int ReturnsEleven() const = 0;

	virtual ~ITestObjectInterface() { }
};

class IWrongInterface {

public:

	static constexpr Uid IID = { 0xabd6f4a2, 0xa611, 0x4f8f, 0xb6, 0xb8, 0xae, 0x2b, 0x5d, 0x8b, 0x84, 0x51 };

	virtual ~IWrongInterface() { }
};

class TestSimulatorObject : public ITestObjectInterface {

public:

	virtual int ReturnsEleven() const override
	{
		return 11;
	}
};

class TestSimulatorAccess : public oddf::simulator::backend::ISimulatorAccess {

private:

	TestSimulatorObject m_simulatorObject;

public:

	TestSimulatorAccess() = default;

	virtual void EnsureValid() override
	{
	}

	virtual void *GetSimulatorObjectInterface(ResourcePath const &path, Uid const &iid) override
	{
		if (path == "ExistingObject") {

			if (iid == ITestObjectInterface::IID)
				return static_cast<void *>(&m_simulatorObject);
			else
				throw Exception(ExceptionCode::InterfaceNotFound);
		}
		else
			throw Exception(ExceptionCode::ResourceNotFound);
	}

	using oddf::simulator::backend::ISimulatorAccess::GetSimulatorObjectInterface;
};

void Test_ISimulatorAccess()
{
	TestSimulatorAccess simulatorAccess;

	ITestObjectInterface &interface = simulatorAccess.GetSimulatorObjectInterface<ITestObjectInterface>("ExistingObject");

	Expect(interface.ReturnsEleven() == 11);

	ExpectThrows(ExceptionCode::ResourceNotFound, [&]() {
		simulatorAccess.GetSimulatorObjectInterface<ITestObjectInterface>("NonExistingObject");
	});

	ExpectThrows(ExceptionCode::InterfaceNotFound, [&]() {
		simulatorAccess.GetSimulatorObjectInterface<IWrongInterface>("ExistingObject");
	});
}

} // namespace oddf::testing::simulator::backend
