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

#include <oddf/utility/ListView.h>
#include <oddf/utility/ResourcePath.h>

#include "DesignBlockClass.h"
#include "IBlockInput.h"
#include "IBlockOutput.h"

#include <string>

namespace oddf {
namespace design {
namespace blocks {
namespace backend {

class IDesignBlock {

public:

	virtual ~IDesignBlock() { }

	virtual utility::ResourcePath GetPath() const = 0;
	virtual DesignBlockClass GetClass() const = 0;

	virtual utility::ListView<IBlockInput const &> GetInputsList() const = 0;
	virtual utility::ListView<IBlockOutput const &> GetOutputsList() const = 0;
};

} // namespace backend
} // namespace blocks
} // namespace design
} // namespace oddf
