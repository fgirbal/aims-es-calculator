#include <iostream>
#include <string>
#include <ctype.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include "token.h"
#include "op.h"

using namespace std;

class SyntaxTreeNode {
    public:
        Token token;
        SyntaxTreeNode *parent;
        SyntaxTreeNode *left_child;
        SyntaxTreeNode *right_child;

        SyntaxTreeNode(SyntaxTreeNode *given_parent);
};

void print_syntax_tree(SyntaxTreeNode *head, int depth);
int build_parse_tree(std::vector<Token> tokens, SyntaxTreeNode *tree);
int recursive_eval(SyntaxTreeNode *node, float *value);
