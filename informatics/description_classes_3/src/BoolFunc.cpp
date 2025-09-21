#include <iostream>
using namespace std;

#define SIZE_VALUES 4

class BoolFunc{ 
    bool values[SIZE_VALUES];
public:
    BoolFunc(){
        for (bool v : values) v = 0;
    }
    BoolFunc(bool v[SIZE_VALUES]) {
        for (int i = 0; i < SIZE_VALUES; i++) values[i] = v[i];
    }
    BoolFunc(bool v00, bool v01, bool v10, bool v11){
        values[0] = v00;
        values[1] = v01;
        values[2] = v10;
        values[3] = v11;
    }

    bool getValue(bool x, bool y){
        if (x == 0 && y == 0) return values[0];
        if (x == 0 && y == 1) return values[1];
        if (x == 1 && y == 0) return values[2];
        return values[3];
    }

    void conjunction(const BoolFunc & other) { // Модификатор
        for (int i = 0; i < SIZE_VALUES; i++){
            values[i] &= other.values[i];
        }
    }

    BoolFunc disjunction(const BoolFunc& other) const {
        BoolFunc result;
        for (int i = 0; i < 4; i++) {
            result.values[i] = values[i] || other.values[i];
        }
        return result;
    }

    BoolFunc negation() const {
        BoolFunc result;
        for (int i = 0; i < 4; i++) {
            result.values[i] = !values[i];
        }
        return result;
    }

    void print() const {
        cout << "f(00) = " << values[0] << ", "
             << "f(01) = " << values[1] << ", "
             << "f(10) = " << values[2] << ", "
             << "f(11) = " << values[3] << endl;
    }
};

int main(){
    BoolFunc f1(true, false, true, false); // 1, 0, 1, 0
    BoolFunc f2(false, true, false, true); // 0, 1, 0, 1

    cout << "f1(0,0) = " << f1.getValue(false, false) << endl;
    cout << "f1(1,1) = " << f1.getValue(true, true) << endl;


    BoolFunc f3 = f1.disjunction(f2);
    cout << "f1 or f2" << endl;
    f3.print();
   
    BoolFunc f4 = f1.negation();
    cout << "not f1" << endl;
    f4.print();
    
    f1.conjunction(f2);
    cout << "f1 and f2" << endl;
    f1.print();

    return 0;
}