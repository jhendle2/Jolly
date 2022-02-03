#pragma once

#include <string>

#include "variable_type.hpp"

namespace VarUtils{

    bool isDigit(const char& c);
    bool isNumber(const std::string& token);
    bool isDecimal(const std::string& token);
    bool isCharacter(const std::string& token);
    bool isString(const std::string& token);
    bool isType(const std::string& token);
    bool isBoolean(const std::string& token);

    char dropSingleQuotes(const std::string& token);
    std::string dropDoubleQuotes(const std::string& token);
    bool stringToBool(const std::string& token);
    VarType stringToVarType(const std::string& token);
};