//Memoria que almacena ultimos swaps

#include "ts1.h"

// bool SwapEstaEnMemoria(list<Swap>& memoria,Swap sw){
//     Swap sw_invertido = make_pair(sw.second,sw.first);
//     list <Swap> :: iterator it;
//     for(it = memoria.begin(); it != memoria.end(); ++it){
//         if (*it == sw) return true;
//         if (*it == sw_invertido) return true;
//     }
//     return false;
// }

bool SonMismaArista (const Grafo& G,const pair<int,int> a,const pair<int,int> b){
    
    //arista (i,j)
    int i = a.first;
    int j = G[i][a.second].dst;
    //arista(k,z)
    int k = b.first;
    int z = G[j][b.second].dst;

    if (i == k && j == z) return true; // mismo orden 
    if (i == z && j == k) return true; // como (i,j) == (j,i) es true

    return false;

}
bool SwapEstaEnMemoria(const Grafo& G,list<Swap>& memoria,Swap sw){
    Swap sw_invertido = make_pair(sw.second,sw.first);
    list <Swap> :: iterator it;
    for(it = memoria.begin(); it != memoria.end(); ++it){
        if (SonMismaArista(G,(*it).first, sw.first) && SonMismaArista(G,(*it).second, sw.second )) return true;
        if (SonMismaArista(G,(*it).first, sw_invertido.first) && SonMismaArista(G,(*it).second, sw_invertido.second )) return true;
        
    }
    return false;
}

tuple<vector<int>,int,Swap> obtenerMejor(const Grafo& G,vector<pair<int,int>>& vecinos,vector<int> ciclo,int costo_ciclo,list<Swap>& memoria,int hasta){
    
    // Inicializacion costo y ciclo del mejor vecino con un cambio inicial
    int i = vecinos[0].first;
    int j = vecinos[0].second;

    //if(i == n-1) {}

    pair<int,int> par_ind = IndiceAristas_en_Grafo(G, ciclo[i], ciclo[i+1], ciclo[j]);
    cout<< "kasksjdafs" <<endl;
    
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
    
    Swap sw = make_pair( make_pair(ciclo[i],dst_i_Swap) , make_pair(ciclo[j],dst_j_Swap) ); // indices de las dos aristas nuevas
    Swap reverse_sw = make_pair( make_pair(ciclo[i],dst_i) , make_pair(ciclo[j],dst_j) );// indices de las aristas sacadas



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
        
        sw = make_pair( make_pair(ciclo[i],dst_i_Swap) , make_pair(ciclo[j],dst_j_Swap) ); // indices de las dos aristas nuevas
        
        if(costo_vecino < costo_mejor_vecino){

            if(SwapEstaEnMemoria(G,memoria,sw)){ 
                if(costo_vecino < costo_ciclo){    // funcion de aspiracion
                    mejor_vecino = SwapCiclo(ciclo,i,j); // genero el nuevo ciclo
                    costo_mejor_vecino = costo_vecino;
                    reverse_sw = make_pair( make_pair(ciclo[i],dst_i) , make_pair(ciclo[j],dst_j) );;
                }
            }
            else{           // si no esta en memoria lo agrego directamente
                mejor_vecino = SwapCiclo(ciclo,i,j); // genero el nuevo ciclo
                costo_mejor_vecino = costo_vecino;
                reverse_sw = make_pair( make_pair(ciclo[i],dst_i) , make_pair(ciclo[j],dst_j) );;
            }
        }
    }
    return make_tuple(mejor_vecino,costo_mejor_vecino,reverse_sw);
}

// T = Tamanio de la memoria
// max_iter = cantidad de iteraciones maximas
// rango_iter = cantidad de iteraciones maximas en las que no se produjo cambios
// percent = tamanio del subconjunto de la vecindad que explora el algoritmo
// top = cantidad de las mejores de la vecindad sobre las que se elige 

pair<vector<int>,int> tabuSearch(const Grafo& G,vector<int> SolucionInicial,int costo_ciclo,int T, int max_iter,int rango_iter,int percent,int top){
    
    //Inicializacion de variables
    vector<int> ciclo = SolucionInicial;
    vector<int> mejor_ciclo = ciclo;
    list<Swap> memoria; // Swap = pair<pair<int,int>, pair<int,int>>
                         // donde cada par del Swap representa el indice de una arista 
                         // en el grafo
    int costo_mejor_ciclo = costo_ciclo ;
    int ult_i = 0;       // ultima iteracion donde hubo una mejora en la solucion
    vector<pair<int,int>> vecinos = createPairVector(G.size()); // Todos los posibles vecinos
    int hasta = (G.size()*percent)/100; // hasta que vecino veo
    
    //Ciclo Principal
    for (int i = 0; i < max_iter ; ++i){
        
        if( ult_i - i > rango_iter) break; // no hubo mejora en rango_iter iteraciones
        
        obtenerSubVecindad(vecinos); // realiza permutacion aleatoria de los vecinos
        
        tuple<vector<int>,int,Swap> mejor = obtenerMejor(G,vecinos,ciclo,costo_mejor_ciclo,memoria,hasta); 

        ciclo = get<0>(mejor);
        costo_ciclo = get<1>(mejor);
        Swap sw = get<2>(mejor);
        
        memoria.push_front(sw); // guardamos en memoria el Swap al principio de la lista

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