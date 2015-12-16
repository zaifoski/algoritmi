#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

//COMPILARE
//	/usr/bin/g++ -DEVAL -static -O2 -o mincover mincover.cpp -std=c++0x

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
vector<int> D;
//vector<int> foglie;
//int numFoglie = 0;
//int count = 0;

//funzioni
int mincover(int nodo, bool covered);
int minFun(int a,int b);
//void mincoverRic(int nodo);

int main(){
  
  //lettura input
  ifstream in("input1.txt");
  in >> N;
  albero.resize (N);
  D.resize (N);
  //albero[0].padre = -1;
  for(int i=0;i<N-1;i++){
    //albero[i].covered = 0;
    //albero[i].visited = false;
    int p,f;
    in >> p >> f;
    albero[p].figli.push_back(f);
    D[i]=0;
    //albero[f].padre = p;
  }
  //D.resize (s1.size(),vector<int> (s2.size(),-1));

  //mio algoritmo
  //int ris = 0;
  D[0] = mincover(0,true);
  //count = (N-count < count)?N-count:count;

  //stampo output
  ofstream out("output.txt");
  out<<D[0]<<"\n";

  return 0;
}

//funzioni
int mincover(int nodo, bool covered){
  if(albero[nodo].figli.empty()){
    if(covered == true){
      return 0;
    }
    else{
      return 1;
    }
  }
  else{
    int minimoMinimo;
    int minimoMinimoF;
    int minimoMinimoT;
    if(covered == true){

      minimoMinimoF = mincover(albero[nodo].figli[0],false);

      for(int v:albero[nodo].figli){
        int minimoF = mincover(v,false);
        if(minimoF<minimoMinimoF) minimoMinimoF = minimoF;
      }
      
      minimoMinimoT = (mincover(albero[nodo].figli[0],true) + 1);

      for(int v:albero[nodo].figli){
        int minimoT = (mincover(v,true)+1);
        if(minimoT<minimoMinimoT) minimoMinimoT = minimoT;
      }

      minimoMinimo = minFun(minimoMinimoT,minimoMinimoF);

    }
    else{
      minimoMinimo = (mincover(albero[nodo].figli[0],true) + 1);
      for(int v:albero[nodo].figli){
        int minimo = (mincover(v,true)+1);
        if(minimo<minimoMinimo) minimoMinimo = minimo;
      }

    }

    return minimoMinimo;
  }
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
