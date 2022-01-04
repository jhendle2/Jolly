#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <string>

#include "variable.hpp"

Variable evaluateExpression(std::vector<std::string> tokens);

bool isOperator(std::string op);
bool isDelimiter(char c);