#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

//COMPILARE
//	/usr/bin/g++ -DEVAL -static -O2 -o batman batman.cpp -std=c++0x

//costanti

  //variabili
  int N;
  int M;
  int S;
  int T;

//nodo
struct nodo{
  vector<int> vic;
  bool visited;
  int succ;
};

//grafo
vector<nodo> grafo;
vector<int> dt;
vector<int> ft;
int tempo = 0;
int altrocount =0;
//vector<nodo> grafoTrasposto;
//vector<int> erdos;

//funzioni
//int distanza(int N,int S,int T);
//void numpercorsi(int via,int stop,int& count,set<int> erdos);
bool schema(int via,int stop,int& count);

int main(){
  

  //lettura input
  ifstream in("input10.txt");
  in >> N >> M >> S >> T;
  //erdos.resize(N);
  grafo.resize(N);
  dt.resize(N);
  ft.resize(N);
  //grafoTrasposto.resize(N);
  for(int i=0;i<N;i++){
    dt[i]=0;
    ft[i]=0;
    grafo[i].succ = N;
  }
  for(int i=0;i<M;i++){
    int from, to;
    in >> from >> to;
    grafo[from].vic.push_back(to);
    //grafoTrasposto[to].vic.push_back(from);
  }

  //mio algoritmo
  //distanza(N,S,T);
  //set<int> erdos;
  //erdos.insert(S);
  int count = 0;
  schema(S,T,count);
  //numpercorsi(S,T,count,erdos);

  //stampo output
  cout << "Archi all'indietro: " << altrocount << endl;
  ofstream out("output.txt");
  out << count << "\n";

  return 0;
}

//funzioni
bool schema(int via,int stop,int& count){
  tempo++;
  dt[via]=tempo;
  for(int v:grafo[via].vic){
    if(grafo[v].succ != via){
      if(ft[v] == 0 && dt[via]>dt[v] && dt[v] != 0){
        altrocount++;
        grafo[v].succ = via;
      }
      else{
        if(v == stop){
          count++;
        }
        else{
          if(grafo[v].succ == N){
            schema(v,stop,count);
          }
          else{
            schema(grafo[v].succ,stop,count);
          }
        }
      }
    }
  }
  tempo++;
  ft[via]=tempo;
  return true;
}
/*void numpercorsi(int via,int stop,int& count,set<int> erdos){
  for(int v:grafo[via].vic){
    if (v == stop){
      count ++;
    }
    else {
      set<int> erdos2 = erdos;
      pair<set<int>::iterator,bool> ret;
      ret = erdos2.insert(v);
      if(ret.second==false) return;
      numpercorsi(v,stop,count,erdos2);
    }
  }
  return;
}*/
/*void numpercorsi(int via,int stop,int& count){
  for(int v:grafoTrasposto[stop].vic){
    if (erdos[v] == 0){
      count ++;
    }
    else {
       numpercorsi(via,v,count);
    }
  }
  //return count;
}*/
/*int distanza(int N,int via,int stop){
  int dist = -1;
  queue<int> S;
  S.push(via);
  for(int j=0;j<N;j++){
    erdos[j]=-1;
  }
  erdos[via]=0;
  while(!S.empty()){
    int u = S.front();
    S.pop();
    for(int v:grafo[u].vic){
      if(erdos[v]<0){
        erdos[v]=erdos[u]+1;
        S.push(v);
        if(v==stop){
          dist = erdos[v];
        }
      }
    }
  }
  return dist;
}*/

