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
    double a;                                   // Коэф. для распада
    double b;                                   // Коэф. для распада
    int ka;                                     // Кол-во кластеров создаваемых при распаде массы 'a'
    int kb;                                     // Кол-во кластеров создаваемых при распаде массы 'b'
    int m;                                      // Масса всего вещества
    double p;                                   // Доля вещества в пространстве
    double S;                                   // Влияет на количество образуемых кластеров при перестройке
    std::list<Fraction> fractions;              // Список фракций
    std::list<Fraction> newFractions;           // Список ново-созданных фракций
    std::list<Fraction> fractionsForRemove;     // Список фракций для удаления
private:
    /**
     * @brief parseFractionFromFile        Заполняет список 'fractions'
     * @param pathToFractions              - Путь к файлу с фракциями
     */
    void parseFractionFromFile(std::string pathToFractions);


    /**
     * @brief getM                  Вычисляет массу всего вещества
     * @return                      Возвращает массу
     */
    int getM();


    /**
     * @brief getPab                Вероятность критического сближения двух кластеров
     * @param ma                    - Вес первого кластера
     * @param mb                    - Вес второго кластера
     * @return                      Возвращает вероятность
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
     * @brief getKm                 Вычисляет кол-во нераспавшихся кластеров
     * @param m                     - Масса кластеров слипшихся фракций
     * @param n                     - Кол-во кластеров слипшихся фракций
     * @param ma                    - Масса распада
     * @param mb                    - Масса распада
     * @return
     */
    int getKm(int m, int n, int ma, int mb);


    /**
     * @brief getM                  Вычисляет выравнивающий фрагмент
     * @param m                     - Масса кластеров слипшихся фракций
     * @param n                     - Кол-во кластеров слипшихся фракций
     * @param km                    - Кол-во нераспавшихся кластеров
     * @param ma                    - Масса распада
     * @param mb                    - Масса распада
     * @return
     */
    int getM_(int m, int n, int km, int ma, int mb);


    /**
     * @brief getN                  Вычисляет кол-во новых кластеров
     * @param fraction1             - Первая фракция участвующая в слипании
     * @param fraction2             - Вторая фракция участвующая в слипании
     * @return                      Возвращает кол-во кластеров
     */
    int getN(std::list<Fraction>::iterator fraction1, std::list<Fraction>::iterator fraction2);


    /**
     * @brief randomSimulate        Высчитвает вероятность попадания
     * @param ma                    - Масса первой фракции
     * @param mb                    - Масса второй фракции
     * @return                      Возвращает 'true' если слипание произошло, иначе 'false'
     */
    bool randomSimulate(int ma, int mb);


    /**
     * @brief findFraction          Ищет фракцию по массе в списке 'fraction'
     * @param list                  - ссылка на список в которм ищется фракция
     * @param m                     - масса кластера в фракции
     * @return                      Возвращает итератор на найденную фракцию или итератор на конец списка
     */
    std::list<Fraction>::iterator findFraction(std::list<Fraction> &list,int m);


    /**
     * @brief changeFractions       Изменяет фракцию {(m | n)} на n
     * @param m                     - Масса по которой происхдит поиск
     * @param n                     - Кол-во на которое изменяется фракция
     */
    void changeFraction(int m, int n);


    /**
     * @brief restructingOfFractions  Перестраивает список 'fracions'
     */
    void restructingOfFractions();


    /**
     * @brief Симуляция одного шага моделирования программы
     */
    void simulateOneStep();

public:
    /**
     * @brief Конструктор, принимающий информацию о фракциях из файла
     * @param V                 - Объём пространства
     * @param M                 - Объём вещества
     * @param Y                 - Вероятностно/Временной коэф.
     * @param N                 - Кол-во прогонов
     * @param a                 - Коэф. для распада
     * @param b                 - Коэф. для распада
     * @param ka                - Кол-во кластеров создаваемых при распаде массы 'a'
     * @param kb                - Кол-во кластеров создаваемых при распаде массы 'b'
     * @param pathToFractions   - путь до файла с описанием фракций
     */
    Model(int V, int M, double Y, int N, double a, double b, int ka, int kb, std::string pathToFractions);


    /**
     * @brief printFractions     Распечатывает фракции
     */
    void printFractions();


    /**
     * @brief Запуск моделирования
     */
    void simulate();

    friend Test;
};

#endif
