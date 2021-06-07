#include "tipos.h"

#ifndef TP2_ALGO3_AUX_H
#define TP2_ALGO3_AUX_H

void print_vecino(const vector<Vecino>& v);
void print_camino(const vector<int>& v);
void print_grafo(const Grafo& g);
pair<Vecino,Vecino> AristasDesde(const vector<Vecino>& vecinos, int w,int q);
int peso_camino(const Grafo& g, const vector<int>& camino);

#endif //TP2_ALGO3_AUX_H
