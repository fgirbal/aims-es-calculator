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
#include "token.h"
#include "stree.h"
#include "postfix.h"

using namespace std;

int postfix_evaluate(std::vector<Token> tokens, float *value, clock_t *time);
int syntax_tree_evaluate(std::vector<Token> tokens, float *value, clock_t *time);
double clock_to_time(clock_t time);
void process_expression(int mode, char *expression, int size);
