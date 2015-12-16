#include <fstream>
#include <iostream>
using namespace std;
//Data una matrice di interi da R righe e C colonne, trovare il rettangolo
//al suo interno di somma massima. Stamparne la somma.

const int DIM = 2000;
int a[DIM][DIM];

//dichiarazioni
int maxFun(int a,int b);
int massimaSottomatrice(int r, int c);
int massimaSottosequenzaD(int partenza, int n, int fisso);
int massimaSottosequenzaG(int partenza, int n, int fisso);
int massimaSottomatriceRic(int r, int c, int max, int i, int j);

//massimo tra 2
int maxFun(int a,int b){
  if(a>b)
    return a;
  else
    return b;
}

//massima sottosequenza
int massimaSottosequenzaD(int partenza, int n, int fisso){
  int here = 0;
  int max = 0;
  for(int i = partenza; i<n; i++){
    here = maxFun(here+a[fisso][i],0);
    max = maxFun(here,max);
  }
  return max;
}
int massimaSottosequenzaG(int partenza, int n, int fisso){
  int here = 0;
  int max = 0;
  for(int i = partenza; i<n; i++){
    here = maxFun(here+a[i][fisso],0);
    max = maxFun(here,max);
  }
  return max;
}

//massima Sottomatrice Ricorsiva
int massimaSottomatriceRic(int r, int c, int max, int i, int j){
  if ( (i > (r-1) ) && (j > (c-1) ) ) {
    return max;
  }

  max = maxFun(max, a[i][j]);
  int maxUnidim = maxFun(massimaSottosequenzaD(j,c,i),massimaSottosequenzaG(i,r,j));
  max = maxFun(max, maxUnidim);
  if ( (i == (r-1) ) && ( j == (c-1) ) )
    massimaSottomatriceRic(r,c,max,i+1,j+1);
  else if ( i == (r-1) )
    massimaSottomatriceRic(r,c,max,0,j+1);
  else
    massimaSottomatriceRic(r,c,max,i+1,j);
}

//wrapper della ricorsiva
int massimaSottomatrice(int r, int c){
  return massimaSottomatriceRic(r,c,0,0,0);
}

int main(){

  int max = 1;
  int r=0;
  int c=0;

  //leggo input
  ifstream in("input.txt");
  in>>r>>c;
  for(int i = 0; i<r; i++){
    for(int j = 0; j<c; j++){
      in>>a[i][j];
    }
  }

  max = massimaSottomatrice(r,c);

  //stampo output
  ofstream out("output.txt");
  out << max <<"\n";
  cout << "max " << max << "\n";

  return 0;
}
