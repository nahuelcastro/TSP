#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <set>
#include <map>

#ifndef TP2_ALGO3_TIPOS_H
#define TP2_ALGO3_TIPOS_H

using namespace std;

typedef int Vertice;
typedef int Peso;
struct Vecino {
    Vertice dst;
    Peso peso;
    Vecino(Vertice d, Peso p) : dst(d), peso(p) {}
};

typedef vector<vector<Vecino>> Grafo;


#endif //TP2_ALGO3_TIPOS_H
