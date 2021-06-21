#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <stdlib.h>
#include <vector>
#include <stack>
#include <map>
#include <time.h>
#include <numeric>
#include "aux.h"

using namespace std;


void intro() {
    cout << "\n";
    cout << "-------------- Welcome to the parser calculator! --------------\n";
    cout << "|                                                             |\n";
    cout << "| Enter an expression using the operators +, -, *, /, ^, (, ) |\n";
    cout << "|                                                             |\n";
    cout << "|  - The default engine uses an infix to postfix conversion   |\n";
    cout << "|      (enter 'p' to go back to it)                           |\n";
    cout << "|  - Enter 's' for parsing using a syntax tree                |\n";
    cout << "|  - Enter 'h' for a detailed comparison of both parsers      |\n";
    cout << "|  - Enter 'e' to exit                                        |\n";
    cout << "|                                                             |\n";
    cout << "---------------------------------------------------------------\n";
}

void process_expression(int mode, char *expression, int size) {
    // tokenize the expression
    std::vector<Token> tokens = tokenize(expression, size);

    if(tokens.size() == 0)
        return;
    
    // run it depending on the mode
    clock_t time_taken;
    float output_value;
    int ret_code;
    switch(mode) {
        case 0:
            ret_code = postfix_evaluate(tokens, &output_value, &time_taken);
            if(ret_code == 0)
                cout << "[p] >> Output: " << output_value << " (in " << clock_to_time(time_taken) << "ns)\n";
            else
                cout << "[p] >> Expression syntax error (e.g. unbalanced parenthesis or unparsable operator)\n";
            break;
        case 1:
            ret_code = syntax_tree_evaluate(tokens, &output_value, &time_taken);
            if(ret_code == 0)
                cout << "[s] >> Output: " << output_value << " (in " << clock_to_time(time_taken) << "ns)\n";
            else
                cout << "[s] >> Expression syntax error - in the syntax tree mode, expressions must be fully parenthesized\n";
            break;
        case 2:
            clock_t time_taken_p, time_taken_s;
            float output_value_p, output_value_s;
            int ret_code_p, ret_code_s;
            ret_code_p = postfix_evaluate(tokens, &output_value_p, &time_taken_p);
            ret_code_s = syntax_tree_evaluate(tokens, &output_value_s, &time_taken_s);

            if(ret_code_p == 0 && ret_code_s == 0)
                cout << "[h] >> Postfix: { success=true, value=" << output_value_p << ", time=" << clock_to_time(time_taken_p) << "ns }; " << "Syntax: { success=true, output_value=" << output_value_s << ", time=" << clock_to_time(time_taken_s) << "ns }" << "\n";
            if(ret_code_p != 0 && ret_code_s == 0)
                cout << "[h] >> Postfix: { success=false, time=" << clock_to_time(time_taken_p) << "ns }; " << "Syntax: { success=true, output_value=" << output_value_s << ", time=" << clock_to_time(time_taken_s) << "ns }" << "\n";
            if(ret_code_p == 0 && ret_code_s != 0)
                cout << "[h] >> Postfix: { success=true, value=" << output_value_p << ", time=" << clock_to_time(time_taken_p) << "ns }; " << "Syntax: { success=false, time=" << clock_to_time(time_taken_s) << "ns }" << "\n";
            if(ret_code_p != 0 && ret_code_s != 0)
                cout << "[h] >> Postfix: { success=false, time=" << clock_to_time(time_taken_p) << "ns }; " << "Syntax: { success=false, time=" << clock_to_time(time_taken_s) << "ns }" << "\n";
            break;
    }
}


int main() {
    intro();
    int expression_length = 1000;
    char expression[expression_length];
    int mode = 0;

    while(true) {
        switch(mode) {
            case 0:
                cout << "[p] ";
                break;
            case 1:
                cout << "[s] ";
                break;
            case 2:
                cout << "[h] ";
                break;
        }

        cout << ">> ";
        cin.getline(expression, expression_length);

        if(strcmp(expression, "") == 0)
            continue;

        if(strcmp(expression, "p") == 0) {
            mode = 0;
            cout << "[p] >> Changed mode to postfix parsing\n";
            continue;
        }

        if(strcmp(expression, "s") == 0) {
            mode = 1;
            cout << "[s] >> Changed mode to syntax tree parsing - expressions must be fully parenthesized in this mode!\n";
            continue;
        }

        if(strcmp(expression, "h") == 0) {
            mode = 2;
            cout << "[h] >> Changed mode to hybrid comparsion parsing\n";
            continue;
        }

        if(strcmp(expression, "e") == 0)
            return 0;

        process_expression(mode, expression, expression_length);
    }
}
