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

    Provides template class `CollectionView`, which is a view into a collection
    of elements, where the type of the underlying container has been erased.
    Elements are accessed through the type specified by a template parameter.
    The container itself cannot be modified (i.e., elements cannot be added or
    deleted); but the elements can if `referenceT` specifies a non-const
    reference or pointer.

*/

#pragma once

#include "backend/StdContainerViewImplementation.h"

#include <utility>

namespace oddf::utility {

/*
    A view into a collection of elements, where the type of the
    underlying container has been erased. Elements are accessed through the
    type specified by template parameter `referenceT`. The container itself
    cannot be modified (i.e., elements cannot be added or deleted); but the
    elements can if `referenceT` specifies a non-const reference or pointer.
*/
template<typename referenceT>
class CollectionView {

protected:

	std::unique_ptr<backend::AbstractContainerViewImplementation<referenceT>> m_implementation;

public:

	// Constructs a `CollectionView` based on the provided implementation of `AbstractContainerViewImplementation`.
	CollectionView(std::unique_ptr<backend::AbstractContainerViewImplementation<referenceT>> &&implementation) :
		m_implementation(std::move(implementation))
	{
	}

	// Constructs a copy of the given `CollectionView`.
	CollectionView(CollectionView<referenceT> const &other) :
		m_implementation(other.m_implementation->Clone())
	{
	}

	// Returns an enumerator for the elements in the collection.
	Enumerator<referenceT> GetEnumerator() const
	{
		return m_implementation->GetEnumerator();
	}

	// Returns the number of elements in the collection.
	size_t GetSize() const
	{
		return m_implementation->GetSize();
	}

	// Returns whether the collection is empty.
	bool IsEmpty() const
	{
		return m_implementation->GetSize() == 0;
	}

	// Returns the first element of the collection.
	referenceT GetFirst() const
	{
		return this->m_implementation->GetFirst();
	}
};

/*
    Returns a `CollectionView` for the given standard library container. The
    type for element access can be overridden using the first template parameter
    `referenceTypeSpec`. All standard type conversions based on `static_cast`
    are permitted. Additionally, elements that are stored as pointers or
    `unique_ptr` in the original collection can be viewed as normal pointers or
    references.
*/
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
