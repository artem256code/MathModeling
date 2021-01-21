#include <iostream>

#include "model.hpp"

int main(){

    int V, M;       // Объём пространства, объём вещества
    double Y;       // Вероятносто\временной коэф.,
    int N;          // Кол-во прогонов
    double a, b;    // Коэффициенты для распада
    int ka, kb;     // Кол-во кластеров создаваемых при распаде массы 'a' и массы 'b'
    std::string pathToFile = "input.txt";

    std::cout << "Введите V, M, Y, N, a, b, ka, kb:" << std::endl;
    std::cin >> V >> M >> Y >> N >> a >> b >> ka >> kb;

    Model model(V, M, Y, N, a, b, ka, kb, pathToFile);
    model.printFractions();
    model.simulate();
    model.printFractions();
    model.writeFractions();

    return 0;
}

