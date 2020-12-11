#ifndef TESTS_HPP
#define TESTS_HPP

#include "../src/fraction.hpp"

class Test{
private:
    /**
     * @brief   Проверка функции getProbabilityOfConvergence()
     * @return  Закрывает программу, если тест не пройден или возвращает 0
     */
    int test_getPab();


    /**
     * @brief   Проверка функции getNab
     * @return  Закрывает программу, если тест не пройден или возвращает 0
     */
    int test_getNab();


    /**
     * @brief    Проверка функции getNaa
     * @return   Закрывает программу, если тест не пройден или возвращает 0
     */
    int test_getNaa();


    /**
     * @brief    Проверка функции findFraction
     * @return   Закрывает программу, если тест не пройден или возвращает 0
     */
    int testFindFraction();


    /**
     * @brief    Проверка функции restructingOfFractions
     * @return   Закрывает программу, если тест не пройден или возвращает 0
     */
    int testRestructingOfFractions();

public:
    /**
     * @brief   Вызывает все тесты
     * @return  Закрывает программу, если какой-то тест не пройден или возвращает 0
     */
    int testing();
};

#endif
