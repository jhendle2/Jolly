#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "debug.hpp"
#include "errors.hpp"
#include "file_reader.hpp"
#include "types.hpp"
#include "tokens.hpp"

#include "function_builder.hpp"

void Interpret(std::string filename){
    std::vector<struct Line> file_as_lines = readFileAsLines(filename);

    // First pass to isolate functions
    std::unordered_map<std::string, struct FunctionBlock> functions;
    std::vector<Tokens> lines_as_tokens;

    std::string last_function_name = "";
    bool inside_function_block = false;
    for(int i = 0; i<(int)file_as_lines.size(); i++){
        DEBUG_last_line = file_as_lines[i];
        Tokens tokens = tokenizeLine(file_as_lines[i].line);
        std::cout<<file_as_lines[i].line_number<<" - "<<tokensToString(tokens)<<"\n";
        if(tokensIsFunctionHeader(tokens, last_function_name)){
            if(inside_function_block){
                ERROR(ParseWarningNestedFunctions);
            }
            struct FunctionBlock new_function;
            new_function.name = last_function_name;
            new_function.lines.push_back(tokens);
            functions.insert({last_function_name, new_function});
            inside_function_block = true;
            continue;
        }

        if(tokensIsFunctionCloser(tokens, last_function_name)){
            functions[last_function_name].lines.push_back(tokens);
            inside_function_block = false;
            continue;
        }

        if(inside_function_block){
            functions[last_function_name].lines.push_back(tokens);
        }
        else{
            lines_as_tokens.push_back(tokens);
        }
    }
    std::cout<<"\n";

    std::cout<<"found ("<<functions.size()<<") functions:\n";
    for(auto pair : functions){
        std::cout<<pair.first<<" with ("<<pair.second.lines.size()<<") lines\n";
    }
    std::cout<<"\n";

    std::cout<<"found ("<<lines_as_tokens.size()<<") lines:\n";
    for(Tokens tokens : lines_as_tokens){
        std::cout<<tokensToString(tokens)<<"\n";
    }
    std::cout<<"\n";
}

int main(int argc, char** argv){
    NOTE("Starting Smile-Parser");

    std::string filename = std::string(argv[1]);
    Interpret(filename);

    // std::string line = "Hello this (is) \'a+b\' c++ \"test\" \'line\'.";
    // Tokens line_as_tokens = tokenizeLine(line);

    // for(std::string token : line_as_tokens){
    //     std::cout<<"["<<token<<"] ";
    // }

    std::cout<<"\n";
    return 0;
}