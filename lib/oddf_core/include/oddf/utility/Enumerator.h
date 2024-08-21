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

#include "backend/AbstractEnumeratorImplementation.h"

namespace oddf {
namespace utility {

template<typename referenceT>
class Enumerator {

	std::unique_ptr<backend::AbstractEnumeratorImplementation<referenceT>> m_Implementation;

public:

	Enumerator(std::unique_ptr<backend::AbstractEnumeratorImplementation<referenceT>> &&implementation) :
		m_Implementation(std::move(implementation))
	{
	}

	Enumerator(Enumerator<referenceT> const &other) :
		m_Implementation(other.m_Implementation->Clone())
	{
	}

	referenceT GetCurrent() const
	{
		return m_Implementation->GetCurrent();
	}

	bool MoveNext()
	{
		return m_Implementation->MoveNext();
	}

	void Reset()
	{
		m_Implementation->Reset();
	}
};

} // namespace utility
} // namespace oddf
