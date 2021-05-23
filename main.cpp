#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <set>
#include <map>

typedef int Vertice;
typedef int Peso;
struct Vecino {
  Vertice dst;
  Peso peso;
  Vecino(Vertice d, Peso p) : dst(d), peso(p) {}
};

typedef vector<vector<Vecino>> Grafo;

Grafo leerGrafo() {
  int n, m;
  cin >> n >> m;
  Grafo G(n, vector<Vecino>());
  for (int i = 0; i < m; i++) {
    int v, w, peso;
    cin >> v >> w >> peso;
    G[v].push_back(Vecino(w, peso));
    G[w].push_back(Vecino(v, peso));
  }
  return G;
}

int main(int argc, char **argv) {

    // Leemos el parametro que indica el algoritmo a ejecutar.
    map <string, string> algoritmos_implementados = {
            {"VMC",   "Vecino mas cercano"},
            {"I",   "Insercion"},
            {"AGM", "Arbol generador minimo"},
            {"VMC-TS1",   "Vecino mas cercano"},
            {"I-TS1",   "Insercion"},
            {"AGM-TS1", "Arbol generador minimo"},
            {"VMC-TS2",   "Vecino mas cercano"},
            {"I-TS2",   "Insercion"},
            {"AGM-TS2", "Arbol generador minimo"},
    };

    // Verificar que el algoritmo pedido exista.
    if (argc < 2 || algoritmos_implementados.find(argv[1]) == algoritmos_implementados.end()) {
        cerr << "Metodo no encontrado: " << argv[1] << endl;
        cerr << "Los metodos existentes son: " << endl;
        for (auto &alg_desc: algoritmos_implementados)
            cerr << "\t- " << alg_desc.first << ": " << alg_desc.second << endl;
        return 0;
    }
    string algoritmo = argv[1];

    // Leemos el input.
    Grafo G = leerGrafo();
    // Ejecutamos el algoritmo y obtenemos su tiempo de ejecución.
    int costo = 0;
    vector<int> H;

    auto start = chrono::steady_clock::now();
    if (algoritmo == "VMC") {
        //H,costo = VMC(G);
    } else if (algoritmo == "I") {
        //H,costo = I(G);
    } else if (algoritmo == "AGM") {
        //H,costo = AGM();
    } else if (algoritmo == "VMC-TS1") {
          //H,costo = VMC(G);
    } else if (algoritmo == "I-TS1") {
          //H,costo = I(G);
    } else if (algoritmo == "AGM-TS1") {
          //H,costo = AGM();
    } else if (algoritmo == "VMC-TS2") {
          //H,costo = VMC(G);
    } else if (algoritmo == "I-TS2") {
          //H,costo = I(G);
    } else if (algoritmo == "AGM-TS2") {
          //H,costo = AGM();
    }
    auto end = chrono::steady_clock::now();
    double total_time = chrono::duration<double, milli>(end - start).count();

    // Imprimimos el tiempo de ejecución por stderr.
    clog << total_time << endl;

    // Imprimimos el resultado por stdout.
    cout << H.size() << " " << costo << endl;
    for (int v : H) cout << v << " ";
    cout <<  "\n";

    return 0;
}
