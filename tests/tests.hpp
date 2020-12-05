#ifndef TESTS_HPP
#define TESTS_HPP

#include "../src/cluster.hpp"

class Test{
private:
    /**
     * @brief   Проверка функции getProbabilityOfConvergence()
     * @return  Закрывает программу, если тест не пройден или возвращает 0
     */
    int testGetProbabilityOfConvergence();


    /**
     * @brief Проверка функции GetNumberOfNewClustersInFraction
     * @param cluster1      - первый кластер
     * @param cluster2      - второй кластер
     * @param testChecker   - кластер который должен получиться
     * @return              - Закрывает программу, если тест не пройден или возвращает 0
     */
    int testGetNumberOfNewClustersInFraction(Cluster cluster1, Cluster cluster2, int testChecker);
public:
    /**
     * @brief   Вызывает все тесты
     * @return  Закрывает программу, если какой-то тест не пройден или возвращает 0
     */
    int testing();
};

#endif
