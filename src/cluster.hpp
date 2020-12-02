#ifndef CLUSTER_HPP
#define CLUSTER_HPP


class Cluster{
public:
    int m;              //Размер одной частицы
    long long int n;    //Кол-во частиц
public:
    Cluster(int m, long long int n);

    int getM();
    long long int getN();
};



#endif
