#pragma once
#include <iostream>
#include <string>
#include <ctype.h>
#include <stdlib.h>
#include <vector>
#include <map>

using namespace std;

enum TokenType { operand, symbol, undefined };
const string TokenTypes[] = { "Operand", "Symbol", "Undefined" };
static std::map<char, int> PriorityMap = {
    {'(', 0}, // for the postfix notation, parenthesis do not have priority
    {')', 0},
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2},
    {'^', 3}
};

class Token {
    public:
        TokenType type;
        float operand_value = 0.0;
        char symbol_value = 0;
        unsigned short int priority = 0;

        Token();
        Token(TokenType given_type);
        void set_symbol_value(char given_value);
};

ostream& operator<<(ostream& os, const Token& token);
bool is_operand_char(char exp_char);
void get_operand_starting_at_location(char* expression, int size, int exp_location, float *operand, int *end_location);
std::vector<Token> tokenize(char *expression, int size);
