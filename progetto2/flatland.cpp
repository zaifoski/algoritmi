#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

//COMPILARE
//	/usr/bin/g++ -DEVAL -static -O2 -o flatland flatland.cpp -std=c++0x

//Come ogni anno, Babbo Natale Esagonale porter` i suoi regali ai piccoli e poveri triangoli di Flatlandia. I triangoli si metteranno in fila ad aspettare i regali, ogni triangolo girato verso sinistra o destra, ed i regali verranno consegnati secondo la seguente procedura:
//1. Babbo Natale Esagonale sceglie un triangolo che non sia primo o ultimo nella fila.
//2. Babbo Natale Esagonale consegna due regali al triangolo scelto.
//3. Il triangolo scelto dona uno dei suoi regali al triangolo di fronte. Se il triangolo scelto e girato verso sinistra, sceglier` il primo triangolo sulla sua sinistra.
//4. I due triangoli vanno a giocare insieme fuori dalla fila
//Babbo Natale Esagonale vuole continuare questa procedura fino a quando tutti i triangoli hanno ricevuto un regalo. Purtroppo, se i triangoli sono in un numero dispari, ne avanzer` sempre uno. Nella sequenza di immagini in fondo al pdf potete vedere un esempio di consegna regali. Babbo Natale Esagonale consegna due regali al triangolo 5, il quale ne dona uno al triangolo di fronte (4) prima di lasciare la fila. Babbo Natale Esagonale poi sceglie il triangolo 3, che condivide i doni con 6. Nell’ultimo passo, l’unico triangolo valido e 1 (visto che 0 e 2 sono rispettivamente il primo e l’ultimo nella fila) e quindi il triangolo 2 rimarr` da solo nella fila. Se Babbo Natale Esagonale avesse fatto altre scelte, altri triangoli sarebbero potuti rimanere solitari nella fila. Il vostro dovere e, data la lista di triangoli ed il loro orientamento, trovare quali triangoli potrebbero rimanere solitari.

//INPUT
//La prima riga contiene l’intero N, il numero di triangoli. La seconda riga contiene una parola di N caratteri. L’iesimo carattere e s l’iesimo triangolo e rivolto a sinistra, d se e rivolto a destra.

//OUTPUT
//La prima riga dell’output contiene S, il numero di triangoli solitari trovati dal vostro programma. La seconda riga contiene S interi separati da spazio, gli indici dei triangoli trovati, in un ordine qualsiasi.

//ASSUNZIONI
//Nei primi dieci casi 1 ≤ N≤ 1
//1 ≤ N ≤ 200

//NOTE
//• Se trovate almeno un triangolo solitario, raggiungete almeno il 30%
//• N e sempre dispari
//• Non si puo cambiare l’ordine dei triangoli in input
//• L’ordine in cui e stampata in output la soluzione e irrelevante
//• Un triangolo e il primo della fila se non c’` alcun triangolo alla sua sinistra. All’inizio si tratta e del triangolo 0, ma puo cambiare nel corso della distribuzione dei regali. Stesso concetto per il triangolo in fondo alla fila.
//• La programmazione dinamica vi porta alla soluzione ottima, ma si possono usare altre tecniche per soluzioni intermedie!


//variabili
int N;
//int count;
vector<pair<int,int>> fila;

//funzioni
int trovaTriangolo(int indice);
//int maxFun(int a,int b);

int main(){
  
  //lettura input
  ifstream in("input.txt");
  in >> N;
  //count = N+1;
  fila.resize(N);
  for(int i = 0; i<N; i++){
    fila[i].second=i;
    char c;
    in >> c;
    if(c=='s') fila[i].first=1;
    else fila[i].first=2;
  }

  //mio algoritmo
  int ris;
  if(N>1){
    ris = trovaTriangolo(0);
  }
  else {
    ris = fila[0].second;
  }

  //stampo output
  ofstream out("output.txt");
  out<<1<<"\n"<<ris<<"\n";

  return 0;
}

//funzioni

int trovaTriangolo(int indice){
  if(fila.size()==3){
    if (fila[1].first == 1) return fila[2].second;
    else if (fila[1].first == 2) return fila[0].second;
  }
  else if(indice==0 && fila[indice].first==1){
    trovaTriangolo(indice+1);
  }
  else if(indice==N-1 && fila[indice].first==2){
    trovaTriangolo(indice-1);
  }
  else if(fila[indice].first==1){
    fila.erase(fila.begin() + indice);
    fila.erase(fila.begin() + (indice-1));
    trovaTriangolo(indice-1);
  }
  else if(fila[indice].first==2){
    fila.erase(fila.begin() + (indice+1));
    fila.erase(fila.begin() + indice);
    trovaTriangolo(indice);
  }
}


