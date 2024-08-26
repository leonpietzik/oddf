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

#include <oddf/design/blocks/backend/DesignBlockClass.h>

#include "../../../Expect.h"

#include <set>
#include <unordered_set>
#include <type_traits>

namespace oddf::testing::design::blocks::backend {

void Test_DesignBlockClass()
{
	using oddf::design::blocks::backend::DesignBlockClass;

	static_assert(std::is_copy_constructible_v<DesignBlockClass>);
	static_assert(std::is_copy_assignable_v<DesignBlockClass>);

	DesignBlockClass blockClass("TestClass");

	// Must have a method ToString() that returns a string representation of the class
	Expect(blockClass.ToString() == "TestClass");

	// Class DesignBlockClass must be usable in ordered and unordered containers.
	std::set<DesignBlockClass> set;
	std::unordered_set<DesignBlockClass> unordered_set;

	set.emplace("Class1");
	set.emplace(blockClass);

	unordered_set.emplace("Class1");
	unordered_set.emplace(blockClass);
}

} // namespace oddf::testing::design::blocks::backend
