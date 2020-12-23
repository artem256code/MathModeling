#include "model.hpp"
#include "../tests/tests.hpp"

int main(){
    Test test;
    test.testing();

    int V       = 100;      // Объём пространства
    int M       = 50;       // Объём вещества
    double Y    = 0.2;      // Вероятносто\временной коэф.
    int N       = 30;       // Кол-во прогонов

    double a    = 0.01;     // Коэф. для распада
    double b    = 0.02;      // Коэф. для распада
    int ka      = 1;        // Кол-во кластеров создаваемых при распаде массы 'a'
    int kb      = 1;        // Кол-во кластеров создаваемых при распаде массы 'b'
    std::string pathToFile = "../MathModeling/data/fractions.txt";

    Model model(V, M, Y, N, a, b, ka, kb, pathToFile);
    model.printFractions();
    model.simulate();
    model.printFractions();

    return 0;
}

