#include <iostream>

#include "function.hpp"
#include "keywords.hpp"
#include "expressions.hpp"
#include "interpreter.hpp"
#include "logging.hpp"

Function::Function(std::string name) : Scope(name){
    setScopeType(SCOPE_FUNCTION);
    // addVariable(Variable("return", Prim_Nothing));
}

Function::~Function(){

}

void Function::setLines(struct FunctionBlock lines){
    this->lines = lines;
}
struct FunctionBlock Function::getLines(){
    return lines;
}

std::vector<std::string> Function::getParamsOrder(){
    return params_order;
}

void Function::addParam(Variable param_variable){
    std::string local_name = name + "." + param_variable.getName();
    this->params_order.push_back(local_name);
    addVariable(param_variable);
}

void Function::setReturnVariable(Variable return_variable){
    // return_variable.setName("return");
    updateVariable("return", return_variable);
}

void Function::dump(){
    std::cout<<"-----FUNCTION ("<<name<<")-----\n";
    std::cout<<"\tparent=";
    if(parent == nullptr) std::cout<<"Null\n";
    else std::cout<<parent->getName()<<"\n";
    std::cout<<"\ttruthiness="<<(truthiness?"TRUE":"FALSE")<<"\n";
    
    std::cout<<"\n--LINES ("<<variables.size()<<")--\n";
    for(Tokens tokens : lines.lines){
        std::cout<<"\t* "<<tokensToString(tokens)<<"\n";
    }

    std::cout<<"\n--VARIABLES ("<<variables.size()<<")--\n";
    for(auto pair : variables){
        Variable var = pair.second;
        std::cout<<"\t* ";
        pair.second.dumpString();
    }
    
    std::cout<<"\n--SUBSCOPES ("<<scopes.size()<<")--\n";
    for(auto pair : scopes){
        std::cout<<"\t* "<<pair.second->getName()<<"\n";
    }

    std::cout<<"\n-----END SCOPE ("<<name<<")-----\n";
}

/***************************************/

Variable returnFunction(Function*& func){
    Scope* current_scope = (Scope*)(func);
    Variable return_variable = Variable();
    for(Tokens tokens : func->getLines().lines){
        DEBUG_last_line = {0, tokensToString(tokens)};

        if(tokens.size() == 0){
            continue;
        }

        std::string first_token = tokens[0];
        if(first_token == KW_FUNCTION){
            continue;
        }

        if(first_token == KW_END){
            if(tokens.size() > 1 && tokens[1] == func->getName()){
                break;
            }
        }

        if(first_token == KW_YIELD || first_token == KW_YIELD_ALT){
            if(current_scope->getTruthiness() == true){
            
                Tokens shifted_tokens = shiftTokens(tokens, 1);
                return_variable = evaluateExpression(current_scope, shifted_tokens);
                func->setReturnVariable(return_variable);

                break;
            }
            continue;
        }

        interpret_tokens(current_scope, tokens);        
    }

    if(LOGLEVEL == LOGLEVELDEBUG) func->dump();
    return return_variable;
}

Variable returnFunction(Function*& func, std::vector<Variable> args){
    for(auto arg : args){
        func->updateVariableRecursive(arg);
    }

    return returnFunction(func);
}