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

#include "CollectionView.h"

namespace oddf::utility {

template<typename referenceT>
class ListView : public CollectionView<referenceT> {

public:

	ListView(std::unique_ptr<backend::AbstractContainerViewImplementation<referenceT>> &&implementation) :
		CollectionView<referenceT>(std::move(implementation))
	{
	}

	ListView(ListView<referenceT> const &other) :
		CollectionView<referenceT>(other.m_implementation->Clone())
	{
	}

	referenceT operator[](size_t index) const
	{
		return this->m_implementation->operator[](index);
	}
};

template<
	typename referenceTypeSpec = void,
	typename containerT>
auto MakeListView(containerT &container)
{
	using referenceT = std::conditional_t<
		std::is_same_v<referenceTypeSpec, void>,
		decltype(*std::begin(std::declval<containerT &>())),
		referenceTypeSpec>;

	return ListView<referenceT>(std::make_unique<backend::StdContainerViewImplementation<referenceT, containerT>>(container));
}

} // namespace oddf::utility
