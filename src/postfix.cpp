#include "postfix.h"

int infix_to_postfix(std::vector<Token> infix_tokens, std::vector<Token> *postfix_tokens) {
    std::stack<Token> opstack;
    std::vector<Token> postfix;

    for(std::vector<Token>::iterator it = infix_tokens.begin() ; it != infix_tokens.end(); ++it) {
        if(it->type == operand) {
            postfix.push_back(*it);
        } else {
            // token is a symbol
            if(it->symbol_value == '(') {
                opstack.push(*it);
            } else if (it->symbol_value == ')') {
                if(opstack.empty())
                    return -1;

                Token op = opstack.top();
                opstack.pop();
                while(op.symbol_value != '(') {
                    postfix.push_back(op);

                    if(opstack.empty())
                        return -1;

                    op = opstack.top();
                    opstack.pop();
                }
            } else {
                Token op;
                while(!opstack.empty() && opstack.top().priority >= it->priority){
                    op = opstack.top();
                    opstack.pop();
                    postfix.push_back(op);
                }
                opstack.push(*it);
            }
        }
    }

    while(!opstack.empty()) {
        Token op = opstack.top();
        opstack.pop();
        postfix.push_back(op);
    }

    *postfix_tokens = postfix;

    return 0;
}


int evaluate_postfix(std::vector<Token> postfix_tokens, float *value) {
    std::stack<Token> operand_stack;

    for(std::vector<Token>::iterator it = postfix_tokens.begin() ; it != postfix_tokens.end(); ++it) {
        if(it->type == operand) {
            operand_stack.push(*it);
        } else {
            // pop two operands and compute the operation
            Token op1, op2;

            if(operand_stack.empty())
                return -1;
            op2 = operand_stack.top();
            operand_stack.pop();

            if(operand_stack.empty())
                return -1;
            op1 = operand_stack.top();
            operand_stack.pop();

            if(op1.type != operand || op2.type != operand)
                return -1;

            Token result_token (operand);
            result_token.operand_value = OpFunctions[it->symbol_value](op1.operand_value, op2.operand_value);
            operand_stack.push(result_token);
        }
    }

    if(operand_stack.size() > 1)
        return -1;

    float result = operand_stack.top().operand_value;
    *value = result;
    return 0;
}