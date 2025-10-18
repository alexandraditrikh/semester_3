#include "Rac.h"
#include <iostream>
#include <cmath>

using namespace std;

void Rac::reduce() {
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

Rac::Rac(int ch, int zn) : ch(ch), zn(zn) {
    if (zn == 0) {
        cerr << "err: zn = 0" << endl;
        this->zn = 1;
    }
    reduce();
}

Rac::Rac(const Rac& other) : ch(other.ch), zn(other.zn) {}

Rac::~Rac() {}

int Rac::getCh() const { return ch; }
int Rac::getZn() const { return zn; }

void Rac::setCh(int newCh) { 
    ch = newCh; 
    reduce(); 
}

void Rac::setZn(int newZn) { 
    if (newZn == 0) {
        cerr << "err: zn = 0" << endl;
        return;
    }
    zn = newZn; 
    reduce(); 
}

void Rac::adding_fraction_modif(const Rac& other) {
    ch = ch * other.zn + other.ch * zn;
    zn = zn * other.zn;
    reduce();
}

Rac Rac::multiplication_fraction_gener(const Rac& other) const {
    Rac result(ch * other.ch, zn * other.zn);
    return result;
}

void Rac::output() const {
    if (zn == 1) {
        std::cout << ch;
    } else {
        std::cout << ch << "/" << zn;
    }
}