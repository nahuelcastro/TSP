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

// pair<int, Vecino> buscarmin(const Grafo& g, vector<bool>& visitados){
//     Vecino v_min = V_INDEF;
//     int n_min = INT_MAX;
//     for (int i = 0; i < visitados.size(); i++) { // O(n)
//         if(visitados[i]){
//             for ( Vecino v : g[i]){ // O(n)
//                 bool visitado = visitados[v.dst];
//                 if( v_min.peso > v.peso and !visitado){
//                     v_min = v;
//                     n_min = i;
//                 }
//             }
//         }
//     }
//     return make_pair(n_min, v_min);
// }

// Grafo prim2(const Grafo& g, int v_0 = 0 ){
//     Grafo res_agm (g.size());   // O(n) creamos grafo con la cantidad de nodos y los vecinos vacios
//     vector<bool> visitados (g.size(), false); // O(n)
//     visitados[v_0] = true;
//     for (int i = 0; i < g.size(); ++i) {        // O(n)
//         pair<int, Vecino> t = buscarmin(g,visitados);
//         Vecino vecino_min = t.second;
//         int n = t.first;
//         visitados[vecino_min.dst] = true;
//         res_agm[n].push_back(vecino_min);
//         res_agm[vecino_min.dst].push_back(Vecino(n, vecino_min.peso));
//     }
//     return res_agm;
// }

Grafo prim(const Grafo& g, int v){
    vector<bool> visitados (g.size(), false); // O(n)
    vector<int> distancia (g.size(), INT_MAX); // O(n)
    vector<int> padre (g.size(), v); // O(n)

    Grafo res_agm (g.size());

    // viendo primer nodo
    for (Vecino vc : g[v]){ //O(n)
        distancia[vc.dst] = vc.peso;
        padre[vc.dst] = v;
    }

    distancia[v] = 0;
    visitados[v] = true;

    for (int i = 1; i < g.size() ; ++i) { // O(n) * adentro = O(n) * O(2n)= O(n²)
        int n;
        int dist_min = INT_MAX;

        // buscar el nodo a menor distancia del subarbol que no fue visitado
        for (int j = 0; j < distancia.size() ; ++j) {  // O(n)
            if(distancia[j] < dist_min and visitados[j] == false){
                dist_min = distancia[j];
                n = j;
            }
        }
        visitados[n] = true;
        for(Vecino vc : g[n]){ // O(n)
            if(distancia[vc.dst] > vc.peso){
                distancia[vc.dst] = vc.peso;
                padre[vc.dst] = n;

            }
        }

    }

    // armado de grafo para devolver
    for (int i = 0; i < padre.size() ; ++i) { //O(n)
        if (i != padre[i]){
            res_agm[i].push_back(Vecino(padre[i],distancia[i]));
            res_agm[padre[i]].push_back(Vecino(i,distancia[i]));
        }

    }
    return  res_agm;
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

//nuevo
pair<vector<int>,int> AGM(const Grafo& g){
    Grafo g_agm = prim(g,0);                  //
    vector<int> camino = dfs(g_agm,0);      // complejidad DFS
    int peso = peso_camino(g,camino);       //
    return make_pair(camino, peso);
}

////viejo
//pair<vector<int>,int> AGM(const Grafo& g){
//    Grafo g_agm = prim2(g,0);                  //
//    vector<int> camino = dfs(g_agm,0);      // complejidad DFS
//    int peso = peso_camino(g,camino);       //
//
//    return make_pair(camino, peso);
//}

