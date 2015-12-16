#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//Vi viene dato in input un grafo non orientato. Dovete trovare la coppia di nodi piu lontani e stamparne la distanza.

//INPUT
//La prima riga contiene due interi, N e M. N e il numero di nodi, M il numero di archi. Le successive M righe contengono due interi per riga, i due nodi collegati dall’arco.

//OUTPUT
//Un intero, uguale alla massima distanza fra due nodi.

// 1 ≤ N ≤ 1000
// 1 ≤ M ≤ 10000

//NOTE
//Il percorso minimo fra il nodo 1 ed il nodo 5 utilizza 3 archi (1,4,3,5)

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
int diametro(vector<nodo>& grafo, int N);

int main(){
  
  //variabili
  int N;
  int M;

  //lettura input
  ifstream in("input.txt");
  in >> N >> M;
  grafo.resize(N);
  /*for(int i=0;i<N;i++){
    grafo[i].visited=false;
  }*/
  for(int i=0;i<M;i++){
    int from, to;
    in >> from >> to;
    grafo[from].vic.push_back(to);
    grafo[to].vic.push_back(from);//perché nn orientato!
  }

  //mio algoritmo
  int diam = diametro(grafo,N);

  //stampo output
  ofstream out("output.txt");
  out<<diam<<"\n";

  return 0;
}

//funzioni
int diametro(vector<nodo>& grafo, int N){
  int max = 0;
  for(int i=0;i<N;i++){
    queue<int> S;
    S.push(i);
    int dist[N];
    for(int j=0;j<N;j++){
      dist[j]=-1;
    }
    dist[i]=0;
    while(!S.empty()){
      int u = S.front();
      S.pop();
      for(int v:grafo[u].vic){
        if(dist[v]<0){
          dist[v]=dist[u]+1;
          if(dist[v]>max){
            max=dist[v];
          }
          S.push(v);
        }
      }
    }
  }
  return max;
}


