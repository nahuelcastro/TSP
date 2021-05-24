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



Grafo grafo_prueba =
        {{Vecino(2-1,10), Vecino(4-1,20), Vecino(3-1,15)},
         {Vecino(1-1,10), Vecino(4-1,25), Vecino(3-1,35)},
         {Vecino(1-1,15), Vecino(2-1,35), Vecino(4-1,30)},
         {Vecino(1-1,20), Vecino(2-1,25), Vecino(3-1,30)}};


// DFS

vector<bool> visitados(grafo_prueba.size(),false);
vector<int> orden;

void dfs_rec(int v){

    for (Vecino n : grafo_prueba[v]){ // CAMBIAR GRAFO PRUEBA
        if (visitados[n.dst] == false){
            visitados[n.dst] = true;
            orden.push_back(n.dst);
//          cout << n.dst << endl;
            dfs_rec(n.dst);
        }
    }
}
vector<int> dfs(const Grafo& G,int v0){ // 0 1 3 2 ->    1 2 4 3
    v0 = 0 ;

    visitados[v0] = true;
    orden.push_back(v0);
    dfs_rec(v0);

    return orden;
}


// FIN DFS





pair<int, Vecino> buscarmin(Grafo g){
    Vecino v_min = V_INDEF;
    int n_min = INT_MAX;
    for (int i = 0; i < visitados.size(); i++) {
        if(visitados[i]){
            for ( Vecino v : g[i]){
                bool visitado = visitados[v.dst];
                if( v_min.peso > v.peso and !visitado){
                    v_min = v;
                    n_min = i;
                }
            }
        }
    }
    return make_pair(n_min, v_min);
}

Grafo agm(Grafo g){
    int v_0 = 0;
    Grafo res_agm (g.size()); // creamos grafo con la cantidad de nodos y los vecinos vacios
    int contador = g.size();
    visitados[v_0] = true;
    while (contador != 1){
        pair<int, Vecino> t = buscarmin(g);
        Vecino vecino_min = get<1>(t);
        int n = get<0>(t);
        visitados[vecino_min.dst] = true;
        res_agm[n].push_back(vecino_min);
        res_agm[vecino_min.dst].push_back(Vecino(n, vecino_min.peso));
        contador --;
    }

    return res_agm;
}


void print_vecino(vector<Vecino> v){
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

void print_camino(vector<int> v){
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] + 1 << " ";
    }
    cout << endl;

}

void print_grafo(Grafo g){
    for (int i = 0; i < g.size(); ++i) {
        cout << i + 1 << " -> ";
        print_vecino(g[i]);
        cout << " " << endl;
    }
}


int peso_camino(Grafo g, vector<int> camino){
    int res = 0;
    for (int i = 0; i < camino.size(); ++i) {
        int s = i + 1;
        if (s == camino.size()) s = 0;
        for (Vecino v : g[camino[i]]) {
            if (v.dst == camino[s]) {
                res += v.peso;
                break;
            }
        }
    }
    return res;
}

void limpiar_visitados(){
    for (int i = 0; i < visitados.size() ; ++i) {
        visitados[i] = false;
    }
}

void AGM(Grafo g){
    Grafo g_agm = agm(g);
    limpiar_visitados();
    vector<int> camino = dfs(g_agm,0);
    cout<< " AGUANTE ALL BOYS" << endl;
    int peso = peso_camino(g,camino);

    cout << g.size() << " " << peso << endl;
    print_camino(camino);
}

//int main(int argc, char **argv) {
////    print_grafo(agm(grafo_prueba));
//    AGM(grafo_prueba);
//    return 0;
//}


