#include <iostream>

#include "variable_table.hpp"

std::unordered_map<std::string, Variable> VariableTable;

void setVariable(std::string name, Variable var){
    VariableTable.insert({name, var});
}

Variable getVariable(std::string name){
    return VariableTable.at(name);
}

bool isKnownVariable(std::string name){
    return VariableTable.count(name) > 0;
}

void updateVariable(std::string name, Variable value){
    VariableTable[name] = value;
}

void updateVariable(std::string name, std::string value_expression){
    VariableTable[name].setFromString(value_expression);
}

void setVariableFromOtherVariable(std::string name, std::string other_name){
    VariableTable[name] = VariableTable[other_name];
}

void updateVariableFromOtherVariable(std::string name, std::string other_name){
    VariableTable[name] = VariableTable[other_name];
}

void dumpVariables(){
    std::cout<<"--Variables--\n";
    for(auto pair : VariableTable){
        std::cout << pair.first << " " << pair.second.dump() << "\n";
    }
    std::cout<<"--End Variables--\n";
}