#include <iostream>
#include <stdexcept>

#include "lists.h"

using namespace std;


//1
int number_of_occurr(Elem* cur, int x) {
    if (!cur) return 0;
    
    if (cur->info == x) {
        return 1 + number_of_occurr(cur->next, x);
    } else {
        return number_of_occurr(cur->next, x);
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
    } else 
        adding_after_each_el(cur->next, x, y);
}

//4
void building_a_copy(Elem* cur, Elem* other_cur){
    if (!other_cur) return;

    cur->info = other_cur->info;
    building_a_copy(cur->next, other_cur->next);
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
        
        int num = number_of_occurr(top, x); 
        cout << "num of occurr " << x << ": " << num << endl;
    }
    case 2: {

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
    }
    case 4:
        Elem *new_list = nullptr;
        

    }
    
    
    return 0;
}