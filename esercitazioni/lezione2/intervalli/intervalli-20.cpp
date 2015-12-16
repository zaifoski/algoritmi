#include <fstream>
using namespace std;

//Vi vengono dati una serie di N intervalli temporali, ognuno rappresentati come una coppia Inizio i , Fine i di interi. Vogliamo sapere quale e il piu lungo periodo non coperto da alcun intervallo, considerando solo gli istanti compresi fra il minimo istante di inizio ed il massimo istante di fine degli intervalli.
//INPUT La prima riga contiene l’intero N, il numero di intervalli. Le successive N righe contengono due interi separati da spazio, l’istante di inizio e quello di fine dell’intervallo.
//OUTPUT Due interi che rappresentano l’istante di inizio e quello di fine del piu lungo periodo scoperto. Se ci sono piu di un periodo scoperto della stessa lunghezza, restituire quello con inizio minore.
//ASSUNZIONI 1 ≤ N ≤ 100000

struct coppia{
  int inizio;
  int fine;
};

const int MAXN = 100000;
coppia array[MAXN];


int minFun(coppia array[],int n){
  int min = array[0].inizio;
  for(int i = 1; i<n; i++){
    if(array[i].inizio<min)
      min = array[i].inizio;
  }
  return min;
}
int maxFun(coppia array[], int n){
  int max = array[0].fine;
  for(int i = 1; i<n; i++){
    if(array[i].fine>max)
      max = array[i].fine;
  }
  return max;
}
bool controllaPresenza(int i, int min, int max,int n){

  for(int j = 0; j<n; j++){
    if(i>=array[j].inizio && i<=array[j].fine){
      return true;
    }
  }
  return false;
}


int main(){
  int n;
  ifstream in("input.txt");
  in>>n;
  for(int i = 0; i<n; i++){
    in>>array[i].inizio>>array[i].fine;
  }
  
  int min = minFun(array,n);
  int max = maxFun(array,n);
  int inizio = 0;
  int fine = 0;
  
  coppia nonPresenteTemp = {0,0};
  int maxx = 0;
  int maxxTemp = 0;
  for(int i = min; i<=max;i++){
    bool presente = controllaPresenza(i,min,max,n);
    if(!presente){//l'elemento è un candidato
      if(nonPresenteTemp.fine == i){//l'elemento precedente è un candidato
        maxxTemp++;
        nonPresenteTemp.fine = i+1;
      }
      else{//l'elemento è il primo dell'intervallo candidato
        nonPresenteTemp.inizio = i-1;
        nonPresenteTemp.fine = i+1;
        maxxTemp++;
      }
    }
    else{//l'elemento non è un candidato
      if(nonPresenteTemp.fine == i){//ma l'elemento prima sì
        if(maxxTemp>maxx){
          maxx = maxxTemp;
          inizio = nonPresenteTemp.inizio;
          fine = nonPresenteTemp.fine;
        }
      }
      else{//neanche l'elemento prima lo è
      }
    }
  }

  ofstream out("output.txt");
  out<<inizio<<" "<<fine<<"\n";
  return 0;
}
