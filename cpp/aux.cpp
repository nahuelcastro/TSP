//
// Created by juan and Naju on 24/5/21.
//

#include "aux.h"


// Devuelve las aristas de minimo peso de los vecinos de un vertice que conectan a "w" y a "q".
pair<Vecino,Vecino> AristasDesde(const vector<Vecino>& vecinos, int w,int q){ 
    Vecino min_w(-1,-1,0);
    Vecino min_q(-1,-1,0);
    bool encontreMinW = false;
    bool encontreMinQ = false;

    //Inicializacion peso minimo. Se busca la primer arista a w.
    for (int i = 0; i < vecinos.size(); i++) {
        if (encontreMinW && encontreMinQ) break;
        if(vecinos[i].dst == w){
            min_w = vecinos[i];
            encontreMinW = true;
        }
        if(vecinos[i].dst == q){
            min_q = vecinos[i];
            encontreMinQ = true;
        }
    }
    return make_pair(min_w,min_q);
}


int costo_camino(const Grafo& g, const vector<int>& camino){
    int res = 0;
    for (int i = 0; i < camino.size(); ++i) { //O(n)
        int s = i + 1;
        if (s == camino.size()) s = 0;
        for (Vecino v : g[camino[i]]) {      //O(n)
            if (v.dst == camino[s]) {
                res += v.peso;
                break;
            }
        }
    }
    return res;
}

