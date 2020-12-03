#ifndef TESTS_HPP
#define TESTS_HPP

class Test{
private:
    /**
     * @brief   Проверка функции getProbabilityOfConvergence()
     * @return  Закрывает программу, если тест не пройден или возвращает 0
     */
    int testGetProbabilityOfConvergence();
public:
    /**
     * @brief   Вызывает все тесты
     * @return  Закрывает программу, если какой-то тест не пройден или возвращает 0
     */
    int testing();
};

#endif
