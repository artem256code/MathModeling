#include <iostream>
#include <cmath>
#include <list>

#include "tests.hpp"
#include "../src/model.hpp"
#include "../src/fraction.hpp"

Model model(100, 50, 1, 2, "/home/artem/C++/MathModeling/data/test_fractions.txt");

int Test::testing(){
    test_getPab();
    test_getNab();
    test_getNaa();
    testFindFraction();
    testRestructingOfFractions();
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

int Test::testFindFraction(){
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

int Test::testRestructingOfFractions(){
    model.newFractions.push_back(Fraction(8, 9));
    model.restructingOfFractions();
    model.newFractions.clear();
    if(model.findFraction(model.fractions, 8) == model.fractions.end() ||
            model.findFraction(model.fractions, 8)->getN() != 9){
        std::cout << "Не пройден тест: testRestructingOfFractions" << std::endl;
        exit(EXIT_FAILURE);
    }

    model.fractionsForRemove.push_back(Fraction(1, 2));
    model.restructingOfFractions();
    model.fractionsForRemove.clear();
    if(model.findFraction(model.fractions, 1) != model.fractions.end()){
        std::cout << "Не пройден тест: testRestructingOfFractions" << std::endl;
        exit(EXIT_FAILURE);
    }
    return 0;
}
