#include <iostream>
using namespace std;

class Rac {
    int ch, zn;
    
    void reduce() {
        if (ch == 0) {
            zn = 1;
            return;
        }
        
        int a = abs(ch);
        int b = abs(zn);

        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        int gcd = a;
        
        ch /= gcd;
        zn /= gcd;
        
        if (zn < 0) {
            ch = -ch;
            zn = -zn;
        }
    }
public: 
    Rac(int ch = 0, int zn = 1) : ch(ch), zn(zn) {
        if (zn == 0) {
            cerr << "err: zn = 0" << endl;
            this->zn = 1;
        }
        reduce();
    }
    
    Rac(const Rac& other) : ch(other.ch), zn(other.zn) {}
    ~Rac() {}

    int getCh() const { return ch; }
    int getZn() const { return zn; }
    void setCh(int newCh) { ch = newCh; reduce(); }
    void setZn(int newZn) { 
        if (newZn == 0) {
            cerr << "err: zn = 0" << endl;
            return;
        }
        zn = newZn; 
        reduce(); 
    }

    Rac operator+(const Rac& other) const {
       if (zn == other.zn) return Rac(ch + other.ch, zn);
       return Rac(ch * other.zn + other.ch * zn, zn * other.zn);
    }
    Rac operator*(const Rac& other) const {
        return Rac(ch * other.ch, zn * other.zn);
    }
    friend ostream& operator<<(ostream& os, const Rac& r);
    friend istream& operator>>(istream& is, Rac& r);
    Rac& operator++() { 
        ch += zn;
        return *this;  // Возвращаем сам объект
    }
    Rac operator++(int) {  // int - фиктивный параметр для различия
        Rac temp = *this;  // Сохраняем исходное значение
        ch += zn;          // Изменяем текущий объект
        return temp;       // Возвращаем старое значение
    }

};

ostream& operator<<(ostream& os, const Rac& r) {
    if (r.zn == 1) {
        os << r.ch;
    } else {
        os << r.ch << "/" << r.zn;
    }
    return os;
}
istream& operator>>(istream& is, Rac& r) {
    int ch, zn;
    if (is >> ch >> zn) {
        r = Rac(ch, zn);
    }
    return is;
}



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
void delete_matrix(Rac** matrix, int n) {
    if (!matrix) return;
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
Rac** create_matrix(int n) {
    Rac** matrix = new Rac*[n];
    if (!matrix) {
        return nullptr;
    }
    
    for (int i = 0; i < n; i++) {
        matrix[i] = new Rac[n];
        if (!matrix[i]) {
            delete_matrix(matrix, i + 1);
            return nullptr;
        }

        for (int j = 0; j < n; j++) 
            matrix[i][j] = Rac(0, 1);
    }
    return matrix;
}
bool enter_matrix(Rac** matrix, int n) {
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

            matrix[i][j] = Rac(ch, zn);
        }
    }
    return true;
}
Rac** matrix_multiplication(Rac** matrix1, Rac** matrix2, int n) { 
    if (!matrix1 || !matrix2 || n <= 0) return nullptr;
    
    Rac** result = create_matrix(n);
    if (!result) {
        cerr << "err: failed init result mstrix" << endl;
        return nullptr;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                Rac cur_mult = matrix1[i][k];
                cur_mult.multiplication_fraction_gener(matrix2[k][j]);

                result[i][j].adding_fraction_modif(cur_mult);
            }
        }
    }

    return result;
}
Rac finding_trace_matrix(Rac** matrix, int n) {
    if (!matrix || n <= 0) return 0;

    Rac result;
    for (int i = 0; i < n; i++) {
        result.adding_fraction_modif(matrix[i][i]);
    }

    return result;
}
void print_matrix(Rac** matrix, int n) {
    if (!matrix || n <= 0) {
        cerr << "err: invalid matrix for printing" << endl;
        return;
    } 

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j].output();
            cout << "\t";
        }
        cout << endl;
    }
}

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

        Rac* array1 = create_array(n);
        if (!array1 || !enter_array(array1, n)) {
            delete_array(array1);
            return 1;
        }

        Rac* array2 = create_array(n);
        if (!array2 || !enter_array(array2, n)) {
            delete_array(array1);
            delete_array(array2);
            return 1;
        }

        cout << endl << "array1:" << endl;
        output_array(array1, n);
        cout << endl << "array2:" << endl;
        output_array(array2, n);

        Rac* scalar_array = scalar_multiplication(array1, array2, n);
        if (scalar_array) {
            cout << endl << "scalar array:" << endl;
            output_array(scalar_array, n);
        }

        delete_array(array1);
        delete_array(array2);
        delete_array(scalar_array);
    }
    case 2: {
        int n;
        cout << "enter size matrices: ";
        if (!(cin >> n) || n <= 0) {
            cerr << "err: invalid size" << endl;
            return 1;
        }

        Rac** matrix1 = create_matrix(n);
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

        Rac** matrix2 = create_matrix(n);
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

        Rac** multiplied_matrices = matrix_multiplication(matrix1, matrix2, n);
        if (!multiplied_matrices) {
            cerr << "err: matrix multiplication failed" << endl;
            return 1;
        }
        cout << endl << "multiplied_matrices: " << endl;
        print_matrix(multiplied_matrices, n);

        Rac trace1 = finding_trace_matrix(matrix1, n);
        Rac trace2 = finding_trace_matrix(matrix2, n);
        cout << endl << "trace1: ";
        trace1.output();
        cout << endl << "trace2: ";
        trace2.output();
        cout << endl;
        
        Rac trace_multiplied_matrices = finding_trace_matrix(multiplied_matrices, n);
        cout << endl << "trace_multiplied_matrices: ";
        trace_multiplied_matrices.output();
        cout << endl;

        delete_matrix(matrix1, n);
        delete_matrix(matrix2, n);
        delete_matrix(multiplied_matrices, n);
    }
    }
    return 0;
}