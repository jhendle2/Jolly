#pragma once

#include <string>
#include <vector>

typedef std::vector<std::string> Tokens;

std::string dropFileExtension(std::string filename);

bool hasQuotes(std::string s);
std::string stripQuotes(std::string s);

Tokens shiftTokens(Tokens tokens, int shift);
std::string tokensToString(Tokens tokens);
std::string tokensToLine(Tokens tokens);
Tokens tokenizeLine(std::string line);
bool tokensIsList(Tokens tokens);
std::vector<Tokens> listToListOfTokens(Tokens tokens);