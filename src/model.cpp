#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cmath>
#include <stdio.h>
#include "model.hpp"

void Model::parseFractionFromFile(std::string pathToFractions){
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
}


int Model::getM(){
    int m = 0;
    for(auto iter = fractions.begin(); iter != fractions.end(); iter++){
        m += iter->getM() * iter->getN();
    }
    return m;
}


Model::Model(int V, int M, double Y, int N, double a, double b, int ka, int kb, std::string pathToFractions):
    V(V), M(M), Y(Y), N(N), a(a), b(b), ka(ka), kb(kb){

    p = M / (double) V;                     // Рассчитываем долю
    parseFractionFromFile(pathToFractions); // Заполняем список с фракциями
    m = getM();                             // Получаем суммарную массу вещества
    S = Y * p / m;                          // Вычисляем коэфицент 'S'
}


double Model::getPab(int ma, int mb){
    return p * pow(pow(ma, 1/3.0) + pow(mb, 1/3.0), 3) /  m;
}

int Model::getNab(Fraction fraction1, Fraction fraction2){
    return S * (fraction1.getN() * fraction2.getN()) *
            pow(pow(fraction1.getM(), 1/3.0) + pow(fraction2.getM(), 1/3.0), 3);
}

int Model::getNaa(Fraction fraction){
    return S * 0.5 * fraction.getN()*(fraction.getN() - 1) *
            pow(pow(fraction.getM(), 1/3.0) + pow(fraction.getM(), 1/3.0), 3);
}

int Model::getKm(int m, int n, int ma, int mb){
    return ((m * n) - (ma * ka) - (mb * kb)) / m;
}

int Model::getM_(int m, int n, int km, int ma, int mb){
    return m * n - (ma * ka + mb * kb + m * km);
}


int Model::getN(std::list<Fraction>::iterator fraction1, std::list<Fraction>::iterator fraction2){
    int n;
    if(fraction1 != fraction2)  n = getNab(*fraction1, *fraction2);
    else                        n = getNaa(*fraction1);

    if(n > fraction1->getN() || n > fraction2->getN()){
        n = (fraction1->getN() > fraction2->getN())? fraction2->getN():fraction1->getN();
    }
    return n;
}


std::list<Fraction>::iterator Model::findFraction(std::list<Fraction> &list, int m){
    for(std::list<Fraction>::iterator iter = list.begin(); iter != list.end(); iter++){
        if(iter->getM() == m)   return iter;
    }
    return list.end();
}


void Model::changeFraction(int m, int n){
    if(n > 0 && m > 0){
        // Пробуем найти фракцию с массой 'm'
        auto fraction = findFraction(fractions, m);
        // Если нашли, то увеличиваем кол-во её кластеров на 'n'
        if(fraction != fractions.end())          fraction->setN(fraction->getN()+n);
        else{
            // Аналогично проверяем есть ли в 'очереди' такая фракция
            fraction = findFraction(newFractions, m);
            // Если нашли, то увеличиваем кол-во её кластеров на 'n'
            if(fraction != newFractions.end())          fraction->setN(fraction->getN()+n);
            // Иначе добавляем эту фракцию в 'очередь'
            else                                        newFractions.push_back(Fraction(m, n));
        }
    }
}


void Model::restructingOfFractions(){
    // Удалили фракции
    for(auto  iter = fractionsForRemove.begin(); iter != fractionsForRemove.end(); iter++){
        auto removeIter = findFraction(fractions,iter->getM());
        if(removeIter != fractions.end() && removeIter->getN() == 0){
            fractions.erase(removeIter);
        }
    }
    // Добавили фракции
    for(auto iter = newFractions.begin(); iter != newFractions.end(); iter++){
        fractions.push_back(*iter);
    }

    // Очищаем временные списки
    newFractions.clear();
    fractionsForRemove.clear();
}


void Model::simulateOneStep(){
    for(auto fraction1 = fractions.begin(); fraction1 != fractions.end(); fraction1++){
        if(fraction1->getN() <= 0) continue;    // Если в данной фракции нет кластеров;
        for(auto fraction2 = fraction1; fraction2 != fractions.end(); fraction2++){
            if(fraction2->getN() <= 0) continue; // Если в данной фракции нет кластеров;

            int m = fraction1->getM() + fraction2->getM();  // Масса новой фракции
            int n = getN(fraction1, fraction2);             // Кол-во кластеров в ней

            int ma = m*a;                                   // Масса новой распавш. фракции 'a'
            int mb = m*b;                                   // Масса новой распавш. фракции 'b'
            int km = getKm(m, n, ma, mb);                   // Кол-во нераспавшихся класетров

            // Моделируем чисто слипание
            if(km == n){
                changeFraction(m, n);
            }
            // Моделируем слипание с распадом
            else{
                if(ma * ka + mb * kb <= m * n){
                    int m_ = getM_(m, n, km, ma, mb);       // Масса выравнивающего фрагмента
                    changeFraction(ma, ka);
                    changeFraction(mb, kb);
                    changeFraction(m, km);
                    changeFraction(m_, 1);
                }
            }

            // Уменьшаем массу фракций, которые учавствовали в слипании
            fraction1->setN(fraction1->getN() - n);
            fraction2->setN(fraction2->getN() - n);


            // Если фракции распались, то добавляем их в список для последующ. удаления
            if(fraction1->getN() <= 0 && findFraction(fractionsForRemove, fraction1->getM()) == fractionsForRemove.end()){
                fractionsForRemove.push_back(*fraction1);
            }
            if(fraction2->getN() <= 0 && findFraction(fractionsForRemove, fraction2->getM()) == fractionsForRemove.end()){
                fractionsForRemove.push_back(*fraction2);
            }
        }
    }
    // Выполнилняем перестройку всех фракций, добавляя и удаляя ненужные
    restructingOfFractions();
}


void Model::printFractions(){
    for(auto iter = fractions.begin(); iter != fractions.end(); iter++){
        std::cout << "{(" << iter->getM() << "|" << iter->getN() << ")}" << std::endl;
    }
    std::cout << "m = " << getM() << std::endl;
}


void Model::simulate(){
    for(int i = 0; i < N; i++){
        simulateOneStep();
    }
    fractions.sort();
}
