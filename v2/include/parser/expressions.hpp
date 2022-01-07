#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <string>

#include "variable.hpp"
#include "object_table.hpp"
#include "function.hpp"

bool isOperator(std::string op);
bool isDelimiter(char c);

Variable evaluateExpression(Scope* scope, std::vector<std::string> tokens);