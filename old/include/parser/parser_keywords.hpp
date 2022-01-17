#pragma once

#include <string>
#include <unordered_map>

enum ReservedKeyword{
    RESERVED_FUNCTION,
    RESERVED_END,

    RESERVED_IF,
    RESERVED_ELSE,
    RESERVED_ELSIF,

    RESERVED_YIELD,
    // !!REMEMBER!! to update the Parser_Keyword.cpp unordered map!
};

bool isReservedKeyword(std::string word);
enum ReservedKeyword getReservedKeyword(std::string word);