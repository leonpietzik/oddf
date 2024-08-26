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

#include "testing/RunTest.h"

#include "testing/Uid.h"

#include "testing/utility/CollectionView.h"
#include "testing/utility/ListView.h"

#include "testing/design/blocks/backend/DesignBlockClass.h"

#include "testing/simulator/backend/ISimulatorAccess.h"

int main()
{
	using namespace oddf::testing;

	RunTest("Uid", Test_Uid);

	RunTest("utility::ListView", utility::Test_ListView);
	RunTest("utility::CollectionView", utility::Test_CollectionView);

	RunTest("design::blocks::backend::DesignBlockClass", design::blocks::backend::Test_DesignBlockClass);

	RunTest("simulator::backend::ISimulatorAccess", simulator::backend::Test_ISimulatorAccess);

	return 0;
}
