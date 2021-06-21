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


int generate_success_random_fp_expression(int k, char * expression, int max_size) {
    // generate a cascading random fully parenthesized expression with k operations
    if(k < 1) {
        return -1;
    }

    int expression_cursor = 0;
    // add the opening of parenthesis
    for(int i=0; i<k; i++) {
        expression[expression_cursor] = '(';
        expression_cursor++;
        if(expression_cursor >= max_size)
            return -1;
    }

    float operand;
    // add the first operand
    operand = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1000.0));
    expression_cursor += sprintf(expression+expression_cursor, "%.2f", operand);

    // generate an operation, a random operand, and add a closing parenthesis k-1 times
    for(int i=0; i<k; i++) {
        expression[expression_cursor] = '+';
        expression_cursor++;
        if(expression_cursor >= max_size)
            return -1;

        operand = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1000.0));
        expression_cursor += sprintf(expression+expression_cursor, "%.2f", operand);

        expression[expression_cursor] = ')';
        expression_cursor++;
        if(expression_cursor >= max_size)
            return -1;
    }

    expression[expression_cursor] = '\0';
    return 0;
}

void calculate_mean_and_std_dev(std::vector<float> v, float *mean, float *stdev) {
    float sum = std::accumulate(std::begin(v), std::end(v), 0.0);
    float m =  sum / v.size();

    float accum = 0.0;
    std::for_each (std::begin(v), std::end(v), [&](const float d) {
        accum += (d - m) * (d - m);
    });

    *mean = m;
    *stdev = sqrt(accum / (v.size()-1));
}


void run_comparison(char * filename) {
    cout << "Running comparison...\n";

    int max_size_expression = 10000;
    char expression_buffer[max_size_expression];
    int k;
    int N = 100;
    std::ofstream csv_file;

    // open CSV file
    csv_file.open(filename);
    csv_file << "Index,Expression,Success_P,Avg_Time_P,Std_Time_P,Success_S,Avg_Time_S,Std_Time_S\n";

    for(k=1; k<200; k++) {
        // generate an expression of size k
        int success = 1;
        while(success)
            success = generate_success_random_fp_expression(k, expression_buffer, max_size_expression);    

        std::vector<Token> tokens = tokenize(expression_buffer, max_size_expression);

        std::vector<float> time_p, time_s;

        clock_t it_time_taken_p, it_time_taken_s;        
        float it_output_value_p, it_output_value_s;
        int ret_code_p, ret_code_s;

        for(int v=0; v<N; v++)  {
            ret_code_p = postfix_evaluate(tokens, &it_output_value_p, &it_time_taken_p);
            ret_code_s = syntax_tree_evaluate(tokens, &it_output_value_s, &it_time_taken_s);
            time_p.push_back(clock_to_time(it_time_taken_p));
            time_s.push_back(clock_to_time(it_time_taken_s));
        }

        float time_p_mean, time_p_stdev, time_s_mean, time_s_stdev;
        calculate_mean_and_std_dev(time_p, &time_p_mean, &time_p_stdev);
        calculate_mean_and_std_dev(time_s, &time_s_mean, &time_s_stdev);

        csv_file << k << "," << expression_buffer << "," << ret_code_p << "," << time_p_mean << "," << time_p_stdev << "," << ret_code_s << "," << time_s_mean << "," << time_s_stdev << '\n';
    }
    csv_file.close();
    return;
}