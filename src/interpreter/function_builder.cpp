#include "function_builder.hpp"
#include "errors.hpp"
#include "keywords.hpp"

bool tokensIsFunctionHeader(Tokens tokens, std::string& function_name){
    if(tokens.size() < 1){
        return false;
    }
    
    if(tokens[0] == KW_FUNCTION){
        if(tokens.size() < 2){
            ERROR(SyntaxErrorIncompleteStatement);
        }
        function_name = tokens[1];
        return true;
    }
    return false;
}
bool tokensIsFunctionCloser(Tokens tokens, std::string function_name){
    if(tokens.size() < 1){
        return false;
    }
    
    if(tokens[0] == KW_END){
        if(tokens.size() < 2){
            ERROR(SyntaxErrorIncompleteStatement);
        }
        if(tokens[1] == function_name){
            return true;
        }
    }
    return false;
}