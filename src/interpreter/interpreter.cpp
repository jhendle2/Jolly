#include "interpreter.hpp"
#include "errors.hpp"
#include "logging.hpp"

#include "variable.hpp"
#include "function.hpp"
#include "loop.hpp"

#include "keywords.hpp"
#include "operators.hpp"
#include "expressions.hpp"
#include "tokens.hpp"

// Confirms a name isn't a reserved word
static bool isValidName(std::string name){
    return (
        (name.length() > 0) &&
        !isDelimiter(name.at(0)) &&
        !isOperator(name.at(0)) &&
        !isKeyword(name) &&
        !isPrimType(name) &&
        !isDigit(name.at(0))
    );
}

static bool isConditional(Tokens tokens){
    if(tokens.size() == 0) return false;
    return (
        tokens[0] == KW_IF ||
        tokens[0] == KW_ELSIF ||
        tokens[0] == KW_ELSE ||
        tokens[0] == KW_WHILE ||
        (tokens.size() > 1 && tokens[0] == KW_END && tokens[1] == KW_IF) ||
        (tokens.size() > 1 && tokens[0] == KW_END && tokens[1] == KW_WHILE)
    );
}

static Scope* initConditionalScope(int last_conditional_id, std::string name){
    std::string if_scope_name = "if" + std::to_string(last_conditional_id);
    Scope* if_scope = new Scope(if_scope_name, SCOPE_CONDITIONAL);
    return if_scope;
}

static Variable initVariable(Scope*& current_scope, Tokens tokens){
    if(tokens.size() < 2){
        ERROR(SyntaxErrorIncompleteStatement);
    }

    std::string variable_name = tokens[1];
    if(!isValidName(variable_name)){
        ERROR(SyntaxErrorBadName);
    }

    enum PrimType type = keyword2PrimType(tokens[0]);
    Variable variable = Variable(variable_name, type);
    return variable;
}

static void processKeyword(Scope*& current_scope, Tokens tokens){
    if((tokens[0] == KW_TAKES || tokens[0] == KW_TAKES_ALT) && tokens.size() > 2){
        static int last_param_index = 0;

        if(current_scope->getScopeType() != SCOPE_FUNCTION){
            ERROR(ParseErrorUnexpectedToken);
        }

        Tokens shifted_tokens = shiftTokens(tokens, 1);
        Variable param_variable = initVariable(current_scope, shifted_tokens);

        Function* function = (Function*)current_scope;
        function->addParam(param_variable);
        
        std::string param_name = std::to_string(last_param_index);
        Variable param_evaluated = Variable();
        if(!function->getVariable(param_name, param_evaluated)){
            return;
        }

        function->updateVariable(param_variable.getName(), param_evaluated);
        last_param_index++;
        return;
    }
}

static void processLoop(Scope*& current_scope, Tokens tokens){
    // If we aren't currently building a loop, let's make a new one
    Loop* new_loop = new Loop(tokenToLoopType(tokens[0]));
    Tokens condition = shiftTokens(tokens, 1); // Keeps the condition expression
    new_loop->setLoopCondition(condition);
    addScopeToScope(current_scope, new_loop);
    current_scope = new_loop;
}

static void processConditional(Scope*& current_scope, Tokens tokens){
    static Scope* last_conditional_scope = nullptr;
    static int last_conditional_id = 0;

    if(tokens.size() > 1 && tokens[0] == KW_IF){
        if(current_scope->getTruthiness() == false) return;
        
        Scope* if_scope = initConditionalScope(last_conditional_id, "if");

        Tokens shifted_tokens = shiftTokens(tokens, 1);
        Variable truthiness = evaluateExpression(current_scope, shifted_tokens);
        if_scope->setTruthiness(truthiness.getValueBoolean());

        addScopeToScope(current_scope, if_scope);
        last_conditional_scope = if_scope;
        current_scope = if_scope;

        last_conditional_id++;
        return;
    }

    // If we're any other type of conditional keyword,
    // we'd need a previous conditional scope anyways
    // so clearly we have a problem.
    if(last_conditional_scope == nullptr){
        ERROR(ParseErrorOrphanConditionalScope);
    }

    if(tokens.size() > 1 && tokens[0] == KW_ELSIF){ // TODO: IMPLEMENT
        if(current_scope->getTruthiness() == false) return;
    }

    if(tokens[0] == KW_ELSE){ // TODO: IMPLEMENT
        if(current_scope->getTruthiness() == false) return;
    }
    
    if(tokens.size() > 1 && tokens[0] == KW_END && tokens[1] == KW_IF){
        if(last_conditional_scope == nullptr){
            ERROR(ParseErrorUnmatchedEnd);
        }

        if(current_scope->getParent() == nullptr){
            ERROR(ParseErrorCriticalScopeError);
        }

        current_scope = current_scope->getParent();

        if(current_scope->getScopeType() == SCOPE_CONDITIONAL){
            last_conditional_scope = current_scope;
        }
        else{
            last_conditional_scope = nullptr;
        }

        return;
    }

    ERROR(SyntaxErrorIncompleteStatement);
}

