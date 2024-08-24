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

#include <oddf/utility/Uid.h>

#include <iostream>
#include <cassert>

namespace oddf::testing::utility {

void Test_Uid()
{
	constexpr auto uid1 = oddf::utility::Uid(0x5ece6339, 0x1045, 0x46ec, 0x8f, 0x68, 0x94, 0x2f, 0xe6, 0x55, 0xaf, 0x56);

	constexpr auto uid2 = uid1;
	constexpr auto uid3 = oddf::utility::Uid(0x231f9c8e, 0x760f, 0x4caf, 0x8a, 0x1e, 0x77, 0xf2, 0x7c, 0x66, 0x86, 0x0f);

	static_assert(uid1 == uid2);
	static_assert(uid1 != uid3);

	assert(uid2.ToString() == "{5ece6339-1045-46ec-8f68-942fe655af56}");
	assert(uid3.ToString() == "{231f9c8e-760f-4caf-8a1e-77f27c66860f}");
}

} // namespace oddf::testing::utility
