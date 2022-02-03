#include <iostream>

#include "scope_builder.hpp"
#include "tokens_lines.hpp"
#include "keywords.hpp"

bool isOpenScope(const std::string& keyword){
    return (
        keyword == KW_CLASS ||
        keyword == KW_FUNCTION ||
        keyword == KW_WHILE ||
        keyword == KW_DOWHILE ||
        keyword == KW_FOR ||
        keyword == KW_FOREACH ||
        keyword == KW_COUNT ||
        keyword == KW_IF ||
        keyword == KW_ELSIF ||
        keyword == KW_ELSE
    );
}

bool isCloseScope(const std::string& keyword){
    return (
        keyword == KW_END ||
        keyword == KW_ELSIF ||
        keyword == KW_ELSE
    );
}

/***************************************/

ScopePtr buildScopeFromTokens(const Tokens& tokens){
    static int id = 0;
    if(tokens.size() == 0) return nullptr;

    if(isOpenScope(tokens[0])){
        // std::string scope_name = tokensToLine(tokens);
        std::string scope_name = "";
        if(tokens.size() > 1 && (tokens[0] == KW_FUNCTION || tokens[0] == KW_CLASS)){
            scope_name = tokens[1];
        }
        else{
            scope_name = tokens[0] + "_" + std::to_string(id++);
        }

        enum ScopeType scope_type = stringToScopeType(tokens[0]);
        ScopePtr scope = Scope::create(scope_name, scope_type);
        return scope;
    }

    ScopePtr scope = Scope::create("constant", ScopeConstant);
    return scope;
}