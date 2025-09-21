#include <iostream>
#include <cmath>
#include <stdexcept>
using namespace std;

class Parabola {
    double a, b, c;
public:
    Parabola() : a(0), b(0), c(0) {};
    Parabola(double a, double b, double c) : a(a), b(b), c(c) {};

    double getDiscriminant() const {
        return b * b - 4.0 * a * c;
    }
    
    int getNumberOfRealRoots() const{
       double discriminant = getDiscriminant();
       if (discriminant > 0) return 2;
       if (discriminant == 0) return 1;
       else return 0;
    }

    void normalization(){
        if (a == 0) return;
        double coef = 1.0 / a;
        b *= coef, c *= coef;
        a = 1.0;
    }

    Parabola shift(double p) const {
        return Parabola(a, b, c + p);
    }
};

 
int main() {
    Parabola p1(1, -3, 2);   
    Parabola p2(2, 4, 2); 
    
    cout << "parabola 1" << endl;
    cout << "discriminant: " << p1.getDiscriminant() << endl;
    cout << "number of real roots: " << p1.getNumberOfRealRoots() << endl;
    
    cout << "\nparabola 2" << endl;
    cout << "discriminant: " << p2.getDiscriminant() << endl;
    cout << "number of real roots: " << p2.getNumberOfRealRoots() << endl;
    
    Parabola p2_normalized = p2;
    p2_normalized.normalization();
    
    Parabola p1_shifted = p1.shift(3);

    return 0;
}