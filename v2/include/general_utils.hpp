#pragma once

#include <string>
#include <vector>

bool hasQuotes(std::string s);
std::string stripQuotes(std::string s);

std::vector<std::string> shiftTokens(std::vector<std::string> tokens, int shift);
std::string tokensToString(std::vector<std::string> tokens);
std::vector<std::string> tokenizeLine(std::string line);