#ifndef TESTS_HPP
#define TESTS_HPP

#include "../src/fraction.hpp"

class Test{
private:
    /**
     * @brief   Проверка функции getProbabilityOfConvergence()
     * @return  Закрывает программу, если тест не пройден или возвращает 0
     */
    int testGetProbabilityOfConvergence();


    /**
     * @brief Проверка функции getNumberOfNewClustersInFraction
     * @param fraction1     - первая фракция
     * @param fraction2     - вторая фракция
     * @param testChecker   - фракция которая должна получиться
     * @return              Закрывает программу, если тест не пройден или возвращает 0
     */
    int testGetNumberOfNewClustersInFraction(Fraction fraction1, Fraction fraction2, int testChecker);


    /**
     * @brief Проверка функции addFractionInList
     * @return                 Закрывает программу, если тест не пройден или возвращает 0
     */
    int testAddFractionInList();


    /**
     * @brief Проверка функции findFraction
     * @return                 Закрывает программу, если тест не пройден или возвращает 0
     */
    int testFindFraction();


    /**
     * @brief Проверка функции restructingOfFractions
     * @return                 Закрывает программу, если тест не пройден или возвращает 0
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
