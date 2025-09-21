#include <iostream>
#include <stdexcept>
using namespace std;

class DV {
private:
    double I, R;
public:
    DV() : I(0), R(0) {}
    DV(double I, double R) : I(I), R(R) {
        if (I < 0 || R < 0) throw invalid_argument("i < 0 || r < 0");
    }
    
    void setI(double value) {
        if (value < 0) throw invalid_argument("i < 0");
        I = value;
    }
    
    void setR(double value) {
        if (value < 0) throw invalid_argument("r < 0");
        R = value;
    }
    
    void setBoth(double valueI, double valueR) {
         if (valueI < 0 || valueR < 0) throw invalid_argument("i < 0 || r < 0");
    }

    double getI() const { return I; }
    double getR() const { return R; }

    double calculateVoltage() const { return I * R; }
    double calculatePower() const { return I * I * R; }

    DV serialConnection(const DV& other) const { // Генератор
        DV result(calculateVoltage() + other.calculateVoltage(), I + other.I);
        return result;
    }
    void parallelConnection(const DV& other) { // Модификатор
        setI(I + other.I); 
        if (R + other.R == 0) throw invalid_argument("R + other.R = 0");
        setR(R * other.R / (R + other.R)); 
    }

    void printInfo() const {
    cout << "I = " << I << ", R = " << R << endl
         << "Voltage (U = I * R) = " << calculateVoltage() << endl
         << "Power (W = I^2 * R) = " << calculatePower() << endl;
    }
};

 
int main() {
    try {
        DV dv1(2.0, 3.0);  
        DV dv2(1.0, 6.0);  
        
        cout << "DV1" << endl;
        dv1.printInfo();

        cout << endl << "DV2" << endl;
        dv2.printInfo();
        cout << endl;
        
        DV dv_serial = dv1.serialConnection(dv2);
        cout << "serial connection" << endl;
        dv_serial.printInfo();
        cout << endl;
        
        DV dv1_copy = dv1;  
        dv1_copy.parallelConnection(dv2);
        cout << "parallel connection" << endl;
        dv1_copy.printInfo();
        
    } catch (const exception& e) {
        cerr << "error " << e.what() << endl;
        return 1;
    }
    
    return 0;
}