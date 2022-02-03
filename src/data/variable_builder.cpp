#include <iostream>

#include "variable_builder.hpp"

Variable buildVariableFromTokens(const Tokens& tokens){
    if(tokens.size() < 2){
        std::cout << "!! Error: Not enough tokens to build a variable!\n";
        return Variable();
    }

    if(isVarType(tokens[0])){
        return Variable(tokens[1], tokens[0]);
    }

    return Variable();
}