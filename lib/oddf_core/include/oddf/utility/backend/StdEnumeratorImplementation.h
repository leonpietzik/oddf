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

#include "AbstractEnumeratorImplementation.h"
#include "StdContainerElementTypeCast.h"

namespace oddf {
namespace utility {
namespace backend {

template<typename referenceT, typename iteratorT>
class StdEnumeratorImplementation : public AbstractEnumeratorImplementation<referenceT> {

private:

	iteratorT m_Begin, m_End, m_Current;
	bool m_BeforeBegin;

public:

	StdEnumeratorImplementation(iteratorT begin, iteratorT end) :
		m_Begin(begin), m_End(end), m_Current(end), m_BeforeBegin(false)
	{
	}

	StdEnumeratorImplementation(StdEnumeratorImplementation<referenceT, iteratorT> const &other) :
		m_Begin(other.m_Begin), m_End(other.m_End), m_Current(other.m_Current), m_BeforeBegin(other.m_BeforeBegin)
	{
	}

	virtual std::unique_ptr<AbstractEnumeratorImplementation<referenceT>> Clone() const
	{
		return std::make_unique<StdEnumeratorImplementation<referenceT, iteratorT>>(*this);
	}

	virtual referenceT GetCurrent() const override
	{
		return StdContainerElementTypeCast<referenceT>(*m_Current);
	}

	virtual bool MoveNext() override
	{
		if (m_Current == m_End)
			return false;

		if (m_BeforeBegin)
			m_BeforeBegin = false;
		else
			++m_Current;

		return m_Current != m_End;
	}

	virtual void Reset() override
	{
		m_BeforeBegin = true;
		m_Current = m_Begin;
	}
};

} // namespace backend
} // namespace utility
} // namespace oddf
