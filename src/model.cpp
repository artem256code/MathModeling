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
        if(fraction1->getN() <= 0) continue;    // Если в данной фракции нет кластеров;
        for(std::list<Fraction>::iterator fraction2 = fraction1; fraction2 != fractions.end(); fraction2++){
            if(fraction2->getN() <= 0) continue; // Если в данной фракции нет кластеров;
            // Вычислили вероятность сближения двух кластеров из фракций 'fraction1' и 'fraction2'
            double p = getProbabilityOfConvergence(fraction1->getM(), fraction2->getM());
            // Вероятность попадания в вероятность
            double rand = ((double)(std::rand()) / RAND_MAX);
            // Если попали в вероятность, то перестраиваем кластеры, симулируя слипание
            if(p >= rand){
                // Получили кол-во новых кластеров образованных при слипании и их массу
                int n = getNumberOfNewClustersInFraction(*fraction1, *fraction2);
                int m = fraction1->getM() + fraction2->getM();
                if(n > 0){
                    addFractionInList(newFractions,m, n);       // Добавили фракцию {m | n} в 'очередь' на добавление
                    reductionClusterInFraction(fraction1, n);   // Убавили кол-во кластеров в фракции №1
                    reductionClusterInFraction(fraction2, n);   // Убавили кол-во кластеров в фракции №2
                    // Если фракции распались, то добавляем их в список для последующ. удаления
                    if(fraction1->getN() <= 0)  addFractionInList(fractionsForRemove, fraction1->getM(), n);
                    if(fraction2->getN() <= 0)  addFractionInList(fractionsForRemove, fraction2->getM(), n);
                }

            }
        }
    }
    // Выполнили перестройку всех фракций
    restructingOfFractions();
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

void Model::addFractionInList(std::list<Fraction> &list, int m, long long int n){
    // Ищем есть ли уже фракция с массой 'm' в списке
    std::list<Fraction>::iterator searhIter = findFraction(list, m);

    // И если есть, то просто меняем кол-во кластеров
    if(searhIter != list.end())            searhIter->setN(searhIter->getN() + n);
    // Иначе добавляем новую фракцию
    else                                   list.push_back(Fraction(m, n));
}

void Model::reductionClusterInFraction(std::list<Fraction>::iterator fraction, int delta){
    fraction->setN(fraction->getN() - delta);
}

void Model::restructingOfFractions(){
    // Удалили фракции
    for(std::list<Fraction>::iterator iter = fractionsForRemove.begin(); iter != fractionsForRemove.end(); iter++){
        std::list<Fraction>::iterator removeIter = findFraction(fractions,iter->getM());
        fractions.erase(removeIter);
    }
    // Добавили фракции
    for(std::list<Fraction>::iterator iter = newFractions.begin(); iter != newFractions.end(); iter++){
        addFractionInList(fractions, iter->getM(), iter->getN());
    }

    // Очищаем временные списки
    newFractions.clear();
    fractionsForRemove.clear();
}


std::list<Fraction>::iterator Model::findFraction(std::list<Fraction> &list,int m){
    for(std::list<Fraction>::iterator iter = list.begin(); iter != list.end(); iter++){
        if(iter->getM() == m)   return iter;
    }
    return list.end();
}

void Model::printFraction(){
    for(std::list<Fraction>::iterator iter = fractions.begin(); iter != fractions.end(); iter++){
        std::cout << "{(" << iter->getM() << "|" << iter->getN() << ")}" << std::endl;
    }
    std::cout << std::endl;
}

void Model::simulate(){
    for(int i = 0; i < N; i++){
        simulateOneStepForConglutination();
        printFraction();
    }
}
