#pragma once
#include "Tree.h"

// struct StackNode {
//     T elem;
//     StackNode* next;
// };

StackNode* create_new_stack_node(T node);
StackNode* init_stack();
void push_stack(StackNode*& top, T node);
T pop_stack(StackNode*& top);
T peek_stack(StackNode* top);
bool is_stack_empty(StackNode* top);
StackNode* clear_stack(StackNode* top);
void print_stack(StackNode* top);