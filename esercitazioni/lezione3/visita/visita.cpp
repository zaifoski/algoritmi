#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

//Dato un grafo orientato e un nodo di partenza S, calcolate il numero di nodi raggiungibile da S
//INPUT
//La prima riga contiene tre interi, N, M e S. N e il numero di nodi, M il numero di archi, S il nodo di partenza. Le successive M righe contengono due interi per riga, il nodo di partenza e di arrivo degli archi.
//OUTPUT
//Un intero, uguale al numero di nodi raggiungibili da S (S incluso)

// 1 ≤ N ≤ 10000
// 1 ≤ M ≤ 100000

//NOTE
//Dal nodo 1 si possono raggiungere i nodi 2,3 e 4. In totale si possono raggiungere 4 nodi.

//costanti
const int MAXN = 10000;
const int MAXM = 100000;

//nodo
struct nodo{
  vector<int> vic;
  bool visited;
};

//grafo
vector<nodo> grafo;

//funzioni
void dfs(int n,vector<nodo>& grafo, int& count);

int main(){
  
  //variabili
  int N;
  int M;
  int S;
  int count = 0;

  //lettura input
  ifstream in("input.txt");
  in >> N >> M >> S;
  grafo.resize(N);
  for(int i=0;i<N;i++){
    grafo[i].visited=false;
  }
  for(int i=0;i<M;i++){
    int from, to;
    in >> from >> to;
    grafo[from].vic.push_back(to);
  }

  //mio algoritmo
  dfs(S,grafo,count);

  //stampo output
  ofstream out("output.txt");
  out<<count<<"\n";
  return 0;
}

//funzioni
void dfs(int n,vector<nodo>& grafo, int& count){
  grafo[n].visited = true;
  count++;
  for(int v:grafo[n].vic){
    if(!grafo[v].visited){
      dfs(v,grafo,count);
    }
  }
}





