//
// Created by juan and Naju on 24/5/21.
//

#include "aux.h"

void print_vecino(const vector<Vecino>& v){
    cout << "[";
    for (int i = 0; i < v.size(); i++) {
        if (i == v.size() - 1){
            cout << '(' << v[i].dst + 1 << ',' << v[i].peso << ")";
        } else {
            cout << '(' << v[i].dst + 1 << ',' << v[i].peso << "), ";
        }
    }
    cout << "]";
}

void print_camino(const vector<int>& v){
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] + 1 << " ";
    }
    cout << endl;

}

void print_grafo( const Grafo& g){
    for (int i = 0; i < g.size(); ++i) {
        cout << i + 1 << " -> ";
        print_vecino(g[i]);
        cout << " " << endl;
    }
}

// Devuelve las aristas de minimo peso de los vecinos de un vertice que conectan a "w" y a "q".
pair<Vecino,Vecino> AristasDesde(const vector<Vecino>& vecinos, int w,int q){ 
    Vecino min_w(-1,-1,0);
    Vecino min_q(-1,-1,0);
    int ind = 0;
    bool encontreMinW , encontreMinQ = false;
    //Inicializacion peso minimo. Se busca la primer arista a w.
    for (int i = 0; i < vecinos.size(); i++) {
        if (encontreMinW && encontreMinQ) break;
        if(vecinos[i].dst == w){
            min_w = vecinos[i];
            ind = i;
            encontreMinW = true;
        }
        if(vecinos[i].dst == q){
            min_q = vecinos[i];
            ind = i;
            encontreMinQ = true;
        }
    }
    // Busqueda de una arista a w y a q que tenga el minimo peso.
    for (int i = ind + 1 ; i < vecinos.size(); i++){
        if (vecinos[i].dst == w && vecinos[i].peso < min_w.peso) {
            min_w = vecinos[i];
        }
         if (vecinos[i].dst == q && vecinos[i].peso < min_q.peso) {
            min_q = vecinos[i];
        }
    }
    return make_pair(min_w,min_q);
}


int peso_camino(const Grafo& g, const vector<int>& camino){
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

