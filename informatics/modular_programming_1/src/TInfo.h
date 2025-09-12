#pragma once

struct TreeNode {
    int value;
    TreeNode* right;
    TreeNode* left;
};

typedef TreeNode* T;
struct StackNode{
    T elem;
    StackNode* next;
};

