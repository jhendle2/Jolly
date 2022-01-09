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

// Tries to close up a scope and return its parent
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
    static Scope* last_conditional_scope = nullptr;
    // static bool currently_inside_function = false;
    bool currently_inside_function = false;
    if(parent->hasParent() && parent->getParent()->getScopeType() == SCOPE_FUNCTION){
        currently_inside_function = true;
    }

    if(keyword_type == RESERVED_END){
        // If we're in a function, close up the function

        // TODO: remember to return Nothings!!
        if(currently_inside_function){
            currently_inside_function = false;
            if(parent->hasParent()){
                parent = parent->getParent();
                return parent;
            }
            SAFEERROROUT(parent, ParseErrorUnmatchedEnd, tokensToString(tokens));
        }
        
        // Otherwise, clean up the scope we're in (IF, ELSE, ELSIF, etc.)
        Scope* return_scope = tryAndEndScope(parent, tokens);
        last_conditional_scope = return_scope;
        return return_scope;
    }

    // If we hit a YIELD, let's try and return from the function we're currently in
    // and if we're not currently in a function, let's crash!
    if(keyword_type == RESERVED_YIELD){

        // Crash if we're not in a function
        if(!currently_inside_function){
            SAFEERROROUT(parent, ParseErrorOrphanYield, tokensToString(tokens));
        }

        Variable return_variable = Variable();
        // return_variable.setName(parent->getName() + ".return");

        // // yield expression...
        // if(tokens.size() > 2){
        //     //lord help us
        //     return parent;
        // }

        // yield variable
        return_variable = evaluateExpression(parent, shiftTokens(tokens, 1));
        std::string return_name = parent->getName() + ".return";
        return_variable.setName(return_name);
        
        // parent->getVariableRecursive(tokens[1], return_variable);
        if(!parent->hasParent()){ // this might be unnecessary
            SAFEERROROUT(parent, ParseErrorOrphanYield, tokensToString(tokens));
        }

        // parent = parent->getParent();
        parent->addVariable(return_variable);
        parent = parent->getParent();
        return parent;
    }
    
    // Function keyword
    // Initialize a function

    /*
    if(keyword_type == RESERVED_FUNCTION){
        if(tokens.size() == 1){
            SAFEERROROUT(parent, ParseErrorIncompleteFunctionHeader, tokensToString(tokens));
        }

        if(currently_inside_function){
            WARNING(ParseWarningNestedFunctions, tokensToString(tokens));
        }

        std::string function_name = tokens[1];
        Function* new_function = new Function(function_name); // initializeFunction(parent, tokens[1]);

        // new_function->addLine(tokensToLine(tokens));
        new_function->setParent(parent);
        currently_inside_function = true;
        parent = new_function;
    }*/


    if(keyword_type == RESERVED_IF){
        if(tokens.size() == 1){
            SAFEERROROUT(parent, SyntaxErrorConditionalScopeWithNoCondition, tokensToString(tokens));
        }

        std::vector<std::string> conditional_expression_tokens = shiftTokens(tokens, 1);
        Boolean condition = evaluateExpression(parent, conditional_expression_tokens);
        bool truthiness = condition.getBoolean();

        // Nested IF scopes
        if(last_conditional_scope != nullptr){
            Scope* nested_scope = initializeConditionalScope(last_conditional_scope, tokens, SCOPE_IF, truthiness);
            last_conditional_scope = nested_scope;
            last_conditional_scope->setTruthiness(truthiness);
            return last_conditional_scope;
        }

        // Level 1 IF scope
        else{
            last_conditional_scope = initializeConditionalScope(parent, tokens, SCOPE_IF, truthiness);
            last_conditional_scope->setTruthiness(truthiness);
        }
        return last_conditional_scope;
    }

    if(keyword_type == RESERVED_ELSE){
        parent = tryAndEndScope(last_conditional_scope, tokens);

        if(last_conditional_scope != nullptr){
            // Set me to truthy true if the previous scope was truthy false
            ConditionalScope* new_conditional_scope = initializeConditionalScope(parent, tokens, SCOPE_ELSE, !(last_conditional_scope->getTruthiness()));
            new_conditional_scope->setParent(parent);
            parent->addNextScope(new_conditional_scope);
            last_conditional_scope = new_conditional_scope;
            return last_conditional_scope;
        }
        
        SAFEERROROUT(parent, ParseErrorUnmatchedEnd, tokensToString(tokens));
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

// Takes a list of tokens
// Parses them initializing every scope and variable it sees
// Expands any assignments and expressions by creating a new variable
// from constants or other variables (looks them up in the scope's variable table)
// Adds the generated scopes and variables to the parent scope (this allows for recursion)
// Returns the new scope generated for reassigning the parent scope
Scope* buildVariableAndEvaluateExpressions(Scope* parent, std::vector<std::string> tokens){
    // std::cout<<"toks="<<tokensToString(tokens)<<"\n";
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

    // // Makes IF scopes work
    // if(tokens[0]=="end"){
    //     parent = initializeKeyword(parent, RESERVED_END, tokens);
    //     return parent;
    // }

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

    // If this token is a keyword, determine which and apply the necessary operations on it
    bool first_token_is_keyword = isReservedKeyword(tokens[0]);
    if(first_token_is_keyword){
        enum ReservedKeyword keyword_type = getReservedKeyword(tokens[0]);

        parent = initializeKeyword(parent, keyword_type, tokens);
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

    // If we are calling a function and it is known, we should evaluate it and "return" its return variable
    Function* temp_function = new Function("this is a test");
    // parent->dumpRecursive();

    // I think the issue is we're not setting parent to the function itself
    temp_function = (Function*)(parent->getScopeRecursive(tokens[0]));
    bool first_token_is_known_function = (temp_function!=nullptr); //parent->getScopeRecursive(tokens[0], temp_function); // THIS FUNCTION ISN'T WORKING

    if(first_token_is_known_function){
        // DO THE FUNCTION
        if(temp_function==nullptr){
            SAFEERROROUT(parent, SyntaxErrorUnrecognizedFunction,"whoopsie daisy");
        }
        else {
            // TODO: PASS IN THE PARAMETERS
            // maybe interate thru a list, evaluating parameters
            bool tokens_is_list = tokensIsList(tokens);
            
            if(tokens_is_list){
                std::vector<std::string> tokens_shifted = shiftTokens(tokens, 2); // Gets us in the parentheses
                std::vector<std::vector<std::string>> list_of_tokens_lists = listToListOfTokens(tokens_shifted); // Each parameter is its own vector
                int parameter_index = 0;
                for(std::vector<std::string> parameter_expression : list_of_tokens_lists){
                    // TODO: FINISH THIS
                    Variable evaluated_parameter = evaluateExpression(parent, parameter_expression);
                    std::string parameter_name = temp_function->getParameter(parameter_index).getName();
                    temp_function->addParameter(parameter_name, evaluated_parameter);
                }
                returnFunction(temp_function);

            }
            else{
                returnFunction(temp_function); // <- i think the error is temp_function is somehow uninitialized??
            }
        }
        // Variable return_variable = returnFunction(temp_function);
        // parent->addVariable(return_variable);
        return parent;
    }

    SAFEERROROUT(parent, ParseErrorUnexpectedToken, tokensToString(tokens));
    return parent;
}