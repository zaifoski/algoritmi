#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <stack>
using namespace std;

//COMPILARE
//	/usr/bin/g++ -DEVAL -static -O2 -o batman-cfc batman-cfc.cpp -std=c++0x

//costanti
int conta = 0;

//variabili
int N;
int M;
int S;
int T;

//nodo
struct nodo{
  vector<int> vic;
  bool visited;
};

//grafo
vector<nodo> grafo;
vector<nodo> grafoTrasposto;
vector<nodo> grafoCC;
int tempo = 0;
int altrocount =0;

//VETTORI
vector<bool> messo (N);
vector<int> dt;
vector<int> ft;
vector<int> id (N);

//funzioni
vector<int> scc(vector<int>& id);
stack<int> topsort();
void tsdfs(int u, stack<int>& S);
vector<int> cc(stack<int> Q, vector<int>& id);
void ccdfs(int conta, int u, vector<int>& id);
int dimComMax(vector<int> cfc);
void printGrafo(vector<nodo> grafo);

bool schema(int via,int stop,int& count);
void schemaCiclico(int via,int stop,int& count);

int main(){
  
  //lettura input
  ifstream in("input12.txt");
  in >> N >> M >> S >> T;
  //erdos.resize(N);
  grafo.resize(N);
  messo.resize(N);
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
  vector<int> cfc = scc(id);
  int countCC = conta;
 
  int count = 0;

  if(countCC==N){
    schema(S,T,count);
  }
  else{
    for(int i = 0; i<N; i++){
      grafo[i].visited = false;
    }cout << id[S]<< " "<< id[T];
    if(id[S]-1!=id[T]-1) schemaCiclico(id[S]-1,id[T]-1,count);
  }
  //printGrafo(grafoCC);

  //stampo output
  cout << "countCC: " << countCC << endl;
  ofstream out("output.txt");
  out << count << "\n";

  return 0;
}

//funzioni

void schemaCiclico(int via,int stop,int& count){
  for(int v:grafoCC[via].vic){
    if (v == stop){
      count++;
    }
    else {
      schemaCiclico(v,stop,count);
    }
  }
  return;
}

bool schema(int via,int stop,int& count){
  tempo++;
  dt[via]=tempo;
  for(int v:grafo[via].vic){
      if(ft[v] == 0 && dt[via]>dt[v] && dt[v] != 0){
        altrocount++;
        //schema(v,stop,count);
      }
      else{
        if(v == stop){
          count ++;
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

//componenti connesse del grafo trasposto con stack dei tempi di fine
vector<int> cc(stack<int> Q, vector<int>& id){
  //cout << "Q.size(): " << Q.size() << endl;
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
  vector<bool> componentiCiclose (conta);
  for (int l=0; l<conta; l++) {
    componentiCiclose[l]=false;
  }
  for(int i=0;i<N;i++){
    grafo[i].visited=false;
  }
  grafoCC.resize(conta);
  int componenteAttuale = 1;
  for(int d = 0; d<N; d++){
    for(int v:grafo[d].vic){
      if(grafo[v].visited == false){
        grafo[v].visited=true;
        if(id[v] == componenteAttuale){
          componentiCiclose[id[v]-1]=true;
        }
        else if(id[v]>0){
          int q = id[v]-1;
          cout << q << " ";
          //grafoCC[componenteAttuale].vic.push_back(v);
          grafoCC[componenteAttuale].vic.push_back(q);
          componenteAttuale = id[v];
        }
      }
    }
  }
  return id;
}

void ccdfs(int conta, int u, vector<int>& id){
  id[u] = conta;
  //cout << id[u] << " ; " << u << endl;
  for(int v:grafoTrasposto[u].vic){
    if(id[v] == 0){
      ccdfs(conta,v,id);
    }
  }
}
//stampa grafo
void printGrafo(vector<nodo> grafo){
  for(int i = 0; i<conta; i++){
    cout << i << "-->";
    for(int v:grafo[i].vic){
      cout << " " << v;
    }
    cout << endl;
  }
}
