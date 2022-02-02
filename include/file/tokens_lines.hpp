#pragma once

#include <string>
#include <vector>

typedef std::vector<std::string> Tokens;

typedef struct Line{

    int line_number;
    std::string line;

} Line;

bool validTokensLength(const Tokens& tokens);
std::string tokensToString(const Tokens& tokens);
std::string tokensToLine(const Tokens& tokens);

Tokens tokenizeLine(const std::string& line);
Tokens shiftTokens(const Tokens& tokens, const int& shift);