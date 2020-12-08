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
    std::list<Fraction> newFractions;           //Список ново-созданных фракций
    std::list<Fraction> fractionsForRemove;     //Список фракций для удаления
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
     * @brief findFraction          Ищет фракцию по массе в списке 'fraction'
     * @param list                  - ссылка на список в которм ищется фракция
     * @param m                     - масса кластера в фракции
     * @return                      Возвращает итератор на найденную фракцию или итератор на конец списка
     */
    std::list<Fraction>::iterator findFraction(std::list<Fraction> &list,int m);

    /**
    * @brief addFractionInList      Добавляет новую фракцию в список для добавления
    * @param list                           - cписок в который будет добавлена фракция
    * @param m                              - Масса нового вещества
    * @param n                              - Количество нового вещества
    */
    void addFractionInList(std::list<Fraction> &list, int m, long long int n);
    
    /**
     * @brief reductionClusterInFraction    Уменьшает количество кластеров в полученной фракции
     * @param fraction                      - Фракция в которой уменьшится количество кластеров
     * @param delta                         - Число на которое уменьшится количество кластеров
     */
    void reductionClusterInFraction(std::list<Fraction>::iterator fraction, int delta);


    /**
     * @brief restructingOfFractions  Перестраивает список фракций 'fracions', моделируя слипание
     */
    void restructingOfFractions();


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
     * @brief printFraction     Распечатывает фракции
     */
    void printFraction();

    /**
     * @brief Запуск моделирования
     */
    void simulate();

    friend Test;
};

#endif
