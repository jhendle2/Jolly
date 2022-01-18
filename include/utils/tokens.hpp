#pragma once

#include <string>
#include <vector>

typedef std::vector<std::string> Tokens;

Tokens tokenizeLine(std::string line);
std::string tokensToString(Tokens tokens);