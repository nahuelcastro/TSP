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

