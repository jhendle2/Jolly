#include <iostream>
#include <algorithm>
#include <iostream>
#include <fstream>

#include "file_reader.hpp"

static void removeComments(std::string& in){
    int comment_index = in.find('#');

    if(comment_index >= 0)
        in = in.substr(0,comment_index);
}

static void removeNewLine(std::string& in){
    in.erase(std::remove(in.begin(), in.end(), '\n'), in.end());
    in.erase(std::remove(in.begin(), in.end(), '\r'), in.end());
}

static void removeSpaces(std::string& in){
    int i;
    for(i = 0; i<(int)in.length(); i++){
        if(in.at(i) != '\t' && in.at(i) != ' ') break;
    }
    in = in.substr(i);
}

static bool lastCharacterIsLineExtension(std::string in){
    if(in.length() == 0) return false;
    if(in.at(in.length()-1)=='\\') return true;
    return false;
}

static bool isBlankLine(std::string in){
    for(int i = 0; i<(int)in.length(); i++){
        if(in.at(i) != ' ' && in.at(i) != '\t'){
            return false;
        }
    } return true;
}

std::string lineToString(Line line){
    std::string out = std::to_string(line.line_number) + " - " + line.line;
    return out;
}


std::vector<Line> readFileAsLines(std::string file_path){
    std::vector<Line> lines;
    std::fstream newfile;
    newfile.open(file_path, std::ios::in); //open a file to perform read operation using file object
    if (newfile.is_open()){   //checking whether the file is open
        std::string tp;
        int line_number = 1;
        bool last_line_had_line_extension = false;
        while(getline(newfile, tp)){ //read data from file object and put it into string.
            removeNewLine(tp);
            removeComments(tp);
            removeSpaces(tp);

            if(!isBlankLine(tp)){
                if(last_line_had_line_extension){
                    std::string last_line = lines.back().line;
                    int last_line_number = lines.back().line_number;
                    lines.pop_back();
                    last_line = last_line.substr(0, last_line.length()-1);
                    last_line += " " + tp;
                    last_line_had_line_extension = false;
                    lines.push_back({last_line_number, last_line});
                }
                else{
                    lines.push_back({line_number, tp});
                }
                last_line_had_line_extension = lastCharacterIsLineExtension(tp);
            }
            line_number++;
        }
        newfile.close(); //close the file object.
    }
    return lines;
}

// Isolates a file_name from a larger file_path
// ex: dir/test.jolly -> test
std::string fileName(std::string file_path){
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

bool endsInJollyExtension(const std::string& str_in){
    std::string extension = ".jolly";
    int extension_length = (int)extension.length();
    if((int)str_in.length() < (extension_length + 1)) return false;

    int start_index = str_in.length() - extension_length;
    int end_index = str_in.length();
    std::string str_in_substr = str_in.substr(start_index, end_index);
    if(str_in_substr == extension) return true;
    return false;
}