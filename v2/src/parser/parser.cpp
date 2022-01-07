#include <iostream>
#include <iterator>
#include <vector>
#include <string>

#include "errors.hpp"
#include "general_utils.hpp"

#include "parser.hpp"
#include "parser_keywords.hpp"
#include "expressions.hpp"

#include "variable.hpp"
#include "object_table.hpp"
#include "scope.hpp"
#include "function.hpp"
#include "conditional_scope.hpp"

// Creates a new variable, sets its name, and links it to its parent scope
void initializeVariable(Scope* parent, std::string type_string, std::string variable_name){
    enum ObjectType type = getTypeFromString(type_string);
    Variable var = Variable(type);
    ///std::cout<<"~Initialized Var="<<variable_name<<"\n";
    parent->addVariable(variable_name, var);
    ///std::cout<<"~"<<parent->getVariable(variable_name).toString()<<"\n";
}

// Creates a new conditional scope and links it to its parent scope
ConditionalScope* initializeConditionalScope(Scope* parent, std::vector<std::string> tokens, enum ScopeType scope_type){
    int last_scope_index = parent->lastScopeIndex();
    ConditionalScope* new_condition = new ConditionalScope(scope_type, last_scope_index);  
    addScopeToScope(parent, new_condition);
    return new_condition;
}

// Creates a new function and links it to its parent scope
Function* initializeFunction(Scope* parent, std::vector<std::string> tokens){
    std::string function_name = tokens[1];
    Function* new_function = new Function(function_name);  
    addScopeToScope(parent, new_function);
    return new_function;
}

// Tries to close up a scope and return its parent
// If it can't, there's PROBABLY an error and we should quit
Scope* tryAndEndScope(Scope* scope, std::vector<std::string> tokens){
    bool has_parent = scope->hasParent();
    ///std::cout<<"&&&&&&&&<"<<scope->getName()<<"> has_parent="<<has_parent<<"\n";
    if(has_parent){
        return scope->getParent();
    }
    else{
        return nullptr;
        // ERROROUT(ParseErrorUnmatchedEnd, tokensToString(tokens));
    }
    return scope;
}

// Determines if a token is a reserved keyword
// and tries to create the proper scope for it
// then depending on the new scope type
// modifies the parent scope
Scope* initializeKeyword(Scope* parent, enum ReservedKeyword keyword_type, std::vector<std::string> tokens){
    static Scope* last_conditional_scope = nullptr;

    if(keyword_type == RESERVED_END){
        ///std::cout<<"#####GOING_UP\n";
        Scope* return_scope = tryAndEndScope(parent, tokens);
        last_conditional_scope = return_scope;
        return return_scope;
    }
    
    ///std::cout<<"#####GOING_DOWN\n";
    if(keyword_type == RESERVED_FUNCTION){
        return initializeFunction(parent, tokens);
    }


    if(keyword_type == RESERVED_IF){

        // Nested IF scopes
        if(last_conditional_scope != nullptr){
            Scope* nested_scope = initializeConditionalScope(last_conditional_scope, tokens, SCOPE_IF);
            last_conditional_scope = nested_scope;
            return last_conditional_scope;
        }

        // Level 1 IF scope
        else{
            last_conditional_scope = initializeConditionalScope(parent, tokens, SCOPE_IF);
        }
        return last_conditional_scope;
    }

    if(keyword_type == RESERVED_ELSE){
        ///std::cout<<"OH BABY WE HIT AN ELSE\n";
        ///std::cout<<"currently_in="<<parent->getName()<<"\n";
        parent = tryAndEndScope(last_conditional_scope, tokens);
        ///std::cout<<"now_in="<<parent->getName()<<"\n";

        if(last_conditional_scope != nullptr){
            ///std::cout<<"****1\n";
            ConditionalScope* new_conditional_scope = initializeConditionalScope(parent, tokens, SCOPE_ELSE);
            ///std::cout<<"****2\n";
            new_conditional_scope->setParent(parent);
            ///std::cout<<"****3\n";
            parent->addNextScope(new_conditional_scope);
            ///std::cout<<"****4\n";
            last_conditional_scope = new_conditional_scope;
            ///std::cout<<"****5\n";
            return last_conditional_scope;
        }
        
        ERROROUT(ParseErrorUnmatchedEnd, tokensToString(tokens));
    }

    return parent;
}

// Takes a list of tokens
// Parses them initializing every scope and variable it sees
// Expands any assignments and expressions by creating a new variable
// from constants or other variables (looks them up in the scope's variable table)
// Adds the generated scopes and variables to the parent scope (this allows for recursion)
// Returns the new scope generated for reassigning the parent scope
Scope* buildVariableAndEvaluateExpressions(Scope* parent, std::vector<std::string> tokens){
    ///std::cout<<"#################CURRENTLY IN = "<<parent->getName()<<"\n";
    // Obvious error
    if(tokens.size() == 0)
        ERROROUT(ParseDebugNoTokens, tokensToString(tokens));
    
    // Single word keywords
    if(tokens.size() == 1){
        std::string first_token = tokens[0];
        if(isReservedKeyword(first_token)){
            enum ReservedKeyword keyword_type = getReservedKeyword(tokens[0]);

            parent = initializeKeyword(parent, keyword_type, tokens);
            return parent;
        }
        
        ERROROUT(ParseDebugOneToken, tokensToString(tokens));
    }

    if(tokens[0]=="Print"){
        Variable v;
        bool exists = parent->getVariableRecursive(tokens[2], v);
        if(exists) std::cout<<"> "<<v.toStringValue();
        return parent;
    }
    else if(tokens[0]=="Println"){
        Variable v;
        bool exists = parent->getVariableRecursive(tokens[2], v);
        if(exists) std::cout<<"> "<<v.toStringValue()<<"\n";
        else std::cout<<"> \n";
        return parent;
    }

    // Expressions, function calls, variables initialization, etc.
    bool first_token_is_type = isObjectType(tokens[0]);
    if(first_token_is_type){
        ///std::cout<<"######################\n";
        bool second_token_is_known_variable = parent->isKnownVariable(tokens[1]);
        ///std::cout<<"stikv="<<second_token_is_known_variable<<"\n";
        if(second_token_is_known_variable){
            ERROROUT(SyntaxErrorReinitializedVariable, tokensToString(tokens));
        }

        std::string type_string = tokens[0];
        std::string variable_name = tokens[1];
        initializeVariable(parent, type_string, variable_name);

        // if there are still tokens left
        if(tokens.size() > 2){
            std::vector<std::string> shifted_tokens = shiftTokens(tokens, 1);
            parent = buildVariableAndEvaluateExpressions(parent, shifted_tokens); // recurse and do it again now with var initialized
        }

        return parent;
    }

    bool first_token_is_keyword = isReservedKeyword(tokens[0]);
    if(first_token_is_keyword){
        enum ReservedKeyword keyword_type = getReservedKeyword(tokens[0]);

        parent = initializeKeyword(parent, keyword_type, tokens);
        return parent;
    }

    Variable temp = Variable();
    bool first_token_is_known_variable = parent->getVariableRecursive(tokens[0], temp);
    if(first_token_is_known_variable){
        std::string variable_name = tokens[0];
        Variable expression_result = evaluateExpression(parent, tokens);
        parent->updateVariableRecursive(variable_name, expression_result);
        return parent;
    }

    return parent;
}