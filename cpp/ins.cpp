#include "aux.h"
#include "tipos.h"

Vecino elegir(Grafo G, vector<bool>& visitados, int v){
    Vecino min(-1, 0);
    int ind;
    //Iniciliazacion peso minimo. Se busca el primer vecino no visitado.
    for (int i = 0; i < v; i++)
    {
        vector<Vecino> vecinos = G[i];
        for (int j = 0; j < vecinos.size(); j++)
        {
            if(!visitados[vecinos[j].dst]){
                min = vecinos[j];
                ind = i;
                i = v;
                break;
            }
        }
    }

    // Elijo el vertice más cercano (menos peso) entre los insertados para insertarlo
    for (int i = 0; i < v; i++)
    {
        vector<Vecino> vecinos = G[i];
        for (int j = 0; j < vecinos.size(); j++)
        {
            if(!visitados[vecinos[j].dst] && vecinos[j].peso < min.peso){
                min = vecinos[j];
            }
        }
    }
    return min;
}

void insertar(Grafo G, Vertice w, vector<bool>& visitados, int costo){

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
        Vecino w = elegir(G, visitados, i+2);
        if (w.dst == -1) return make_pair(H,costo); // No se encontro ningun vecino que no genere ciclos.
        insertar(G, w.dst, visitados, costo);

        H.push_back(w.dst);
    }
    return make_pair(H, costo);
}