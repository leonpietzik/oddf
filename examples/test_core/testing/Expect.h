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

#include <oddf/Exception.h>

#include <iostream>
#include <stdexcept>
#include <functional>

namespace oddf::testing {

inline void Expect(bool condition)
{
	if (!condition)
		throw std::runtime_error("Expect(): 'condition' was false.");
}

inline void ExpectThrows(ExceptionCode exceptionCode, std::function<void()> test)
{
	try {

		test();
		throw std::runtime_error("ExpectThrows(): 'testFunction' was expected to throw an 'oddf::Exception', but it did not.");
	}
	catch (oddf::Exception &e) {

		if (e.GetCode() != exceptionCode)
			throw std::runtime_error("ExpectThrows(): 'testFunction' threw an 'oddf::Exception', as expected, but the exception code does not match the expectation.");
	}
	catch (...) {

		throw std::runtime_error("ExpectThrows(): 'testFunction' threw an unexpected exception, which was not of type 'oddf::Exception'.");
	}
}

} // namespace oddf::testing
