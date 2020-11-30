#ifndef MODEL_HPP
#define MODEL_HPP

#include <string>
#include <list>

#include "cluster.hpp"



class Model{
private:
    // Объём пространства, объём вещества, вероятносто\временной коэф., кол-во прогонов.
    int V, M, Y, N;
    int numberOfClusters;
    std::list<Cluster> fraction;
public:
    Model(int V, int M, int Y, int N, std::string pathToClusters);
};


#endif
