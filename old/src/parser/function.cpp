#include "function.hpp"
#include "parser.hpp"
#include "general_utils.hpp"
#include "errors.hpp"

Function::Function(std::string function_name) : Scope(function_name, SCOPE_FUNCTION){
    this->return_type = TYPE_NOTHING;
    // addVariable("return", Variable());
}

Function::Function(std::string function_name, enum ObjectType return_type) : Scope(function_name, SCOPE_FUNCTION){
    this->return_type = return_type;
    // addVariable("return", Variable());
}

void Function::addParam(std::string name, Variable param){
    addVariable(name, param);
}

void Function::addLine(std::string line){
    this->unprocessed_lines.push_back(line);
}

// All return variables are named "func_name.return"
void Function::setReturnVariable(Variable return_variable){
    updateVariable(this->name + ".return", return_variable);
}

void Function::dump(){
    std::cout<<"\n===========FUNCTION("<<name<<")===========\n";
    std::cout<<"##RETURN_TYPE: "<<typeToString(getReturnType())<<"\n";

    if(parent != nullptr) std::cout<<"PARENT SCOPE: "<<parent->getName()<<"\n";
    else std::cout<<"NO PARENT!\n";

    std::cout<<"##VARIABLES##:\n";
    variables.dump(); std::cout<<"\n\n";
    
    std::cout<<"##UNPROCESSED LINES##:\n";
    std::cout<<"\n------------------------------------------\n";
    int i = 0;
    for(std::string line : unprocessed_lines){
        std::cout<<(i++)<<" - "<<line<<"\n";
    }
    std::cout<<"\n------------------------------------------\n";

    std::cout<<"##SCOPES##:\n";
    std::cout<<"\n------------------------------------------\n";
    for(auto pair : scopes){
        std::cout<<"* "<<pair.second->getName()<<" <"<<scopeTypeToString(pair.second->getScopeType())<<">\n";
    }
    std::cout<<"\n==========================================\n";
}

void Function::dumpRecursive(){
    std::cout<<"{{{{{{{{{{{{{{{{{{{{{{{{\n";
    dump();

    for(auto pair : scopes){
        std::cout<<"\n";
        pair.second->dumpRecursive();
    }

    std::cout<<"}}}}}}}}}}}}}}}}}}}}}}}}\n";
}

enum ObjectType Function::getReturnType(){
    return return_type;
}
// Process the function filling variables and internal scopes
static void evaluate_function(Function* func){
    // TODO: Implement this better. This just caps all fucntions at the recursion depth limit.
    static int recursion_step = 0;
    if( (recursion_step++) == RECURSIONDEPTHLIMIT) SAFEERROROUT(func, ParseErrorRecursionLimitReached, func->getName());

    // func->unprocessed_lines.erase(func->unprocessed_lines.begin() + (func->unprocessed_lines.size() - 1) );
    // func->unprocessed_lines.erase(func->unprocessed_lines.begin());

    // TODO: would be faster if you had a cached params list to compare a new params list with
    // compare(OLD PARAMS, NEW PARAMS) --> if different, re-run this function. Else return the return variable

    Scope* current_scope = (Scope*)func;
    std::string local_name = "unknown_function";
    for(std::string line : func->unprocessed_lines){
        std::vector<std::string> lineAsTokens = tokenizeLine(line);

        // ignores the keyword 'function' inside a function but keeps track of its local name for later
        if(lineAsTokens.size() > 1 && lineAsTokens[0] == "function"){
            local_name = lineAsTokens[1];
            continue;
        }
        
        // ignores the keyword 'end' inside a function if it is followed by the function's local name
        // this allows end if, etc. to still work properly
        if(lineAsTokens.size() > 1 && lineAsTokens[0] == "end" && lineAsTokens[1] == local_name){
            continue;
        }

        current_scope = buildVariableAndEvaluateExpressions(current_scope, lineAsTokens);
    }
}

Variable Function::getReturnVariable(){
    Variable return_variable = Variable();
    // bool has_return_variable = getVariableRecursive("return", return_variable);
    getVariableRecursive("return", return_variable);
    return return_variable;
}

Variable returnFunction(Function* func){
    evaluate_function(func);
    Variable return_variable = func->getReturnVariable();
    return return_variable;
}