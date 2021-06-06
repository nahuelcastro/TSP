#include "ts2.h"
//tabu search implementacion con Memoria que almacena ultimas aristas

bool EstaEnMemoria(list<pair<Vecino,Vecino>>& memoria,pair<Vecino,Vecino> sw){
    pair<Vecino,Vecino> sw_invertido = make_pair(sw.second,sw.first);
    list <pair<Vecino,Vecino>> :: iterator it;
    for(it = memoria.begin(); it != memoria.end(); ++it){
        if (*it == sw) return true;
        if (*it == sw_invertido) return true;
    }
    return false;
}

tuple<vector<int>,int,pair<Vecino,Vecino>> obtenerMejor(const Grafo& G,vector<pair<int,int>>& vecinos,vector<int> ciclo,int costo_ciclo,list<pair<Vecino,Vecino>>& memoria,int hasta){
    
    // Inicializacion costo y ciclo del mejor vecino con un cambio inicial
    int n = G.size();

    int i = vecinos[0].first;
    int j = vecinos[0].second;

    int vecino_i = (i == n-1) ? 0 : i+1; // si  i = n-1 cierra el ciclo 
    int vecino_j = (j == n-1) ? 0 : j+1; 

    pair<Vecino,Vecino> aristas_desde_i = AristasDesde( G[ciclo[i]] , ciclo[vecino_i], ciclo[j] ); // <arista original del ciclo, arista nueva> 
    pair<Vecino,Vecino> aristas_desde_j = AristasDesde( G[ciclo[j]], ciclo[vecino_j], ciclo[vecino_i]);
    
    int costo_mejor_vecino = costo_ciclo ;
    costo_mejor_vecino -= (aristas_desde_i.first).peso - (aristas_desde_j.first).peso; // quitar peso de aristas originales
    costo_mejor_vecino +=  (aristas_desde_i.second).peso + (aristas_desde_j.second).peso; // agregar peso de aristas nuevas
    
    pair<Vecino,Vecino> sw = make_pair( aristas_desde_i.second , aristas_desde_j.second );         // aristas nuevas
    pair<Vecino,Vecino> reverse_sw = make_pair( aristas_desde_i.first , aristas_desde_j.first);    // aristas quitadas

    vector<int> mejor_vecino = SwapCiclo(ciclo,i,j); // genero el nuevo ciclo

    for (int k = 1; k < hasta; k++ ){
        i = vecinos[k].first;
        j = vecinos[k].second;

        vecino_i = (i == n-1) ? 0 : i+1; 
        vecino_j = (j == n-1) ? 0 : j+1; 

        aristas_desde_i = AristasDesde( G[ciclo[i]] , ciclo[vecino_i], ciclo[j] );
        aristas_desde_j = AristasDesde( G[ciclo[j]], ciclo[vecino_j], ciclo[vecino_i]);
        
        int costo_vecino = costo_ciclo ;
        costo_vecino -= (aristas_desde_i.first).peso - (aristas_desde_j.first).peso; 
        costo_vecino +=  (aristas_desde_i.second).peso + (aristas_desde_j.second).peso; 
        
        sw = make_pair( aristas_desde_i.second , aristas_desde_j.second );            

        if(costo_vecino < costo_mejor_vecino){

            if(EstaEnMemoria(memoria,sw)){ 
                if(costo_vecino < costo_ciclo){         // funcion de aspiracion
                    mejor_vecino = SwapCiclo(ciclo,i,j); // genero el nuevo ciclo
                    costo_mejor_vecino = costo_vecino;
                    reverse_sw = make_pair( aristas_desde_i.first , aristas_desde_j.first);
                }
            }

            else{           // si no esta en memoria lo agrego directamente
                mejor_vecino = SwapCiclo(ciclo,i,j); // genero el nuevo ciclo
                costo_mejor_vecino = costo_vecino;
                reverse_sw = make_pair( aristas_desde_i.first , aristas_desde_j.first);
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
pair<vector<int>,int> tabuSearch2(const Grafo& G,vector<int> SolucionInicial,int costo_ciclo,int T, int max_iter,int rango_iter,int percent ){
    
    //Inicializacion de variables
    vector<int> ciclo = SolucionInicial;
    vector<int> mejor_ciclo = ciclo;
    list<pair<Vecino,Vecino>> memoria; 
    int costo_mejor_ciclo = costo_ciclo ;
    int ult_i = 0;              // ultima iteracion donde hubo una mejora en la solucion
    vector<pair<int,int>> vecinos = createPairVector(G.size()); // Todos los pares de los indices de nuestro ciclo.(Sin permutacion)
    int hasta = (G.size()*percent)/100; // hasta que vecino veo
    
    //Ciclo Principal
    for (int i = 0; i < max_iter ; ++i){
        
        if( ult_i - i > rango_iter) break; // no hubo mejora en "rango_iter" iteraciones
        
        obtenerSubVecindad(vecinos);        // realiza permutacion aleatoria de los vecinos
        
        tuple<vector<int>,int,pair<Vecino,Vecino>> mejor = obtenerMejor(G,vecinos,ciclo,costo_mejor_ciclo,memoria,hasta); 

        ciclo = get<0>(mejor);
        costo_ciclo = get<1>(mejor);
        pair<Vecino,Vecino> sw = get<2>(mejor); // aristas sacadas
        
        memoria.push_front(sw); // guardamos al principio de la lista "memoria" las aristas quitadas 

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