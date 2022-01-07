#pragma once

#include <string>
#include <unordered_map>

enum ReservedKeyword{
    RESERVED_FUNCTION,
    RESERVED_END,
};

bool isReservedKeyword(std::string word);
enum ReservedKeyword getReservedKeyword(std::string word);