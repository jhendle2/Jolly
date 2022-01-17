#include <iostream>
#include <iterator>
#include <vector>
#include <string>

#include "errors.hpp"
#include "general_utils.hpp"

#include "parser.hpp"
#include "parser_keywords.hpp"
#include "expressions.hpp"
#include "function.hpp"

#include "variable.hpp"
#include "object_table.hpp"
#include "scope.hpp"
#include "function.hpp"
#include "conditional_scope.hpp"

bool _smile_show_tokens = false;

// Creates a new variable, sets its name, and links it to its parent scope
void initializeVariable(Scope* parent, std::string type_string, std::string variable_name){
    enum ObjectType type = getTypeFromString(type_string);
    Variable var = Variable(type);
    parent->addVariable(variable_name, var);
}

// Creates a new conditional scope and links it to its parent scope
ConditionalScope* initializeConditionalScope(Scope* parent, std::vector<std::string> tokens, enum ScopeType scope_type, bool truthiness){
    int last_scope_index = parent->lastScopeIndex();
    ConditionalScope* new_condition = new ConditionalScope(scope_type, last_scope_index, truthiness);  
    addScopeToScope(parent, new_condition);
    return new_condition;
}

// Function* initializeFunction(Scope* parent, std::vector<std::string> function_header_tokens){
//     std::string function_name = function_header_tokens[1];
//     Function* new_function = new Function(function_name);  
//     addScopeToScope(parent, new_function);
//     return new_function;
// }

// Tries to close up a scope  and return its parent
// If it can't, there's PROBABLY an error and we should quit
Scope* tryAndEndScope(Scope* scope, std::vector<std::string> tokens){
    bool has_parent = scope->hasParent();
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

    static ConditionalScope* last_conditional_scope = nullptr;

    if(keyword_type == RESERVED_END){
        if(tokens.size() == 1){
            SAFEERROROUT(parent, SyntaxErrorIncompleteStatement, tokensToString(tokens));
        }

        if(tokens[1] == "if"){
            if(!parent->hasParent()){
                SAFEERROROUT(parent, ParseErrorUnmatchedEnd, tokensToString(tokens));
            }

            parent = parent->getParent();

            if(parent->getScopeType() == SCOPE_IF || parent->getScopeType() == SCOPE_ELSE || parent->getScopeType() == SCOPE_ELSIF){
                last_conditional_scope = (ConditionalScope*)parent;
            }
            else{
                last_conditional_scope = nullptr;
            }

            return parent;
        }
    }

    if(keyword_type == RESERVED_YIELD){
        if(parent->getTruthiness() == false) return parent; // This prevents yielding from inside a false condition

        // Escapes any yields inside if/else/elsif
        while(parent->getScopeType() != SCOPE_FUNCTION){
            if(parent == nullptr){
                SAFEERROROUT(parent, ParseErrorOrphanYield, tokensToString(tokens));
            }
            parent = parent->getParent();
        }

        // yield with no following tokens just returns a Nothing variable
        Function* func = (Function*)parent;
        if(tokens.size() == 1){
            func->setReturnVariable(Variable());
            parent = parent->getParent();
            return parent;
        }

        // Otherwise, let's fill the return variable
        std::vector<std::string> tokens_shifted = shiftTokens(tokens, 1); // drops the 'yield' keyword
        Variable return_variable = evaluateExpression(parent, tokens_shifted);
        func->setReturnVariable(return_variable);

        if(!parent->hasParent()){
            SAFEERROROUT(parent, ParseErrorOrphanYield, tokensToString(tokens));
        }

        parent = parent->getParent();
        return parent;
    }
    
    if(keyword_type == RESERVED_IF){
        if(tokens.size() == 1){
            SAFEERROROUT(parent, SyntaxErrorConditionalScopeWithNoCondition, tokensToString(tokens));
        }

        std::vector<std::string> tokens_shifted = shiftTokens(tokens, 1);
        Variable condition_variable = evaluateExpression(parent, tokens_shifted);
        bool truthiness = condition_variable.getBoolean() && parent->getTruthiness(); // If my parent is false, I must be false
        ConditionalScope* if_scope = initializeConditionalScope(parent, tokens, SCOPE_IF, truthiness);

        last_conditional_scope = if_scope;
        parent = last_conditional_scope;

        return parent;
    }

    if(keyword_type == RESERVED_ELSE){
        if(last_conditional_scope == nullptr){
            SAFEERROROUT(parent, SyntaxErrorElseWithoutIf, tokensToString(tokens));
        }

        parent = last_conditional_scope->getParent(); // this goes before the truthiness check because otherwise, else statements would always be set to false, no matter what
         // If my parent is false, I must be false
        bool truthiness = !(last_conditional_scope->getTruthiness()) && parent->getTruthiness(); // Else is always the opposite truthiness of the previous if/elsif
        ConditionalScope* else_scope = initializeConditionalScope(parent, tokens, SCOPE_ELSE, truthiness);

        last_conditional_scope = else_scope;
        parent = last_conditional_scope;

        return parent;
    }

    return parent;
}

// Print(value) (AND) Print(expression) handler
void Print(Scope* parent, std::vector<std::string> tokens){
    Variable print_variable;

    // Print(expression)
    if(tokens.size() >= 4){
        std::vector<std::string> shifted_tokens = shiftTokens(tokens, 1);
        print_variable = evaluateExpression(parent, shifted_tokens);
        std::cout<<"> "<<print_variable.toStringValue();
        return;
    }

    // Print(value)
    bool exists = parent->getVariableRecursive(tokens[2], print_variable);
    if(exists) std::cout<<"> "<<print_variable.toStringValue();
}

