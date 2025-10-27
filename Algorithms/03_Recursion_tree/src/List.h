#pragma once

using namespace std;
#include <iostream>

struct Elem {
    int info;
    Elem* next;
};

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

void delete_list(Elem* top) {
    while (top) {
        Elem* temp = top;
        top = top->next;
        delete temp;
    }
}