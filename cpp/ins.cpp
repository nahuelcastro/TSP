#include "tipos.h"

Vecino elegir(Grafo G, vector<bool>& visitados, int v){
    Vecino min(-1,-1, 0);
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

int insertar(Grafo G, Vertice w, vector<bool>& visitados, int& costo){
    vector<Vecino> vecinos = G[w];
    int pesoCaminoExistente, nuevoCosto;
    for (int i = 0; i < vecinos.size(); i++)
    {
        for (int j = i+1; j < vecinos.size(); j++)
        {
            if(j==1){ // Una cabezeada mística, estaba muy cansado cuando lo hice, perdón
                nuevoCosto = vecinos[i].peso + vecinos[j].peso;
            }
            if(nuevoCosto)
            if(visitados[vecinos[i].dst] && visitados[vecinos[j].dst]){
                for (int q = 0; q < G[i].size(); q++) // Tiene que haber una mejor forma de hacerlo que esto, medio cabeza, pero buen, queda O(n^3), si estuviese ordenado quedaría O(n^2*log(n))
                {
                    if(G[i][q].dst == vecinos[j].dst){
                        pesoCaminoExistente = G[i][q].peso;
                        break;
                    }
                }
                nuevoCosto = min(vecinos[i].peso + vecinos[j].peso - pesoCaminoExistente, nuevoCosto);
            }
        }
    }
    visitados[w] = true;
    costo += nuevoCosto;
    return costo;

}

pair<vector<int>,int> I(const Grafo& G){
    vector<int> H;
    int costo = 0;
    int n = G.size();
    vector<bool> visitados(n);
    // Agrego el primer vertice del ciclo
    H.push_back(0);
    visitados[0] = true;
    // Agrego los dos siguientes vertices del ciclo
    for (int i = 1; i < 3; i++)
    {
        H.push_back(i);
        vector <Vecino> vecinos = G[i];
        for (int j = 0; j < vecinos.size(); j++)
        {
            if(vecinos[j].dst == j){
                costo += vecinos[j].peso;
            }
        }
        visitados[i] = true;
    }
    // Elijo e inserto los vertices
    for (int i = 0 ; i < n-1; i++){
        Vecino w = elegir(G, visitados, i+2);
        if (w.dst == -1) return make_pair(H,costo); // No se encontro ningun vecino que no genere ciclos.
        costo = insertar(G, w.dst, visitados, costo);
        H.push_back(w.dst);
    }
    return make_pair(H, costo);
}