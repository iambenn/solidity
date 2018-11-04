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

#pragma once

#include <libyul/ASTDataForward.h>
#include <libyul/YulString.h>

#include <libdevcore/CommonData.h>

#include <memory>

namespace dev
{
namespace solidity
{
namespace assembly
{
class AsmAnalysisInfo;
}
}
namespace yul
{

/**
 * Yul code and data object container.
 */
class YulObject
{
public:
	std::string toString();

	std::string name;
	std::shared_ptr<Block> code;
	std::map<YulString, bytes> data;
	std::map<YulString, YulObject> subObjects;
	std::shared_ptr<solidity::assembly::AsmAnalysisInfo> analysisInfo;
};

}
}
