#include "token.h"

Token::Token() {
    type = undefined;
}
Token::Token(TokenType given_type) {
    type = given_type;
}

void Token::set_symbol_value(char given_value) {
    symbol_value = given_value;
    if(type == symbol) {
        priority = PriorityMap[given_value];
    }
}

ostream& operator<<(ostream& os, const Token& token) {
    if(token.type == operand)
        os << TokenTypes[token.type] << " token with value " << token.operand_value << "\n";
    else
        os << TokenTypes[token.type] << " token with value '" << token.symbol_value << "' (priority " << token.priority << ")\n";
    return os;
}

bool is_parenthesis_char(char exp_char) {
    return exp_char == '(' || exp_char == ')';
}

bool is_operand_char(char exp_char) {
    return isdigit(exp_char) || exp_char == '.';
}

void get_operand_starting_at_location(char* expression, int size, int exp_location, float *operand, int *end_location) {
    char op_buffer[size];
    int op_buffer_location = 0;

    // ignore any spaces before the operand
    while(expression[exp_location] == ' ')
        exp_location++;

    // get the characters of the operand
    while(is_operand_char(expression[exp_location]) && exp_location < size) {
        op_buffer[op_buffer_location] = expression[exp_location];
        op_buffer_location++;
        exp_location++;
    }
    if(op_buffer_location == 0)
        return;

    op_buffer[op_buffer_location] = '\0';

    // write back the returns
    *operand = (float) atof(op_buffer);
    *end_location = exp_location;
}

std::vector<Token> tokenize(char *expression, int size) {
    std::vector<Token> tokens;
    int exp_location = 0;
    bool close_after_operand = false;

    while(exp_location < size) {
        while(expression[exp_location] == ' ')
            exp_location++;

        char given_char = expression[exp_location];

        if(given_char == '\0')
            break;

        if(is_operand_char(given_char)) {
            // is it a digit?
            float value;
            get_operand_starting_at_location(expression, size, exp_location, &value, &exp_location);
            Token new_token (operand);
            new_token.operand_value = value;
            tokens.push_back(new_token);

            if(close_after_operand) {
                // add closing parenthesis
                Token close_paren (symbol);
                close_paren.symbol_value = ')';
                tokens.push_back(close_paren);
                close_after_operand = false;
            }
        } else {
            // it's a symbol

            // if it's a '-', it could be a negation of a first operand in an expression;
            // if there's no previous symbol, or it's '(', add a parenthesis and a 0 operand to the tokens
            if(given_char == '-' && (tokens.size() == 0 || (tokens.back().type == symbol && tokens.back().symbol_value == '('))) {
                // add parenthesis
                Token open_paren (symbol);
                open_paren.symbol_value = '(';
                tokens.push_back(open_paren);

                // add a zero
                Token zero_op (operand);
                zero_op.operand_value = 0;
                tokens.push_back(zero_op);

                close_after_operand = true;
            }

            Token new_token (symbol);
            new_token.set_symbol_value(given_char);
            tokens.push_back(new_token);
            exp_location++;
        }
    }

    return tokens;
}