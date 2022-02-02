// #include <stdlib.h>

#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "file_reader.hpp"
#include "tokens_lines.hpp"

#include "scope.hpp"
#include "scope_builder.hpp"

// Isolates a file_name from a larger file_path
// ex: dir/test.jolly -> test
static std::string fileName(std::string file_path){
    if(file_path.length() < 2) return "invalid_name";

    file_path = file_path.substr(0, file_path.find(".jolly"));

    int i;
    for(i = file_path.length() - 1; i >= 0; i--){
        char atchar = file_path.at(i);
        
        // We hit a directory
        if(atchar == '/'){
            i++;
            break;
        }

    }

    return file_path.substr(i);
}

static ScopePtr processFile(std::string file_path){
    std::vector<Line> file_as_lines = readFileAsLines(file_path);

    std::string file_name = fileName(file_path);
    ScopePtr master_scope = Scope::create(file_name, ScopeClass);
    ScopePtr current_scope = master_scope;

    for(auto line : file_as_lines){
        std::cout << "(" << line.line_number << ") " << line.line << "\n";

        Tokens tokens = tokenizeLine(line.line);
        if(isCloseScope(tokens[0])){

            if(current_scope->getParent() == nullptr){
                std::cout << "!! Critical Scope Error - No Parent\n";
                exit(EXIT_FAILURE);
            }

            current_scope = current_scope->getParent();
            // No continue here so that elsif/else can both
            // close and open new scopes
        }

        if(isOpenScope(tokens[0])){
            
            current_scope->addLine(line);
            ScopePtr new_open_scope = buildScopeFromTokens(tokens);
            current_scope->addChild(new_open_scope);
            current_scope = new_open_scope;

            continue;
        }

        if(!isCloseScope(tokens[0]) && !isOpenScope(tokens[0])){
            current_scope->addLine(line);
        }
    }

    return master_scope;
}

int main(int argc, char** argv){
    std::cout << "\nJolly v0.0.6\n\n";

    /*
    // std::shared_ptr<Scope> master_scope = Scope::create("master", ScopeFunction);
    // std::shared_ptr<Scope> child_scope = Scope::create("child", ScopeWhile);
    // std::shared_ptr<Scope> child2_scope = Scope::create("child2", ScopeWhile);
    // std::shared_ptr<Scope> child3_scope = Scope::create("child3", ScopeWhile);

    // master_scope->addChild(child_scope);
    // child_scope->addChild(child2_scope);
    // master_scope->addChild(child3_scope);

    // master_scope->tree(0);
    */

    ScopePtr master_scope = processFile(argv[1]);

    std::cout << "\n";
    master_scope->tree();
    std::cout << "\n";

    std::cout << "\n";
    master_scope->dumpRecursive();
    std::cout << "\n";

    std::cout<<"\n";
    return EXIT_SUCCESS;
}