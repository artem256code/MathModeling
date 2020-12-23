#include <iostream>
#include <cmath>
#include <list>

#include "tests.hpp"
#include "../src/model.hpp"
#include "../src/fraction.hpp"

Model model(100, 50, 1, 2, 0.1, 0.2, 2, 1, "../MathModeling/data/test_fractions.txt");

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
    int result = 90;

    if(result != testChecker){
        std::cout << "Не пройден тест: test_getM " << std::endl;
        exit(EXIT_FAILURE);
    }
    return 0;
}


int Test::test_getPab(){
    double testChecker = round(0.064122035*10000)/10000;
    double result = round(model.getPab(1,2)*10000)/10000;
    if(result != testChecker){
        std::cout << "Не пройден тест: test_getNab " << std::endl;
        exit(EXIT_FAILURE);
    }
    return 0;
}

int Test::test_getNab(){
    int result = model.getNab(Fraction(1, 2), Fraction(2, 5));
    if( result != 0){
        std::cout << "Не пройден тест: test_getNab " << std::endl;
        exit(EXIT_FAILURE);
    }
    result = model.getNab(Fraction(6, 12), Fraction(15, 37));
    if( result != 193){
        std::cout << "Не пройден тест: test_getNab " << std::endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}

int Test::test_getNaa(){
    int result = model.getNaa(Fraction(1, 2));
    if( result != 0){
        std::cout << "Не пройден тест: test_getNaa " << std::endl;
        exit(EXIT_FAILURE);
    }
    result = model.getNaa(Fraction(100, 63));
    if( result != 8679){
        std::cout << "Не пройден тест: test_getNaa " << std::endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}

int Test::test_getKm(){
    auto fraction1 = model.findFraction(model.fractions, 1);
    auto fraction2 = model.findFraction(model.fractions, 4);

    int m = fraction1->getM() + fraction2->getM();
    int ma = m * model.a;
    int mb = m * model.b;
    int n = model.getN(fraction1, fraction2);

    int testChecker = 1;
    int result = model.getKm(m, n, ma, mb);

    if(result != testChecker){
        std::cout << "Не пройден тест: test_getKm " << std::endl;
        exit(EXIT_FAILURE);
    }
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

    int testChecker = 4;
    int result = model.getM_(m, n, km, ma, mb);

    if(result != testChecker){
        std::cout << "Не пройден тест: test_getM_ " << std::endl;
        exit(EXIT_FAILURE);
    }
    return 0;
}

int Test::test_findFraction(){
    model.newFractions.push_back(Fraction(2, 1));
    model.newFractions.push_back(Fraction(3, 5));
    model.newFractions.push_back(Fraction(9, 4));
    std::list<Fraction>::iterator testIter1 = model.findFraction(model.newFractions,3);
    std::list<Fraction>::iterator testIter2 = model.findFraction(model.newFractions,10);

    if(testIter1->getM() != 3 || testIter2 != model.newFractions.end()){
        std::cout << "Не пройден тест: testFindFraction" << std::endl;
        exit(EXIT_FAILURE);
    }
    return 0;
}

int Test::test_getN(){
    auto fraction1 = model.findFraction(model.fractions, 2);
    auto fraction2 = model.findFraction(model.fractions, 3);
    double testChecker = 3;
    double result = model.getN(fraction1, fraction2);

    if(result != testChecker){
        std::cout << "Не пройден тест: test_getN (1 часть) " << std::endl;
        exit(EXIT_FAILURE);
    }


    fraction1 = model.findFraction(model.fractions, 3);
    fraction2 = model.findFraction(model.fractions, 3);
    testChecker = 1;
    result = model.getN(fraction1, fraction2);

    if(result != testChecker){
        std::cout << "Не пройден тест: test_getN (2 часть) " << std::endl;
        exit(EXIT_FAILURE);
    }


    fraction1 = model.findFraction(model.fractions, 3);
    fraction2 = model.findFraction(model.fractions, 4);
    testChecker = 6;
    result = model.getN(fraction1, fraction2);

    if(result != testChecker){
        std::cout << "Не пройден тест: test_getN (3 часть) " << std::endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}

int Test::test_changeFraction(){
    model.changeFraction(1, 1);
    if(model.fractions.begin()->getM() != 1 || model.fractions.begin()->getN() != 3){
        std::cout << "Не пройден тест: test_changeFraction (1 часть)" << std::endl;
        exit(EXIT_FAILURE);
    }

    model.newFractions.clear();
    model.newFractions.push_back(Fraction(8, 3));
    model.changeFraction(8, 5);
    if(model.findFraction(model.newFractions, 8)->getN() != 8){
        std::cout << "Не пройден тест: test_changeFraction (2 часть)" << std::endl;
        exit(EXIT_FAILURE);
    }

    model.newFractions.clear();
    model.changeFraction(15, 4);
    if(model.findFraction(model.newFractions, 15)->getN() != 4){
        std::cout << "Не пройден тест: test_changeFraction (3 часть)" << std::endl;
        exit(EXIT_FAILURE);
    }
    return 0;
}

int Test::test_restructingOfFractions(){
    model.newFractions.clear();
    model.newFractions.push_back(Fraction(8, 9));
    model.restructingOfFractions();
    model.newFractions.clear();
    if(model.findFraction(model.fractions, 8) == model.fractions.end() ||
            model.findFraction(model.fractions, 8)->getN() != 9){
        std::cout << "Не пройден тест: testRestructingOfFractions" << std::endl;
        exit(EXIT_FAILURE);
    }

    model.fractionsForRemove.push_back(Fraction(1, 0));
    model.findFraction(model.fractions, 1)->setN(0);
    model.restructingOfFractions();
    model.fractionsForRemove.clear();
    if(model.findFraction(model.fractions, 1) != model.fractions.end()){
        std::cout << "Не пройден тест: testRestructingOfFractions" << std::endl;
        exit(EXIT_FAILURE);
    }
    return 0;
}
