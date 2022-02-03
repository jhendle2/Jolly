#include <iostream>
#include <string>
#include <vector>
#include <stack>

#include "errors.hpp"
#include "logging.hpp"

#include "tokens_lines.hpp"
#include "parser.hpp"
#include "file_reader.hpp"
#include "variable_builder.hpp"
#include "expressions.hpp"
#include "keywords.hpp"
#include "logging.hpp"

#include "builtins.hpp"

ScopePtr buildTreeFromFile(std::string file_path){
    /*
        Builds a tree representing all constant expressions and
        scopes within a file. It also duplicates scope creation lines
        so that we can later pull important info from them.
        
        So, the line "if x > 10" would generate a scope <if_#> and then
        give that scope the full line "if x > 10" so we can later
        pull the necessary boolean operation to set the if's truthiness. 
        
        For example:

        Input: (test.jolly)
            function func1
                Number x = 10
                if x > 10
                    Println("Hello, World!")
                end if
            end func1
        
        Output: (test.tree)
            test
            ----<func1_0>
            --------function func1
            --------Number x = 10
            --------<if_1>
            ------------if x > 10
            ------------Println("Hello, World!")
            --------end func1
    */
    std::vector<Line> file_as_lines = readFileAsLines(file_path);

    std::string file_name = fileName(file_path);
    ScopePtr master_scope = Scope::create(file_name, ScopeClass);
    ScopePtr current_scope = master_scope;

    for(auto line : file_as_lines){
        if(LOGLEVEL == LOGLEVELDEBUG) std::cout << "(" << line.line_number << ") " << line.line << "\n";

        Tokens tokens = tokenizeLine(line.line);
        if(isCloseScope(tokens[0])){

            // This makes sure that we successfully close if/elsif/else blocks
            // and pop off the conditional truthiness stack
            if(tokens.size() > 1 && tokens[1] == KW_IF) current_scope->addLine(line);

            if(current_scope->getParent() == nullptr){
                ERROR(ParseErrorCriticalScopeError);
            }

            current_scope = current_scope->getParent();
            // No continue here so that elsif/else can both
            // close and open new scopes
        }

        if(isOpenScope(tokens[0])){
            
            ScopePtr new_open_scope = buildScopeFromTokens(tokens);
            current_scope->addChild(new_open_scope);
            current_scope->addLine({line.line_number,
                new_open_scope->getName()}); // So parent has a "pointer" to the child scope
            current_scope = new_open_scope;
            current_scope->addLine(line); // So child has a copy of line

            continue;
        }

        if(!isCloseScope(tokens[0]) && !isOpenScope(tokens[0])){
            current_scope->addLine(line);
        }
    }

    return master_scope;
}

void parseTreeButIgnoreFunctionsAndClasses(ScopePtr& current_scope){
    if(current_scope->getScopeType() == ScopeFunction ||
        current_scope->getScopeType() == ScopeClass) return;
    parseTree(current_scope);
}

void parseTree(ScopePtr& current_scope){

    for(Line line : current_scope->getLines()){
        LOGDEBUG((current_scope->getTruthiness()?"PT <True> ":"PT <False> ")+line.line);
        DEBUG_last_line = line;

        // Don't run scopes that shouldn't happen
        if(current_scope->getTruthiness() == false) continue;

        // We gotta go down a scope
        if(isScopeHeader(line.line)){
            ScopePtr child_scope = current_scope->getChild(line.line);
            parseTreeButIgnoreFunctionsAndClasses(child_scope); // So we don't accidentally trigger functions
            continue;
        }

        // Else, we need to evaluate this line directly
        evaluateLine(current_scope, tokenizeLine(line.line));
    }

}

