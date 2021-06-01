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
    Vertice origen;
    Peso peso;
    Vecino(Vertice o , Vertice d, Peso p) : origen(o), dst(d), peso(p) {}
    bool operator==(const Vecino& w) const{
        if (origen == w.origen && dst == w.dst && peso == w.peso) return true;
        if (origen == w.dst && dst == w.origen && peso == w.peso) return true;
        return false;
    }      
};

typedef vector<vector<Vecino>> Grafo;


#endif //TP2_ALGO3_TIPOS_H
