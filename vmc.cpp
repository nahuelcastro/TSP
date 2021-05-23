
bool cmp(const Size& lhs, const Size& rhs)
{
  return lhs.width < rhs.width  && visitados[w] == false ;
}

// auto minmax_widths = std::minmax_element(sizes.begin(), sizes.end(),
//          [] (Size const& lhs, Size const& rhs) {return lhs.width < rhs.width;});

pair<vector<int>,int> vecinoMasCercano(Grafo G){

  int v = 1 // = v0
  vector<int> H ;
  H.push_back(v);
  int costo = 0;
  vector<bool> visitados(n);
  while (H.size() <= n){
    int w = min_element(sizes.begin(), sizes.end(), cmp);
    visitados[w] = true;
    costo = costo //+ peso(v->w);
    H.push_back(w);
    w = v;
  }
  return make_pair(H,costo);
}



// Prim (Grafo G)
//   visitado [n] = {false, . . . ,false}
//   distancia [n] = { Infinito , . . . , Infinito}
//   padre[n] = { null , . . . , null }
//   s = tomo un nodo cualquiera de G como nodo i n i c i a l
//     para cada w en V[G] hacer
//     si existe arista entre s y w entonces9distancia [w] = peso (s, w)
//     padre[w] = s
//   distancia [s] = 0
//   visitado [s] =true
//   mientras que no esten visitados todos hacer
//     v = nodo de menor distancia para agregar que no fue visitado aun
//     visitado [v] =true
//     para cada w en sucesores (G, v) hacer
//     si distancia [w] > peso(v, w) entonces
//     distancia [w] = peso(v, w)
//     padre[w] = v
//   devolver padres
