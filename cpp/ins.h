#ifndef TP2_ALGO3_I_H
#define TP2_ALGO3_I_H

#include "tipos.h"

int elegir(Grafo G, vector<bool> insertado);
int insertar(Grafo G, Vertice w, map<pair<int, int>, int>longitudes, map<int, int> &conexiones, vector<bool> &insertado);
pair<vector<int>,int> I(const Grafo& G);

#endif //TP2_ALGO3_I_H