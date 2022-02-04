
#include "logging.hpp"
#include "errors.hpp"
#include "conditional_parser.hpp"
#include "parser.hpp"
#include "function_parser.hpp"
#include "keywords.hpp"
#include "expressions.hpp"

std::stack<bool> last_conditional_stack;

void emptyConditionalStack(){
    last_conditional_stack = std::stack<bool>();
}

void evaluateOpenScopeLine(ScopePtr& current_scope, Tokens tokens){
    if(last_conditional_stack.size() > 0) LOGDEBUG(last_conditional_stack.top()?"EOSL STACK: TRUE":"EOSL STACK: FALSE");
    
    if(tokens[0] == KW_IF){
        if(tokens.size() < 2){
            ERROR(SyntaxErrorConditionalScopeWithNoCondition);
        }

        Tokens shifted_tokens = shiftTokens(tokens, 1);
        Variable condition = evaluateExpression(current_scope, shifted_tokens);

        bool if_condition = condition.getBoolean();
        last_conditional_stack.push(if_condition); // push my IF condition
        current_scope->setTruthiness(if_condition); // and set me to that condition
        return;
    }

    if(tokens[0] == KW_ELSIF){
        ifInvalidTokensSize(tokens, 2) ERROR(SyntaxErrorConditionalScopeWithNoCondition);

        Tokens shifted_tokens = shiftTokens(tokens, 1);
        Variable condition = evaluateExpression(current_scope, shifted_tokens);
        
        if(last_conditional_stack.size() == 0){ // if stack is empty, there was no prior IF or ELSIF
            ERROR(SyntaxErrorElsifWithoutIf);
        }

        bool last_top = last_conditional_stack.top(); // get the last IF or ELSIF condition
        bool elsif_truthiness = false;
        if(last_top == false){
            last_conditional_stack.pop(); // pop the last IF condition
            elsif_truthiness = condition.getBoolean() && !last_top; // I'm only true if the last scope was false and my condition is true
            last_conditional_stack.push(elsif_truthiness); // then push ELSIF condition to the stack
        }
        current_scope->setTruthiness(elsif_truthiness);
        return;
    }

    if(tokens[0] == KW_ELSE){
        if(last_conditional_stack.size() == 0){ // if stack is empty, there was no prior IF or ELSIF
            ERROR(SyntaxErrorElseWithoutIf);
        }

        bool else_truthiness = !last_conditional_stack.top(); // ELSE truthiness is always the opposite of the last IF/ELSIF 
        current_scope->setTruthiness(else_truthiness);
        last_conditional_stack.pop();
        return;
    }
}