#include <iostream>
#include <ctype.h>
#include <stdlib.h>
#include <vector>
#include <stack>
#include "token.h"
#include "op.h"

using namespace std;

int infix_to_postfix(std::vector<Token> infix_tokens, std::vector<Token> *postfix_tokens);
int evaluate_postfix(std::vector<Token> postfix_tokens, float *value);
