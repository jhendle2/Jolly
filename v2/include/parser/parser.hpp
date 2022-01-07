#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "variable.hpp"
#include "object_table.hpp"
#include "function.hpp"

std::vector<std::string> tokenizeLine(std::string line);

// void buildVariableAndEvaluateExpressions(ObjectTable<Variable>& vt, std::vector<std::string> tokens);
Function* buildVariableAndEvaluateExpressions(Function* scope, std::vector<std::string> tokens);