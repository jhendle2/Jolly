#include "function_builder.hpp"
#include "errors.hpp"
#include "keywords.hpp"
#include "logging.hpp"

bool tokensIsFunctionHeader(Tokens tokens, std::string& function_name){
    if(tokens.size() < 1){
        return false;
    }
    
    if(tokens[0] == KW_FUNCTION){
        if(tokens.size() < 2){
            ERROR(SyntaxErrorIncompleteStatement);
        }
        function_name = tokens[1];
        return true;
    }
    return false;
}
bool tokensIsFunctionCloser(Tokens tokens, std::string function_name){
    if(tokens.size() < 1){
        return false;
    }
    
    if(tokens[0] == KW_END){
        if(tokens.size() < 2){
            ERROR(SyntaxErrorIncompleteStatement);
        }
        if(tokens[1] == function_name){
            return true;
        }
    }
    return false;
}

struct FunctionsLinesPair LocateFunctionsAndLines(std::string filename){
    std::vector<struct Line> file_as_lines = readFileAsLines(filename);

    // First pass to isolate functions
    std::unordered_map<std::string, struct FunctionBlock> functions;
    std::vector<Tokens> lines_as_tokens;

    std::string last_function_name = "";
    bool inside_function_block = false;
    for(int i = 0; i<(int)file_as_lines.size(); i++){
        DEBUG_last_line = file_as_lines[i];
        Tokens tokens = tokenizeLine(file_as_lines[i].line);
        if(LOGLEVEL == LOGLEVELDEBUG) std::cout<<file_as_lines[i].line_number<<" - "<<tokensToString(tokens)<<"\n";
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

    if(LOGLEVEL == LOGLEVELDEBUG){
        std::cout<<"\n";

        std::cout<<"found ("<<functions.size()<<") functions:\n";
        for(auto pair : functions){
            std::cout<<pair.first<<" with ("<<pair.second.lines.size()<<") lines\n";
            for(auto line : pair.second.lines){
                std::cout<<"\t\t** "<<tokensToString(line)<<"\n";
            }
        }
        std::cout<<"\n";

        std::cout<<"found ("<<lines_as_tokens.size()<<") lines:\n";
        for(Tokens tokens : lines_as_tokens){
            std::cout<<tokensToString(tokens)<<"\n";
        }
        std::cout<<"\n";
    }
    
    struct FunctionsLinesPair out_pair{
        lines_as_tokens,
        file_as_lines,
        functions
    };

    return out_pair;
}