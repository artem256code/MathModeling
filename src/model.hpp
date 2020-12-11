#ifndef MODEL_HPP
#define MODEL_HPP

#include <string>
#include <list>

#include "fraction.hpp"
#include "../tests/tests.hpp"


class Model{
private:
    int V;                                      // Объём пространства
    int M;                                      // Объём вещества
    double Y;                                   // Вероятносто\временной коэф.
    int N;                                      // Kол-во прогонов
    int numberOfFractions;                      // Текущее кол-во фракций
    int m;                                      // Масса всего вещества
    double p;                                   // Доля вещества в пространстве
    double S;                                   // Влияет на количество образуемых кластеров при перестройке
    std::list<Fraction> fractions;              // Список фракций
    std::list<Fraction> newFractions;           // Список ново-созданных фракций
    std::list<Fraction> fractionsForRemove;     // Список фракций для удаления
private:
    /**
     * @brief getPab                        Вероятность критического сближения двух кластеров
     * @param ma                            - Вес первого кластера
     * @param mb                            - Вес второго кластера
     * @return                              Возвращает вероятность
     */
    double getPab(int ma, int mb);


    /**
     * @brief getNab                Вычисляет кол-во новых кластеров при слипании разных фракций
     * @param fraction1             - Первая фракция для вычислений
     * @param fraction2             - Вторая фракция для вычислений
     * @return                      Кол-во кластеров
     */
    int getNab(Fraction fraction1, Fraction fraction2);


    /**
     * @brief getNaa                Вычисляет кол-во новых кластеров при слипании одинаковых фракций
     * @param fraction              - Фракция используемая при вычислении
     * @return                      Кол-во кластеров
     */
    int getNaa(Fraction fraction);


    /**
     * @brief restructingOfFractions  Перестраивает список фракций 'fracions', моделируя слипание
     */
    void restructingOfFractions();


    /**
     * @brief findFraction          Ищет фракцию по массе в списке 'fraction'
     * @param list                  - ссылка на список в которм ищется фракция
     * @param m                     - масса кластера в фракции
     * @return                      Возвращает итератор на найденную фракцию или итератор на конец списка
     */
    std::list<Fraction>::iterator findFraction(std::list<Fraction> &list,int m);


    /**
     * @brief Симуляция одного шага моделирования программы
     */
    void simulateOneStepForConglutination();
public:
    /**
     * @brief Конструктор, принимающий информацию о фракциях из файла
     * @param V                 - Объём пространства
     * @param M                 - Объём вещества
     * @param Y                 - Вероятностно/Временной коэф.
     * @param N                 - Кол-во прогонов
     * @param pathToFractions   - путь до файла с описанием фракций
     */
    Model(int V, int M, double Y, int N, std::string pathToFractions);


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
