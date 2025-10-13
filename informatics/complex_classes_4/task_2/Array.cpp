#include "Array.h"
#include <iostream>

using namespace std;

Rac* create_array(int n) {
    if (n <= 0) {
        cerr << "err: size array <= 0" << endl;
        return nullptr;
    }
    return new Rac[n];
}

bool enter_array(Rac* array, int n) {
    if (!array || n <= 0) {
        cerr << "err: invalid array or size" << endl;
        return false;
    }

    int ch, zn;
    cout << "enter " << n << " elem matrix (ch zn):" << endl;
    for (int i = 0; i < n; i++) {
        if (!(cin >> ch >> zn)) {
            cerr << "err: failed read ch zn" << endl;
            return false;
        }
        array[i] = Rac(ch, zn);
    }
    return true;
}

void output_array(Rac* array, int n) {
    if (!array || n <= 0) return;

    for (int i = 0; i < n; i++) {
        array[i].output();
    }
}

Rac* scalar_multiplication(Rac* array1, Rac* array2, int n) {
    if (!array1 || !array2 || n <= 0) return nullptr;
    
    Rac* result = create_array(n);
    if (!result) return nullptr;
    
    for (int i = 0; i < n; i++) {
        result[i] = array1[i].multiplication_fraction_gener(array2[i]);
    }
    return result;
}

void delete_array(Rac* array) {
    if (array) {
        delete[] array;
    }
}