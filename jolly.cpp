#include <iostream>
#include <string>
#include <vector>

#include "file_manager.hpp"

#include "object.hpp"
#include "variable.hpp"
#include "boolean.hpp"
#include "character.hpp"
#include "number.hpp"
#include "string.hpp"

#include "function.hpp"
#include "object_table.hpp"
#include "parser.hpp"

/*int main(int argc, char** argv){
    
    
    // // std::string test_line1 = "String s1 = \"hello\"";
    // std::string test_line1 = "Number x = 5";
    // // std::string test_line2 = "String s2 = \"world\"";
    // std::string test_line2 = "Number y = 8";
    // std::vector<std::string> tokens1 = tokenizeLine(test_line1);
    // std::vector<std::string> tokens2 = tokenizeLine(test_line2);

    // // Variable var1 = buildVariableFromTokens(tokens1);
    // // std::cout << var1.toString() << " + ";
    // // Variable var2 = buildVariableFromTokens(tokens2);
    // // std::cout << var2.toString() << " = ";
    // // var1.merge(var2);
    // // std::cout << var1.toString() << "\n";

    // buildVariableFromTokensAndAdd(tokens1);
    // buildVariableFromTokensAndAdd(tokens2);
    // dumpVariables();
    // Variable z = getVariable("x");
    // Variable w = getVariable("y");
    // z.merge(w);
    // std::cout << z.toString() << "\n";
    // std::cout << w.toString() << "\n";
    // dumpVariables();
    
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

    // std::string line1 = "Number a = 1";
    // std::string line2 = "Number b = 5";
    // std::string line3 = "Number c = a + b";
    // std::string line4 = "Number d";
    // std::string line5 = "d = c";

    // std::vector<std::string> tokens1 = tokenizeLine(line1);
    // std::vector<std::string> tokens2 = tokenizeLine(line2);
    // std::vector<std::string> tokens3 = tokenizeLine(line3);
    // std::vector<std::string> tokens4 = tokenizeLine(line4);
    // std::vector<std::string> tokens5 = tokenizeLine(line5);

    // buildVariableAndEvaluateExpressions(tokens1);
    // buildVariableAndEvaluateExpressions(tokens2);
    // buildVariableAndEvaluateExpressions(tokens3);
    // buildVariableAndEvaluateExpressions(tokens4);
    // dumpVariables();

    // buildVariableAndEvaluateExpressions(tokens5);

    // dumpVariables();


    // std::string filename = std::string(argv[1]);

    // std::vector<std::string> file_as_lines = readFileAsLines(filename);

    // for(std::string line : file_as_lines){
    //     std::cout<< line <<"\n";
    // }

    // VariableTable gvt = VariableTable();

    // for(std::string line : file_as_lines){
    //     std::vector<std::string> lineAsTokens = tokenizeLine(line);
    //     for(std::string token : lineAsTokens){
    //         std::cout<<"["<<token<<"] ";
    //     }
    //     std::cout<<"\n";
        
    //     buildVariableAndEvaluateExpressions(gvt, lineAsTokens);
    //     gvt.dumpVariables();
    // }

    // gvt.dumpVariables();

    // Object o = Object(TYPE_BOOL);
    // o.setName("object_o");
    // o.dump();
    // std::cout<<"\n";

    // Variable v = Variable(5);
    // v.setName("variable_v");
    // v.dump();
    // std::cout<<"\n";

    // Variable w = Variable(6);
    // w.setName("variable_w");
    // w.dump();
    // std::cout<<"\n";

    // w.eq(v);
    // w.dump();
    // std::cout<<"\n";

    // Boolean b = Boolean(w.equality(v));
    // b.setName("variable_b");
    // b.dump();
    // std::cout<<"\n";

    // Character c = Character('X');
    // c.setName("character_c");
    // c.dump();
    // std::cout<<"\n";
    // char ch = c.getCharacter();
    // std::cout<<"c="<<ch<<"\n";

    // String s = String("hello");
    // s.dump();
}*/

int main(int argc, char** argv){

    std::string filename = std::string(argv[1]);

    std::vector<std::string> file_as_lines = readFileAsLines(filename);

    for(std::string line : file_as_lines){
        std::cout<< line <<"\n";
    }

    // Function func1 = Function("func1");
    // Function func2 = Function("func2");
    // addFunctionToFunction(func1, func2);
    Function mainScope = Function("mainScope");

    Function* current_scope = new Function("mainScope");
    for(std::string line : file_as_lines){
        std::vector<std::string> lineAsTokens = tokenizeLine(line);
        for(std::string token : lineAsTokens){
            std::cout<<"["<<token<<"] ";
        }
        std::cout<<"\n";
        
        current_scope = buildVariableAndEvaluateExpressions(current_scope, lineAsTokens);
        std::cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$"<<current_scope->getName()<<"\n";
    }

    // func1.dump();
    // func2.dump();
    std::cout<<"\n\n\n";
    current_scope->dumpRecursive();
    // Variable temp = Variable();
    // bool has_var_a = current_scope->getFunction("func1").getVariableRecursive("a", temp);
    // std::cout<<"Has_var_a="<<has_var_a<<"\n";
    // if(has_var_a) std::cout<<"a="<<temp.toString()<<"\n";
    // std::cout<<"\n";
    return 0;
}