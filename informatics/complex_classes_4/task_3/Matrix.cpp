#include "Matrix.h"
#include <iostream>

using namespace std;

void delete_matrix(Rac*** matrix, int n) {
    if (!matrix) return;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            delete matrix[i][j];
        }
        delete[] matrix[i];
    }
    delete[] matrix;
}

Rac*** create_matrix(int n) {
    Rac*** matrix = new Rac**[n];
    if (!matrix) {
        return nullptr;
    }
    
    for (int i = 0; i < n; i++) {
        matrix[i] = new Rac* [n];
        if (!matrix[i]) {
            delete_matrix(matrix, i + 1);
            return nullptr;
        }

        for (int j = 0; j < n; j++) 
            matrix[i][j] = new Rac;
    }
    return matrix;
}

bool enter_matrix(Rac*** matrix, int n) {
    if (!matrix || n <= 0) {
        cerr << "err: invalid matrix or size" << endl;
        return false;
    }

    int ch, zn;
    cout << "enter " << n * n << " elem arr (ch zn):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!(cin >> ch >> zn)) {
                cerr << "err: fail reading ch zn" << endl;
                return false;
            }

            *matrix[i][j] = Rac(ch, zn);
        }
    }
    return true;
}

Rac*** matrix_multiplication(Rac*** matrix1, Rac*** matrix2, int n) { 
    if (!matrix1 || !matrix2 || n <= 0) return nullptr;
    
    Rac*** result = create_matrix(n);
    if (!result) {
        cerr << "err: failed init result mstrix" << endl;
        return nullptr;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                Rac cur_mult = matrix1[i][k]->multiplication_fraction_gener(*matrix2[k][j]);

                result[i][j]->adding_fraction_modif(cur_mult);
            }
        }
    }

    return result;
}

Rac* finding_trace_matrix(Rac*** matrix, int n) {
    if (!matrix || n <= 0) return 0;

    Rac* result;
    for (int i = 0; i < n; i++) {
        result->adding_fraction_modif(*matrix[i][i]);
    }

    return result;
}

void print_matrix(Rac*** matrix, int n) {
    if (!matrix || n <= 0) {
        cerr << "err: invalid matrix for printing" << endl;
        return;
    } 

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j]->output();
            cout << "\t";
        }
        cout << endl;
    }
}