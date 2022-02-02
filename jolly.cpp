#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "file_reader.hpp"
#include "tokens_lines.hpp"
#include "scope.hpp"

static void processFile(std::string file_path){
    std::vector<Line> file_as_lines = readFileAsLines(file_path);

    for(auto line : file_as_lines){
        std::cout << "(" << line.line_number << ") " << line.line << "\n";
    }
}

int main(int argc, char** argv){
    std::cout << "\nJolly v0.0.6\n\n";

    // std::shared_ptr<Scope> master_scope = Scope::create("master", ScopeFunction);
    // std::shared_ptr<Scope> child_scope = Scope::create("child", ScopeWhile);
    // std::shared_ptr<Scope> child2_scope = Scope::create("child2", ScopeWhile);
    // std::shared_ptr<Scope> child3_scope = Scope::create("child3", ScopeWhile);

    // master_scope->addChild(child_scope);
    // child_scope->addChild(child2_scope);
    // master_scope->addChild(child3_scope);

    // master_scope->tree(0);

    processFile(argv[1]);

    std::cout<<"\n";
    return EXIT_SUCCESS;
}