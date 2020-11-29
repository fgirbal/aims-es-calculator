#pragma once
#include <map>

using namespace std;

typedef float (*t_op)(float,float);

float add(float op1, float op2);
float sub(float op1, float op2);
float mul(float op1, float op2);
float div(float op1, float op2);

static std::map<char, t_op> OpFunctions = {
    {'+', &add},
    {'-', &sub},
    {'*', &mul},
    {'/', &div},
    {'^', &pow}
};