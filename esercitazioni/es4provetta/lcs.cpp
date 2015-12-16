#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//COMPILARE
//	/usr/bin/g++ -DEVAL -static -O2 -o lcs lcs.cpp -std=c++0x

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
int lcs(int[]P, int[]T, int m, int n){
  vector<vector <int>> D;
  D.resize (m+1,vector<int> (n+1,0));
  for(int i = 1; i <= m; i++) D[i][0] = i;
  for(int j = 1; j <= n; j++) D[0][j] = j;
  D[0][0] = 0;
  for(int i = 1; i <= m; i++) {
    for(int j = 1; j <= n; j++){
      int t = D[i-1][j-1] + (P[i]==T[j]?0:1);
    }
  }
}

int minFun(int a,int b){
  if(a>=b) return b;
  else return a;
}


