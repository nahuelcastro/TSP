
// bool cmp(const Size& lhs, const Size& rhs)
// {
//   return lhs.width < rhs.width  && visitados[w] == false ;
// }
//
// auto minmax_widths = minmax_element(sizes.begin(), sizes.end(),
//          [] (Vecino& x, Vecino& y,vector<bool> visitados) {return x.peso < y.peso && visitados == false;});
int buscarMinimo(vector<Vecino>& vecinos, vector<bool>& visitados){
  int min = -1;
  int peso_min;
  int ind;
  //Iniciliazacion peso minimo. Se busca el primer vecino no visitado.
  for (int i = 0; i < vecinos.size(); i++) {
    if(visitados[vecinos[i].dst] == false){
      peso_min = vecinos[i].peso;
      min = vecinos[i].dst;
      ind = i;
      break;
    }
  }
  // No se encontro ningun vecino no visitado.
  if (min ==-1) return min;

  // Busqueda de un vecino que tenga el minimo peso.
  for (int i = ind + 1 ; i < vecinos.size(); i++){
    if (visitados[vecinos[i].dst] == false && vecinos[i].peso < peso_min) {
      peso_min = vecinos[i].peso;
      min = vecinos[i].dst;
  }

  return min;

}
pair<vector<int>,int> vecinoMasCercano(Grafo G){

  int v = 1
  vector<int> H ;
  H.push_back(v);
  int costo = 0;
  vector<bool> visitados(n);
  while (H.size() < n){
    int w = -1;
    w = buscarMinimo(G[v], visitados);
    if (w == -1) return make_pair(H,costo); // no se encontro ningun vecino que no genere ciclos.
    visitados[w] = true;
    costo = costo + w.peso;
    H.push_back(w);
    v = w;
  }
  if (existe arista de H[0] a H[n-1]){
    return make_pair(H,costo + peso de esa arista);
  }
  else {
    error
  }
}
