#include <iostream>
#include <cmath>
#include <list>

#include "tests.hpp"
#include "../src/model.hpp"
#include "../src/fraction.hpp"

int Test::testing(){
	testGetProbabilityOfConvergence();
    testGetNumberOfNewClustersInFraction(Fraction(1,2), Fraction(2,5), 0);
    testGetNumberOfNewClustersInFraction(Fraction(4,15), Fraction(4,15), 18);
    testFindFraction();
    testAddFractionInList();
    testRestructingOfFractions();
    return 0;
}

int Test::testGetProbabilityOfConvergence(){
    Model model(100, 50, 1, 2, "/home/artem/C++/MathModeling/data/fractions.txt");

    double testChecker = round(0.064122035*10000)/10000;
    double result = round(model.getProbabilityOfConvergence(1,2)*10000)/10000;
    if( result != testChecker){
		std::cout << "Не пройден тест: model.getProbabilityOfConvergence(1,2)" << std::endl;
        std::cout << "Результат: " << result << " Должно быть: " << testChecker << std::endl;
        exit(EXIT_FAILURE);
	}
    return 0;
}

int Test::testGetNumberOfNewClustersInFraction(Fraction fraction1, Fraction fraction2, int testChecker){
    Model model(100, 50, 1, 2, "/home/artem/C++/MathModeling/data/fractions.txt");

    int result = model.getNumberOfNewClustersInFraction(fraction1, fraction2);
    if( result != testChecker){
        std::cout << "Не пройден тест: model.getNumberOfNewClustersInFraction(fraction1(1, 2), fraction2(2, 5))" << std::endl;
        std::cout << "Результат: " << result << " Должно быть: " << testChecker << std::endl;
        exit(EXIT_FAILURE);
    }
    return 0;
}

int Test::testFindFraction(){
    Model model(100, 50, 1, 2, "/home/artem/C++/MathModeling/data/fractions.txt");

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

int Test::testAddFractionInList(){
    Model model(100, 50, 1, 2, "/home/artem/C++/MathModeling/data/fractions.txt");

    model.addFractionInList(model.newFractions, 5, 4);
    if(model.findFraction(model.newFractions, 5) == model.newFractions.end() ||
            model.findFraction(model.newFractions, 5)->getN() != 4){
        std::cout << "Не пройден тест: testAddFractionInListOfAdding" << std::endl;
        exit(EXIT_FAILURE);
    }

    model.addFractionInList(model.newFractions, 5, 2);
    if(model.findFraction(model.newFractions, 5) == model.newFractions.end() ||
            model.findFraction(model.newFractions, 5)->getN() != 6){
        std::cout << "Не пройден тест: testAddFractionInListOfAdding" << std::endl;
        exit(EXIT_FAILURE);
    }
    return 0;
}

int Test::testRestructingOfFractions(){
    Model model(100, 50, 1, 2, "/home/artem/C++/MathModeling/data/fractions.txt");
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
