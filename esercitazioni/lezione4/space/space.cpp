#include <fstream>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

//COMPILARE
//	/usr/bin/g++ -DEVAL -static -O2 -o space space.cpp -std=c++0x

//Vi viene dato in input un grafo orientato ed una coppia di nodi S e T. Dovete trovare quanti diversi cammini di lunghezza minima ci sono fra S e T.

//INPUT
//L’input rappresenta una galassia. La prima riga contiene due interi, N (il numero di pianeti) e M (il numero di wormhole). Le successive M righe contengono ognuna due interi separati da spazio. L’i-esima riga contiene gli identificatori dei due pianeti collegati dall i-esimo wormhole.


//OUTPUT
//La prima riga contiene l’intero K, il numero di vicer ́ installati nella galassia. La riga successiva e contiene gli identificatori dei pianeti in cui sono stati installati i vicer ́ .

//ASSUNZIONI
// 1 ≤ N ≤ 500000
// 1 ≤ M ≤ 1000000
// K >= 2

//costanti
const int MAXN = 500000;
const int MAXM = 1000000;

//variabili
int N = 0;
int M = 0;
int conta = 0;
int nVice = 1;

//nodo
struct nodo{
  vector<int> vic;
  bool visited;
};

//grafo
vector<nodo> grafo;
vector<nodo> viceres;

//funzioni
vector<int> cc(vector<nodo> grafo,int i);
void ccdfs(int conta, int u, vector<int>& id,vector<nodo>& grafo);
int contaVicere(vector<int>& ccI, int i);
int contaFun(int comp,int vicr,vector<nodo>& componente);

int main(){
  
  //lettura input
  ifstream in("input.txt");
  in >> N >> M;

  //GRAFO
  grafo.resize(N);
  for(int i=0;i<M;i++){
    int from, to;
    in >> from >> to;
    grafo[from].vic.push_back(to);
    grafo[to].vic.push_back(from);
  }

  //VICERE
  viceres.resize(nVice);
  //viceres[nVice].visited=true;
  for(int i=0;i<N;i++){
    viceres[0].vic.push_back(i);
  }
  
  //mio algoritmo
  for(int i = 0; i<N; i++){//per ogni nodo i..
    vector<int> ccI = cc(grafo,i);//..mi riporto le componenti connesse tolto il nodo i
    if(conta > 1){
      int nVice = contaVicere(ccI,i);
    }
  }

  //stampo output
  ofstream out("output.txt");
  out << nVice << " " << " " << "\n";

  return 0;
}

//funzioni

int contaVicere(vector<int>& ccI, int i){
  vector<nodo> componente;
  componente.resize(conta);
  for(int j = 0; j<N; j++){//per ogni nodo lo assegno alla sua componente
    if(j!=i){ //tranne quello attentato
      componente[ccI[j]-1].vic.push_back(j);
    }
  }
  return contaFun(1,1,componente);
}
int contaFun(int comp,int vicr,vector<nodo>& componente){
  for(int nc:componente[comp].vic){
    for(int v:viceres[vicr].vic){
      if(v == nc){
        for(int v:viceres[vicr].vic){
        //0+contaFun(comp+1,vicr+1);
      }
    }
  }
}

vector<int> cc(vector<nodo> grafo,int i){
  conta = 0;
  vector<int> id (N);
  stack<int> S;
  for(int j=0;j<N;j++){
    S.push(j);
    id[j]=0;
  }
  id[i]=-1;
  while(!S.empty()){
    int u = S.top();
    S.pop();
    //cout << u << " "<< id[u] << " ";
    if(id[u]==0){
      conta = conta + 1;
      ccdfs(conta,u,id,grafo);
    }
  }
  //cout << i << ": "<< conta << ".\t";
  return id;
}

void ccdfs(int conta, int u, vector<int>& id,vector<nodo>& grafo){
  if(id[u]!=-1){
    id[u] = conta;
    //cout << id[u] << " ; " << u << endl;
    for(int v:grafo[u].vic){
      if(id[v] == 0){
        ccdfs(conta,v,id,grafo);
      }
    }
  }
}
