#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

//COMPILARE
//	/usr/bin/g++ -DEVAL -static -O2 -o sottocres sottocres.cpp -std=c++0x

//Vi viene dato in input un array di N interi A1 ...AN . Per ogni elemento potete scegliere se includerlo nell’insieme soluzione, o se ignorarlo. Se un elemento Ai fa parte dell’insieme, tutti gli elementi che lo succedono nell’array e che hanno valore minore di Ai non possono essere inclusi nell’insieme. In altre parole, gli elementi dell’insieme, quando stampati nell’ordine in cui si trovavano nell’array, devono formare una sequenza crescente. Vogliamo massimizzare la somma degli elementi dell’insieme.

//INPUT
//La prima riga contiene un intero N. La seconda riga contiene N interi separati da spazio.

//OUTPUT
//Un intero, la somma degli elementi dell’insieme di somma massima.. (55)

//ASSUNZIONI
// 1 ≤ N ≤ 10000

//costanti
const int MAXN = 10000;

//variabili
int N;
int M = 0;
int m = -1;
int ris = 0;

//vettori
vector<int> A;
vector<vector<int>> D;

//funzioni
int sottocres(int i,int prec);
int maxFun(int a,int b);
void printLongest();

int main(){
  
  //lettura input
  ifstream in("input.txt");
  in >> N;
  A.resize (N);
  for(int i=0;i<N;i++){
    in >> A[i];
    if (A[i]>M) M = A[i];
    if (A[i]<m) m = A[i];
  }
  M++;
  m--;
  D.resize (N,vector<int> (M,m));

  //mio algoritmo
  int max = sottocres(0,A[0]);
  //printLongest();

  //stampo output
  ofstream out("output.txt");
  out<<max<<"\n";

  return 0;
}

//funzioni
void printLongest(){
  for(int i = 0; i<N; i++){
    for(int j = 0; j<M; j++){
      if(D[i][j]!=m)
        cout << "D[" << i << "][" << j << "]" << D[i][j] << "\t";
    }
  }
}
int sottocres(int i,int prec){
  if (i==N) {
    return 0;
  }
  if (D[i][prec] == m) {
    if(A[i]<prec && i!=0){
      D[i][prec] = sottocres(i+1,prec);
    }
    else{
      //cout << sottocres(i+1,prec) << "\t" <<sottocres(i+1,A[i])+A[i]<<endl;
      D[i][prec] = maxFun(sottocres(i+1,prec),sottocres(i+1,A[i])+A[i]);
    }
  }
  //cout << i << ":\t" << D[i] << ";\t";
  return D[i][prec];
}

int maxFun(int a,int b){
  if(a>=b) return a;
  else return b;
}


