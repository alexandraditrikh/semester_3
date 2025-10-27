#include "Tree.h"

// 12 
void found_count_occur_in_tree (TreeNode* root, int x, int& count) {
    if (!root) return;


    if (root->info == x) count++;
    found_count_occur_in_tree(root->right, x, count);
    found_count_occur_in_tree(root->left, x, count);
}

int main() {
    int choice;
    cout << "enter the choice" << endl; 
    if (!(cin >> choice)) {
        cerr << "!(cin >> choice)" << endl;
        return 1;
    }

    TreeNode* root = create_enter_tree();
    if (!root) return 1;

    switch (choice) {
        case 12: {
            int x;
            cout << "enter x: ";
            if (!(cin >> x)) {
                cerr << "!(cin >> x)" << endl;
                return 1;
            }

            int count = 0;
            found_count_occur_in_tree(root, x, count);
            cout << "count: " << count << endl;
            break;
        }
        default: cout << "Invalid choice\n";
    }


    delete_tree(root);
}