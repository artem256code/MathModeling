#ifndef FRACTION_HPP
#define FRACTION_HPP


class Fraction{
public:
    int m;              //Размер одной частицы
    long long int n;    //Кол-во частиц
public:
    Fraction(int m, long long int n);
    ~Fraction();
    bool operator ==(const Fraction two);
    bool operator < (const Fraction two);
    int getM();
    long long int getN();

    void setM(int m);
    void setN(long long int n);
};



#endif
