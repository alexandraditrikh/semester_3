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

    void adding_fraction_modif(const Rac& other) {
        ch = ch * other.zn + other.ch * zn;
        zn = zn * other.zn;
        reduce();
    }
    
    Rac multiplies_fraction_gener(const Rac& other) const {
        Rac result(ch * other.ch, zn * other.zn);
        return result;
    }
    
    void output() const {
        if (zn == 1) {
            cout << ch;
        } else {
            cout << ch << "/" << zn;
        }
        cout << endl;
    }
};

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
    cout << "enter " << n << " elem arr (ch zn):" << endl;
    for (int i = 0; i < n; i++) {
        if (!(cin >> ch >> zn)) {
            cerr << "err: fail reading ch zn" << endl;
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

Rac* scalar_multiply(Rac* array1, Rac* array2, int n) {
    if (!array1 || !array2 || n <= 0) return nullptr;
    
    Rac* result = create_array(n);
    if (!result) return nullptr;
    
    for (int i = 0; i < n; i++) {
        result[i] = array1[i].multiplies_fraction_gener(array2[i]);
    }
    return result;
}

void delete_array(Rac* array) {
    if (array) {
        delete[] array;
    }
}

int main() {
    int n;
    cout << "enter size: ";
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

    Rac* scalar_array = scalar_multiply(array1, array2, n);
    if (scalar_array) {
        cout << endl << "scalar array:" << endl;
        output_array(scalar_array, n);
    }

    delete_array(array1);
    delete_array(array2);
    delete_array(scalar_array);
    
    return 0;
}