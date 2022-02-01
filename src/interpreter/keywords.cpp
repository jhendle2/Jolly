#include "keywords.hpp"

bool isKeyword(std::string str){
    return (
        str==KW_FUNCTION ||
        str==KW_END ||
        str==KW_IF ||
        str==KW_ELSIF ||
        str==KW_ELSE ||
        str==KW_YIELD ||
        str==KW_YIELD_ALT ||
        str==KW_TAKES ||
        str==KW_TAKES_ALT ||
        str==KW_YIELDS ||
        str==KW_YIELDS_ALT ||
        str==KW_WHILE
    );
}