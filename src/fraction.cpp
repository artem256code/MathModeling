#include "fraction.hpp"

Fraction::Fraction(int m, long long int n): m(m), n(n){};
Fraction::~Fraction() {}
int Fraction::getM()                     {return m;}
long long int Fraction::getN()           {return n;}

void Fraction::setM(int m)               {this->m = m;}
void Fraction::setN(long long int n)     {this->n = n;}

bool Fraction::operator==(const Fraction two){
    if(m == two.m && n == two.n)    return true;
    return false;
}

bool Fraction::operator < (const Fraction two){
    if(m < two.m)   return true;
    return false;
}
