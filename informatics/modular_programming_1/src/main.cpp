#include <iostream>
#include "Tree.h"
#include "Stack.h"
using namespace std;

int main() {
    TreeNode* root = nullptr;
    root = input_tree_from_console();
    output_tree_klp(root);
    delete_tree(root);
    return 0;
}