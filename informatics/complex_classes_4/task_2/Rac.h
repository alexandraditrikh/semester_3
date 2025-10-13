#pragma once

#include <iostream>

class Rac {
    int ch, zn;
    
    void reduce();

public: 
    Rac(int ch = 0, int zn = 1);
    Rac(const Rac& other);
    ~Rac();

    int getCh() const;
    int getZn() const;
    void setCh(int newCh);
    void setZn(int newZn);

    void adding_fraction_modif(const Rac& other);
    Rac multiplication_fraction_gener(const Rac& other) const;
    void output() const;
};