// Internal debugging so I don't have to keep re-compiling
bool _smile_debug(Scope* parent, std::vector<std::string> tokens){
    if(tokens[0]=="_smile.dump"){
        parent->dump();
        std::cout<<"\n";
        return true;
    }
    else if(tokens[0]=="_smile.dump_recursive"){
        parent->dumpRecursive();
        std::cout<<"\n";
        return true;
    }
    else if(tokens[0]=="_smile.show_tokens"){
        _smile_show_tokens=true;
        std::cout<<"\n";
        return true;
    }
    else if(tokens[0]=="_smile.hide_tokens"){
        _smile_show_tokens=false;
        std::cout<<"\n";
        return true;
    }
    else if(tokens[0]=="_smile.scope"){
        std::cout<<parent->getName()<<"\n";
        return true;
    }
    else if(tokens[0]=="_smile.scope.parent"){
        if(parent->hasParent()) std::cout<<parent->getParent()->getName()<<"\n";
        else std::cout<<parent->getName()<<" has no parent\n";
        return true;
    }
    else if(tokens[0]=="_smile.scope.lineage"){
        Scope* temp = parent;
        while(temp!=nullptr){
            std::cout<<" * "<<temp->getName()<<"\n";
            temp = temp->getParent();
        }
        return true;
    }
    return false;
}

// Takes a list of tokens
// Parses them initializing every scope and variable it sees
// Expands any assignments and expressions by creating a new variable
// from constants or other variables (looks them up in the scope's variable table)
// Adds the generated scopes and variables to the parent scope (this allows for recursion)
// Returns the new scope generated for reassigning the parent scope
Scope* buildVariableAndEvaluateExpressions(Scope* parent, std::vector<std::string> tokens){
    if(_smile_show_tokens) std::cout<<"["<<parent->getName()<<"] (truth="<<parent->getTruthiness()<<") = "<<tokensToString(tokens)<<"\n";
    ///std::cout<<"#################CURRENTLY IN = "<<parent->getName()<<"\n";
    // Obvious error
    if(tokens.size() == 0)
        SAFEERROROUT(parent, ParseDebugNoTokens, tokensToString(tokens));
    
    // Single word keywords
    if(tokens.size() == 1){
        std::string first_token = tokens[0];
        if(isReservedKeyword(first_token)){
            enum ReservedKeyword keyword_type = getReservedKeyword(tokens[0]);

            parent = initializeKeyword(parent, keyword_type, tokens);
            return parent;
        }
        
        SAFEERROROUT(parent, ParseDebugOneToken, tokensToString(tokens));
    }

    // Debugging inside the interpreter so I don't have to keep re-compiling lol
    if(_smile_debug(parent, tokens)) return parent;

    // If this token is a keyword, determine which and apply the necessary operations on it
    // This goes before the parent truthiness tester because otherwise if/elsif/else ladders would constantly break
    bool first_token_is_keyword = isReservedKeyword(tokens[0]);
    if(first_token_is_keyword){
        enum ReservedKeyword keyword_type = getReservedKeyword(tokens[0]);

        parent = initializeKeyword(parent, keyword_type, tokens);
        return parent;
    }

    // Don't run scopes that are truthy false.
    // If it's an end or an else though, we should probably look into that
    // because we might be closing an if/elsif/else ladder
    // if( (tokens[0]!="end" && tokens[0]!="else") && parent->getTruthiness() == false) return parent;
    if(parent->getTruthiness() == false) return parent;

    // Makes Print/Println work
    if(tokens[0]=="Print"){
        Print(parent, tokens);
        return parent;
    }
    else if(tokens[0]=="Println"){
        Print(parent, tokens);
        std::cout<<"\n";
        return parent;
    }

    // If this token is a variable type, we should initialize a variable
    // Recursively evaluates expressions as well
    bool first_token_is_type = isObjectType(tokens[0]);
    if(first_token_is_type){

        // If we accidentally re-define a defined variable
        bool second_token_is_known_variable = parent->isKnownVariable(tokens[1]);
        if(second_token_is_known_variable){
            SAFEERROROUT(parent, SyntaxErrorReinitializedVariable, tokensToString(tokens));
        }

        // Clearly we didn't have a problem, so let's chug along
        std::string type_string = tokens[0];
        std::string variable_name = tokens[1];
        initializeVariable(parent, type_string, variable_name);

        // If there are still tokens left, recursively evaluate the expression remaining
        if(tokens.size() > 2){
            std::vector<std::string> shifted_tokens = shiftTokens(tokens, 1);
            parent = buildVariableAndEvaluateExpressions(parent, shifted_tokens); // recurse and do it again now with var initialized
        }

        return parent;
    }

    // If we know this variable, we should assign it to an expression
    Variable temp = Variable();
    bool first_token_is_known_variable = parent->getVariableRecursive(tokens[0], temp);
    if(first_token_is_known_variable){
        std::string variable_name = tokens[0];
        Variable expression_result = evaluateExpression(parent, tokens);
        parent->updateVariableRecursive(variable_name, expression_result);
        return parent;
    }

    // If we know this function, we should evaluate it, then return its return variable
    Scope* func_as_scope = parent->getScopeRecursive(tokens[0]);
    bool first_token_is_known_func = (func_as_scope != nullptr);
    if(first_token_is_known_func){
        Function* func = (Function*)func_as_scope;
        Variable function_return = returnFunction(func); // Evaluates the function if it hasn't already been. This variable is thrown away
        return parent;
    }

    SAFEERROROUT(parent, ParseErrorUnexpectedToken, tokensToString(tokens));
    return parent;
}