#ifndef TP2_ALGO3_TS2_H
#define TP2_ALGO3_TS2_H

#include "tipos.h"
#include "vmc.h"
#include <random>
#include <list>

vector<pair<int,int>> createPairVector(int n);
vector<int> SwapCiclo(const vector<int>& ciclo,int i ,int j);
pair<vector<Vecino>,int> tabuSearch2(const Grafo& G,vector<Vecino> SolucionInicial,int costo_ciclo,int T, int max_iter,int rango_iter,int percent,int top);
void obtenerSubVecindad(vector<pair<int,int>>& v);
pair<int,int> IndiceAristas_en_Grafo(const Grafo& G,int i , int z,int j );

#endif //TP2_ALGO3_TS2_H