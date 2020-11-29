#include "stree.h"

SyntaxTreeNode::SyntaxTreeNode(SyntaxTreeNode *given_parent) {
    token = Token();
    parent = given_parent;
    left_child = (SyntaxTreeNode*) NULL;
    right_child = (SyntaxTreeNode*) NULL;
};

void print_syntax_tree(SyntaxTreeNode *head, int depth) {
    SyntaxTreeNode *current_node = head;
    for(int i=0; i<depth; i++)
        cout << '-';

    cout << current_node->token;
    if(current_node->left_child != NULL)
        print_syntax_tree(current_node->left_child, depth+1);
    if(current_node->right_child != NULL)
        print_syntax_tree(current_node->right_child, depth+1);
}

int build_parse_tree(std::vector<Token> tokens, SyntaxTreeNode *tree) {
    SyntaxTreeNode head = SyntaxTreeNode((SyntaxTreeNode*) NULL);
    SyntaxTreeNode *current_node = &head;

    for(std::vector<Token>::iterator it = tokens.begin() ; it != tokens.end(); ++it) {
        // if at any point the current_node is NULL, there's an issue with the expression
        if(current_node == NULL)
            return -1;

        if(it->type == symbol) {
            if(it->symbol_value == '(') {
                if (current_node->left_child != NULL)
                    return -1;
                // add a new node as the left child, and descend into it
                current_node->left_child = new SyntaxTreeNode(current_node);
                current_node = current_node->left_child;
            } else if(it->symbol_value == ')') {
                // parenthesis closed, go back to parent
                current_node = current_node->parent;
            } else {
                if (current_node->right_child != NULL)
                    return -1;
                // any other operator, take it for the current node and go to the right child
                current_node->token = *it;
                current_node->right_child = new SyntaxTreeNode(current_node);
                current_node = current_node->right_child;
            }
        } else if (it->type == operand) {
            // it's an operand, set the token to the current node and move to the parent
            current_node->token = *it;
            current_node = current_node->parent;
        }
    }

    *tree = head;
    return 0;
}

int recursive_eval(SyntaxTreeNode *node, float *value) {
    SyntaxTreeNode *left_child = node->left_child;
    SyntaxTreeNode *right_child = node->right_child;

    if(left_child != NULL && right_child != NULL) {
        // it's not a leaf node, it's an operation
        int success_left_child, success_right_child;
        float left_child_value, right_child_value;
        success_left_child = recursive_eval(left_child, &left_child_value);
        success_right_child = recursive_eval(right_child, &right_child_value);
        if(success_left_child || success_right_child)
            return -1;

        *value = OpFunctions[node->token.symbol_value](left_child_value, right_child_value);
        return 0;
    } else if (left_child == NULL && right_child == NULL) {
        // it's a leaf node, just return its value, unless it's not an operand, then the expression
        // is unbalanced
        if(node->token.type != operand)
            return -1;

        *value = node->token.operand_value;
        return 0;
    } else if (left_child != NULL && right_child == NULL && node->token.type == undefined) {
        // it's an extra pair of parenthesis; evaluate the left child's
        int success_left_child;
        float left_child_value;
        success_left_child = recursive_eval(left_child, &left_child_value);
        if(success_left_child)
            return -1;

        *value = left_child_value;
        return 0;
    }

    // this shouldn't happen; the expression is wrong/poorly balanced
    return -1;
}
