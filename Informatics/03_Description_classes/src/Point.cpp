#include <iostream>
#include <cmath>
using namespace std;

class Point {
    double x, y;

public:
    Point() : x(0), y(0) {}
    Point(double x, double y) : x(x), y(y) {}

    double getX() const { return x; }
    double getY() const { return y; }

    void set_coordinates(double x, double y) {
        this->x = x;
        this->y = y;
    }

    ~Point() {
        cout << "Point (" << x << ", " << y << ") destroyed" << endl;
    }

    double distance_to(const Point &other) const {
        return sqrt(pow(other.x - x, 2) + pow(other.y - y, 2));
    }

    void print() const {
        cout << "(" << x << ", " << y << ")";
    }
};

 
int main() {
    Point p1;  
    Point p2(3.0, 4.0);
    Point p3(1.0, 1.0);

    p1.print(); cout << endl;
    p1.set_coordinates(2.0, 3.0);
    p1.print(); cout << endl;

    cout << "\ndistance p1 p2: " << p1.distance_to(p2) << endl;
    cout << "distance p2 p3: " << p2.distance_to(p3) << endl << endl;

    return 0;
}