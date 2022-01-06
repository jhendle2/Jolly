#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <string>

#include "variable.hpp"
#include "object_table.hpp"

bool isOperator(std::string op);
bool isDelimiter(char c);

Variable evaluateExpression(ObjectTable<Variable>& vt, std::vector<std::string> tokens);