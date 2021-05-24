#include <iostream>
#include <vector>
#include <algorithm>
//#include <cstdio>
//#include <cstdlib>
//#include <chrono>
//#include <set>
//#include <map>

#include "aux.h"

// types, despues sacar, va en main
using namespace std;
typedef vector<vector<Vecino>> Grafo;
typedef int Vertice;
typedef int Peso;
struct Vecino {
    Vertice dst;
    Peso peso;
    Vecino(Vertice d, Peso p) : dst(d), peso(p) {}
};


// variables globales
const int INT_MAX = 2147483647;
Vecino V_INDEF = Vecino(INT_MAX, INT_MAX);
vector<bool> visitados(grafo_prueba.size(),false);
vector<int> orden;



Grafo grafo_prueba =
        {{Vecino(2-1,10), Vecino(4-1,20), Vecino(3-1,15)},
         {Vecino(1-1,10), Vecino(4-1,25), Vecino(3-1,35)},
         {Vecino(1-1,15), Vecino(2-1,35), Vecino(4-1,30)},
         {Vecino(1-1,20), Vecino(2-1,25), Vecino(3-1,30)}};


// DFS
void dfs_rec(int v){

    for (Vecino n : grafo_prueba[v]){ // CAMBIAR GRAFO PRUEBA
        if (visitados[n.dst] == false){
            visitados[n.dst] = true;
            orden.push_back(n.dst);
            //cout << n.dst << endl;
            dfs_rec(n.dst);
        }
    }
}
vector<int> dfs(const Grafo& G,int v0){
    v0 = 0 ;

    visitados[v0] = true;
    orden.push_back(v0);
    dfs_rec(v0);

    return orden;
}



pair<int, Vecino> buscarmin(const Grafo& g){
    Vecino v_min = V_INDEF;
    int n_min = INT_MAX;
    for (int i = 0; i < visitados.size(); i++) {
        if(visitados[i]){
            for ( Vecino v : g[i]){
                bool visitado = visitados[v.dst];
                if( v_min.peso > v.peso and !visitado){
                    v_min = v;
                    n_min = i;
                }
            }
        }
    }
    return make_pair(n_min, v_min);
}

Grafo prim(const Grafo& g){
    int v_0 = 0;
    Grafo res_agm (g.size()); // creamos grafo con la cantidad de nodos y los vecinos vacios
    int contador = g.size();
    visitados[v_0] = true;
    while (contador != 1){
        pair<int, Vecino> t = buscarmin(g);
        Vecino vecino_min = get<1>(t);
        int n = get<0>(t);
        visitados[vecino_min.dst] = true;
        res_agm[n].push_back(vecino_min);
        res_agm[vecino_min.dst].push_back(Vecino(n, vecino_min.peso));
        contador --;
    }

    return res_agm;
}




int peso_camino(const Grafo& g, const vector<int>& camino){
    int res = 0;
    for (int i = 0; i < camino.size(); ++i) {
        int s = i + 1;
        if (s == camino.size()) s = 0;
        for (Vecino v : g[camino[i]]) {
            if (v.dst == camino[s]) {
                res += v.peso;
                break;
            }
        }
    }
    return res;
}

void limpiar_visitados(){
    for (int i = 0; i < visitados.size() ; ++i) {
        visitados[i] = false;
    }
}

void AGM(const Grafo& g){
    Grafo g_agm = prim(g);
    limpiar_visitados();
    vector<int> camino = dfs(g_agm,0);
    cout<< " AGUANTE ALL BOYS" << endl;
    int peso = peso_camino(g,camino);

    cout << g.size() << " " << peso << endl;
    print_camino(camino);
}

//int main(int argc, char **argv) {
////    print_grafo(agm(grafo_prueba));
//    AGM(grafo_prueba);
//    return 0;
//}


