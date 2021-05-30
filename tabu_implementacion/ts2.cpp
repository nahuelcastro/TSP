//Memoria que almacena ciclos

#include "ts2.h"

vector<pair<int,int>> createPairVector(int n){
    vector<pair<int,int>> v;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {   
            v.push_back(make_pair(i,j));
        }
    }
    return v;
}

void obtenerSubVecindad(vector<pair<int,int>>& v){

    random_shuffle(v.begin(), v.end());
} 

vector<int> SwapCiclo(const vector<int>& ciclo,int i ,int j){

    // ciclo_Swap[0:i] = ciclo[0:i]
    auto first = ciclo.begin();
    auto last = ciclo.begin() + i + 1 ;  
    vector<int> ciclo_Swap(first, last);

    //ciclo_Swap[i+1:j] = reverso(ciclo_Swap[i+1:j])
    for (int k = j; k >= i+1; k--){
        ciclo_Swap.push_back(ciclo[k]);
    }

    // ciclo_Swap[j+1:] = ciclo[j+1:]
    for (int k = j+1;k < ciclo.size(); k++){
        ciclo_Swap.push_back(ciclo[k]);
    }
    return ciclo_Swap;
}

pair<int,int> IndiceAristas_en_Grafo(const Grafo& G,int i , int z,int j ){
    // devuelve los indices del vertice z y j en G[i]
    int indice_j , indice_z;

    for (int k = 0; i < G[i].size() ; ++k){

        if (G[i][k].dst == z){
            indice_z = k;
        }
        if (G[i][k].dst == j){
            indice_j = k;
        }
    }   
    return make_pair(indice_z,indice_j);
}

bool CicloEstaEnMemoria(list<vector<int>>& memoria,vector<int> ciclo){
    list <vector<int>> :: iterator it;
    for(it = memoria.begin(); it != memoria.end(); ++it){
        if (*it == ciclo) return true;
    }
    return false;
}

tuple<vector<int>,int> obtenerMejor(const Grafo& G,vector<pair<int,int>>& vecinos,vector<int> ciclo,int costo_ciclo,list<vector<int>>& memoria,int hasta){
    
    // Inicializacion costo y ciclo del mejor vecino con un cambio inicial
    int i = vecinos[0].first;
    int j = vecinos[0].second;

    pair<int,int> par_ind = IndiceAristas_en_Grafo(G, ciclo[i], ciclo[i+1], ciclo[j]);
    int dst_i = par_ind.first;          // indice del destino de original en Ciclo
    int dst_i_Swap = par_ind.second;    // indice del destino del Swap 

    Peso peso_arista1 = G[ciclo[i]][dst_i].dst ;     // peso arista original
    Peso peso_arista1_Swap = G[ciclo[i]][dst_i_Swap].dst ; // peso arista Swap

    par_ind = IndiceAristas_en_Grafo(G, ciclo[j], ciclo[j+1], ciclo[i+1]);
    int dst_j = par_ind.first;          // indice del destino de original en Ciclo
    int dst_j_Swap = par_ind.second;    // indice del destino del Swap 
    
    Peso peso_arista2 = G[ciclo[j]][dst_j].dst ; // peso arista original
    Peso peso_arista2_Swap = G[ciclo[j]][dst_j_Swap].dst ; // peso arista Swap
        
    int costo_mejor_vecino = costo_ciclo - peso_arista1 - peso_arista2; // quitar peso de aristas originales
    costo_mejor_vecino +=  peso_arista1_Swap - peso_arista2_Swap; // agregar peso de aristas nuevas

    vector<int> mejor_vecino = SwapCiclo(ciclo,i,j); // genero el nuevo ciclo

    for (int k = 0; k < hasta; k++ ){
        i = vecinos[k].first;
        j = vecinos[k].second;

        par_ind = IndiceAristas_en_Grafo(G, ciclo[i], ciclo[i+1], ciclo[j]);
        dst_i = par_ind.first;          // indice del destino de original en Ciclo
        dst_i_Swap = par_ind.second;    // indice del destino del Swap 

        Peso peso_arista1 = G[ciclo[i]][dst_i].dst ;     // peso arista original
        Peso peso_arista1_Swap = G[ciclo[i]][dst_i_Swap].dst ; // peso arista Swap

        par_ind = IndiceAristas_en_Grafo(G, ciclo[j], ciclo[j+1], ciclo[i+1]);
        dst_j = par_ind.first;          // indice del destino de original en Ciclo
        dst_j_Swap = par_ind.second;    // indice del destino del Swap 
        
        Peso peso_arista2 = G[ciclo[j]][dst_j].dst ; // peso arista original
        Peso peso_arista2_Swap = G[ciclo[j]][dst_j_Swap].dst ; // peso arista Swap
            
        int costo_vecino = costo_ciclo - peso_arista1 - peso_arista2; // quitar peso de aristas originales
        costo_vecino +=  peso_arista1_Swap - peso_arista2_Swap; // agregar peso de aristas nuevas
        
        vector<int> vecino = SwapCiclo(ciclo,i,j);

        if(costo_vecino < costo_mejor_vecino){

            if(CicloEstaEnMemoria(memoria,vecino)){ 
                if(costo_vecino < costo_ciclo){    // funcion de aspiracion
                    mejor_vecino = vecino; // genero el nuevo ciclo
                    costo_mejor_vecino = costo_vecino;
                }
            }
            else{           // si no esta en memoria lo agrego directamente
                mejor_vecino = vecino; // genero el nuevo ciclo
                costo_mejor_vecino = costo_vecino;
            }
        }
    }
    return make_tuple(mejor_vecino,costo_mejor_vecino);
}


