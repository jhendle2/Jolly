#include "parser_keywords.hpp"

std::unordered_map<std::string, enum ReservedKeyword> ParserReservedWords = {
    {"function", RESERVED_FUNCTION},
    {"end", RESERVED_END},
    {"if", RESERVED_IF},
    {"else", RESERVED_ELSE},
    {"elsif", RESERVED_ELSIF},
};

bool isReservedKeyword(std::string word){
    return (ParserReservedWords.count(word) > 0);
}

enum ReservedKeyword getReservedKeyword(std::string word){
    return ParserReservedWords[word];
}