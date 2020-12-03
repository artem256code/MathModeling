#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cmath>

#include "model.hpp"

Model::Model(int V, int M, int Y, int N, std::string pathToClusters): V(V), M(M), Y(Y), N(N) {
    std::srand(N);          // Привязываем ГПСЧ к кол-ву прогонов
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
    S = Y * p / m;                  // Вычисляем тот самый коэфицент 'S'
}


double Model::getProbabilityOfConvergence(int ma, int mb){
    double result = p * pow(pow(ma, 1/3.0) + pow(mb, 1/3.0), 3) /  m;
    return result;
}


void Model::simulateOneStepForConglutination(){
    for(std::list<Cluster>::iterator cluster1 = fraction.begin(); cluster1 != fraction.end(); cluster1++){
        for(std::list<Cluster>::iterator cluster2 = cluster1; cluster2 != fraction.end(); cluster2++){
            // Вычислили вероятность сближения cluster1 и cluster2
            double p = getProbabilityOfConvergence(cluster1->getM(), cluster1->getM());
            // Вероятность попадания в вероятность
            double rand = ((double)(std::rand()) / RAND_MAX);
            // Если попали в вероятность, то перестраиваем кластеры, симулируя слипание
            if(p >= rand){
                // Some code...
            }
        }
    }
}

int Model::getNumberOfNewClustersInFraction(Cluster &fraction1, Cluster &fraction2){
    double result;
    // Если массы фракций равны, то производим расчёт по этой формуле
    if(fraction1.getM() == fraction2.getM()){
        result = S * 0.5 * fraction1.getN()*(fraction1.getN() - 1) *
                 pow(pow(fraction1.getM(), 1/3.0) + pow(fraction1.getM(), 1/3.0), 3);
        return result;
    }
    // Иначе по этой формуле
    result = S * (fraction1.getN() * fraction2.getN()) *
             pow(pow(fraction1.getM(), 1/3.0) + pow(fraction2.getM(), 1/3.0), 3);
    return result;
}

void Model::start(){
    for(int i = 0; i < N; i++){
        simulateOneStepForConglutination();
    }
}
