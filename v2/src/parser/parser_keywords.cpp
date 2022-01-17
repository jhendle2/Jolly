#include "parser_keywords.hpp"

std::unordered_map<std::string, enum ReservedKeyword> ParserReservedWords = {
    {"function", RESERVED_FUNCTION},
    {"end", RESERVED_END},
    {"if", RESERVED_IF},
    {"else", RESERVED_ELSE},
    {"elsif", RESERVED_ELSIF},
    {"yield", RESERVED_YIELD},
    {"return", RESERVED_YIELD}, // Here Michael! Now return works also. Stinky boy!
    {"takes", RESERVED_TAKES},
    {"entrypoint", RESERVED_ENTRYPOINT},
    {"include", RESERVED_INCLUDE},
    // !!REMEMBER!! to update the Parser_Keyword.hpp enum ReservedKeyword list!
};

bool isReservedKeyword(std::string word){
    return (ParserReservedWords.count(word) > 0);
}

enum ReservedKeyword getReservedKeyword(std::string word){
    return ParserReservedWords[word];
}