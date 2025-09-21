#include <stdexcept> 
#include <iostream>
using namespace std;

class Perm {
    int n;
    int* p;
public:
    Perm() : n(0), p(nullptr) {}
    
    Perm(int size) : n(size), p(new int[size]) {
        cout << "enter " << n << " elements perm ";
        for (int i = 0; i < n; i++) {
            if (!(cin >> p[i])) { 
                delete[] p;
                throw runtime_error("failed to read elem");
            }
        }
    }
    
    Perm(const Perm& other) : n(other.n), p(new int[other.n]) {
        for (int i = 0; i < n; i++) p[i] = other.p[i];
    }
    
    ~Perm() { delete[] p; }

    int getValue(int i) const { 
        if (i < 0 || i >= n) throw out_of_range("index out of bounds");
        return p[i];
    }

    bool isEqualPerm(const Perm& other) const {
        if (n != other.n) return false;
        for (int i = 0; i < n; i++) 
            if (p[i] != other.p[i]) return false;
        return true;
    }

    void multiPerm(const Perm& other) {

        int* temp = new int[n];
        for (int i = 0; i < n; i++) {
            temp[i] = p[other.p[i]]; 
        }
        
        delete[] p;
        p = temp;
    }

    Perm reversePerm() const {
        Perm result;
        result.n = n;
        result.p = new int[n];
        
        for (int i = 0; i < n; i++) {
            result.p[i] = 0;
        }
        
        for (int i = 0; i < n; i++) {
            result.p[p[i]] = i;
        }
        return result;
    }
};

int main() {
    try {
        int n;
        cout << "enter perm size ";
        if (!(cin >> n)) throw runtime_error("failes size input");

        Perm p(n), q(n);

        p.multiPerm(q), q.multiPerm(p);
        
        cout << (q.reversePerm().isEqualPerm(p) ? "no" : "yes");
        
    } catch (const exception& e) {
        cerr << "err " << e.what() << endl;
        return 1;
    }
    
    return 0;
}