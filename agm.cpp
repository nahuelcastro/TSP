#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <set>
#include <map>



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

//
//Grafo grafo_prueba =
//        {{Vecino(1,10), Vecino(3,20), Vecino(2,15)},
//         {Vecino(1-1,10), Vecino(4-1,25), Vecino(3-1,35)},
//         {Vecino(1-1,15), Vecino(2-1,35), Vecino(4-1,30)},
//         {Vecino(1-1,20), Vecino(2-1,25), Vecino(3-1,30)}};


Vecino buscarmin(Grafo g){
    Vecino v_min = V_INDEF;
    for ( int n : visitados){
        for ( Vecino v : g[n]){
            bool valido = (find(visitados.begin(), visitados.end(), v.dst) != visitados.end());
            if( v_min.peso > v.peso and valido) v_min = v;
        }
    }
    return v_min;
}


Grafo AGM(Grafo g){
    Grafo res_agm (g.size()); // creamos grafo con la cantidad de nodos y los vecinos vacios
    int contador = g.size();
    int i = 0;

    while (contador != 0){
        visitados.push_back(i);
        Vecino vecino_min = buscarmin(g);
        i = vecino_min.dst;
        res_agm[i].push_back(vecino_min);
        contador --;
    }

    return res_agm;
}


//
//int main(int argc, char **argv) {
//    AGM(grafo_prueba);
//    return 0;
//}


//ForwardIt min_element(ForwardIt first, ForwardIt last, Compare comp)

