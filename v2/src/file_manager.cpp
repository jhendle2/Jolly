#include <algorithm>

#include "file_manager.hpp"
#include "general_utils.hpp"
#include "parser_keywords.hpp"

static void removeComments(std::string& in){
    int comment_index = in.find('#');

    if(comment_index >= 0)
        in = in.substr(0,comment_index);
}

void removeNewLine(std::string& in){
    in.erase(std::remove(in.begin(), in.end(), '\n'), in.end());
    in.erase(std::remove(in.begin(), in.end(), '\r'), in.end());
}

static bool isBlankLine(std::string in){
    if(in == "") return true;

    int length = in.length();
    if(length > 2){
        char last_char = in.at(length-1);
        char second_to_last_char = in.at(length-2);

        if((last_char == ' ' && second_to_last_char == ' ') || last_char == '\t') return true;
    }
    else if(length > 1){
        char last_char = in.at(length-1);
        if(last_char == '\t') return true;
    }

    return false;
}

std::vector<std::string> readFileAsLines(std::string filename){
    std::vector<std::string> lines;
    std::fstream newfile;
    newfile.open(filename,std::ios::in); //open a file to perform read operation using file object
    if (newfile.is_open()){   //checking whether the file is open
        std::string tp;
        while(getline(newfile, tp)){ //read data from file object and put it into string.
            removeNewLine(tp);
            removeComments(tp);

            if(!isBlankLine(tp))
                lines.push_back(tp);
        }
        newfile.close(); //close the file object.
    }
    return lines;   
}

// TODO: This is gonna have awful complexity so we should make it do the job of 
// readFileAsLines() internally instead and take a filename instead of a vector of lines
std::vector<struct TokensBlock> readLinesAsLinesAndFunctions(std::vector<std::string> lines){
    std::vector<struct TokensBlock> lines_and_functions;
    struct TokensBlock temp_lines;
    temp_lines.type = BLOCK_LINES;

    for(std::string line : lines){
        std::vector<std::string> line_as_tokens = tokenizeLine(line);

        std::cout<<"\ttoken="<<line_as_tokens[0]<<"\n";
        enum ReservedKeyword keyword = getReservedKeyword(line_as_tokens[0]);

        if(keyword == RESERVED_FUNCTION){
            std::cout<<"\t\tRESERVED_FUNCTION\n";
            lines_and_functions.push_back(temp_lines);
            temp_lines.block_name = line_as_tokens[1];
            temp_lines.lines.clear();
            temp_lines.lines.push_back(line);
            temp_lines.type = BLOCK_FUNCTION;
        }

        else if(keyword == RESERVED_END){
            std::cout<<"\t\tRESERVED_END\n";
            temp_lines.lines.push_back(line);
            enum ReservedKeyword keyword_second = getReservedKeyword(line_as_tokens[1]);
            if(keyword_second != RESERVED_IF && temp_lines.type == BLOCK_FUNCTION){
                lines_and_functions.push_back(temp_lines);
                temp_lines.lines.clear();
                temp_lines.type = BLOCK_LINES;
            }
        }

        else if(keyword == RESERVED_INCLUDE){
            std::cout<<"\t\tRESERVED_INCLUDE\n";
            temp_lines.lines.push_back(line);
            temp_lines.block_name = line_as_tokens[1];
            temp_lines.lines.clear();
            temp_lines.lines.push_back(line);
            temp_lines.type = BLOCK_INCLUDE;
        }

        else{
            temp_lines.lines.push_back(line);
        }
    }

    if(temp_lines.lines.size() > 0){
        lines_and_functions.push_back(temp_lines);
    }

    return lines_and_functions;
}