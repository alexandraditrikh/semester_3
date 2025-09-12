#include <iostream>
#include "Tree.h"
#include "Stack.h"
using namespace std;


TreeNode* input_tree_from_console() {
    TreeNode* root = nullptr;
    int n, value;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> value;
        insert_value_to_tree(root, value);
    }
    
    return root;
}

TreeNode* create_new_tree_node(int x) {
    TreeNode* new_node = new TreeNode;
    new_node->value = x;
    new_node->right = nullptr;
    new_node->left = nullptr;
    return new_node;
}

void insert_value_to_tree(TreeNode*& root, int x) {
    TreeNode* new_node = create_new_tree_node(x);

    if (!root) {
        root = new_node;
        return;
    }

    TreeNode* prev = nullptr, *cur = root;
    while (cur) {
        prev = cur;
        
        if (x < cur->value) {
            cur = cur->left;
        } else if (x > cur->value) {
            cur = cur->right;
        } else {
            delete new_node;
            return;
        }
    }

    if (x < prev->value) {
        prev->left = new_node;
    } else {
        prev->right = new_node;
    }
}

void output_tree_klp(TreeNode* root) {
    if (!root) return;
    
    StackNode* stack = init_stack();
    push_stack(stack, root);
    
    while (stack != nullptr) {
        TreeNode* current = pop_stack(stack);
        
        cout << current->value << " ";
        
        // Сначала правый, потом левый - для обхода KLP (корень-левый-правый)
        if (current->right) push_stack(stack, current->right);
        if (current->left) push_stack(stack, current->left);
    }
    cout << endl;
}

void delete_tree(T root) {
    if (!root) return;
    
    StackNode* stack = init_stack();
    push_stack(stack, root);
    
    while (stack != nullptr) {
        TreeNode* current = pop_stack(stack);
        
        if (current->left) push_stack(stack, current->left);
        if (current->right) push_stack(stack, current->right);
        
        delete current;
    }
}