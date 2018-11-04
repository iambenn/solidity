/*
	This file is part of solidity.

	solidity is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	solidity is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with solidity.  If not, see <http://www.gnu.org/licenses/>.
*/
/**
 * Yul code and data object container.
 */

#include <libyul/YulObject.h>

#include <libyul/Exceptions.h>

#include <libsolidity/inlineasm/AsmPrinter.h>

#include <boost/algorithm/string/replace.hpp>

using namespace dev;
using namespace dev::yul;
using namespace std;

namespace
{

string const& indent(std::string& _input)
{
	boost::replace_all("\n", "\n    ", _input);
	return _input;
}

}

string YulObject::toString()
{
	yulAssert(m_code, "No code");
	string inner = "code {\n" + indent(solidity::assembly::AsmPrinter{}(*m_code)) + "}\n";

	inner += "\n";
	for (auto const& data: m_data)
		inner += "data \"" + data.name + "\" hex\"" + toHex(data.second) + "\"\n";


	return "object {\n" + indent(inner) + "}\n";
}
