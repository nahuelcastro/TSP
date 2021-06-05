#include "aux.h"
#include "tipos.h"

// variables globales
const int INT_MAX = 2147483647;
Vecino V_INDEF = Vecino(-1,INT_MAX, INT_MAX);

void dfs_rec(int v,const Grafo &g, vector<bool>&visitados,vector<int>& orden){
    for (Vecino n : g[v]){
        if (!visitados[n.dst]){
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

Grafo prim(const Grafo& g, int v){
    vector<bool> visitados (g.size(), false); // O(n)
    vector<int> distancia (g.size(), INT_MAX); // O(n)
    vector<int> padre (g.size(), v); // O(n)

    Grafo res_agm (g.size());

    // carga distancia de todos los nodos al nodo inicial
    for (Vecino vc : g[v]){ //O(n)
        distancia[vc.dst] = vc.peso;
        padre[vc.dst] = v;
    }

    distancia[v] = 0;
    visitados[v] = true;

    for (int i = 1; i < g.size() ; ++i) { // O(n) * adentro = O(n) * O(2n)= O(nÂ²)
        int n;
        int dist_min = INT_MAX;

        // buscar el nodo a menor distancia del subarbol que no fue visitado
        for (int j = 0; j < distancia.size() ; ++j) {  // O(n)
            if(distancia[j] < dist_min and !visitados[j]){
                dist_min = distancia[j];
                n = j;
            }
        }
        visitados[n] = true;

        // actualiza distancias teniendo en cuenta el nuevo subarbol
        for(Vecino vc : g[n]){ // O(n)
            if(distancia[vc.dst] > vc.peso and !visitados[vc.dst]){
                distancia[vc.dst] = vc.peso;
                padre[vc.dst] = n;

            }
        }

    }

    // armado de grafo para devolver
    for (int i = 0; i < padre.size() ; ++i) { //O(n)
        if (i != padre[i]){
            res_agm[i].push_back(Vecino(i,padre[i],distancia[i]));
            res_agm[padre[i]].push_back(Vecino(padre[i],i,distancia[i]));
        }

    }

    return  res_agm;
}

int peso_camino2(const Grafo& g, const vector<int>& camino){
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

pair<vector<int>,int> AGM(const Grafo& g){
    Grafo g_agm = prim(g,0);                          // O(n^2)
    vector<int> camino = dfs(g_agm,0);                  // complejidad DFS
    int peso = peso_camino2(g,camino);                   // O(n^2)
    return make_pair(camino, peso);

}