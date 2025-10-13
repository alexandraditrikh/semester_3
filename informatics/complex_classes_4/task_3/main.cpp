#include "Rac.h"
#include "Array.h"
#include "Matrix.h"
#include <iostream>

using namespace std;

int main() {
    int choice;
    cin >> choice;

    switch(choice) {
    case 1: {
        int n;
        cout << "enter size arrays: ";
        if (!(cin >> n) || n <= 0) {
            cerr << "err: invalid size" << endl;
            return 1;
        }

        Rac** array1 = create_array(n);
        if (!array1 || !enter_array(array1, n)) {
            delete_array(array1, n);
            return 1;
        }

        Rac** array2 = create_array(n);
        if (!array2 || !enter_array(array2, n)) {
            delete_array(array1, n);
            delete_array(array2, n);
            return 1;
        }

        cout << endl << "array1:" << endl;
        output_array(array1, n);
        cout << endl << "array2:" << endl;
        output_array(array2, n);

        Rac** scalar_array = scalar_multiplication(array1, array2, n);
        if (scalar_array) {
            cout << endl << "scalar array:" << endl;
            output_array(scalar_array, n);
        }

        delete_array(array1, n);
        delete_array(array2, n);
        delete_array(scalar_array, n);
        break;
    }
    case 2: {
        int n;
        cout << "enter size matrices: ";
        if (!(cin >> n) || n <= 0) {
            cerr << "err: invalid size" << endl;
            return 1;
        }

        Rac*** matrix1 = create_matrix(n);
        if (!matrix1) {
            cerr << "err: failed create matrix1" << endl;
            return 1;
        }
        
        cout << "\nenter elements for matrix1:" << endl;
        if (!enter_matrix(matrix1, n)) {
            cerr << "err: failed enter matrix1" << endl;
            delete_matrix(matrix1, n);
            return 1;
        }

        Rac*** matrix2 = create_matrix(n);
        if (!matrix2) {
            cerr << "err: failed create matrix2" << endl;
            delete_matrix(matrix1, n);
            return 1;
        }
        
        cout << "\nenter elements for matrix2:" << endl;
        if (!enter_matrix(matrix2, n)) {
            cerr << "err: failed enter matrix2" << endl;
            delete_matrix(matrix1, n);
            delete_matrix(matrix2, n);
            return 1;
        }

        cout << endl << "matrix1: " << endl;
        print_matrix(matrix1, n);
        cout << "matrix2: " << endl;
        print_matrix(matrix2, n);

        Rac*** multiplied_matrices = matrix_multiplication(matrix1, matrix2, n);
        if (!multiplied_matrices) {
            cerr << "err: matrix multiplication failed" << endl;
            return 1;
        }
        cout << endl << "multiplied_matrices: " << endl;
        print_matrix(multiplied_matrices, n);

        Rac* trace1 = finding_trace_matrix(matrix1, n);
        Rac* trace2 = finding_trace_matrix(matrix2, n);
        cout << endl << "trace1: ";
        trace1->output();
        cout << endl << "trace2: ";
        trace2->output();
        cout << endl;
        
        Rac* trace_multiplied_matrices = finding_trace_matrix(multiplied_matrices, n);
        cout << endl << "trace_multiplied_matrices: ";
        trace_multiplied_matrices->output();
        cout << endl;

        delete_matrix(matrix1, n);
        delete_matrix(matrix2, n);
        delete_matrix(multiplied_matrices, n);
        break;
    }
    }
    return 0;
}