#include <fstream>
#include <iostream>
using namespace std;
//Data una matrice di interi da R righe e C colonne, trovare il rettangolo
//al suo interno di somma massima. Stamparne la somma.

const int DIM = 2000;
int a[DIM][DIM];
int r=0;
int c=0;

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
  /*for(int i = partenza; i<n; i++){
    here = maxFun(here+a[fisso][i],0);
    max = maxFun(here,max);
  }*/
  //prova inizio
  for(int i = partenza; i<n; i++){
    for(int j = fisso; j<r; j++){
      here = maxFun(here+a[fisso][i]+a[j][i],0);
      max = maxFun(here,max);
    }
  }
  //prova fine
  return max;
}
int massimaSottosequenzaG(int partenza, int n, int fisso){
  int here = 0;
  int max = 0;
  /*for(int i = partenza; i<n; i++){
    here = maxFun(here+a[i][fisso],0);
    max = maxFun(here,max);
  }*/
  //prova inizio
  for(int i = partenza; i<n; i++){
    for(int j = fisso; j<r; j++){
      here = maxFun(here+a[i][fisso]+a[i][j],0);
      max = maxFun(here,max);
    }
  }
  //prova fine
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
  if ( (i == (r-1) ) && ( j == (c-1) ) ){
    massimaSottomatriceRic(r,c,max,i+1,j+1);
  }
  else if ( i == (r-1) ){
    massimaSottomatriceRic(r,c,max,0,j+1);
  }
  else{
    /*int here = a[i][j];
    int maxQ = 0;
    for(int k = i; k <= r-2; k++){
      for(int l = j; l <= c-2; l++){
        here = maxFun(here+a[k][l+1]+a[k+1][l+1]+a[k+1][l],0);
        maxQ = maxFun(here,maxQ);
      }
    }
    max = maxFun(max, maxQ);*/
    massimaSottomatriceRic(r,c,max,i+1,j);    
  }
}

//wrapper della ricorsiva
int massimaSottomatrice(int r, int c){
  return massimaSottomatriceRic(r,c,0,0,0);
}

int main(){

  int max = 0;

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
