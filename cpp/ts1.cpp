#include "ts1.h"


vector<pair<int,int>> createPairVector(int n){
    vector<pair<int,int>> v;
    for (int i = 0; i < n; i++) {
        for (int j = i+2; j < n; j++) {
            v.push_back(make_pair(i,j));
        }
    }
    return v;
}

void obtenerSubVecindad(vector<pair<int,int>>& v){
    srand(time(NULL));
    random_shuffle(v.begin(), v.end());
}

vector<int> SwapCiclo(const vector<int>& ciclo,int i ,int j){

    vector<int> ciclo_Swap;
    
    // ciclo_Swap[0:i] = ciclo[0:i]
    for (int k = 0; k <= i; k++){
        ciclo_Swap.push_back(ciclo[k]);
    }

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

bool CicloEstaEnMemoria(list<vector<int>>& memoria,vector<int> ciclo){
    list <vector<int>> :: iterator it;
    for(it = memoria.begin(); it != memoria.end(); ++it){
        if (*it == ciclo) return true;
    }
    return false;
}

tuple<vector<int>,int> obtenerMejor(const Grafo& G,vector<pair<int,int>>& vecinos,vector<int> ciclo,int costo_ciclo,list<vector<int>>& memoria,int hasta){

    // Inicializacion costo y ciclo del mejor vecino con un cambio inicial
    int n = G.size();

    int i = vecinos[0].first;
    int j = vecinos[0].second;

    vector<int> mejor_vecino = SwapCiclo(ciclo,i,j); // genero el nuevo ciclo
    int costo_mejor_vecino = costo_camino(G, mejor_vecino);

    for (int k = 1; k < hasta; k++ ){

        i = vecinos[k].first;
        j = vecinos[k].second;

        vector<int> vecino = SwapCiclo(ciclo,i,j);
        int costo_vecino = costo_camino(G, vecino); 

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
pair<vector<int>,int> tabuSearch(const Grafo& G,vector<int> SolucionInicial,int costo_ciclo,int T, int max_iter,int rango_iter,int percent){

    //Inicializacion de variables
    vector<int> ciclo = SolucionInicial;
    vector<int> mejor_ciclo = ciclo;
    list<vector<int>> memoria; //  almacena ultimos ciclos
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