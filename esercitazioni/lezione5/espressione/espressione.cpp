#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

//COMPILARE
//	/usr/bin/g++ -DEVAL -static -O2 -o espressione espressione.cpp -std=c++0x

//Siano dati in input N interi positivi ed alcuni obiettivi (V1 ...VK ). Supponendo di avere a disposizione gli operatori + e * e la possibilit` di raggruppare operatori ed operandi fra parentesi a piacimento, a trovare per ognuno degli obiettivi Vi se esiste un’espressione matematica che includa tutti e soli gli N interi, nell’ordine dato, e il cui valore sia esattamente Vi .Ad esempio, con i valori 2 4 3 5 e possibile ottenere 19 = ( 2 + (4 * 3) + 5) ma non e possibile ottenere 15. Per ognuno degli interi obiettivo scrivete se e possibile ottenerlo dalla sequenza di N interi

//INPUT
//La prima riga contiene due interi, N ed K Le seconda riga contiene la sequenza di N interi che formano l’espressione separati da spazio. Le K righe successive contengono la lista degli interi che vogliamo ottenere


//OUTPUT
//Il file di output contiene K righe. L’iesima riga contiene la stringa SI se e possibile ottenere l’iesimo intero obiettivo dalla sequenza di N interi, NO se cio non e possibile. SI NO


//ASSUNZIONI
// 1 ≤ N ≤ 10000
//Gli interi che formano l’espressione sono interi positivi minori di 100.
//Gli interi obiettivo sono interi positivi minori di 20000.

//costanti
const int MAXN = 20;
const int MAXK = 5;

//variabili
int N;
int K;
vector<int> A;
vector<int> B;

//funzioni
bool espressione(int j,int i);

int main(){
  
  //lettura input
  ifstream in("input.txt");
  in >> N >> K;
  A.resize(N);
  B.resize(K);
  vector<int> C (K);
  for(int i=0;i<N;i++){
    in >> A[i];
  }
  for(int i=0;i<K;i++){
    in >> B[i];
  }

  //mio algoritmo
  for(int i=0;i<K;i++){
    C[i] = espressione(0,B[i]);
  }

  //stampo output
  ofstream out("output.txt");
  for(int i=0;i<K;i++){
    if (C[i] == false){
      out<<"NO"<<"\n";
    }
    else{
      out<<"SI"<<"\n";
    }
  }

  return 0;
}

//funzioni
bool espressione(int j,int obiettivo,int ris){
  if(j==N-1){
    if(ris==obiettivo) return true;
    else return false;
  }
  else{//0 è + ; 1 è *; 2 è il numero
    D[j,0] = ris*j;
    D[j,1] = ris+j;
    D[j,2] = j;
    return espressione (j++,)
  }
}

/*
  if(j==N-1 && obiettivo==0){
    return true;
  }
  if(j==N){
    return false;
  }
  else if (obiettivo<0){
    return false;
  }
  else if(j<N-1){
    return (A[j]+espressione(j+1,obiettivo-A[j]) == obiettivo ||
            A[j]*espressione(j+1,obiettivo/A[j]) == obiettivo ||
            (A[j]+A[j+1])+espressione(j+2,obiettivo-(A[j]+A[j+1])) == obiettivo ||
            (A[j]*A[j+1])+espressione(j+2,obiettivo-(A[j]+A[j+1])) == obiettivo ||
            (A[j]+A[j+1])*espressione(j+2,obiettivo-(A[j]/A[j+1])) == obiettivo ||
            (A[j]*A[j+1])*espressione(j+2,obiettivo-(A[j]/A[j+1])) == obiettivo);
  }
  else{
    return (A[j]+espressione(j+1,obiettivo-A[j]) == obiettivo ||
            A[j]*espressione(j+1,obiettivo/A[j]) == obiettivo);
  }
}


