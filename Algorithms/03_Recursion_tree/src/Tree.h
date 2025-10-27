#pragma once

using namespace std;
#include <fstream>
#include <iostream>

struct TreeNode {
    int info;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* create_new_treeNode (int x) {
    TreeNode* new_node = new TreeNode;
    if (!new_node) return nullptr;

    new_node->info = x;
    new_node->left = new_node->right = nullptr;
    return new_node;
}

TreeNode* create_tree(ifstream& in) {
    int x;
    if (!(in >> x)) {
        return nullptr;
    }
    TreeNode* root = create_new_treeNode(x);

    root->left = create_tree(in);
    root->right = create_tree(in);

    return root;
}

TreeNode* create_enter_tree() {
    ifstream in("../Input/Tree.txt");
    if (!in.is_open()) {
        cerr << "!in.is_open()\n";
        return nullptr;
    }

    return create_tree(in);
}


void delete_tree(TreeNode* root) {
    if (!root) return;
  
    delete_tree(root->left);
    delete_tree(root->right);

    delete root; 
}