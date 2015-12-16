#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

//COMPILARE
//	/usr/bin/g++ -DEVAL -static -O2 -o componente componente.cpp -std=c++0x

//Dato un grafo orientato, trovare la dimensione della componente fortemente connessa di dimensione massima. Un insieme di nodi forma una componente fortemente connessa se esiste un percorso fra ogni coppia di nodi in entrambe le direzioni.

//INPUT
//La prima riga contiene due interi, N e M. N e il numero di nodi, M il numero di archi. Le successive M righe contengono ognuna due interi. L’iesima riga contiene la sorgente e la destinazione dell’iesimo arco.

//OUTPUT
//Un intero pari alla dimensione della piu grande componente fortemente connessa.

//ASSUNZIONI
// 1 ≤ N ≤ 10000
// 1 ≤ M ≤ 100000

//costanti
const int MAXN = 10000;
const int MAXM = 100000;

//variabili
int N;
int M;
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
vector<int> scc(vector<nodo> grafo,vector<nodo> grafoTrasposto);
stack<int> topsort(vector<nodo> grafo);
void tsdfs(vector<nodo> grafo,int u, stack<int>& S);
vector<int> cc(vector<nodo> grafoTrasposto,stack<int> Q);
void ccdfs(vector<nodo> grafoTrasposto,int conta, int u, vector<int>& id);
int dimComMax(vector<int> cfc);
void printGrafo(vector<nodo> grafo);

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
  vector<int> cfc = scc(grafo,grafoTrasposto);
  int count = dimComMax(cfc);

  //stampo output
  ofstream out("output.txt");
  out << count << "\n";

  return 0;
}

//funzioni
int dimComMax(vector<int> cfc){
  vector<int> count (conta);
  for (int l=0; l<N; l++) {
    count[cfc[l]-1]++;
  }
  int max = 0;
  for (int l=0; l<conta; l++){
    if (count[l] > max){
      max = count[l];
    }
  }
  return max;
}

vector<int> scc(vector<nodo> grafo,vector<nodo> grafoTrasposto){
  stack<int> Q = topsort(grafo);
  return cc(grafoTrasposto,Q);
}

//calcolo stack dei tempi di fine grafo
stack<int> topsort(vector<nodo> grafo){
  for (int i=0;i<N;i++){
    messo[i]=false;
  }
  stack<int> S;
  for (int i=0;i<N;i++){
    if (!grafo[i].visited){
      tsdfs(grafo,i,S);
    }
  }
  return S;
}

void tsdfs(vector<nodo> grafo,int u, stack<int>& S){
  grafo[u].visited=true;
  //cout << u << " ";
  for(int v:grafo[u].vic){
    if(!grafo[v].visited){
      tsdfs(grafo,v,S);
    }
  }
  if(messo[u]==false){
    S.push(u);
    messo[u]=true;
  }
}

//componenti connesse del grafo trasposto con stack dei tempi di fine
//NOTA sembra andare bene mentre il problema e' l'ordine con cui sono passati i nodi nello stack :-(
vector<int> cc(vector<nodo> grafoTrasposto,stack<int> Q){
  //cout << "Q.size(): " << Q.size() << endl;
  vector<int> id (N);
  for(int i=0;i<N;i++){
    id[i]=0;
  }
  while(!Q.empty()){
    int u = Q.top();
    Q.pop();
    if(id[u]==0){
      conta = conta + 1;
      ccdfs(grafoTrasposto,conta,u,id);
    }
  }
  return id;
}

void ccdfs(vector<nodo> grafoTrasposto,int conta, int u, vector<int>& id){
  id[u] = conta;
  //cout << id[u] << " ; " << u << endl;
  for(int v:grafoTrasposto[u].vic){
    if(id[v] == 0){
      ccdfs(grafoTrasposto,conta,v,id);
    }
  }
}
//stampa grafo
void printGrafo(vector<nodo> grafo){
  for(int i = 0; i<N; i++){
    cout << i << "-->";
    for(int v:grafo[i].vic){
      cout << " " << v;
    }
    cout << endl;
  }
}
