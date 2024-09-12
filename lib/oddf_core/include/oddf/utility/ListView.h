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

    Provides template class `ListView`, a random-access view into a collection
    of elements, where the type of the underlying container has been erased.
    Elements are accessed through the type specified by a template parameter.
    The container itself cannot be modified (i.e., elements cannot be added or
    deleted); but the elements can if `referenceT` specifies a non-const
    reference or pointer. Derives from class `CollectionView`.

*/

#pragma once

#include "CollectionView.h"

namespace oddf::utility {

/*
    A random-access view into a collection of elements, where the type of the
    underlying container has been erased. Elements are accessed through the
    type specified by template parameter `referenceT`. The container itself
    cannot be modified (i.e., elements cannot be added or deleted); but the
    elements can if `referenceT` specifies a non-const reference or pointer.
    Derives from class `CollectionView`.
*/
template<typename referenceT>
class ListView : public CollectionView<referenceT> {

public:

	// Constructs a `ListView` based on the provided implementation of `AbstractContainerViewImplementation`.
	ListView(std::unique_ptr<backend::AbstractContainerViewImplementation<referenceT>> &&implementation) :
		CollectionView<referenceT>(std::move(implementation))
	{
	}

	// Constructs a copy of the given `ListView`.
	ListView(ListView<referenceT> const &other) :
		CollectionView<referenceT>(other.m_implementation->Clone())
	{
	}

	// Accesses element at the given index.
	referenceT operator[](size_t index) const
	{
		return this->m_implementation->operator[](index);
	}
};

/*
    Returns a `ListView` for the given standard library container. The type
    for element access can be overridden using the first template parameter
    `referenceTypeSpec`. All standard type conversions based on `static_cast`
    are permitted. Additionally, elements that are stored as pointers or
    `unique_ptr` in the original collection can be viewed as normal pointers or
    references.
*/
template<
	typename referenceTypeSpec = void,
	typename containerT>
inline auto MakeListView(containerT &container)
{
	using referenceT = std::conditional_t<
		std::is_same_v<referenceTypeSpec, void>,
		decltype(*std::begin(std::declval<containerT &>())),
		referenceTypeSpec>;

	return ListView<referenceT>(std::make_unique<backend::StdContainerViewImplementation<referenceT, containerT>>(container));
}

} // namespace oddf::utility
