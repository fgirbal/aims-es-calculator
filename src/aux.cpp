#include "aux.h"

int postfix_evaluate(std::vector<Token> tokens, float *value, clock_t *time) {
    clock_t t;
    t = clock();

    float result;
    int ret_code;
    std::vector<Token> postfix_tokens;
    
    ret_code = infix_to_postfix(tokens, &postfix_tokens);
    if(ret_code != 0){
        t = clock() - t;
        *value = 0;
        *time = t;
        return ret_code;
    }
    ret_code = evaluate_postfix(postfix_tokens, &result);

    t = clock() - t;

    *value = result;
    *time = t;
    return ret_code;
}

int syntax_tree_evaluate(std::vector<Token> tokens, float *value, clock_t *time) {    
    clock_t t;
    t = clock();

    // build a syntax tree
    float result;
    int ret_code;
    SyntaxTreeNode head (NULL);

    ret_code = build_parse_tree(tokens, &head);
    if(ret_code != 0){
        t = clock() - t;
        *value = 0;
        *time = t;
        return ret_code;
    }
    ret_code = recursive_eval(&head, &result);

    t = clock() - t;

    *value = result;
    *time = t;
    return ret_code;
}

double clock_to_time(clock_t time) {
    return 1e6 * (double) time / CLOCKS_PER_SEC;
}