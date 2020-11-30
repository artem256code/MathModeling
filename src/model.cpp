#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>

#include "model.hpp"

Model::Model(int V, int M, int Y, int N, std::string pathToClusters): V(V), M(M), Y(Y), N(N) {
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

        fraction.push_back(Cluster(numbers[0], numbers[1]));    // Заполнили кластер
    }

}

