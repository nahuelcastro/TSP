#ifndef TP2_ALGO3_AGM_H
#define TP2_ALGO3_AGM_H

#include "tipos.h"

// variables globales
extern const int INT_MAX;
extern Vecino V_INDEF;
// vector<bool> visitados;
// vector<int> orden;


void dfs_rec(int v, Grafo& g);
vector<int> dfs(const Grafo& G,int v0);
Grafo prim(const Grafo& g, int v);



pair<vector<int>,int> AGM(const Grafo& g);

#endif //TP2_ALGO3_AGM_H
