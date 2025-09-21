#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class Car {
    string make;
    string model;
    int year;
    int mileage;
public:
    Car() : make(""), model(""), year(0), mileage(0) {};

    Car(string make, string model, int year, int mileage = 0)
        : make(make), model(model), year(year), mileage(mileage) {
        if (year > 2025) throw invalid_argument("year > 2025");
        if (mileage < 0) throw invalid_argument("mileage < 0");
    };
    
    ~Car() { 
        cout << "car " << make << " " << model << " is destroyed" << endl; 
    }

    void getInfo() const {
        cout << "Make: " << make << ", model: " << model << ", year: " << year << 
        ", mileage: " << mileage << " miles" << endl;
    }

    void addMileage(int miles) { 
        if (miles < 0) throw invalid_argument("miles < 0");
        mileage += miles; 
    }

    void setMileage(int mileage) {
        if (mileage < 0) throw invalid_argument("mileage < 0");
        this->mileage = mileage; 
    }
};

int main() {
    try {
        Car car1("toyota", "camry", 2020, 15000);
        Car car2("honda", "civic", 2018);
        
        cout << "car 1 info" << endl;
        car1.getInfo();
        
        cout << "car 2 info" << endl;
        car2.getInfo();
        

        car1.addMileage(500);
        car1.getInfo();
        
        car2.setMileage(30000);
        car2.getInfo();
        
        // car1.setMileage(-100);
        
    } catch (const exception& e) {
        cerr << "error " << e.what() << endl;
        return 1;
    }

    return 0;
}