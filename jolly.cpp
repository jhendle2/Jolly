// #include <stdlib.h>

#include <iostream>
#include <string>
#include <memory>
#include <vector>

// #include "file_reader.hpp"
#include "keywords.hpp"
#include "tokens_lines.hpp"

#include "scope.hpp"
// #include "scope_builder.hpp"

#include "parser.hpp"
#include "logging.hpp"
#include "errors.hpp"

static ScopePtr processFile(std::string file_path){
    ScopePtr file_as_tree = buildTreeFromFile(file_path);

    if(LOGLEVEL == LOGLEVELDEBUG){
        std::cout<<"\n";
        file_as_tree->treeLines();
        std::cout<<"\n";
    }

    parseTree(file_as_tree);

    if(LOGLEVEL == LOGLEVELDEBUG) file_as_tree->treeLines();
    if(LOGLEVEL == LOGLEVELDEBUG) file_as_tree->dumpRecursive();

    return file_as_tree;
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
        processFile(filename);
    }
    else{
        LOGERROR("No files to process!");
    }

    if(LOGLEVEL > LOGLEVELNONE) TITLE("All done.");

    std::cout<<"\n";
    return 0;
}