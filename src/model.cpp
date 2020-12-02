#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cmath>

#include "model.hpp"

Model::Model(int V, int M, int Y, int N, std::string pathToClusters): V(V), M(M), Y(Y), N(N) {
    m = 0;                  // Инициализируем массу
    p = M / (double) V;     // Рассчитываем долю

    std::ifstream fileWithClusters(pathToClusters);
    // Если файл не найден
    if(!fileWithClusters) {
        std::cout << "Файл не найден: " << pathToClusters <<  std::endl;
        exit(EXIT_FAILURE);
    }

    std::string tmpStr;
    // Парсим кол-во кластеров
    getline(fileWithClusters, tmpStr);
    numberOfClusters = std::stoi(tmpStr);

    // Парсим сами кластеры и записываем их в list
    std::string num;                // Текущая полученная число
    int numbers[2];                 // Вес и кол-во
    for(int i = 0; i < numberOfClusters; i++){
        getline(fileWithClusters, tmpStr);
        std::stringstream ss(tmpStr);           // Строковый поток
        for(int j = 0; j < 2; j++){
            ss >> num;
            numbers[j] = std::stoi(num);
        }
        m += numbers[0] * numbers[1];
        fraction.push_back(Cluster(numbers[0], numbers[1]));    // Заполнили кластер
    }
}


double Model::getProbabilityOfConvergence(int weightOfCluster1, int weightOfCluster2){
    double w12 = pow(pow(weightOfCluster1, 1/3.0) + pow(weightOfCluster2, 1/3.0), 3);
    double result = p * w12 /  m;
    return result;
}


void Model::simulateOneStepForConglutination(){
    for(std::list<Cluster>::iterator i = fraction.begin(); i != fraction.end(); i++){
        for(std::list<Cluster>::iterator j = i; j != fraction.end(); j++){
            float p = getProbabilityOfConvergence(i->getM(), j->getM()) * 100;
        }
    }
}


void Model::start(){
    for(int i = 0; i < N; i++){
        simulateOneStepForConglutination();
    }
}
