#include <iostream>
using namespace std;

class Rac {
int ch, z;

// double reducing_fraction() {
    
// }

public: 
    Rac(int ch, int z) : ch(ch), z(z) { ; }
    ~Rac() {}
    int getCh() const { return ch; }
    int getz() const { return z; }
    
    void adding_fraction_modif(const Rac& other) {
        ch += other.ch;
        z += other.z;
    }

    Rac multiplies_fraction_gener(const Rac& other) const {
        Rac result (ch * other.ch, z * other.z);
        return result;
    }

    void output(){
        cout << ch << '\n' << "--" << '\n' << z << endl;
    }
};

int main() {
    Rac r (5, 3);
    r.output();
    return 0;
}