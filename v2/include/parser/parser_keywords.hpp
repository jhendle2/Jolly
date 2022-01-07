#pragma once

#include <string>
#include <unordered_map>

enum ReservedKeyword{
    RESERVED_FUNCTION,
    RESERVED_END,
    RESERVED_IF,
    RESERVED_ELSE,
    RESERVED_ELSIF,
};

bool isReservedKeyword(std::string word);
enum ReservedKeyword getReservedKeyword(std::string word);