#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <stack>
#include <utility>
#include <algorithm>
using namespace std;

//COMPILARE
//	/usr/bin/g++ -DEVAL -static -O2 -o batman batman.cpp -std=c++0x

//nodi
struct nodo{
  vector<int> vic;
  bool visited;
};
struct nodo2{
  set<int> vic;
  bool visited;
};

//variabili
int N;
int M;
int S;
int T;
int conta = 0;
int tempo = 0;
int altrocount = 0;

//grafi
vector<nodo> grafo;
vector<nodo> grafoTrasposto;
vector<nodo2> grafoCC;

//VETTORI
vector<bool> messo (N);
vector<int> dt;
vector<int> ft;
vector<int> id (N);
vector<pair<int,int>> erdos (N);

//funzioni per le componenti fortemente connesse
vector<int> scc(vector<int>& id);
stack<int> topsort();
void tsdfs(int u, stack<int>& S);
vector<int> cc(stack<int> Q, vector<int>& id);
void ccdfs(int conta, int u, vector<int>& id);

//funzioni per nemici
bool schema(int via,int stop,int& count);
bool schema2(int via,int stop,int& count);
void creaGrafoCC();
vector<int> distanza(int via,int stop,vector<int>& id);

//funzioni di controllo output
void printGrafo(vector<nodo2> grafo);

//main
int main(){
  //lettura input
  ifstream in("input1.txt");
  in >> N >> M >> S >> T;
  grafo.resize(N);
  messo.resize(N);
  erdos.resize(N);
  dt.resize(N);
  ft.resize(N);
  id.resize(N);
  grafoCC.resize(N);
  grafoTrasposto.resize(N);
  for(int i=0;i<N;i++){
    dt[i]=0;
    ft[i]=0;
  }
  for(int i=0;i<M;i++){
    int from, to;
    in >> from >> to;
    grafo[from].vic.push_back(to);
    grafoTrasposto[to].vic.push_back(from);
  }
  for(int i=0;i<N;i++){
    grafo[i].visited=false;
  }

  //mio algoritmo
  vector<int> cfc = distanza(S,T,id);
  //vector<int> cfc = scc(id);
  int countCC = conta;
  int count = 0;
  if(countCC==N){
    schema(S,T,count);
  }
  else{
    schema2(id[S]-1,id[T]-1,count);
  }

  //stampo output
  ofstream out("output.txt");
  //out << count << " " << altrocount << "\n";
  out << count << "\n";

  return 0;
}

//funzioni
vector<int> distanza(int via,int stop,vector<int>& id){
  stack<int> mioStack;
  queue<int> S;
  S.push(via);
  for(int j=0;j<N;j++){
    pair<int,int> coppia;
    coppia.first = -1;
    coppia.second = j;
    erdos[j]=coppia;
  }
  erdos[via].first=0;
  while(!S.empty()){
    int u = S.front();
    S.pop();
    for(int v:grafo[u].vic){
      if(erdos[v].first<0){
        erdos[v].first=erdos[u].first+1;
        S.push(v);
      }
    }
  }
  sort(erdos.begin(),erdos.end());
  for(int i = N-1; i>=0; i--){
    if(erdos[i].first != -1){
      mioStack.push(erdos[i].second);
      cout << "erdos[i].first\t" << erdos[i].first << ".\terdos[i].second\t" << erdos[i].second << endl;
    }
  }
  return cc(mioStack,id);
}

//componenti connesse del grafo trasposto con stack dei tempi di fine
vector<int> cc(stack<int> Q, vector<int>& id){
  for(int i=0;i<N;i++){
    id[i]=0;
  }
  while(!Q.empty()){
    int u = Q.top();
    
    Q.pop();
    if(id[u]==0){
      conta = conta + 1;
      ccdfs(conta,u,id);
    }
  }
  grafoCC.resize(conta);
  creaGrafoCC();
  return id;
}

void ccdfs(int conta, int u, vector<int>& id){
  id[u] = conta;cout << u;
  //for(int v:grafoTrasposto[u].vic){//inverti se usi il grafoTrasposto
  for(int v:grafo[u].vic){ //PROBLEMA SEGFAULT QUI
    if(id[v] == 0){
      ccdfs(conta,v,id);
    }
  }
}

//crea il grafo delle componenti fortemente connesse
void creaGrafoCC(){
  for(int i = 0; i<N; i++){
    if(erdos[i].first!=-1){
      for(int v:grafo[i].vic){
        if(id[v]!=id[i] && erdos[v].first!=-1 && erdos[i].first!=-1){
          int to = id[i]-1;//inverti se usi il grafoTrasposto
          int from = id[v]-1;
          grafoCC[from].vic.insert(to);
        }
      }
    }
  }
  printGrafo(grafoCC);
}

//nemici con cilci
bool schema2(int via,int stop,int& count){
  tempo++;
  dt[via]=tempo;
  for(int v:grafoCC[via].vic){
      if(ft[v] == 0 && dt[via]>dt[v] && dt[v] != 0){
        altrocount++;
      }
      else{
        if(v == stop){
          count++;
        }
        else{
          schema2(v,stop,count);
        }
      }
  }
  tempo++;
  ft[via]=tempo;
  return true;
}

//nemici senza cilci
bool schema(int via,int stop,int& count){
  tempo++;
  dt[via]=tempo;
  for(int v:grafo[via].vic){
      if(ft[v] == 0 && dt[via]>dt[v] && dt[v] != 0){
        altrocount++;
      }
      else{
        if(v == stop){
          count++;
        }
        else{
          schema(v,stop,count);
        }
      }
  }
  tempo++;
  ft[via]=tempo;
  return true;
}

//inizio funzioni per componenti fortemente connesse
vector<int> scc(vector<int>& id){
  stack<int> Q = topsort();
  return cc(Q,id);
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

//funzione per controllo output stampa grafo
void printGrafo(vector<nodo2> grafo){
  for(int i = 0; i<conta; i++){
    cout << i << "-->";
    for(int v:grafo[i].vic){
      cout << " " << v;
    }
    cout << endl;
  }
}
