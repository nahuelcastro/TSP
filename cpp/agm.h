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
//pair<int, Vecino> buscarmin(const Grafo& g,vector<bool> visitados);

//Grafo prim(const Grafo& g, int v);

int peso_camino(const Grafo& g, const vector<int>& camino);
//void limpiar_visitados();
pair<vector<int>,int> AGM(const Grafo& g);

#endif //TP2_ALGO3_AGM_H
