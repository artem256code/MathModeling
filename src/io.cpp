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


    // Парсим сами фракции и записываем их в list
    std::string tmpStr;
    std::string num;                // Текущее полученное число
    int numbers[2];                 // Вес и кол-во
    while(!fileWithFractions.eof()){
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
    // Сначала очищаем файл
    std::ofstream file("data/out.txt");
    file.close();
    // После записываем фракции в файл
    std::ofstream fileWithFractions("data/out.txt", std::ios::app);
    if(fileWithFractions.is_open()){
        for(auto fraction = fractions.begin(); fraction!= fractions.end(); fraction++){
            fileWithFractions << (*fraction).getM() << " " << (*fraction).getN() << std::endl;
        }
    }
    fileWithFractions.close();
}
