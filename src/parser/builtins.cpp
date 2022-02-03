#include <iostream>

#include "errors.hpp"
#include "builtins.hpp"
#include "expressions.hpp"
#include "keywords.hpp"

bool StandardJolly::isBuiltin(const std::string& keyword){
    return (
        keyword == KW_PRINT ||
        keyword == KW_PRINTLN ||
        keyword == KW_TYPEOF
    );
}

Variable StandardJolly::runBuiltin(ScopePtr& current_scope, const Tokens& tokens){
    if(tokens[0] == KW_PRINT) StandardJolly::Print(current_scope, tokens);
    else if(tokens[0] == KW_PRINTLN) StandardJolly::Println(current_scope, tokens);
    else if(tokens[0] == KW_TYPEOF) return StandardJolly::Typeof(current_scope, tokens);
    return Variable();
}

void StandardJolly::Print(ScopePtr& current_scope, const Tokens& tokens){
    VerifyTokensForFunctionCall(tokens);

    Tokens tokens_shifted = shiftTokens(tokens, 1); // Print( ... ) -> ( ... )
    Variable print_variable = evaluateExpression(current_scope, tokens_shifted);

    std::cout<<print_variable.valueString();
}
void StandardJolly::Println(ScopePtr& current_scope, const Tokens& tokens){
    StandardJolly::Print(current_scope, tokens);
    std::cout<<"\n";
}

Variable StandardJolly::Typeof(ScopePtr& current_scope, const Tokens& tokens){
    VerifyTokensForFunctionCall(tokens);

    Tokens tokens_shifted = shiftTokens(tokens, 1); // Typeof( ... ) -> ( ... )
    Variable expression_variable = evaluateExpression(current_scope, tokens_shifted);
    Variable typeof_variable = Variable("constant", KW_TYPE);
    typeof_variable.setValue(expression_variable.getValueType());

    return typeof_variable;
}