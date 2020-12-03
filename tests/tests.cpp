#include <iostream>
#include <cmath>

#include "tests.hpp"
#include "../src/model.hpp"
#include "../src/cluster.hpp"

int Test::testing(){
	testGetProbabilityOfConvergence();
    testGetNumberOfNewClustersInFraction(Cluster(1,2), Cluster(2,5), 0);
    testGetNumberOfNewClustersInFraction(Cluster(4,15), Cluster(4,15), 18);

    return 0;
}

int Test::testGetProbabilityOfConvergence(){
    Model model(100, 50, 1, 2, "/home/artem/C++/MathModeling/data/clusters.txt");

    double testChecker = round(0.064122035*10000)/10000;
    double result = round(model.getProbabilityOfConvergence(1,2)*10000)/10000;
    if( result != testChecker){
		std::cout << "Не пройден тест: model.getProbabilityOfConvergence(1,2)" << std::endl;
        std::cout << "Результат: " << result << " Должно быть: " << testChecker << std::endl;
        exit(EXIT_FAILURE);
	}
    return 0;
}

int Test::testGetNumberOfNewClustersInFraction(Cluster cluster1, Cluster cluster2, int testChecker){
    Model model(100, 50, 1, 2, "/home/artem/C++/MathModeling/data/clusters.txt");

    int result = model.getNumberOfNewClustersInFraction(cluster1, cluster2);
    if( result != testChecker){
        std::cout << "Не пройден тест: model.getNumberOfNewClustersInFraction(cluster1(1, 2), cluster2(2, 5))" << std::endl;
        std::cout << "Результат: " << result << " Должно быть: " << testChecker << std::endl;
        exit(EXIT_FAILURE);
    }
    return 0;
}
