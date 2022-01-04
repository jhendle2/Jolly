#include <iostream>
#include <string>
#include <vector>

#include "variable.hpp"
#include "number.hpp"
#include "parser.hpp"
#include "operators.hpp"
#include "file_manager.hpp"

int main(int argc, char** argv){

    /*
    // std::string test_line1 = "String s1 = \"hello\"";
    std::string test_line1 = "Number x = 5";
    // std::string test_line2 = "String s2 = \"world\"";
    std::string test_line2 = "Number y = 8";
    std::vector<std::string> tokens1 = tokenizeLine(test_line1);
    std::vector<std::string> tokens2 = tokenizeLine(test_line2);

    // Variable var1 = buildVariableFromTokens(tokens1);
    // std::cout << var1.toString() << " + ";
    // Variable var2 = buildVariableFromTokens(tokens2);
    // std::cout << var2.toString() << " = ";
    // var1.merge(var2);
    // std::cout << var1.toString() << "\n";

    buildVariableFromTokensAndAdd(tokens1);
    buildVariableFromTokensAndAdd(tokens2);
    dumpVariables();
    Variable z = getVariable("x");
    Variable w = getVariable("y");
    z.merge(w);
    std::cout << z.toString() << "\n";
    std::cout << w.toString() << "\n";
    dumpVariables();*/
    
    // Number n1 = Number(10);
    // Number n2 = Number(2);
    // Number n3 = n1.divide(n2);
    // std::cout<<"n1="<<n1.toString()<<"\n";
    // std::cout<<"n2="<<n2.toString()<<"\n";
    // std::cout<<"n3="<<n3.toString()<<"\n";

    // std::string test_line1 = "3 ^ 2 == 9";
    // std::vector<std::string> tokens1 = tokenizeLine(test_line1);

    // Variable result = evaluate(tokens1);
    // std::cout<<"result="<<result.toString()<<"\n";

    // Number a(5);
    // Number b(6);
    // Variable a2 = a;
    // Variable b2 = b;
    // a2.addEq(b);

    // std::cout<<a2.toString()<<" "<<b2.toString()<<"\n";

    /*
    std::string line1 = "Number a = 1";
    std::string line2 = "Number b = 5";
    std::string line3 = "Number c = a + b";
    std::string line4 = "Number d";
    std::string line5 = "d = c";

    std::vector<std::string> tokens1 = tokenizeLine(line1);
    std::vector<std::string> tokens2 = tokenizeLine(line2);
    std::vector<std::string> tokens3 = tokenizeLine(line3);
    std::vector<std::string> tokens4 = tokenizeLine(line4);
    std::vector<std::string> tokens5 = tokenizeLine(line5);

    buildVariableAndEvaluateExpressions(tokens1);
    buildVariableAndEvaluateExpressions(tokens2);
    buildVariableAndEvaluateExpressions(tokens3);
    buildVariableAndEvaluateExpressions(tokens4);
    dumpVariables();

    buildVariableAndEvaluateExpressions(tokens5);

    dumpVariables();
    */

    std::string filename = std::string(argv[1]);

    std::vector<std::string> file_as_lines = readFileAsLines(filename);
    // for(std::string line : file_as_lines){
    //     std::cout<< line <<"\n";
    // }

    for(std::string line : file_as_lines){
        std::vector<std::string> lineAsTokens = tokenizeLine(line);
        // for(std::string token : lineAsTokens){
        //     std::cout<<"["<<token<<"] ";
        // }
        // std::cout<<"\n";
        
        buildVariableAndEvaluateExpressions(lineAsTokens);
    }

    // dumpVariables();
    std::cout<<"\n";
    return 0;
}