#ifndef IO_HPP
#define IO_HPP

#include <list>
#include <string>

#include "fraction.hpp"

std::list<Fraction> parseFractionsFromFile(std::string pathToFractions);

void writeFractionsInFile(std::list<Fraction> fractions);

#endif // IO_HPP
