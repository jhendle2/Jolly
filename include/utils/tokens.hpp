#pragma once

#include <string>
#include <vector>

typedef std::vector<std::string> Tokens;

bool validTokensLength(Tokens tokens);

Tokens tokenizeLine(std::string line);
std::string tokensToString(Tokens tokens);
Tokens shiftTokens(Tokens tokens, int shift);