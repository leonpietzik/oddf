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

#include <exception>
#include <string>
#include <cstdint>

namespace oddf {

enum class ExceptionCode : std::uint32_t {

	Generic = 0x00000001,

	ResourceNotFound = 0x00000002,
	InterfaceNotFound = 0x00000003
};

class Exception : public std::exception {

private:

	ExceptionCode m_code;
	std::string m_message;

public:

	Exception(std::string const &message) :
		m_code(ExceptionCode::Generic),
		m_message(message)
	{
	}

	Exception(ExceptionCode code) :
		m_code(code),
		m_message("<no message>")
	{
	}

	virtual char const *what() const noexcept override
	{
		return m_message.c_str();
	}

	char const *GetMessage() const noexcept
	{
		return m_message.c_str();
	}

	ExceptionCode GetCode() const noexcept
	{
		return m_code;
	}
};

} // namespace oddf
