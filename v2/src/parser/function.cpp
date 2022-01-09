#include "function.hpp"
#include "general_utils.hpp"
#include "parser.hpp"
#include "errors.hpp"

Function::Function() : Scope("unnamed_function", SCOPE_FUNCTION){
    this->return_type = TYPE_NOTHING;
    this->return_variable = Variable(TYPE_NOTHING);
    this->has_been_evaluated = false;
    function_scope = nullptr;
}

Function::Function(std::string name) : Scope(name, SCOPE_FUNCTION){
    this->return_type = TYPE_NOTHING;
    this->return_variable = Variable(TYPE_NOTHING);
    this->has_been_evaluated = false;
    function_scope = nullptr;
}

Function::Function(std::string name, enum ObjectType return_type) : Scope(name, SCOPE_FUNCTION){
    this->name = name;
    this->return_type = return_type;
    this->return_variable = Variable(return_type);
    this->has_been_evaluated = false;
    function_scope = nullptr;
}

Function::~Function(){
    if(function_scope != nullptr)
        delete function_scope;
}

enum ObjectType Function::getReturnType(){
    return return_type;
}
Variable Function::getReturnVariable(){
    return return_variable;
}

void Function::dump(){
    std::cout<<"\n===========FUNCTION("<<name<<")===========\n";
    if(parent != nullptr) std::cout<<"PARENT FUNCTION: "<<parent->getName()<<"\n";
    else std::cout<<"NO PARENT!\n";
    std::cout<<"##RETURNS: "<<typeToString(return_type)<<"\n";
    std::cout<<"##VARIABLES##:\n";
    variables.dump(); std::cout<<"\n\n";
    std::cout<<"##LINES:\n";
    std::cout<<"\n------------------------------------------\n";
    for(auto line : lines){
        std::cout<<"> "<<line<<"\n";
    }
    std::cout<<"##SCOPES##:\n";
    std::cout<<"\n------------------------------------------\n";
    for(auto pair : scopes){
        std::cout<<"* "<<pair.second->getName()<<"\n";
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


int Function::numLines(){
    return lines.size();
}
void Function::addLine(std::string line){
    lines.push_back(line);
}
void Function::popLine(int index){
    lines.erase(lines.begin());
}
std::string Function::getLine(int index){
    return lines[index];
}
std::vector<std::string> Function::getLineAsTokens(int index){
    return tokenizeLine(lines[index]);
}
std::vector<std::string> Function::getLines(){
    return lines;
}

void Function::addParameter(Object param){
    params.push_back(param);
}

void Function::addParameter(std::string name, Object value){
    value.setName(name);
    params.push_back(value);
}

Object Function::getParameter(std::string name){
    return params[getParameterIndex(name)];
}

Object Function::getParameter(int index){
    return params[index];
}

void Function::setParameter(std::string name, Object value){
    params[getParameterIndex(name)] = value;
}

int Function::getParameterIndex(std::string name){
    int index = 0;
    for(Object param : params){
        std::string parameter = param.getName();
        if(parameter == name) return index;
        index++;
    }
    return -1;
}

// Creates a new function and links it to its parent scope
Function* initializeFunction(Scope* parent, std::string name){
    return new Function(name);
}
// Function* initializeFunction(Scope* parent, std::vector<std::string> tokens){
//     std::string function_name = tokens[1];
//     Function* new_function = new Function(function_name);  
//     addScopeToScope(parent, new_function);
//     return new_function;
// }

bool Function::hasBeenEvaluated(){
    return has_been_evaluated;
}

void Function::setFunctionScope(Scope* function_scope){
    this->function_scope = function_scope;
}

Scope* Function::getFunctionScope(){
    return function_scope;
}

Variable returnFunction(Function* function){
    // bool has_been_evaluated = function->hasBeenEvaluated();

    // If the return value has already been crunched, just return it (BUT WE NEED TO CHANGE PARAMETERS)
    if(function->hasBeenEvaluated()){
        // TODO: ADD CODE TO UPDATE ALL VARIABLES AND REINTERPRET IF PARAMS CHANGE
        return function->getReturnVariable();
    }

    // Else, we build a new Scope for the function,
    // evaluate the scope to get our return variable,
    // and return the variable if it exists
    // or return a Nothing variable for a void function
    buildFunctionFromItsLines(function);
    Scope* function_scope = function->getScope(function->getName() + ".scope");
    bool return_value_exists = function_scope->isKnownVariable(function_scope->getName() + ".return");
    if(!return_value_exists){
        SAFEERROROUT(function, ParseDebugNoReturnVariableSet, function->getName());
    }

    Variable return_variable = function_scope->getVariable(function_scope->getName() + ".return");
    function->setHasBeenEvaluated();
    return return_variable;

    // else{
    //     Scope* function_scope = new Scope(name + ".scope");
    //     for(std::string line : lines){
    //         function_scope = buildVariableAndEvaluateExpressions(function_scope, tokenizeLine(line));
    //     }
    //     bool has_been_evaluated = function_scope->getVariableRecursive(name+".return", return_variable);
        
    //     if(has_been_evaluated) return return_variable;
    //     else return Variable();
    // }
}

void Function::setHasBeenEvaluated(){
    this->has_been_evaluated = true;
}

void Function::clearHasBeenEvaluated(){
    this->has_been_evaluated = false;
}

// If a function hasn't had its scope built (variable table, function table, etc.)
// then parse all of its lines and build the scope
// otherwise, don't rebuild it (UNLESS THERE ARE NEW PARAMETERS)
void buildFunctionFromItsLines(Function* function){
    if(function->hasBeenEvaluated()) return; // add a thing here that checks if parameters are "dirty"

    Scope* function_scope = new Scope("scope");
    addScopeToScope(function, function_scope);

    Scope* temp_scope = function_scope;
    for(std::string line : function->getLines()){
        std::vector<std::string> tokens = tokenizeLine(line);
        if(tokens[0] == "function"){
            // WARNING(ParseWarningNestedFunctions, line);
            continue;
        }
        temp_scope = buildVariableAndEvaluateExpressions(temp_scope, tokenizeLine(line));
    }
    function->setHasBeenEvaluated();
}