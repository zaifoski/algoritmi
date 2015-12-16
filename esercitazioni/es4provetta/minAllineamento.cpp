#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//COMPILARE
//	/usr/bin/g++ -DEVAL -static -O2 -o minAllineamento minAllineamento.cpp -std=c++0x

//variabili
string s1;
string s2;
vector<vector <int>> D;

//funzioni
int minAllineamento(string P, string T, int m, int n);
int minFun(int a,int b);

int main(){
  
  //lettura input
  ifstream in("input1.txt");
  in >> s1 >> s2;
  D.resize (s1.size()+1,vector<int> (s2.size()+1,0));
  //for(int i = 0; i<s1.size(); i++) cout << s1[i]; cout << endl;

  //mio algoritmo
  //int ris = 0;
  int ris = minAllineamento(s1,s2,s1.size(),s2.size());
  for(int k = 0; k<=s1.size(); k++){
    for(int l = 0; l<=s2.size(); l++){
      cout << D[l][k] << "\t";
    }
    cout << endl;
  }

  //stampo output
  ofstream out("output1.txt");
  out<<ris<<"\n";

  return 0;
}

//funzioni
int minAllineamento(string P, string T, int m, int n){
  for(int i = 1; i <= m; i++) D[i][0] = i;
  for(int j = 1; j <= n; j++) D[0][j] = j;
  D[0][0] = 0;
  for(int i = 1; i <= m; i++) {
    for(int j = 1; j <= n; j++){
      int t = D[i-1][j-1] + (P[i]==T[j]?0:1);
      t = minFun(t,D[i-1][j]+1);
      t = minFun(t,D[i][j-1]+1);
      D[i][j]=t;
    }
  }
  return D[m][n];
}

int minFun(int a,int b){
  if(a>=b) return b;
  else return a;
}


