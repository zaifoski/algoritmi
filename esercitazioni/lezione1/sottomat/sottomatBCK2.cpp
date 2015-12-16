#include <fstream>
#include <iostream>
using namespace std;
//Data una matrice di interi da R righe e C colonne, trovare il rettangolo
//al suo interno di somma massima. Stamparne la somma.

const int DIM = 2000;
int a[DIM][DIM];

//dichiarazioni
int maxFunQ(int a,int b, int c, int d);
int maxFun(int a,int b);
int massimaSottomatrice(int r, int c);

//massimo tra 4
int maxFunQ(int a,int b, int c, int d){
  return maxFun(maxFun(a,b),maxFun(c,d));
}

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
  if (!(i<r) && !(j<c)) {
    return max;
  }
  if (!(i<r)) {
    int max = maxFun(massimaSottosequenzaD(j,c,i),massimaSottosequenzaG(i,r,j));
    max = maxFun(a[i][j],max);
    massimaSottomatriceRic(r,c,max,i+1,j);
  }
  else if (!(j<c)) {
    i=0;
    int max = maxFun(massimaSottosequenzaD(j,c,i),massimaSottosequenzaG(i,r,j));
    max = maxFun(a[i][j],max);
    massimaSottomatriceRic(r,c,max,i,j+1);
  }
}

//wrapper della ricorsiva
int massimaSottomatrice(int r, int c){
  return massimaSottomatriceRic(r,c,0,0,0);
}

//massima sottomat
/*int massimaSottomatrice(int r, int c){
  int max = 0;
  for(int i = 0; i<c; i++){
    for(int j = 0; j<r; j++){
      max = maxFun(max, a[i][j]);
      int here = a[i][j];
      int k = i;
      int l = j;
      while (k<r-1 && l<c-1){
        int p2 = here+a[k+1][l]+a[k][l+1]+a[k+1][l+1];
        max = maxFun(max, p2);
        here = p2;
        k++;
        l++;
      }
      k = i;
      l = j;
      here = a[i][j];
      while (k<r-1){
        int p2 = here+a[k+1][l];
        max = maxFun(max,p2);
        here = p2;
        k++;
      }
      k = i;
      l = j;
      here = a[i][j];
      while (j<c-1){
        int p2 = here+a[k][l+1];
        max = maxFun(max,p2);
        here = p2;
        k++;
      }
    }
  }
  return max;
}*/

int main(){

  int max = 0;
  int here = 0;
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

  //max <-- tutta la matrice
  /*for(int i = 0; i<r; i++){
    for(int j = 0; j<c; j++){
      max += a[i][j];
    }
  }*/

  max = massimaSottomatrice(r,c);

  //stampo output
  ofstream out("output.txt");
  out<<max<<"\n";

  //test output
  cout << "max " << max << "\n";
  cout << "here " << here << "\n";


  return 0;
}
