#ifndef MODEL_HPP
#define MODEL_HPP

#include <string>
#include <list>

#include "fraction.hpp"
#include "../tests/tests.hpp"


class Model{
private:
    // Объём пространства, объём вещества, вероятносто\временной коэф., кол-во прогонов.
    int V, M, Y, N;
    int numberOfFractions;                      //Текущее кол-во фракций
    int m;                                      //Масса всего вещества
    double p;                                   //Доля вещества в пространстве
    double S;                                   //Влияет на количество образуемых кластеров при перестройке
    std::list<Fraction> fractions;              //Список фракций
private:
    /**
     * @brief Симуляция одного шага моделирования программы
     */
    void simulateOneStepForConglutination();


    /**
     * @brief getProbabilityOfConvergence   Вероятность критического сближения двух кластеров
     * @param weightOfCluster1              - Вес первого кластера
     * @param weightOfCluster2              - Вес второго кластера
     * @return                              Возвращает вероятность
     */
    double getProbabilityOfConvergence(int ma, int mb);


    /**
     * @brief getNumberOfNewClustersInFraction  Количество новых кластеров при слипании двух фракций
     * @param fraction1                         - Первая фракция
     * @param fraction2                         - Вторая фракция
     * @return                                  Возвращает целое количество новых кластеров
     */
    int getNumberOfNewClustersInFraction(Fraction &fraction1, Fraction &fraction2);


    /**
     * @brief restructingOfGroup    Перестраивает список фракций 'fracions', моделируя слипание
     */
    void restructingOfGroup();


public:
    /**
     * @brief Конструктор, принимающий информацию о фракциях из файла
     * @param V                 - Объём пространства
     * @param M                 - Объём вещества
     * @param Y                 - Вероятностно/Временной коэф.
     * @param N                 - Кол-во прогонов
     * @param pathToFractions   - путь до файла с описанием фракций
     */
    Model(int V, int M, int Y, int N, std::string pathToFractions);

    /**
     * @brief Запуск моделирования
     */
    void simulate();

    friend Test;
};

#endif
