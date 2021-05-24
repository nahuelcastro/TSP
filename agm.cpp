//
// Created by juan on 23/5/21.
//
#include <algorithm>

using namespace std;

typedef int Vertice;
typedef int Peso;
struct Vecino {
    Vertice dst;
    Peso peso;
    Vecino(Vertice d, Peso p) : dst(d), peso(p) {}
};
int INT_MAX = 2147483647;
Vecino V_INDEF = Vecino(INT_MAX, INT_MAX);

typedef vector<vector<Vecino>> Grafo;
vector<int> visitados;


Grafo agm_prim(Grafo g){
    Grafo res_agm (Grafo.size(), {}); // creamos grafo con la cantidad de nodos y los vecinos vacios
    int contador = grafo.size();
    int i = 0;

    while (contador != 0){
        visitados.pushback(i);
        Vecino vecino_min = buscarmin(g);
        i = vecino_min.dst;
        res_agm[i].pushback(vecino_min);
        contador --;
    }

    return res_agm;
}


Vecino buscarmin(Grafo g){
    Vecino v_min;
    v_min = V_INDEF;
    for ( n : visitados){
        for ( v : g[n]){
            bool valido = (find(visitados.begin(), visitados.end(), v.dst) != visitados.end())
            if( v_min.peso > g[n][v].peso and valido) v_min = v;
        }
    }
    return v_min;
}


//ForwardIt min_element(ForwardIt first, ForwardIt last, Compare comp)

