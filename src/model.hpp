#ifndef MODEL_HPP
#define MODEL_HPP

#include <string>
#include <list>

#include "cluster.hpp"



class Model{
private:
    // Объём пространства, объём вещества, вероятносто\временной коэф., кол-во прогонов.
    int V, M, Y, N;
    int numberOfClusters;           //Текущее кол-во кластеров
    int m;                          //Масса всего вещества
    double p;                       //Доля вещества в пространстве
    std::list<Cluster> fraction;    //Список фракций
private:
    /**
     * @brief Симуляция одного шага слипания кластеров
     */
    void simulateOneStepForConglutination();
    /**
     * @brief getProbabilityOfConvergence   Вероятность критического сближения двух кластеров
     * @param weightOfCluster1              - Вес первого кластера
     * @param weightOfCluster2              - Вес второго кластера
     * @return                              Возвращает вероятность
     */
    double getProbabilityOfConvergence(int weightOfCluster1, int weightOfCluster2);
public:
    /**
     * @brief Конструктор, принимающий информацию о кластерах из файла
     * @param V                 - Объём пространства
     * @param M                 - Объём вещества
     * @param Y                 - Вероятностно/Временной коэф.
     * @param N                 - Кол-во прогонов
     * @param pathToClusters    - путь до файла с описанием кластеров
     */
    Model(int V, int M, int Y, int N, std::string pathToClusters);

    /**
     * @brief Запуск моделирования
     */
    void start();
};

#endif
