#ifndef TP2_ALGO3_TS2_H
#define TP2_ALGO3_TS2_H

#include "tipos.h"
#include "vmc.h"
#include "aux.h"
#include <random>
#include <list>

vector<pair<int,int>> createPairVector(int n);
vector<int> SwapCiclo(const vector<int>& ciclo,int i ,int j);
pair<vector<int>,int> tabuSearch(const Grafo& G,vector<int> SolucionInicial,int costo_ciclo,int T, int max_iter,int rango_iter,int percent);
void obtenerSubVecindad(vector<pair<int,int>>& v);
pair<int,int> IndiceAristas_en_Grafo(const Grafo& G,int i , int z,int j );

#endif //TP2_ALGO3_TS2_H