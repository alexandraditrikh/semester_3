#pragma once

#define MAX_IDENT_LENGTH 10

#include <cstring>

struct VariableNode {
    char name[MAX_IDENT_LENGTH + 1]; 
    int value; 
    VariableNode* next; 
};

VariableNode* find_variable(VariableNode* top, const char* ident_str);

void set_variable_value(VariableNode*& top, const char* ident_str, int value, int m);

int get_variable_value(VariableNode*& top, const char* ident_str, int m);

void clear_variable_list(VariableNode* top);
