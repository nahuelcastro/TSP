#ifndef TP2_ALGO3_TS1_H
#define TP2_ALGO3_TS1_H
#include "ts2.h"
#include <list>
#include <iterator>

pair<vector<int>,int> tabuSearch(const Grafo& G,vector<int> SolucionInicial,int costo_ciclo,int T, int max_iter,int rango_iter,int percent,int top);

#endif //TP2_ALGO3_TS1_H