#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "debug.hpp"
#include "errors.hpp"
#include "logging.hpp"
#include "utils.hpp"
#include "file_reader.hpp"
#include "types.hpp"
#include "tokens.hpp"

#include "function_builder.hpp"
#include "function.hpp"
#include "interpreter.hpp"

void Interpret(std::string filename){
    LOGNOTE("Interpretering \"" + filename + "\"");

    struct FunctionsLinesPair functions_lines_pair = LocateFunctionsAndLines(filename);
    
    std::vector<Tokens> lines_as_tokens = functions_lines_pair.lines_as_tokens;
    std::vector<struct Line> file_as_lines = functions_lines_pair.file_as_lines;
    std::unordered_map<std::string, struct FunctionBlock> functions = functions_lines_pair.functions;

    Scope* main_scope = new Scope(dropExtension(filename));
    Scope* current_scope = main_scope;

    for(auto pair : functions){
        std::string function_name = pair.first;
        Function* func = new Function(function_name);
        func->setLines(pair.second);
        addScopeToScope(current_scope, func);
    }

    current_scope = main_scope;
    int index = 0;
    for(Tokens token_line : lines_as_tokens){
        DEBUG_last_line = file_as_lines[index++];
        interpret_tokens(current_scope, token_line); 
    }

    if(LOGLEVEL == LOGLEVELDEBUG) main_scope->dumpRecursive();

    delete main_scope;
}

int main(int argc, char** argv){
    LOGLEVEL = LOGLEVELNONE;
    if(LOGLEVEL > LOGLEVELNONE) TITLE("Starting Smile-Parser");

    // Set up our command line flags
    std::string filename = "";
    for(int i = 0; i<argc; i++){
        std::string flag = argv[i];

        if(flag == "--note") LOGLEVEL = LOGLEVELNOTE;
        else if(flag == "--error") LOGLEVEL = LOGLEVELERROR;
        else if(flag == "--warning") LOGLEVEL = LOGLEVELWARNING;
        else if(flag == "--debug") LOGLEVEL = LOGLEVELDEBUG;

        if(endsInJollyExtension(flag)){
            filename = flag;
        }
    }

    // As long as we were supplied a file, we should interpret it
    if(filename != ""){
        Interpret(filename);
    }
    else{
        LOGERROR("No files to process!");
    }

    if(LOGLEVEL > LOGLEVELNONE) TITLE("All done.");

    std::cout<<"\n";
    return 0;
}