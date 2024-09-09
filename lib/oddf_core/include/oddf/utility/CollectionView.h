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

#include "backend/StdContainerViewImplementation.h"

#include <utility>

namespace oddf::utility {

template<typename referenceT>
class CollectionView {

protected:

	std::unique_ptr<backend::AbstractContainerViewImplementation<referenceT>> m_implementation;

public:

	CollectionView(std::unique_ptr<backend::AbstractContainerViewImplementation<referenceT>> &&implementation) :
		m_implementation(std::move(implementation))
	{
	}

	CollectionView(CollectionView<referenceT> const &other) :
		m_implementation(other.m_implementation->Clone())
	{
	}

	Enumerator<referenceT> GetEnumerator() const
	{
		return m_implementation->GetEnumerator();
	}

	size_t GetSize() const
	{
		return m_implementation->GetSize();
	}

	bool IsEmpty() const
	{
		return m_implementation->GetSize() == 0;
	}

	referenceT GetFirst() const
	{
		return this->m_implementation->GetFirst();
	}
};

template<
	typename referenceTypeSpec = void,
	typename containerT>
auto MakeCollectionView(containerT &container)
{
	using referenceT = std::conditional_t<
		std::is_same_v<referenceTypeSpec, void>,
		decltype(*std::begin(std::declval<containerT &>())),
		referenceTypeSpec>;

	return CollectionView<referenceT>(std::make_unique<backend::StdContainerViewImplementation<referenceT, containerT>>(container));
}

} // namespace oddf::utility
