#include <iostream>
#include <string>
#include <vector>

#include "file_manager.hpp"

#include "object.hpp"
#include "variable.hpp"
#include "boolean.hpp"
#include "character.hpp"
#include "number.hpp"
#include "string.hpp"

#include "general_utils.hpp"

#include "function.hpp"
#include "object_table.hpp"
#include "parser.hpp"

int main(int argc, char** argv){

    // std::string filename = std::string(argv[1]);

    // std::vector<std::string> file_as_lines = readFileAsLines(filename);

    // // for(std::string line : file_as_lines){
    // //     std::cout<< line <<"\n";
    // // }

    // Scope* main_scope = new Scope("mainScope");
    // Scope* current_scope = main_scope;
    // for(std::string line : file_as_lines){
    //     std::vector<std::string> lineAsTokens = tokenizeLine(line);
    //     // for(std::string token : lineAsTokens){
    //     //     std::cout<<"["<<token<<"] ";
    //     // }
    //     // std::cout<<"\n";
        
    //     current_scope = buildVariableAndEvaluateExpressions(current_scope, lineAsTokens);
    //     // std::cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$"<<current_scope->getName()<<"\n";
    // }

    // // std::cout<<"\n\n\n";
    // main_scope->dumpRecursive();

    std::string s = "'x'";
    s = stripQuotes(s);
    std::cout<<s<<"\n";
    Character c = Character("'c'");
    c.dump();

    std::cout<<"\n";
    return 0;
}