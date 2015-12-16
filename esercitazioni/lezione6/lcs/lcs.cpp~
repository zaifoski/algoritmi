#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//COMPILARE
//	/usr/bin/g++ -DEVAL -static -O2 -o lcs lcs.cpp -std=c++0x

//Definiamo come sottosequenza di una stringa una qualunque sequenza di caratteri ottenibile partendo dalla stringa di partenza, ed eliminando 0 o piu caratteri e senza cambiarne l’ordine. Il nostro obiettivo e quello di trovare, date due stringhe, la piu lunga sottosequenza in comune e stamparne la lunghezza

//INPUT
//L’input consiste di due righe, ogni riga contiene una delle due stringhe
//taccbt
//atbcbd   --> 3 per tcb e acb
//
//abfddbe
//befbede  --> 4 per bfde e bfbe

//OUTPUT
//Un intero, la lunghezza della sottosequenza comune massimale.

//ASSUNZIONI
//stringhe ≤ 1000

//NOTE
//int dim = s.size();
//char c = s[2];

//variabili
string s1;
string s2;
vector<vector <int>> D;

//funzioni
int lcs(int i,int j);
int maxFun(int a,int b);

int main(){
  
  //lettura input
  ifstream in("input.txt");
  in >> s1 >> s2;
  D.resize (s1.size(),vector<int> (s2.size(),-1));
  for(int i = 0; i<s1.size(); i++) cout << s1[i]; cout << endl;

  //mio algoritmo
  //int ris = 0;
  int ris = lcs(s1.size()-1,s2.size()-1);

  //stampo output
  ofstream out("output.txt");
  out<<ris<<"\n";

  return 0;
}

//funzioni
int lcs(int i, int j){
  if(i==-1 || j==-1) return 0;
  if(D[i][j]==-1) {
    if(s1[i]==s2[j]) D[i][j] = lcs(i-1,j-1) + 1;
    else D[i][j] = maxFun(lcs(i-1,j),lcs(i,j-1));
  }
  return D[i][j];
}

int maxFun(int a,int b){
  if(a>=b) return a;
  else return b;
}


