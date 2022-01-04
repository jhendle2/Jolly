#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "variable.hpp"

void setVariable(std::string name, Variable var);
Variable getVariable(std::string name);
void dumpVariables();

std::vector<std::string> tokenizeLine(std::string line);

Variable buildVariableFromTokens(std::vector<std::string> tokens);
void buildVariableFromTokensAndAdd(std::vector<std::string> tokens);
void buildVariableAndEvaluateExpressions(std::vector<std::string> tokens);