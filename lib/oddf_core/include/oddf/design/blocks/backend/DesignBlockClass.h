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

#include <string>

namespace oddf::design::blocks::backend {

class DesignBlockClass {

private:

	std::string m_className;

	friend struct std::hash<DesignBlockClass>;

public:

	DesignBlockClass(std::string const &className) :
		m_className(className) { }

	friend bool operator<(DesignBlockClass const &lhs, DesignBlockClass const &rhs)
	{
		return lhs.m_className < rhs.m_className;
	}

	friend bool operator==(DesignBlockClass const &lhs, DesignBlockClass const &rhs)
	{
		return lhs.m_className == rhs.m_className;
	}

	friend bool operator!=(DesignBlockClass const &lhs, DesignBlockClass const &rhs)
	{
		return lhs.m_className != rhs.m_className;
	}

	std::string ToString() const { return m_className; };
};

} // namespace oddf::design::blocks::backend

template<>
struct std::hash<oddf::design::blocks::backend::DesignBlockClass> {

	std::size_t operator()(const oddf::design::blocks::backend::DesignBlockClass &c) const noexcept
	{
		return std::hash<std::string>()(c.m_className);
	}
};