// T = Tamanio de la memoria
// max_iter = cantidad de iteraciones maximas
// rango_iter = cantidad de iteraciones maximas en las que no se produjo cambios
// percent = tamanio del subconjunto de la vecindad que explora el algoritmo
// top = cantidad de las mejores de la vecindad sobre las que se elige 

pair<vector<int>,int> tabuSearch2(const Grafo& G,vector<int> SolucionInicial,int costo_ciclo,int T, int max_iter,int rango_iter,int percent,int top){
    
    //Inicializacion de variables
    vector<int> ciclo = SolucionInicial;
    vector<int> mejor_ciclo = ciclo;
    list<vector<int>> memoria; // Memoria almacena ultimos ciclos
                         
    int costo_mejor_ciclo = costo_ciclo ;
    int ult_i = 0;       // ultima iteracion donde hubo una mejora en la solucion
    vector<pair<int,int>> vecinos = createPairVector(G.size()); // Todos los posibles vecinos
    int hasta = (G.size()*percent)/100; // hasta que vecino veo
    
    //Ciclo Principal
    for (int i = 0; i < max_iter ; ++i){
        
        if( ult_i - i > rango_iter) break; // no hubo mejora en rango_iter iteraciones
        
        obtenerSubVecindad(vecinos); // realiza permutacion aleatoria de los vecinos
        
        tuple<vector<int>,int> mejor = obtenerMejor(G,vecinos,ciclo,costo_mejor_ciclo,memoria,hasta); 
        ciclo = get<0>(mejor);
        costo_ciclo = get<1>(mejor);
        
        memoria.push_front(ciclo); // guardamos en memoria el Swap al principio de la lista

        if (costo_ciclo < costo_mejor_ciclo) {
            mejor_ciclo = ciclo;
            costo_mejor_ciclo = costo_ciclo;
            ult_i = i;  // actualizo cuando se efectuo el ultimo cambio
        }
        while(memoria.size() > T){ // si la memoria esta llena elimino el elemento que fue agregado primero
            memoria.pop_back();
        }
    }
    return make_pair(mejor_ciclo,costo_mejor_ciclo);
}