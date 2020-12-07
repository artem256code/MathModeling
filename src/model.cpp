#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cmath>

#include "model.hpp"

Model::Model(int V, int M, int Y, int N, std::string pathToFractions): V(V), M(M), Y(Y), N(N) {
    std::srand(N);          // Привязываем ГПСЧ к кол-ву прогонов
    m = 0;                  // Инициализируем массу
    p = M / (double) V;     // Рассчитываем долю


    std::ifstream fileWithFractions(pathToFractions);
    // Если файл не найден
    if(!fileWithFractions) {
        std::cout << "Файл не найден: " << pathToFractions <<  std::endl;
        exit(EXIT_FAILURE);
    }

    std::string tmpStr;
    // Парсим кол-во фракций
    getline(fileWithFractions, tmpStr);
    numberOfFractions = std::stoi(tmpStr);

    // Парсим сами фракции и записываем их в list
    std::string num;                // Текущее полученное число
    int numbers[2];                 // Вес и кол-во
    for(int i = 0; i < numberOfFractions; i++){
        getline(fileWithFractions, tmpStr);
        std::stringstream ss(tmpStr);           // Строковый поток
        for(int j = 0; j < 2; j++){
            ss >> num;
            numbers[j] = std::stoi(num);
        }
        m += numbers[0] * numbers[1];
        fractions.push_back(Fraction(numbers[0], numbers[1]));    // Заполнили фракцию и добавили в список
    }
    S = Y * p / m;                  // Вычисляем коэфицент 'S'
}


double Model::getProbabilityOfConvergence(int ma, int mb){
    double result = p * pow(pow(ma, 1/3.0) + pow(mb, 1/3.0), 3) /  m;
    return result;
}


void Model::simulateOneStepForConglutination(){
    for(std::list<Fraction>::iterator fraction1 = fractions.begin(); fraction1 != fractions.end(); fraction1++){
        for(std::list<Fraction>::iterator fraction2 = fraction1; fraction2 != fractions.end(); fraction2++){
            // Вычислили вероятность сближения двух кластеров из фракций 'fraction1' и 'fraction2'
            double p = getProbabilityOfConvergence(fraction1->getM(), fraction2->getM());
            // Вероятность попадания в вероятность
            double rand = ((double)(std::rand()) / RAND_MAX);
            // Если попали в вероятность, то перестраиваем кластеры, симулируя слипание
            if(p >= rand){
                // Получили кол-во новых кластеров образованных при слипании 
                int n = getNumberOfNewClustersInFraction(*fraction1, *fraction2);
            }
        }
    }
}

int Model::getNumberOfNewClustersInFraction(Fraction &fraction1, Fraction &fraction2){
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
