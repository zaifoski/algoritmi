#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

//COMPILARE
//	/usr/bin/g++ -DEVAL -static -O2 -o mincoverpesato mincoverpesato.cpp -std=c++0x

//Dato un albero, un sottoinsieme dei suoi nodi S e un Node-Cover se, per ogni arco dell’albero, uno dei suoi due nodi fa parte di S. Vi viene dato in input un albero con dei pesi sui nodi. Trovare il Node-Cover con il peso minimo e stamparne la dimensione.

//INPUT
//La prima riga contiene N, il numero di nodi. La riga successiva contiene N interi separati da spazio. L’iesimo intero rappresenta il peso del nodo i. Le successive N − 1 contengono ognuna una coppia Pi , Fi , una coppia padre-figlio.

//OUTPUT
//Un intero, il peso del Node-Cover di peso minimo. (2) (4)

//ASSUNZIONI
// 1 ≤ N ≤ 300000

//costanti
const int MAXC = 100000;
const int MAXN = 1000;

//vettori
vector<vector<int>> D;
vector<int> p;
vector<int> v;

//funzioni
int zaino(int i, int c);
int max(int a,int b);

int main(){
  
  //variabili
  int C;
  int N;

  //lettura input
  ifstream in("input.txt");
  in >> C >> N;
  D.resize(N, vector<int> (C,-1));
  p.resize(N);
  v.resize(N);
  for(int i=0;i<N;i++){
    in >> p[i] >> v[i];
  }

  //mio algoritmo
  int max = zaino(N-1,C-1);

  //stampo output
  ofstream out("output.txt");
  out<<max<<"\n";

  return 0;
}

//funzioni
int zaino(int i, int c){
  if (c<-1) {
    return (-1000000);
  }
  if (i==-1 || c==-1) {
    return 0;
  }
  if (D[i][c] == -1) {
    D[i][c] = max(zaino(i-1,c),zaino(i-1,c-p[i]) + v[i]);
  }
  return D[i][c];
}

int max(int a,int b){
  if(a > b){
    return a;
  }
  else{
    return b;
  }
}


