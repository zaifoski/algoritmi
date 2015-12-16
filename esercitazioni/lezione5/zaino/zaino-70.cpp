#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

//COMPILARE
//	/usr/bin/g++ -DEVAL -static -O2 -o zaino zaino.cpp -std=c++0x

//Avete uno zaino di capacita' C ed un insieme di N oggetti. Per ognuno di questi oggetti, sapete il peso (Pi) e il valore (Vi). Dovete scegliere quali oggetti mettere nello zaino in modo da ottenere il maggior valore possibile senza superare la capacita' dello zaino.

//INPUT
//La prima riga contiene due interi, C e N. Le successive N righe contengono due interi ognuna, Pi e Vi

//OUTPUT
//Un intero: il massimo valore che e possibile trasportare con lo zaino. (16)

//ASSUNZIONI
// 1 ≤ C ≤ 100000
// 1 ≤ N ≤ 1000

//NOTE
//Nel problema dello zaino: Riempire capacita` C utilizzando oggetti da i in poi.

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
//COMMENTO CORREZIONE capacità per numero valori troppo grande
//iterativo più veloce --> 2 righe, mi basta sapere fino a i+1 --> matrice 2*c, stessa complessità, memoria tagliata di ordine n
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


