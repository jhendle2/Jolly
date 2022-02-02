#pragma once

#include <string>
#include <memory>

#include "tokens_lines.hpp"
#include "scope.hpp"

bool isOpenScope(const std::string& keyword);
bool isCloseScope(const std::string& keyword);

/***************************************/

std::shared_ptr<Scope> buildScopeFromTokens(const Tokens& tokens);

/***************************************/


/***************************************/