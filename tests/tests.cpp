#include <iostream>
#include <cmath>

#include "tests.hpp"
#include "../src/model.hpp"

int Test::testing(){
	testGetProbabilityOfConvergence();

    return 0;
}

int Test::testGetProbabilityOfConvergence(){
    Model model(100, 50, 1, 2, "../data/clusters.txt");

    double testChecker = round(0.064122035*10000)/10000;
    double result = round(model.getProbabilityOfConvergence(1,2)*10000)/10000;
    if( result != testChecker){
		std::cout << "Не пройден тест: model.getProbabilityOfConvergence(1,2)" << std::endl;
        std::cout << "Результат: " << result << " Должно быть: " << testChecker << std::endl;
        exit(EXIT_FAILURE);
	}
    return 0;
}