static void _print(Scope*& current_scope, Tokens tokens){
    bool show_cursor = false;
    if(show_cursor) std::cout<<">";
    
    if(tokens.size() < 3){
        return;
    }
    
    if(tokens[1] != "(" && tokens[tokens.size()-1] != ")"){
        ERROR(SyntaxErrorIncompleteStatement);
    }

    Tokens shifted_tokens = shiftTokens(tokens, 2); // ignore the Print and open parenthesis
    shifted_tokens.pop_back(); // drop that last parenthesis
    Variable print_variable = evaluateExpression(current_scope, shifted_tokens);
    std::cout << print_variable.stringValue();
}

static void _println(Scope*& current_scope, Tokens tokens){
    _print(current_scope, tokens);
    std::cout << "\n";
}

void interpret_tokens(Scope*& current_scope, Tokens tokens){
    static bool building_a_loop = false;

    // Check we don't have a nullptr scope
    checkNullScope(current_scope);

    // if(DEBUG_dump_scopes){
    //     current_scope->dump();
    // }
    if(DEBUG_show_lines){
        LOGDEBUG("[" + current_scope->getName() + "] " +
        (current_scope->getTruthiness()?"(TRUE) ":"(FALSE) ") +
        tokensToString(tokens));
    }

    // Check we don't have 0 tokens
    if(!validTokensLength(tokens)) return;

    // Finish Building a loop
    if(tokens.size() > 0 && tokens[0] == KW_END && isLoopType(tokens[1])){
        building_a_loop = false;
        Loop* current_scope_as_loop = (Loop*)(current_scope);
        current_scope_as_loop->addLine(tokens); // adds that LOOP END line before evaluating
        evaluateLoop(current_scope_as_loop);
        current_scope = current_scope_as_loop->getParent();
        return;
    }

    // Begin Building a loop
    if(isLoopType(tokens[0])){
        building_a_loop = true;
        processLoop(current_scope, tokens);
        return;
    }

    // Add lines to a loop
    if(building_a_loop){
        Loop* current_scope_as_loop = (Loop*)(current_scope);
        current_scope_as_loop->addLine(tokens);
        return;
    }

    // If/Elsif/Else checker
    if(isConditional(tokens)){
        processConditional(current_scope, tokens);
        return;
    }

    // If the scope is false, don't do it
    if(current_scope->getTruthiness() == false) return;

    // Other Keywords
    if(isKeyword(tokens[0])){
        processKeyword(current_scope, tokens);
        return;
    }

    // Elementary print handling
    if(tokens[0] == "Print"){
        return _print(current_scope, tokens);
    }
    if(tokens[0] == "Println"){
        return _println(current_scope, tokens);
    }

    // Variable Initialization
    if(isPrimType(tokens[0])){
        // Incomplete initialization: No variable name
        Variable variable = initVariable(current_scope, tokens);
        current_scope->addVariable(variable);

        // If we're just initializing a variable, we're done
        if(tokens.size() < 3){
            return;
        }

        // But if we want to add a value...
        Tokens shifted_tokens = shiftTokens(tokens, 1); // So we just get the variable name
        return interpret_tokens(current_scope, shifted_tokens); // Recurse that same line so we can evaluate the expression
    }

    // Variable assignment
    if(current_scope->hasVariableRecursive(tokens[0])){

        if(tokens.size() < 2) ERROR(SyntaxErrorIncompleteStatement);

        // Variable variable = Variable();
        // bool has_variable = current_scope->getVariableRecursive(tokens[0], variable);
        bool has_variable = current_scope->hasVariableRecursive(tokens[0]);

        if(!has_variable){
            ERROR(SyntaxErrorUnrecognizedObject);
        }

        if(tokens.size() < 2){
            ERROR(SyntaxErrorIncompleteStatement);
        }

        // variable = evaluateExpression(current_scope, tokens);
        evaluateExpression(current_scope, tokens);
        // current_scope->updateVariableRecursive(tokens[0], variable);
        return;
    }
    
    // Function calls
    // TODO: Move this all to expressions and just call that code?
    if(current_scope->hasScopeRecursive(tokens[0])){
        evaluateExpression(current_scope, tokens);
    }
}