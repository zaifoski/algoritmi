#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

//COMPILARE
//	/usr/bin/g++ -DEVAL -static -O2 -o mincoverpesato mincoverpesato.cpp -std=c++0x

//Dato un albero, un sottoinsieme dei suoi nodi S e' un Node-Cover se, per ogni arco dell’albero, uno dei suoi due nodi fa parte di S. Vi viene dato in input un albero con dei pesi sui nodi. Trovare il Node-Cover con il peso minimo e stamparne la dimensione.

//INPUT
//La prima riga contiene N, il numero di nodi. La riga successiva contiene N interi separati da spazio. L’iesimo intero rappresenta il peso del nodo i. Le successive N − 1 contengono ognuna una coppia Pi , Fi , una coppia padre-figlio.

//OUTPUT
//Un intero, il peso del Node-Cover di peso minimo. (2) (4)

//ASSUNZIONI
// 1 ≤ N ≤ 300000

//variabili
int N;

//node
struct node{
  vector<int> figli;
  int peso;
  //int padre;
  //int covered;
  //bool visited;
};

//grafo
vector<node> albero;
vector<vector<int>> D;
//vector<int> foglie;
//int numFoglie = 0;
//int count = 0;

//funzioni
int mincoverpesato(int nodo, int covered, int conta);
int minFun(int a,int b);
//void mincoverRic(int nodo);

int main(){
  
  //lettura input
  ifstream in("input.txt"); //input --> 2; input2 --> 4;
  in >> N;
  albero.resize (N);
  D.resize (N,vector<int> (3,-1));
  //albero[0].padre = -1;
  for(int i=0;i<N;i++){
    in >> albero[i].peso; 
    //albero[f].padre = p;
  }
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
  int count = mincoverpesato(0,0,0);
  //count = (N-count < count)?N-count:count;

  //stampo output
  ofstream out("output.txt");
  out<<count<<"\n";

  return 0;
}

//funzioni
int mincoverpesato(int nodo, int covered, int conta){
  
  if(nodo<0 || nodo>=N) return 0;
  
  if(D[nodo][covered]==-1){
    if(covered == 0)
    {
      D[nodo][covered] = minFun(mincoverpesato(nodo,1,conta),mincoverpesato(nodo,2,conta));
    }
    else if(covered == 1)
    {
      int somma = albero[nodo].peso;
      for(int v:albero[nodo].figli){
        somma += mincoverpesato(v,0,conta+1);
      }
      D[nodo][covered] = somma;
    }
    else if(covered == 2)
    {
      int somma = 0;
      for(int v:albero[nodo].figli){
        somma += mincoverpesato(v,1,conta);
      }
      D[nodo][covered] = somma;
    }
  }
  //cout<<conta;
  return D[nodo][covered];
}

int minFun(int a,int b){
  if(a<=b) return a;
  else return b;
}
