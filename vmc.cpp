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


// bool cmp(const Size& lhs, const Size& rhs)
// {
//   return lhs.width < rhs.width  && visitados[w] == false ;
// }
//
// auto minmax_widths = minmax_element(sizes.begin(), sizes.end(),
//          [] (Vecino& x, Vecino& y,vector<bool> visitados) {return x.peso < y.peso && visitados == false;});
Vecino buscarMinimo(const vector<Vecino>& vecinos, vector<bool>& visitados){
  Vecino min(-1,0);
  int peso_min;
  int ind;
  //Iniciliazacion peso minimo. Se busca el primer vecino no visitado.
  for (int i = 0; i < vecinos.size(); i++) {
    if(visitados[vecinos[i].dst] == false){
      peso_min = vecinos[i].peso;
      min = vecinos[i];
      ind = i;
      break;
    }
  }

  // Busqueda de un vecino que tenga el minimo peso.
  for (int i = ind + 1 ; i < vecinos.size(); i++){
    if (visitados[vecinos[i].dst] == false && vecinos[i].peso < peso_min) {
      peso_min = vecinos[i].peso;
      min = vecinos[i];
      }
  }
  return min;
}

// Vecino buscarAristaMinima(vector<Vecino> vecinos, int w){
//   Vecino min(-1,0);
//   min = minmax_element(vecinos.begin(), vecinos.end(),
//             [] (Vecino& x, Vecino& y,int w) {return x.peso < y.peso && x.dst != w ;});

//   return min;
// }

Vecino buscarAristaMinima(vector<Vecino> vecinos, int w){
  Vecino min(-1,0);
  int peso_min;
  int ind;
  //Iniciliazacion peso minimo. Se busca la primer arista a w.
  for (int i = 0; i < vecinos.size(); i++) {
    if(vecinos[i].dst == w){
      peso_min = vecinos[i].peso;
      min = vecinos[i];
      ind = i;
      break;
    }
  }

  // Busqueda de una arista que tenga el minimo peso.
  for (int i = ind + 1 ; i < vecinos.size(); i++){
    if (vecinos[i].dst == w && vecinos[i].peso < peso_min) {
      peso_min = vecinos[i].peso;
      min = vecinos[i];
      }
  }
  return min;
}
pair<vector<int>,int> vecinoMasCercano(const Grafo& G){

  int v = 1;
  vector<int> H ;
  H.push_back(v);
  int costo = 0;
  int n = G.size();
  vector<bool> visitados(n);
  while (H.size() < n){
    Vecino w = buscarMinimo(G[v], visitados);
    if (w.dst == -1) return make_pair(H,costo); // No se encontro ningun vecino que no genere ciclos.
    
    visitados[w.dst] = true;  
    costo = costo + w.peso;
    H.push_back(w.dst);
    v = w.dst;
  }
  
  Vecino cierre = buscarAristaMinima(G[H[n-1]],H[0]); // arista que cierra el ciclo.
  if (cierre.dst == -1) return make_pair(H, costo + cierre.peso);

  else { // No existe arista que cierre el ciclo.
    return make_pair(H, costo);
  }
}

int main(int argc, char **argv) {

   
   Grafo G =
        {{Vecino(2,10), Vecino(3,20), Vecino(3,15)},
         {Vecino(1,10), Vecino(2,25), Vecino(3,35)},
         {Vecino(1,15), Vecino(2,35), Vecino(3,30)},
         {Vecino(1,8), Vecino(1,25), Vecino(1,30)}};


    Vecino min = buscarAristaMinima(G[2],3);
    cout << min.dst <<" "<<min.peso << endl; 

    return 0;
}
