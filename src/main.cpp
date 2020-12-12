#include "model.hpp"
#include "../tests/tests.hpp"

int main(){
    Test test;
    test.testing();

    Model model(100, 100, 0.12, 12, "../data/fractions.txt");
    model.printFraction();
    model.simulate();
    model.printFraction();
    return 0;
}

