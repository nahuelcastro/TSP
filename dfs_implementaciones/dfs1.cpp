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

typedef vector<vector<Vecino>> Grafo;


void dfs_rec(int v,const Grafo &G, vector<bool>&visitados,vector<int>& orden){

    for (Vecino n : G[v]){
        if (visitados[n.dst] == false){
            visitados[n.dst] = true;
            orden.push_back(n.dst);
            cout << n.dst << endl;
            dfs_rec(n.dst,G,visitados,orden);
        }
    }
}
vector<int> dfs(const Grafo& G,int v0){
    v0 = 0 ;
    vector<bool> visitados(G.size(),false);
    vector<int> orden; 
    visitados[v0] = true;
    cout<< v0 << endl;
    dfs_rec(v0,G,visitados,orden);
    
    return orden;
}


Grafo leerGrafo() {
  int n, m;
  cin >> n >> m;
  Grafo G(n, vector<Vecino>());
  for (int i = 0; i < m; i++) {
    int v, w, peso;
    cin >> v >> w >> peso;
    G[v].push_back(Vecino(w, peso));
    G[w].push_back(Vecino(v, peso));
  }
  return G;
}


int main(int argc, char **argv) {

   
   Grafo G =
        {{Vecino(2,10), Vecino(3,20), Vecino(3,15)},
         {Vecino(1,10), Vecino(2,25), Vecino(3,35)},
         {Vecino(1,15), Vecino(2,35), Vecino(3,30)},
         {Vecino(3,20), Vecino(1,25), Vecino(1,30)}};


    vector<int> orden = dfs(G,1);

    return 0;
}
