#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

//COMPILARE
//	/usr/bin/g++ -DEVAL -static -O2 -o toporder toporder.cpp -std=c++0x

//Dato un grafo orientato aciclico, stampare un suo ordinamento topologico.

//INPUT
//La prima riga contiene due interi, N e M. N e il numero di nodi, M il numero di archi. Le successive M righe contengono ognuna due interi. L’iesima riga contiene la sorgente e la destinazione dell’iesimo arco.


//OUTPUT
//La prima ed unica riga contiene N interi separati da spazio, l’ordinamento topologico trovato dall’algoritmo.


//ASSUNZIONI
// 1 ≤ N ≤ 10000
// 1 ≤ M ≤ 50000

//ESEMPIO
//	input		--------->	output
//	5 5     			3 2 0 1 4
//	3 4
//	3 2
//	2 0
//	2 4
//	0 1

//costanti
const int MAXN = 10000;
const int MAXM = 50000;

//variabili
int N = MAXN;
int M = MAXM;
int conta = 0;

//nodo
struct nodo{
  vector<int> vic;
  bool visited;
};

//grafo
vector<nodo> grafo;
vector<nodo> grafoTrasposto;

//vettori
vector<bool> messo (N);

//funzioni
stack<int> topsort();
void tsdfs(int u, stack<int>& S);
int main(){
  
  //lettura input
  ifstream in("input.txt");
  in >> N >> M;
  grafo.resize(N);
  grafoTrasposto.resize(N);
  for(int i=0;i<M;i++){
    int from, to;
    in >> from >> to;
    grafo[from].vic.push_back(to);
    grafoTrasposto[to].vic.push_back(from);
  }
  for(int i=0;i<N;i++){
    grafo[i].visited=false;
  }
//printGrafo(grafo);
//printGrafo(grafoTrasposto);

  //mio algoritmo
  stack<int> ts = topsort();

  //stampo output
  ofstream out("output.txt");
  for(int i = 0; i<N; i++){
    out << ts.top() << " ";
    ts.pop();
  }
  out << "\n";

  return 0;
}

//calcolo stack dei tempi di fine grafo
stack<int> topsort(){
  for (int i=0;i<N;i++){
    messo[i]=false;
  }
  stack<int> S;
  for (int i=0;i<N;i++){
    if (!grafo[i].visited){
      tsdfs(i,S);
    }
  }
  return S;
}

void tsdfs(int u, stack<int>& S){
  grafo[u].visited=true;
  //cout << u << " ";
  for(int v:grafo[u].vic){
    if(!grafo[v].visited){
      tsdfs(v,S);
    }
  }
  if(messo[u]==false){
    S.push(u);
    messo[u]=true;
  }
}
