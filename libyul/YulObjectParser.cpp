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

#include <libyul/Exceptions.h>

#include <libsolidity/inlineasm/AsmParser.h>

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
			object->code = parseBlock();
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

shared_ptr<YulObject> YulObjectParser::parseObject(YulObject* _containingObject)
{
	RecursionGuard guard(*this);

	if (currentToken() != Token::Identifier || currentLiteral() != "object")
		fatalParserError("Expected keyword \"object\".");
	advance();

	shared_ptr<YulObject> ret = make_shared<YulObject>();
	ret->name = parseUniqueName(_containingObject);

	expectToken(Token::LBrace);

	ret->code = parseCode();

	while (currentToken() != Token::RBrace)
	{
		if (currentToken() == Token::Identifier && currentLiteral() == "object")
			parseObject(ret.get());
		else if (currentToken() == Token::Identifier && currentLiteral() == "data")
			parseData(*ret);
		else
			fatalParserError("Expected keyword \"data\" or \"object\" or \"}\".");
	}
	if (_containingObject)
		_containingObject->subObjects[ret->name] = ret;

	expectToken(Token::RBrace);

	return ret;
}

shared_ptr<Block> YulObjectParser::parseCode()
{
	if (currentToken() != Token::Identifier || currentLiteral() != "code")
		fatalParserError("Expected keyword \"code\".");
	advance();

	return parseBlock();
}

shared_ptr<Block> YulObjectParser::parseBlock()
{
	solidity::assembly::Parser parser(m_errorReporter, m_flavour);
	shared_ptr<Block> block = parser.parse(m_scanner, true);
	yulAssert(block || m_errorReporter.hasErrors(), "Invalid block but no error!");
	return block;
}

void YulObjectParser::parseData(YulObject& _containingObject)
{
	solAssert(
		currentToken() == Token::Identifier && currentLiteral() == "data",
		"parseData called on wrong input."
	);
	advance();

	YulString name = parseUniqueName(&_containingObject);

	expectToken(Token::StringLiteral, false);
	_containingObject.subObjects[name] = asBytes(currentLiteral());
	advance();
}

YulString YulObjectParser::parseUniqueName(YulObject const* _containingObject)
{
	expectToken(Token::StringLiteral, false);
	YulString name{currentLiteral()};
	if (name.empty())
		parserError("Object name cannot be empty.");
	else if (_containingObject && _containingObject->name == name)
		parserError("Object name cannot be the same as the name of the containing object.");
	else if (_containingObject && _containingObject->subObjects.count(name))
		parserError("Object name \"" + name.str() + "\" already exists inside the containing object.");
	advance();
	return name;
}
