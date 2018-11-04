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
 * Parser for Yul code and data object container.
 */

#include <libyul/YulObjectParser.h>

#include <liblangutil/Token.h>

using namespace dev;
using namespace dev::yul;
using namespace langutil;
using namespace std;


shared_ptr<YulObject> YulObjectParser::parse(shared_ptr<Scanner> const& _scanner, bool _reuseScanner)
{
	m_recursionDepth = 0;
	try
	{
		shared_ptr<YulObject> object;
		m_scanner = _scanner;
		if (currentToken() == Token::LBrace)
		{
			object = make_shared<YulObject>();
			object->code = parseCode();
		}
		else
			object = parseObject();
		if (!_reuseScanner)
			expectToken(Token::EOS);
		return object;
	}
	catch (FatalError const&)
	{
		if (m_errorReporter.errors().empty())
			throw; // Something is weird here, rather throw again.
	}
	return nullptr;
}

shared_ptr<Block> YulObjectParser::parseCode()
{

}

void YulObjectParser::parseData(YulObject& _currentObject)
{

}

shared_ptr<YulObject> YulObjectParser::parseObject()
{

}
