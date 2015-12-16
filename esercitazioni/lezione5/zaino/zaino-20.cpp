#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

//COMPILARE
//	/usr/bin/g++ -DEVAL -static -O2 -o zaino zaino.cpp -std=c++0x

//Avete uno zaino di capacit ́ C ed un insieme di N oggetti. Per ognuno di questi oggetti, sapete il peso a(Pi ) e il valore (Vi ). Dovete scegliere quali oggetti mettere nello zaino in modo da ottenere il maggior valore possibile senza superare la capacit ́ dello zaino.

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
int zaino(vector<int> p,vector<int> v,int i, int c, vector<vector<int>> D);
int max(int a,int b);

int main(){
  
  //variabili
  int C;
  int N;

  //lettura input
  ifstream in("input.txt");
  in >> C >> N;
  //D.resize (N, vector<int> (M,-1));
  D.resize (N, vector<int> (C,-1));
  p.resize(N);
  v.resize(N);
  for(int i=0;i<N;i++){
    in >> p[i] >> v[i];
  }

  //mio algoritmo
  int max = zaino(p,v,N-1,C,D);

  //stampo output
  ofstream out("output.txt");
  out<<max<<"\n";

  return 0;
}

//funzioni
int zaino(vector<int> p,vector<int> v,int i, int c, vector<vector<int>> D){
  if (i==-1 || c==-1) {
    return 0;
  }
  if (c<-1) {
    return (-1000000);
  }
  if (D[i][c-1] == -1) {
    D[i][c-1] = max(zaino(p,v,i-1,c,D),zaino(p,v,i-1,c-v[i],D) + p[i]);
  }
  return D[i][c-1];
}

int max(int a,int b){
  if(a>=b) return a;
  return b;
}


