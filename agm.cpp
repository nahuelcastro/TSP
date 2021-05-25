#include "aux.h"
#include "tipos.h"

//Grafo grafo_prueba =
//        {{Vecino(2-1,10), Vecino(4-1,20), Vecino(3-1,15)},
//         {Vecino(1-1,10), Vecino(4-1,25), Vecino(3-1,35)},
//         {Vecino(1-1,15), Vecino(2-1,35), Vecino(4-1,30)},
//         {Vecino(1-1,20), Vecino(2-1,25), Vecino(3-1,30)}};


// variables globales
const int INT_MAX = 2147483647;
Vecino V_INDEF = Vecino(INT_MAX, INT_MAX);


void dfs_rec(int v,const Grafo &g, vector<bool>&visitados,vector<int>& orden){
    for (Vecino n : g[v]){
        if (visitados[n.dst] == false){
            visitados[n.dst] = true;
            orden.push_back(n.dst);
            dfs_rec(n.dst,g,visitados,orden);
        }
    }
}

vector<int> dfs(const Grafo& G,int v0){
    v0 = 0 ;
    vector<bool> visitados(G.size(),false);
    vector<int> orden;
    visitados[v0] = true;
    orden.push_back(v0);
    dfs_rec(v0,G,visitados,orden);

    return orden;
}


pair<int, Vecino> buscarmin(const Grafo& g, vector<bool>& visitados){
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
    vector<bool> visitados (g.size(), false);
    visitados[v_0] = true;
    for (int i = 0; i < g.size(); ++i) {
        pair<int, Vecino> t = buscarmin(g,visitados);
        Vecino vecino_min = t.second;
        int n = t.first;
        visitados[vecino_min.dst] = true;
        res_agm[n].push_back(vecino_min);
        res_agm[vecino_min.dst].push_back(Vecino(n, vecino_min.peso));
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


pair<vector<int>,int> AGM(const Grafo& g){
    Grafo g_agm = prim(g);
    vector<int> camino = dfs(g_agm,0);
    int peso = peso_camino(g,camino);

    return make_pair(camino, peso);

}

