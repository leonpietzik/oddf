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

    Defines and implements the `DesignBlockClass` class, which identifies the
    class of a design block and is used by the ODDF system to distinguish
    programmatically the various kinds of blocks that make up a design.

*/

#pragma once

#include <string>

namespace oddf::design::blocks::backend {

/*
    Identifies the class of a design block and is used by the ODDF system to
    distinguish programmatically the various kinds of blocks that make up a
    design.
*/
class DesignBlockClass {

private:

	/*
	    TODO: the current implementation uses `std::string` to support the
	    migration from the old ('dfx') design implementation to a modern and,
	    hopefully, better implementation.

	    Using `std::string` for the purpose of distinguishing design blocks is slow
	    and memory intensive. A new implementation should be based on pointers to
	    plain old strings instead.
	*/

	std::string m_className;

	friend struct std::hash<DesignBlockClass>;

public:

	DesignBlockClass(std::string const &className) :
		m_className(className) { }

	// Provided to support the use of `DesignBlockClass` in ordered sets and maps.
	friend bool operator<(DesignBlockClass const &lhs, DesignBlockClass const &rhs)
	{
		return lhs.m_className < rhs.m_className;
	}

	// Tests for equality.
	friend bool operator==(DesignBlockClass const &lhs, DesignBlockClass const &rhs)
	{
		return lhs.m_className == rhs.m_className;
	}

	// Tests for inequality.
	friend bool operator!=(DesignBlockClass const &lhs, DesignBlockClass const &rhs)
	{
		return lhs.m_className != rhs.m_className;
	}

	// Returns a human-readable string representation of the design block class.
	std::string ToString() const { return m_className; };
};

} // namespace oddf::design::blocks::backend

/*
    Specialises std::hash to support the use of `DesignBlockClass` in hashed
    sets and maps.
*/
template<>
struct std::hash<oddf::design::blocks::backend::DesignBlockClass> {

	std::size_t operator()(const oddf::design::blocks::backend::DesignBlockClass &c) const noexcept
	{
		return std::hash<std::string>()(c.m_className);
	}
};
