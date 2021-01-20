#include <iostream>
#include <list>
#include <sstream>
#include <fstream>

#include "fraction.hpp"

std::list<Fraction> parseFractionsFromFile(std::string pathToFractions){
    std::list<Fraction> fractions;
    std::ifstream fileWithFractions(pathToFractions);
    // Если файл не найден
    if(!fileWithFractions) {
        std::cout << "Файл не найден: " << pathToFractions <<  std::endl;
        exit(EXIT_FAILURE);
    }

    std::string tmpStr;
    // Парсим кол-во фракций
    getline(fileWithFractions, tmpStr);
    int numberOfFractions = std::stoi(tmpStr);

    // Парсим сами фракции и записываем их в list
    std::string num;                // Текущее полученное число
    int numbers[2];                 // Вес и кол-во
    for(int i = 0; i < numberOfFractions; i++){
        getline(fileWithFractions, tmpStr);
        std::stringstream ss(tmpStr);           // Строковый поток
        for(int j = 0; j < 2; j++){
            ss >> num;
            numbers[j] = std::stoi(num);
        }
        fractions.push_back(Fraction(numbers[0], numbers[1]));    // Заполнили фракцию и добавили в список
    }

    return fractions;       //Возвращаем список фракций
}


void writeFractionsInFile(std::list<Fraction> fractions){
    std::ofstream fileWithFractions("out.txt", std::ios::app);
    if(fileWithFractions.is_open()){
        for(auto fraction = fractions.begin(); fraction!= fractions.end(); fraction++){
            fileWithFractions << (*fraction).getM() << " " << (*fraction).getM() << std::endl;
        }
    }
    fileWithFractions.close();
}