void evaluateLine(ScopePtr& current_scope, Tokens tokens){
    LOGDEBUG("EL " + tokensToLine(tokens));
    
    // Runs built-in functions of the interpreter (Print, Println, Typeof, etc.)
    if(StandardJolly::isBuiltin(tokens[0])){
        StandardJolly::runBuiltin(current_scope, tokens);
        return;
    }

    // First Token is a close-scope keyword
    if(isCloseScope(tokens[0])){
        evaluateCloseScopeLine(current_scope, tokens);
        // No return because we want this to flow thru
    }
    // First Token is an open-scope keyword
    if(isOpenScope(tokens[0])){
        evaluateOpenScopeLine(current_scope, tokens);
        return;
    }

    // Keywords (but not ones like IF, FUNCTION, WHILE, etc.)
    if(isKeyword(tokens[0])){
        evaluateKeyword(current_scope, tokens);
    }

    // Variable initialization
    if(isVarType(tokens[0])){
        if(tokens.size() == 1){
            ERROR(SyntaxErrorIncompleteStatement);
        }
        Variable var = buildVariableFromTokens(tokens);
        current_scope->addVariable(var);

        if(tokens.size() > 2){
            Tokens tokens_shifted = shiftTokens(tokens, 1);
            evaluateLine(current_scope, tokens_shifted);
        }

        return;
    }

    // Known variable
    if(current_scope->hasVariableRecursive(tokens[0])){
        Variable expression_output = evaluateExpression(current_scope, tokens);
        return;
    }
}

void evaluateKeyword(ScopePtr& current_scope, Tokens tokens){
    LOGDEBUG("EK " + tokensToLine(tokens));
    std::string keyword = tokens[0];

    if(keyword == KW_ENTRYPOINT){
        if(tokens.size() < 2) ERROR(SyntaxErrorIncompleteStatement);

        if(current_scope->hasChild(tokens[1])){
            ScopePtr child = current_scope->getChild(tokens[1]);
            parseTree(child);
        }
        return;
    }
}

/**************************************************/

static std::stack<bool> last_conditional_stack;

void evaluateOpenScopeLine(ScopePtr& current_scope, Tokens tokens){
    if(last_conditional_stack.size() > 0) LOGDEBUG(last_conditional_stack.top()?"EOSL STACK: TRUE":"EOSL STACK: FALSE");
    
    if(tokens[0] == KW_IF){
        if(tokens.size() < 2){
            ERROR(SyntaxErrorConditionalScopeWithNoCondition);
        }

        Tokens shifted_tokens = shiftTokens(tokens, 1);
        Variable condition = evaluateExpression(current_scope, shifted_tokens);

        last_conditional_stack.push(condition.getBoolean());
        current_scope->setTruthiness(last_conditional_stack.top());
        return;
    }

    if(tokens[0] == KW_ELSIF){
        if(tokens.size() < 2){
            ERROR(SyntaxErrorConditionalScopeWithNoCondition);
        }

        Tokens shifted_tokens = shiftTokens(tokens, 1);
        Variable condition = evaluateExpression(current_scope, shifted_tokens);
        
        if(last_conditional_stack.size() == 0){
            ERROR(SyntaxErrorElseWithoutIf);
        }

        last_conditional_stack.pop();
        last_conditional_stack.push(condition.getBoolean() && !last_conditional_stack.top());
        current_scope->setTruthiness(last_conditional_stack.top());
        return;
    }

    if(tokens[0] == KW_ELSE){
        if(last_conditional_stack.size() == 0){
            ERROR(SyntaxErrorElseWithoutIf);
        }

        current_scope->setTruthiness(!last_conditional_stack.top());
        return;
    }
}

void evaluateCloseScopeLine(ScopePtr& current_scope, Tokens tokens){
    LOGDEBUG(last_conditional_stack.top()?"ECSL STACK: TRUE":"EOSL STACK: FALSE");

    if(tokens.size() > 1 && tokens[1] == KW_IF){
        last_conditional_stack.pop();
        return;
    }

    // if(tokens[0] == KW_ELSIF || tokens[0] == KW_ELSE){
    //     return;
    // }
}