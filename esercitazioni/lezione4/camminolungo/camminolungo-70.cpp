#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//COMPILARE
//	/usr/bin/g++ -DEVAL -static -O2 -o camminolungo camminolungo.cpp -std=c++0x

//Dato un grafo orientato aciclico, trovare il cammino piu lungo nel grafo.

//INPUT
//La prima riga contiene due interi, N e M. N e il numero di nodi, M il numero di archi. Le successive M righe contengono ognuna due interi. L’iesima riga contiene la sorgente e la destinazione dell’iesimo arco.

//OUTPUT
//L’output consiste di un unica riga contenente un intero pari al cammino di lunghezza massima

//ASSUNZIONI
// 1 ≤ N ≤ 10000
// 1 ≤ M ≤ 50000

//costanti
const int MAXN = 10000;
const int MAXM = 50000;

//nodo
struct nodo{
  vector<int> vic;
  bool visited;
};

//grafo
vector<nodo> grafo;

//funzioni
int camminolungo(int N);

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
  }

  //mio algoritmo
  int diam = camminolungo(N);

  //stampo output
  ofstream out("output.txt");
  out<<diam<<"\n";

  return 0;
}

//funzioni
int camminolungo(int N){
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
        //if(dist[v]<0){
          dist[v]=dist[u]+1;
          if(dist[v]>max){
            max=dist[v];
          }
          S.push(v);
        //}
      }
    }
  }
  return max;
}



