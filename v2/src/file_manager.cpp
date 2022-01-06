#include <algorithm>

#include "file_manager.hpp"

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