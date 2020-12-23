#ifndef TESTS_HPP
#define TESTS_HPP

#include "../src/fraction.hpp"

class Test{
private:

    int test_getM();

    int test_getN();

    int test_getPab();

    int test_getNab();

    int test_getNaa();

    int test_getKm();

    int test_getM_();

    int test_findFraction();

    int test_changeFraction();

    int test_restructingOfFractions();

public:
    /**
     * @brief   Вызывает все тесты
     * @return  Закрывает программу, если какой-то тест не пройден или возвращает 0
     */
    int testing();
};

#endif
