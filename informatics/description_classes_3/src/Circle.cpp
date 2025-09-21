#include <iostream>
#include <cmath>
#include <stdexcept>
using namespace std;

class Circle {
private:
    double x, y;
    double r;

public:
    Circle() : x(0), y(0), r(0) {}
    Circle(double x, double y, double radius) : x(x), y(y), r(radius) {   
        if (radius < 0) throw invalid_argument("r < 0");
    }
    
    ~Circle() { 
        cout << "circle with radius " << r << " destroyed" << endl; 
    }

    double get_radius() const { return r; }
    double get_x() const { return x; }
    double get_y() const { return y; }

     
    void set_radius(double radius) {   
        if (radius < 0) throw invalid_argument("r < 0");
        r = radius;
    }

    double area() const {
        return M_PI * r * r;   
    }

    void print_info() const {
        cout << "circle: radius = " << r 
             << ", center = (" << x << ", " << y << ")"
             << ", area = " << area() << endl;
    }
};

 
int main() {
    try{
        Circle circle1;   
        Circle circle2(3.0, 4.0, 5.0);   
        
        cout << "circle 1" << endl;
        circle1.print_info();
        
        cout << "\ncircle 2" << endl;
        circle2.print_info();
        
        circle1.set_radius(2.5);
        circle1.print_info();
        cout << endl;
    } catch (const exception& e) {
        cerr << "err " << e.what() << endl;
        return 1;
    }
    
    return 0;
}