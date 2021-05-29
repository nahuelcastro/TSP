#include "aux.h"
#include "tipos.h"

Vecino elegir(Grafo G, vector<bool>& visitados, int v){
    
}

void insertar(Grafo G, Vecino w, int v){

}

pair<vector<int>,int> I(const Grafo& G){
    vector<int> H;
    int costo = 0;
    int n = G.size();
    vector<bool> visitados(n);
    // agrego los primeros tres vertices del ciclo
    for (int i = 0; i < 3; i++)
    {
        H.push_back(i);
        visitados[i] = true;
    }
    for (int i = 0 ; i < n-1; i++){
        Vecino w = elegir(G, visitados, i);
        if (w.dst == -1) return make_pair(H,costo); // No se encontro ningun vecino que no genere ciclos.
        insertar(G, w, i);

        visitados[w.dst] = true;
        costo = costo + w.peso;
        H.push_back(w.dst);
    }
    return make_pair(H, costo);
}