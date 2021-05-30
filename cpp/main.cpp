#include "tipos.h"
#include "agm.h"
#include "vmc.h"
#include "ts1.h"
#include "ts2.h"

Grafo leerGrafo() {
  int n, m;
  cin >> n >> m;
  Grafo G(n, vector<Vecino>());
  for (int i = 0; i < m; i++) {
    int v, w, peso;
    cin >> v >> w >> peso;
    v = v-1;
    w = w-1;
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
    int costo;
    vector<int> H;

    auto start = chrono::steady_clock::now();
      if (algoritmo == "VMC") {
            pair<vector<int>,int> p = VMC(G);
            H = p.first;
            costo = p.second;
    } else if (algoritmo == "I") {
        //H,costo = I(G);
    } else if (algoritmo == "AGM") {
            pair<vector<int>,int> p = AGM(G);
            H = p.first;
            costo = p.second;
    } else if (algoritmo == "VMC-TS1") {
            // pair<vector<int>,int> p = VMC(G);
            // vector<int> Hvmc = p.first;
            // int costovmc = p.second;
            // int T = 50;  
            // int max_iter= 100;
            // int rango_iter = 20;
            // int percent= 10;
            // int top = 10;
            // pair<vector<int>,int> res = tabuSearch(G,Hvmc, costovmc, T,  max_iter, rango_iter, percent, top);
            // H = res.first;
            // costo = res.second;
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
    for (int v : H) cout << (v + 1) << " ";
    cout <<  "\n";

    return 0;
}

