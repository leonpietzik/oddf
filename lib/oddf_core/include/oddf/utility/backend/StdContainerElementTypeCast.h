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

namespace oddf {
namespace utility {
namespace backend {

template<typename toT, typename fromT, typename = void>
struct StdContainerElementTypeCastHelper { };

template<typename toT, typename fromT>
struct StdContainerElementTypeCastHelper<toT, fromT, std::enable_if_t<std::is_convertible_v<fromT, toT>>> {

	static toT Cast(fromT from)
	{
		return static_cast<toT>(from);
	}
};

template<typename toT, typename fromT>
struct StdContainerElementTypeCastHelper<toT, fromT, std::enable_if_t<std::is_convertible_v<decltype(*std::declval<fromT>()), toT>>> {

	static toT Cast(fromT from)
	{
		return static_cast<toT>(*from);
	}
};

template<typename toT, typename fromT>
struct StdContainerElementTypeCastHelper<toT, fromT, std::enable_if_t<std::is_convertible_v<decltype(std::declval<fromT>().get()), toT>>> {

	static toT Cast(fromT from)
	{
		return static_cast<toT>(from.get());
	}
};

template<typename toT, typename fromT>
toT StdContainerElementTypeCast(fromT &from)
{
	return StdContainerElementTypeCastHelper<toT, fromT &>::Cast(from);
}

} // namespace backend
} // namespace utility
} // namespace oddf
