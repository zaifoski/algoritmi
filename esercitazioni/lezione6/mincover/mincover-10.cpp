#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

//COMPILARE
//	/usr/bin/g++ -DEVAL -static -O2 -o mincover mincover.cpp -std=c++0x
//http://courses.csail.mit.edu/6.006/spring11/lectures/lec21.pdf

//Dato un albero, un sottoinsieme dei suoi nodi S e' un Node-Cover se, per ogni arco dell’albero, uno dei suoi due nodi fa parte di S Dato un albero, trovare il Node-Cover con il minimo numero di nodi e stamparne la dimensione.

//INPUT
//La prima riga contiene N, il numero di nodi. Le successive N − 1 contengono ognuna una coppia Pi , Fi , una coppia padre-figlio.

//OUTPUT
//Un intero, la dimensione del Node-Cover (2) (1)

//ASSUNZIONI
// 1 ≤ N ≤ 300000

//variabili
int N;
//vector<vector <int>> D;

//nodo
struct nodo{
  vector<int> figli;
  //int padre;
  //int covered;
  //bool visited;
};

//grafo
vector<nodo> albero;
vector<vector<int>> D;
//vector<int> foglie;
//int numFoglie = 0;
//int count = 0;

//funzioni
int mincover(int nodo, int covered);
int minFun(int a,int b);
//void mincoverRic(int nodo);

int main(){
  
  //lettura input
  ifstream in("input.txt");
  in >> N;
  albero.resize (N);
  D.resize (N,vector<int> (3,-1));
  //albero[0].padre = -1;
  for(int i=0;i<N-1;i++){
    //albero[i].covered = 0;
    //albero[i].visited = false;
    int p,f;
    in >> p >> f;
    albero[p].figli.push_back(f);
    //albero[f].padre = p;
  }
  //D.resize (s1.size(),vector<int> (s2.size(),-1));

  //mio algoritmo
  //int ris = 0;
  int count = mincover(0,0);
  //count = (N-count < count)?N-count:count;

  //stampo output
  ofstream out("output.txt");
  out<<count<<"\n";

  return 0;
}

//funzioni
int mincover(int nodo, int covered){
  
  if(nodo<0 || nodo>=N) return 0;
  
  if(D[nodo][covered]==-1){
    if(covered == 0)
    {
      D[nodo][covered] = minFun(mincover(nodo,1),mincover(nodo,2));
    }
    else if(covered == 1)
    {
      int somma = 1;
      for(int v:albero[nodo].figli){
        somma += mincover(v,0);
      }
      D[nodo][covered] = somma;
    }
    else if(covered == 2)
    {
      int somma = 0;
      for(int v:albero[nodo].figli){
        somma += mincover(v,1);
      }
      D[nodo][covered] = somma;
    }
  }

  return D[nodo][covered];
/*
  if(albero[nodo].figli.empty()){
    if(covered == true){
      return 0;
    }
    else{
      return 1;
    }
  }
  if(covered == true){
    for(int v:albero[nodo].figli){
      return minFun((mincover(v,true)+1),mincover(v,false));
    }
  }
  else{
    for(int v:albero[nodo].figli){
      return (mincover(v,true)+1);
    }
  }
*/
}

int minFun(int a,int b){
  if(a<=b) return a;
  else return b;
}


/*
void mincover(){
  for(int i = 0; i<N; i++){
    if(albero[i].figli.empty()){
      mincoverRic(albero[i].padre);
      //foglie.resize (numFoglie+1);
      //foglie[numFoglie] = i; 
    }
  }
}

void mincoverRic(int nodo){
  if(albero[nodo].visited == false){
    albero[nodo].visited = true;
    albero[nodo].covered = true;
    count ++;
    if(albero[nodo].padre == -1){
      //caso base nodo == radice
    }
    else if(albero[nodo].padre == 0){
      //caso base albero[nodo].padre == radice
    }
    else{
      mincoverRic(albero[albero[nodo].padre].padre);
    }
  }
}
*/
