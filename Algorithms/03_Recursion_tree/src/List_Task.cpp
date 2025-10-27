#include "List.h"

using namespace std;

//1
int number_of_occurr(Elem* cur, int x, int count) {
    if (!cur) return count;

    if (cur->info == x) {
        return number_of_occurr(cur->next, x, count + 1);
    } 
    else {
        return number_of_occurr(cur->next, x,count);
    }
}

//2
void delete_first_occurr(Elem*& top, int x) {
    if (!top) return;
    
    if (top->info == x) {
        Elem* temp = top;
        top = top->next;
        delete temp;
        return;
    }
    
    delete_first_occurr(top->next, x);
}

//3
void adding_after_each_el(Elem* cur, int x, int y) {
    if (!cur) return;

    if (cur->info == x) {
        Elem* new_y = create_new_elem(y);
        new_y->next = cur->next;
        cur->next = new_y;
        
        adding_after_each_el(new_y->next, x, y);
    } else {
        adding_after_each_el(cur->next, x, y);
    }
}

//4
void building_a_copy(Elem*& cur, Elem* other_cur) {
    if (!other_cur) {
        cur = nullptr; 
        return;
    }

    cur = new Elem;
    cur->info = other_cur->info;
    building_a_copy(cur->next, other_cur->next);
}

//5
bool are_the_two_lists_equal(Elem* cur, Elem* other_cur) {
    if (!cur && !other_cur) return true;
    if (!cur || !other_cur) return false;
    if (cur->info != other_cur->info) return false;
    
    return are_the_two_lists_equal(cur->next, other_cur->next);
}

//6
void found_max_in_list(Elem* cur, int& max) {
    if (!cur) return;

    if (cur->info > max) max = cur->info;
    found_max_in_list(cur->next, max);
}

//7
void print_list_reverse(Elem* cur) {
    if (!cur) return;

    print_list_reverse(cur->next);
    cout << cur->info << " ";   
}

//8
void delete_list_rec (Elem*& cur) {
    if (!cur) return;

    delete_list_rec(cur->next); 

    delete cur; 
    cur = nullptr;
}

//9
Elem* creating_ord_list_w_destr (Elem*cur1, Elem* cur2) {
    if (!cur1) return cur2;
    if (!cur2) return cur1;

    if (cur1->info < cur2->info) {
        cur1->next = creating_ord_list_w_destr(cur1->next, cur2);
        return cur1;
    }
    else {
        cur2->next = creating_ord_list_w_destr(cur1, cur2->next);
        return cur2;
    }
}

void creating_ord_list (Elem* cur1, Elem* cur2, Elem*& cur3) {
    if (!cur1 && !cur2) {
        cur3 = nullptr;
        return;
    }

    cur3 = new Elem; 
   
    if (!cur1) {
        cur3->info = cur2->info;
        creating_ord_list(cur1, cur2->next, cur3->next);
    } else if (!cur2) {
        cur3->info = cur1->info;
        creating_ord_list(cur1->next, cur2, cur3->next);
    }

    else if (cur1->info >= cur2->info) {
        cur3->info = cur2->info;
        creating_ord_list(cur1, cur2->next, cur3->next);
    } else {
        cur3->info = cur1->info;
        creating_ord_list(cur1->next, cur2, cur3->next);
    }
}

Elem* intersection_ord_lists(Elem* cur1, Elem* cur2) {
    if (!cur1 || !cur2) {
        return nullptr;
    }

    if (cur1->info == cur2->info) {
        Elem* new_node = new Elem;
        new_node->info = cur1->info;
        
        new_node->next = intersection_ord_lists(cur1->next, cur2->next);
        return new_node;
    }
    
    else if (cur1->info < cur2->info) {
        return intersection_ord_lists(cur1->next, cur2);
    }
    else { 
        return intersection_ord_lists(cur1, cur2->next);
    }
}

int main() {
    Elem* top = create_and_enter_list();
    
    int choice;
    cout << "enter the choice" << endl; 
    if (!(cin >> choice)) {
        cerr << "!(cin >> choice)";
        return 1;
    }

    switch (choice){
    case 1: {
        int x;
        cout << "enter x" << endl;
        if (!(cin >> x)) {
            cerr << "!(cin >> x)";
            return 1;
        }
        
        int num = number_of_occurr(top, x, 0); 
        cout << "num of occurr " << x << ": " << num << endl;
        break;
    }
    case 2: {
        int x;
        cout << "enter x to delete" << endl;
        if (!(cin >> x)) {
            cerr << "!(cin >> x)";
            return 1;
        }
        delete_first_occurr(top, x);
        output_list(top);
        break;
    }
    case 3: {
        int x, y;
        cout << "enter x and y" << endl;
        if (!(cin >> x) || !(cin >> y)) {
            cerr << "!(cin >> x) || !(cin >> y)";
            return 1;
        }

        adding_after_each_el(top, x, y);
        output_list(top);
        break;
    }
    case 4: {
        Elem *new_list = nullptr;
        building_a_copy(new_list, top);
        output_list(new_list);
        delete_list(new_list);
        break;
    }
    case 5: {
        Elem* new_list = create_and_enter_list();
        cout << (are_the_two_lists_equal(top, new_list) ? "yes\n" : "no\n");
        delete_list(new_list);
        break;
    }
    case 6: {
        int max = top->info;
        found_max_in_list(top, max);
        cout << "Max = " << max << endl;
        break;
    }
    case 7: {
        print_list_reverse(top);
        break;
    }
    case 8: {
        
    }
    case 9: {
        Elem* L2 = create_and_enter_list();
        Elem* L3 = creating_ord_list_w_destr(top, L2);
        output_list(L3);
        delete_list(L2);
    }
    case 10: {
        Elem* L2 = create_and_enter_list();
        Elem* L3 = nullptr;
        creating_ord_list(top, L2, L3);
        output_list(L3);
        delete_list(L2);
        delete_list(L3);
    }
    case 11: {
        Elem* L2 = create_and_enter_list();
        Elem* L3 = intersection_ord_lists(top, L2);
        output_list(L3);
        delete_list(L2);
        delete_list(L3);
    }
    }
    delete_list(top);
    return 0;
}