#include <iostream>
#include <vector>
#include <algorithm>
//#include <cstdio>
//#include <cstdlib>
//#include <chrono>
//#include <set>
//#include <map>



using namespace std;

typedef int Vertice;
typedef int Peso;
struct Vecino {
    Vertice dst;
    Peso peso;
    Vecino(Vertice d, Peso p) : dst(d), peso(p) {}
};

int INT_MAX = 2147483647;
Vecino V_INDEF = Vecino(INT_MAX, INT_MAX);

typedef vector<vector<Vecino>> Grafo;
vector<int> visitados;


Grafo grafo_prueba =
        {{Vecino(2-1,10), Vecino(4-1,20), Vecino(3-1,15)},
         {Vecino(1-1,10), Vecino(4-1,25), Vecino(3-1,35)},
         {Vecino(1-1,15), Vecino(2-1,35), Vecino(4-1,30)},
         {Vecino(1-1,20), Vecino(2-1,25), Vecino(3-1,30)}};


pair<int, Vecino> buscarmin(Grafo g){
    Vecino v_min = V_INDEF;
    int n_min = INT_MAX;
    for ( int n : visitados){
        for ( Vecino v : g[n]){
            bool invalido = (find(visitados.begin(), visitados.end(), v.dst) != visitados.end());
            if( v_min.peso > v.peso and !invalido){
                v_min = v;
                n_min = n;
            }
        }
    }
    return make_pair(n_min, v_min);
}


Grafo agm(Grafo g){
    Grafo res_agm (g.size()); // creamos grafo con la cantidad de nodos y los vecinos vacios
    int contador = g.size();
    visitados.push_back(0);
    while (contador != 1){
        pair<int, Vecino> t = buscarmin(g);
        Vecino vecino_min = get<1>(t);
        int n = get<0>(t);
        visitados.push_back(vecino_min.dst);
        res_agm[n].push_back(vecino_min);
        res_agm[vecino_min.dst].push_back(Vecino(n, vecino_min.peso));
        contador --;
    }

    return res_agm;
}

void print_vector(vector<Vecino> v){
    cout << "[";
    for (int i = 0; i < v.size(); i++) {
        if (i == v.size() - 1){
            cout << '(' << v[i].dst + 1 << ',' << v[i].peso << ")";
        } else {
            cout << '(' << v[i].dst + 1 << ',' << v[i].peso << "), ";
        }
    }
    cout << "]";
}

void print_grafo(Grafo g){
    for (int i = 0; i < g.size(); ++i) {
        cout << i + 1 << " -> ";
        print_vector(g[i]);
        cout << " " << endl;
    }
}

//int main(int argc, char **argv) {
//    print_grafo(agm(grafo_prueba));
//    return 0;
//}


