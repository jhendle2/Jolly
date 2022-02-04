#include <iostream>
#include <string>
#include <vector>
#include <stack>

#include "errors.hpp"
#include "logging.hpp"

#include "tokens_lines.hpp"
#include "parser.hpp"
#include "function_parser.hpp"
#include "file_reader.hpp"
#include "variable_builder.hpp"
#include "expressions.hpp"
#include "keywords.hpp"
#include "logging.hpp"
#include "operators_delimiters.hpp"

#include "builtins.hpp"

void parseTreeButIgnoreFunctionsAndClasses(ScopePtr& current_scope){
    if(current_scope->getScopeType() == ScopeFunction ||
        current_scope->getScopeType() == ScopeClass) return;
    parseTree(current_scope);
}

void evaluateTakes(ScopePtr& current_scope, Tokens tokens, const Variable& param_value){
    LOGDEBUG(current_scope->getName()+" - ET " + tokensToLine(tokens));
    ifInvalidTokensSize(tokens, 3) ERROR(SyntaxErrorIncompleteStatement); // TAKES TYPE NAME = 3

    std::string variable_name = tokens[2];
    Tokens tokens_shifted = shiftTokens(tokens, 1);

    ScopePtr highest_function_scope = current_scope;
    while(!isFunctionScope(highest_function_scope)){
        highest_function_scope = highest_function_scope->getParent();
        if(highest_function_scope == nullptr){
            ERROR(ParseErrorTakesOutsideFunction);
        }
    }

    evaluateLine(highest_function_scope, tokens_shifted); // Initializes our param variable
    LOGDEBUG("param_value = "+param_value.dump());
    highest_function_scope->updateVariable(variable_name, param_value); // Assign value to param variable
}

Variable parseFunctionCall(ScopePtr& current_scope, std::vector<Variable> params, size_t last_parameter_index){

    if(LOGLEVEL == LOGLEVELDEBUG){
        for(const Variable& v : params){
            std::cout<<current_scope->getName() + " PFCp param "<<v.dump()<<"\n";
        }
    }

    // Establish parameters if they don't already exist
    for(Line line : current_scope->getLines()){
        LOGDEBUG(current_scope->getName()+" - "+(current_scope->getTruthiness()?"PF <True> ":"PT <False> ")+line.line);
        DEBUG_last_line = line;

        size_t debug_params_size = params.size();
        debug_params_size = (debug_params_size>0 ? debug_params_size-1 : 0);
        LOGDEBUG(current_scope->getName() + " param (" + std::to_string(last_parameter_index) + "/" + std::to_string(debug_params_size) + ")");
        
        /* Keeping these blocks from parseFunction allows us
        to have conditional parameters depending on the function's layout:

        function func1
            if True
                Takes Number X
            else
                Takes String X
            end if
            Println(X)
        end func1
        */
        // Don't run scopes that shouldn't happen
        ifScopeCannotRun(current_scope) continue;

        // We gotta go down a scope
        if(isScopeHeader(line.line)){
            ScopePtr child_scope = current_scope->getChild(line.line);
            parseFunctionCall(child_scope, params, last_parameter_index);
            continue;
        }
        
        Tokens tokens = tokenizeLine(line.line);
        // if(tokens[0] == KW_FUNCTION) continue;
        if(tokens[0] == KW_TAKES){
            // if(last_parameter_index >= params.size()) break; // Go back to processing rest of function call
            Variable param = params[last_parameter_index++];
            LOGDEBUG("Passing param ("+std::to_string(last_parameter_index)+") = "+param.dump());
            evaluateTakes(current_scope, tokens, param);
        }
        else if(tokens[0] == KW_YIELD){
            // if(last_parameter_index >= params.size()) break; // Go back to processing rest of function call
            Tokens tokens_shifted = shiftTokens(tokens, 1);
            return evaluateExpression(current_scope, tokens_shifted);
        }
        // else if(tokens[0] == KW_ENTRYPOINT) continue;
        else evaluateLine(current_scope, tokens);
        
    }

    // Then parse normally
    // ProcessFunction(current_scope); // So we don't ignore it, but keep ignoring all children functions/classes
    // parseTreeButIgnoreFunctionsAndClasses(current_scope);
    // DeprocessFunction(current_scope); // So we remember to reprocess params on another call
    return Variable();
}

Variable parseFunctionCall(ScopePtr& current_scope, std::vector<Variable> params){
    return parseFunctionCall(current_scope, params, 0);
}

std::vector<Variable> tokensToListOfVariables(ScopePtr& current_scope, Tokens tokens){
    std::vector<Variable> params;

    ifInvalidTokensSize(tokens, 2) ERROR(SyntaxErrorIncompleteFunctionCall); // No parenthesis, obvious error

    tokens = shiftTokens(tokens, 1); // Drop open paren
    tokens.pop_back(); // Drop close paren

    Tokens param_tokens;
    for(std::string token : tokens){
        
        if(token == OP_COMMA){
            Variable param = evaluateExpression(current_scope, param_tokens);
            params.push_back(param);
            param_tokens.clear();
            continue;
        }

        param_tokens.push_back(token);
    }
    if(param_tokens.size() > 0){ // Still have junk left in param_tokens
        Variable param = evaluateExpression(current_scope, param_tokens);
        params.push_back(param);
        param_tokens.clear();
    }
    return params;
}

Variable parseFunctionCall(ScopePtr& current_scope, Tokens params_tokens){
    LOGDEBUG(current_scope->getName()+" - param tokens= "+tokensToLine(params_tokens));
    std::vector<Variable> params = tokensToListOfVariables(current_scope, params_tokens);
    if(LOGLEVEL == LOGLEVELDEBUG){
        for(const Variable& v : params){
            std::cout<<"PFCt param "<<v.dump()<<"\n";
        }
    }
    return parseFunctionCall(current_scope, params);
}