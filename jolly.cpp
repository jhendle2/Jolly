#include <iostream>
#include <string>
#include <vector>

#include "file_manager.hpp"
#include "general_utils.hpp"
#include "errors.hpp"

#include "object.hpp"
#include "variable.hpp"
#include "boolean.hpp"
#include "character.hpp"
#include "number.hpp"
#include "string.hpp"

#include "function.hpp"
#include "object_table.hpp"
#include "parser.hpp"

// void _Test_Function(){
    
//     Scope* main_scope = new Scope("mainScope");
//     Function* f = new Function("test_function", TYPE_BOOL);
//     f->addLine("function test_function");
//     f->addLine("String s = \"Hello, World\"");
//     f->addLine("Character z = \'!\'");
//     f->addLine("s += z");
//     f->addLine("Println(s)");
//     f->addLine("yield s");
//     f->addLine("end test_function");

//     f->dump();
    
//     std::cout<<"AddScopeToScope\n";
//     addScopeToScope(main_scope, f);

//     std::cout<<"Now to Return\n";
//     Variable return_variable = returnFunction(f);

//     std::cout<<"Taking a Dump\n";
//     f->dumpRecursive();
//     std::cout<<"\n\n";
//     return_variable.dump();

// }

void InterpretOnePass(std::string filename){

    std::vector<std::string> file_as_lines = readFileAsLines(filename);

    for(std::string line : file_as_lines){
        std::cout<< line <<"\n";
    }

    Scope* main_scope = new Scope("mainScope");
    Scope* current_scope = main_scope;
    for(std::string line : file_as_lines){
        std::vector<std::string> lineAsTokens = tokenizeLine(line);
        // for(std::string token : lineAsTokens){
        //     std::cout<<"["<<token<<"] ";
        // }
        // std::cout<<"\n";
        
        current_scope = buildVariableAndEvaluateExpressions(current_scope, lineAsTokens);
        // std::cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$"<<current_scope->getName()<<"\n";
    }

    // std::cout<<"\n\n\n";
    // main_scope->dumpRecursive();

}

void InterpretTwoPass(std::string filename){
    NOTE("Starting Smile-Parser");

    std::vector<std::string> file_as_lines = readFileAsLines(filename);

    std::vector<struct readLinesStruct> lines_and_functions = readLinesAsLinesAndFunctions(file_as_lines);

    // for(readLinesStruct lines : lines_and_functions){
    //     std::cout<<"\n"<<(lines.is_function?"FUNC":"NOT A FUNC")<<"\n";
    //     for(std::string line : lines.lines){
    //         std::cout<< line <<"\n";
    //     }
    //     std::cout<<"\n###############\n\n";
    // }

    // Populate functions first
    std::string scope_name = dropFileExtension(filename);
    NOTE("Parsing scope: " + scope_name);
    Scope* main_scope = new Scope("file."+scope_name);
    main_scope->setMainScope(); // For setting up global variables
    Scope* current_scope = main_scope;
    for(readLinesStruct lines : lines_and_functions){
        if(lines.is_function){
            Function* f = new Function(lines.function_name, TYPE_BOOL);
            for(std::string line : lines.lines){
                f->addLine(line);
            }
            addScopeToScope(main_scope, f);
        }
        // else{
        //     for(std::string line : lines.lines){
        //         std::cout<< line <<"\n";
        //         std::vector<std::string> lineAsTokens = tokenizeLine(line);
        //         bool init_global_vars = true;
        //         current_scope = buildVariableAndEvaluateExpressions(current_scope, lineAsTokens, init_global_vars);
        //     }
        // }
    }

    // So functions are populated before the global vars
    for(readLinesStruct lines : lines_and_functions){
        if(!lines.is_function){
            for(std::string line : lines.lines){
                std::cout<< line <<"\n";
                std::vector<std::string> lineAsTokens = tokenizeLine(line);
                current_scope = buildVariableAndEvaluateExpressions(current_scope, lineAsTokens);
            }
        }
    }

    main_scope->dumpRecursive();
}

int main(int argc, char** argv){

    std::string filename = std::string(argv[1]);

    InterpretTwoPass(filename);

    std::cout<<"\n";
    return 0;
}