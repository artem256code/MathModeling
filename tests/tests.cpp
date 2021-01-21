#include <iostream>
#include <cmath>
#include <assert.h>
#include <list>

#include "tests.hpp"
#include "../src/model.hpp"
#include "../src/fraction.hpp"

// Модель для тестов
Model model(100, 50, 1, 2, 0.1, 0.2, 2, 1, "tests/test_fractions.txt");

int Test::testing(){
    test_getM();
    test_getN();
    test_getPab();
    test_getNab();
    test_getNaa();
    test_getKm();
    test_getM_();
    test_findFraction();
    test_changeFraction();
    test_restructingOfFractions();
    return 0;
}

int Test::test_getM(){
    int testChecker = model.getM();
    std::cout << testChecker << std::endl;
    assert(testChecker == 90);
    return 0;
}


int Test::test_getPab(){
    double testChecker = round(0.064122035*10000)/10000;
    double result = round(model.getPab(1,2)*10000)/10000;

    assert(result == testChecker);
    return 0;
}

int Test::test_getNab(){
    int result1 = model.getNab(Fraction(1, 2), Fraction(2, 5));
    int result2 = model.getNab(Fraction(6, 12), Fraction(15, 37));

    assert(result1 == 0);
    assert(result2 == 193);
    return 0;
}

int Test::test_getNaa(){
    int result1 = model.getNaa(Fraction(1, 2));
    int result2 = model.getNaa(Fraction(100, 63));

    assert(result1 == 0);
    assert(result2 == 8679);
    return 0;
}

int Test::test_getKm(){
    auto fraction1 = model.findFraction(model.fractions, 1);
    auto fraction2 = model.findFraction(model.fractions, 4);
    int m = fraction1->getM() + fraction2->getM();
    int ma = m * model.a;
    int mb = m * model.b;
    int n = model.getN(fraction1, fraction2);

    int result = model.getKm(m, n, ma, mb);

    assert(result == 1);
    return 0;
}

int Test::test_getM_(){
    auto fraction1 = model.findFraction(model.fractions, 1);
    auto fraction2 = model.findFraction(model.fractions, 4);
    int m = fraction1->getM() + fraction2->getM();
    int ma = m * model.a;
    int mb = m * model.b;
    int n = model.getN(fraction1, fraction2);
    int km = model.getKm(m, n, ma, mb);

    int result = model.getM_(m, n, km, ma, mb);

    assert(result == 4);
    return 0;
}

int Test::test_findFraction(){
    model.newFractions.push_back(Fraction(2, 1));
    model.newFractions.push_back(Fraction(3, 5));
    model.newFractions.push_back(Fraction(9, 4));
    std::list<Fraction>::iterator testIter1 = model.findFraction(model.newFractions,3);
    std::list<Fraction>::iterator testIter2 = model.findFraction(model.newFractions,10);

    assert(testIter1->getM() == 3);
    assert(testIter2 == model.newFractions.end());
    return 0;
}

int Test::test_getN(){
    auto fraction1 = model.findFraction(model.fractions, 2);
    auto fraction2 = model.findFraction(model.fractions, 3);
    auto fraction3 = model.findFraction(model.fractions, 3);
    auto fraction4 = model.findFraction(model.fractions, 3);
    auto fraction5 = model.findFraction(model.fractions, 3);
    auto fraction6 = model.findFraction(model.fractions, 4);

    double result1 = model.getN(fraction1, fraction2);
    double result2 = model.getN(fraction3, fraction4);
    double result3 = model.getN(fraction5, fraction6);

    assert(result1 == 3);
    assert(result2 == 1);
    assert(result3 == 6);
    return 0;
}

int Test::test_changeFraction(){
    model.changeFraction(1, 1);
    assert(model.fractions.begin()->getM() == 1);
    assert(model.fractions.begin()->getN() == 3);


    model.newFractions.clear();
    model.newFractions.push_back(Fraction(8, 3));
    model.changeFraction(8, 5);
    assert(model.findFraction(model.newFractions, 8)->getN() == 8);


    model.newFractions.clear();
    model.changeFraction(15, 4);
    assert(model.findFraction(model.newFractions, 15)->getN() == 4);
    return 0;
}

int Test::test_restructingOfFractions(){
    model.newFractions.clear();
    model.newFractions.push_back(Fraction(8, 9));
    model.restructingOfFractions();
    model.newFractions.clear();
    assert(model.findFraction(model.fractions, 8) != model.fractions.end());
    assert(model.findFraction(model.fractions, 8)->getN() == 9);


    model.fractionsForRemove.push_back(Fraction(1, 0));
    model.findFraction(model.fractions, 1)->setN(0);
    model.restructingOfFractions();
    model.fractionsForRemove.clear();
    assert(model.findFraction(model.fractions, 1) == model.fractions.end());
    return 0;
}
