#include "ins.h"

int elegir(Grafo G, vector<bool> insertado){ // O(n²)
    Vecino min(-1,-1,0);

    // Elijo el vertice más cercano (menos peso) a uno ya insertado
    for (int i = 0; i < insertado.size(); i++) // O(n²)
    {
        if(insertado[i]){
            vector<Vecino> vecinos = G[i];
            for (int j = 0; j < vecinos.size(); j++)
            {
                if(!insertado[vecinos[j].dst]){
                    if(min.dst == -1 || vecinos[j].peso < min.peso){
                        min = vecinos[j];
                    }
                }
            }
        }
    }
    return min.dst;
}

int insertar(Grafo G, Vertice w, map<pair<int, int>, int>longitudes, map<int, int> &conexiones, vector<bool> &insertado){
    vector<Vecino> vecinos = G[w];
    int costoViejo, nuevoCosto, iViejo, jViejo;
    bool instanciado = false;

    for (int i = 0; i < vecinos.size(); i++) {
        Vertice iVertice = vecinos[i].dst;
        if(insertado[iVertice]){
            for (int j = 0; j < vecinos.size(); ++j) {
                Vertice jVertice = vecinos[j].dst;
                bool esConsecutivoDeI = insertado[jVertice] && conexiones[iVertice] == jVertice;
                if(instanciado && esConsecutivoDeI) {
                    costoViejo = nuevoCosto;
                    nuevoCosto = min(longitudes[{w,iViejo}] + longitudes[{w,jViejo}] - longitudes[{iViejo,jViejo}], nuevoCosto);
                    if(costoViejo != nuevoCosto) {
                        iViejo = iVertice;
                        jViejo = jVertice;
                    }
                }else if(!instanciado && esConsecutivoDeI){
                    nuevoCosto = longitudes[{w,i}] + longitudes[{w,j}] - longitudes[{i,j}];
                    instanciado = true;
                    iViejo = iVertice;
                    jViejo = jVertice;
                }
            }
        }
    }
    if(conexiones[iViejo] == jViejo) {
        conexiones[w] = jViejo;
        conexiones[iViejo] = w;
    }else{
        conexiones[w] = iViejo;
        conexiones[jViejo] = w;
    }
    insertado[w] = true;
    return nuevoCosto;
}

pair<vector<int>,int> I(const Grafo& G){
    vector<int> H;
    int costo = 0;
    int n = G.size();
    vector<bool> insertado(n);
    map<int, int> conexiones;
    map<pair<int,int>, int> longitudes;

    // Instancio las conexiones en el grafo
    for (int i = 0; i < n; ++i) { // O(n)
        conexiones[i] = -1;
    }

    // Instancio las longitudes entre vertices
    for (int i = 0; i < n; ++i) { // O(n*n*(n-1)/2) -> O(n³) (menos pero ponele)
        for (int j = 0; j < G[i].size(); ++j) {
            longitudes.insert({{G[i][j].origen,G[i][j].dst}, G[i][j].peso});
        }
    }

    // Agrego los tres primeros vertices del ciclo
    for (int i = 0; i < 2; i++) { // O(log(n))
        costo += longitudes[{i,i+1}];
        conexiones[i] = i+1;
        insertado[i]=true;
    }
    conexiones[2]=0;
    costo += longitudes[{0,2}];
    insertado[2]=true;

    // Elijo e inserto el resto de los vertices
    for (int i = 3 ; i < n; i++){ // O(n²*log(n))
        Vertice w = elegir(G, insertado);
        if (w == -1) return make_pair(H,costo); // No se encontro ningun vecino que no genere ciclos.
        costo += insertar(G, w, longitudes, conexiones, insertado);
    }

    // Agrego el camino de vertices en orden
    H.push_back(0);
    int proximo = 0;
    for (int i = 0; i < n-1; ++i) { // O(n)
        proximo = conexiones[proximo];
        H.push_back(proximo);
    }
    return make_pair(H, costo); // O(n)
}