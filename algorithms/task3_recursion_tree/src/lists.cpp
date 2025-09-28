#include <iostream>
#include <stdexcept>

#include "lists.h"

using namespace std;

Elem* create_new_elem(int x){
    Elem* new_elem = new Elem;
    new_elem->info = x;
    new_elem->next = nullptr;
    return new_elem;
}
Elem*  create_and_enter_list(){
    Elem* top = nullptr, *cur = top;

    int n;
    cout << "enter size of list" << endl;
    if (!(cin >> n)) {
        cerr << "!cin >> n";
        return nullptr;
    }

    cout << "enter "  << n << " elem list" << endl;
    int x;
    for (int i = 0; i < n; i++){
        if (!(cin >> x)) {
            cerr << "!cin >> x";
            return top;
        }

        Elem* new_elem = create_new_elem(x);

        if (!top){
            top = new_elem;
            cur = top;
        } else {
            cur->next = new_elem;
            cur = new_elem;
        }
    }

    return top;
}
void output_list(Elem* top){
    Elem* cur = top;
    while (cur){
        cout << cur->info << " ";
        cur = cur->next;
    }
    cout << endl;
}

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
void delete_first_occurr(Elem* cur, int x){
    if (!cur) return;

    if (cur->info == x) ;
}


int main() {
    Elem* top = create_and_enter_list();
    
    int choice;
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
    }
    
    
    return 0;
}