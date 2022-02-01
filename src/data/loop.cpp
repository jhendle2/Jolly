#include <iostream>

#include "loop.hpp"
#include "keywords.hpp"
#include "interpreter.hpp"
#include "boolean.hpp"
#include "expressions.hpp"
#include "logging.hpp"

bool isLoopType(std::string token){
    return (token == KW_WHILE ||
            token == KW_DOWHILE ||
            token == KW_FOR ||
            token == KW_FOREACH ||
            token == KW_COUNT);
}

std::string loopTypeToString(enum LoopType loop_type){
    switch(loop_type){
        case LOOP_COUNT:
            return "count";
        
        case LOOP_WHILE:
            return "while";
        
        case LOOP_FOR:
            return "for";
        
        case LOOP_FOREACH:
            return "foreach";
        
        case LOOP_DOWHILE:
            return "dowhile";
        
        default:
            break;
    }
    return "loop_invalid";
}

enum LoopType tokenToLoopType(std::string token){
    if(token == KW_WHILE) return LOOP_WHILE;
    else if(token == KW_DOWHILE) return LOOP_DOWHILE;
    else if(token == KW_FOR) return LOOP_FOR;
    else if(token == KW_FOREACH) return LOOP_FOREACH;
    else if(token == KW_COUNT) return LOOP_COUNT;
    else return LOOP_INVALID;
}

Loop::Loop(enum LoopType loop_type) : Scope(loopTypeToString(loop_type), SCOPE_LOOP){
    this->loop_type = loop_type;
}

enum LoopType Loop::getLoopType(){
    return loop_type;
}

void Loop::setLoopCondition(Tokens condition){
    this->loop_condition = condition;
}
Tokens Loop::getLoopCondition(){
    return this->loop_condition;
}

void Loop::addLine(Tokens tokens){
    this->lines.push_back(tokens);
}

std::vector<Tokens> Loop::getLines(){
    return this->lines;
}

void Loop::dump(){
    std::cout<<"-----LOOP<"<<loopTypeToString(this->loop_type)<<">-----\n";
    std::cout<<"\tparent=";
    if(parent == nullptr) std::cout<<"Null\n";
    else std::cout<<parent->getName()<<"\n";
    std::cout<<"\ttruthiness="<<(truthiness?"TRUE":"FALSE")<<"\n";
    
    std::cout<<"\n--LINES ("<<variables.size()<<")--\n";
    for(Tokens tokens : this->lines){
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

void evaluateLoop(Loop*& loop){
    Scope* loop_as_scope = (Scope*)(loop);
    Scope* current_scope = loop_as_scope;
    size_t loop_index = 0;
    size_t loop_times = 0;

    Boolean condition = evaluateExpression(loop_as_scope, loop->getLoopCondition());
    bool truthiness = condition.getValueBoolean();
    if(truthiness==false) return;

    for(loop_index = 0; loop_index < loop->getLines().size(); loop_index++){
        if(LOGLEVEL == LOGLEVELDEBUG){
            std::cout<<"["<<loop_times<<"] <"<<truthiness<<"> LOOP INDEX = "<<loop_index<<"\n";
        }
        Tokens tokens = loop->getLines()[loop_index];

        if(tokens.size() == 0){
            continue;
        }

        std::string first_token = tokens[0];

        if(first_token == KW_END){
            if(tokens.size() > 1 && tokens[1] == loopTypeToString(loop->getLoopType())){
                loop_times += 1;
                condition = evaluateExpression(loop_as_scope, loop->getLoopCondition());
                truthiness = condition.getValueBoolean();

                if(truthiness == false){
                    return;
                }
                else{
                    loop_index = -1; // so we start at 0 actually
                    continue;
                }
            }
        }

        // if(loop->getTruthiness() == false) continue;

        interpret_tokens(current_scope, tokens);        
    }
}

bool evaluateLoopCondition(Loop*& loop){
    Scope* loop_as_scope = (Scope*)(loop);
    Boolean condition = evaluateExpression(loop_as_scope, loop->getLoopCondition());
    return condition.getValueBoolean();
}