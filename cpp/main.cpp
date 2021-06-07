#include "tipos.h"
#include "agm.h"
#include "vmc.h"
#include "ts1.h"
#include "ts2.h"
#include "ins.h"
#include <random>
Grafo leerGrafo() {
      int n, m;
      cin >> n >> m;
      Grafo G(n, vector<Vecino>());
      for (int i = 0; i < m; i++) {
            int v, w, peso;
            cin >> v >> w >> peso;
            v = v-1;
            w = w-1;
            G[v].push_back(Vecino(v,w, peso));
            G[w].push_back(Vecino(w,v, peso));
      }
      return G;
}

int randomfunc(int j)
{
    return rand() % j;
}
int main(int argc, char **argv) {

        // Leemos el parametro que indica el algoritmo a ejecutar.
        map <string, string> algoritmos_implementados = {
                {"VMC",   "Vecino mas cercano"},
                {"random",  "random"},
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

        //parametros Tabu
        long T ;
        long max_iter ;
        long rango_iter ;
        long percent ;
        if (argc > 2){
                T = strtol(argv[2], NULL, 10);
                max_iter = strtol(argv[3], NULL, 10);
                rango_iter = strtol(argv[4], NULL, 10);
                percent = strtol(argv[5], NULL, 10);
        }
        
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
        } else if (algoritmo == "random") {
                vector<int> v = {0,1,2,4,5,6,7,8,9,10,11};
                vector<int> cambio ; 
                //auto rd = random_device {}; 
                //auto rng = std::default_random_engine { rd() };

                for (size_t i = 0; i < 6; i++){ 
                        cambio = v; 
                        //shuffle(v.begin(), v.end(),default_random_engine(0));
                        //random_shuffle(cambio.begin(), cambio.end(),randomfunc);
                        //std::shuffle(begin(cambio), std::end(cambio), rng);
                        
                        for (int e : cambio) cout << e << " ";
                        cout<<endl;
                }

        }else if (algoritmo == "I") {
                pair<vector<int>,int> p = I(G);
                H = p.first;
                costo = p.second;
        } else if (algoritmo == "AGM") {
                pair<vector<int>,int> p = AGM(G);
                H = p.first;
                costo = p.second;
        } else if (algoritmo == "VMC-TS1") {
                pair<vector<int>,int> p = VMC(G);
                vector<int> solucion_inicial = p.first;
                int costo_inicial = p.second;

                pair<vector<int>,int> res = tabuSearch(G,solucion_inicial, costo_inicial, T,  max_iter, rango_iter, percent);
                H = res.first;
                costo = res.second;
        
        } else if (algoritmo == "I-TS1") {

                pair<vector<int>,int> p = I(G);
                vector<int> solucion_inicial = p.first;
                int costo_inicial = p.second;

                pair<vector<int>,int> res = tabuSearch(G,solucion_inicial, costo_inicial, T,  max_iter, rango_iter, percent);
                H = res.first;
                costo = res.second;

        } else if (algoritmo == "AGM-TS1") {
                pair<vector<int>,int> p = AGM(G);
                vector<int> solucion_inicial = p.first;
                int costo_inicial = p.second;

                pair<vector<int>,int> res = tabuSearch(G,solucion_inicial, costo_inicial, T,  max_iter, rango_iter, percent);
                H = res.first;
                costo = res.second;

        } else if (algoritmo == "VMC-TS2") {
                pair<vector<int>,int> p = VMC(G);
                vector<int> solucion_inicial = p.first;
                int costo_inicial = p.second;

                pair<vector<int>,int> res = tabuSearch2(G,solucion_inicial, costo_inicial, T,  max_iter, rango_iter, percent);
                H = res.first;
                costo = res.second;

        } else if (algoritmo == "I-TS2") {
                pair<vector<int>,int> p = I(G);
                vector<int> solucion_inicial = p.first;
                int costo_inicial = p.second;

                pair<vector<int>,int> res = tabuSearch2(G,solucion_inicial, costo_inicial, T,  max_iter, rango_iter, percent);
                H = res.first;
                costo = res.second;
        } else if (algoritmo == "AGM-TS2") {
                pair<vector<int>,int> p = AGM(G);
                vector<int> solucion_inicial = p.first;
                int costo_inicial = p.second;

                pair<vector<int>,int> res = tabuSearch2(G,solucion_inicial, costo_inicial, T,  max_iter, rango_iter, percent);
                H = res.first;
                costo = res.second;
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

