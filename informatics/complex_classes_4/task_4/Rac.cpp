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

    // Перегрузка операторов вместо методов
    Rac operator+(const Rac& other) const {
        return Rac(ch * other.zn + other.ch * zn, zn * other.zn);
    }
    
    Rac operator*(const Rac& other) const {
        return Rac(ch * other.ch, zn * other.zn);
    }
    
    // Префиксный инкремент
    Rac& operator++() { 
        ch += zn;
        return *this;
    }
    
    // Постфиксный инкремент
    Rac operator++(int) {
        Rac temp = *this;
        ch += zn;
        return temp;
    }
    
    // Сложение с целым числом
    Rac operator+(int dig) const {
        return *this + Rac(dig, 1);
    }
    
    // Оператор присваивания
    Rac& operator=(const Rac& other) {
        if (this != &other) {
            ch = other.ch;
            zn = other.zn;
        }
        return *this;
    }
    
    // Дружественные функции для ввода/вывода
    friend ostream& operator<<(ostream& os, const Rac& r);
    friend istream& operator>>(istream& is, Rac& r);
    
    // Старые методы для совместимости (убрать в чистой реализации)
    void output() const {
        if (zn == 1) {
            cout << ch;
        } else {
            cout << ch << "/" << zn;
        }
    }
    
    Rac multiplication_fraction_gener(const Rac& other) const {
        return *this * other;
    }
    
    void adding_fraction_modif(const Rac& other) {
        *this = *this + other;
    }
};

// Перегрузка оператора вывода
ostream& operator<<(ostream& os, const Rac& r) {
    if (r.zn == 1) {
        os << r.ch;
    } else {
        os << r.ch << "/" << r.zn;
    }
    return os;
}

// Перегрузка оператора ввода
istream& operator>>(istream& is, Rac& r) {
    int ch, zn;
    if (is >> ch >> zn) {
        r = Rac(ch, zn);
    }
    return is;
}

// Глобальные функции для работы с массивами
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

    cout << "enter " << n << " elem array (ch zn):" << endl;
    for (int i = 0; i < n; i++) {
        if (!(cin >> array[i])) {
            cerr << "err: failed to read fraction" << endl;
            return false;
        }
    }
    return true;
}

void output_array(Rac* array, int n) {
    if (!array || n <= 0) return;

    for (int i = 0; i < n; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

Rac scalar_multiplication(Rac* array1, Rac* array2, int n) {
    if (!array1 || !array2 || n <= 0) return Rac(0, 1);
    
    Rac result(0, 1);
    for (int i = 0; i < n; i++) {
        result = result + (array1[i] * array2[i]);
    }
    return result;
}

void delete_array(Rac* array) {
    if (array) {
        delete[] array;
    }
}

// Глобальные функции для работы с матрицами
Rac** create_matrix(int n) {
    if (n <= 0) return nullptr;
    
    Rac** matrix = new Rac*[n];
    if (!matrix) return nullptr;
    
    for (int i = 0; i < n; i++) {
        matrix[i] = new Rac[n];
        if (!matrix[i]) {
            for (int j = 0; j < i; j++) {
                delete[] matrix[j];
            }
            delete[] matrix;
            return nullptr;
        }
    }
    return matrix;
}

bool enter_matrix(Rac** matrix, int n) {
    if (!matrix || n <= 0) {
        cerr << "err: invalid matrix or size" << endl;
        return false;
    }

    cout << "enter " << n * n << " elem matrix (ch zn for each):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!(cin >> matrix[i][j])) {
                cerr << "err: failed to read matrix element" << endl;
                return false;
            }
        }
    }
    return true;
}

Rac** matrix_multiplication(Rac** matrix1, Rac** matrix2, int n) { 
    if (!matrix1 || !matrix2 || n <= 0) return nullptr;
    
    Rac** result = create_matrix(n);
    if (!result) {
        cerr << "err: failed to create result matrix" << endl;
        return nullptr;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = Rac(0, 1);
            for (int k = 0; k < n; k++) {
                result[i][j] = result[i][j] + (matrix1[i][k] * matrix2[k][j]);
            }
        }
    }
    return result;
}

Rac finding_trace_matrix(Rac** matrix, int n) {
    if (!matrix || n <= 0) return Rac(0, 1);

    Rac result(0, 1);
    for (int i = 0; i < n; i++) {
        result = result + matrix[i][i];
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
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void delete_matrix(Rac** matrix, int n) {
    if (!matrix) return;
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
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

            Rac scalar_result = scalar_multiplication(array1, array2, n);
            cout << endl << "scalar multiplication result: " << scalar_result << endl;

            Rac test1 = array1[0] + array2[0];
            cout << "array1[0] + array2[0] = " << test1 << endl;
            
            Rac test2 = array1[0] * array2[0];
            cout << "array1[0] * array2[0] = " << test2 << endl;
            
            Rac test3 = array1[0] + 5;
            cout << "array1[0] + 5 = " << test3 << endl;
            
            ++array1[0];
            cout << "++array1[0] = " << array1[0] << endl;

            delete_array(array1);
            delete_array(array2);
            break;
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
                cerr << "err: failed to create matrix1" << endl;
                return 1;
            }
            
            cout << "\nenter elements for matrix1:" << endl;
            if (!enter_matrix(matrix1, n)) {
                cerr << "err: failed to enter matrix1" << endl;
                delete_matrix(matrix1, n);
                return 1;
            }

            Rac** matrix2 = create_matrix(n);
            if (!matrix2) {
                cerr << "err: failed to create matrix2" << endl;
                delete_matrix(matrix1, n);
                return 1;
            }
            
            cout << "\nenter elements for matrix2:" << endl;
            if (!enter_matrix(matrix2, n)) {
                cerr << "err: failed to enter matrix2" << endl;
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
                delete_matrix(matrix1, n);
                delete_matrix(matrix2, n);
                return 1;
            }
            cout << endl << "multiplied matrices: " << endl;
            print_matrix(multiplied_matrices, n);

            Rac trace_multiplied = finding_trace_matrix(multiplied_matrices, n);
            cout << endl << "trace of multiplied matrices: " << trace_multiplied << endl;

            delete_matrix(matrix1, n);
            delete_matrix(matrix2, n);
            delete_matrix(multiplied_matrices, n);
            break;
        }
        default:
            cerr << "err: invalid choice" << endl;
            return 1;
    }
    return 0;
}