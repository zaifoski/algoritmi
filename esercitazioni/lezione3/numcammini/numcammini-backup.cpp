#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//Vi viene dato in input un grafo orientato ed una coppia di nodi S e T. Dovete trovare quanti diversi cammini di lunghezza minima ci sono fra S e T.

//INPUT
//La prima riga contiene quattro interi, N, M, S e T. N è il numero di nodi, M il numero di archi, S il nodo di partenza e T il nodo di arrivo. Le successive M righe contengono due interi per riga, il nodo di partenza e di arrivo degli archi.

//OUTPUT
//Due interi separati da spazio. Il primo è uguale alla distanza fra S e T, il secondo al numero di percorsi di lunghezza minima da S a T.

//ASSUNZIONI
// 1 ≤ N ≤ 1000
// 1 ≤ M ≤ 10000

//ESEMPIO
//	input		--------->	output
//	7 8 0 6     			3 3
//	0 1
//	0 2
//	2 3
//	0 4
//	4 3
//	1 5
//	5 6
//	3 6

//NOTE
//Ci sono tre percorsi di lunghezza minima da 0 a 6: (0,1,3,6), (0,2,3,6), (0,4,3,6)

//costanti
const int MAXN = 10000;
const int MAXM = 100000;

//nodo
struct nodo{
  vector<int> vic;
  bool visited;
};

//grafo
vector<nodo> grafo;
vector<nodo> grafoTrasposto;
int erdos[MAXN];

//funzioni
int distanza(vector<nodo>& grafo,int N,int S,int T);
int numpercorsi(int N,int via,int stop,int dist);
int percorso(int N,int via,int stop,int dist);

int main(){
  
  //variabili
  int N;
  int M;
  int S;
  int T;

  //lettura input
  ifstream in("input.txt");
  in >> N >> M >> S >> T;
  grafo.resize(N);
  grafoTrasposto.resize(N);
  /*for(int i=0;i<N;i++){
    grafo[i].visited=false;
  }*/
  for(int i=0;i<M;i++){
    int from, to;
    in >> from >> to;
    grafo[from].vic.push_back(to);
    grafoTrasposto[to].vic.push_back(from);
  }

  //mio algoritmo
  int dist = distanza(grafo,N,S,T);
  int numper = numpercorsi(N,S,T,dist);

  //stampo output
  ofstream out("output.txt");
  out << dist << " " << numper << "\n";

  return 0;
}

//funzioni
int distanza(vector<nodo>& grafo,int N,int via,int stop){
  int dist = -1;
  queue<int> S;
  S.push(via);
  for(int j=0;j<N;j++){
    erdos[j]=-1;
  }
  erdos[via]=0;
  while(!S.empty()){
    int u = S.front();
    S.pop();
    for(int v:grafo[u].vic){
      if(erdos[v]<0){
        erdos[v]=erdos[u]+1;
        S.push(v);
        if(v==stop){
          dist = erdos[v];
        }
      }
    }
  }
  return dist;
}

int numpercorsi(int N,int via,int stop,int dist){
  int numper = 0;
  int maxT = 0;
  for(int v:grafoTrasposto[stop].vic){
    if (erdos[v] == dist-1){
      maxT = 1 + percorso(N,via,v,dist-1);
    }
    if (maxT == dist){
      numper++;
    }
  }
  return numper;

}

int percorso(int N,int via,int stop,int dist){
  for(int v:grafoTrasposto[stop].vic){
    if (via == v){
      return 1;
    }
    else if (erdos[v] == dist-1){
      return 1 + percorso(N,via,v,dist);
    }
  }
}



/*meglio
int numpercorsi(int via,int stop,int dist){
  return percorso(via,stop,dist,0);
}

int percorso(int via,int stop,int dist,int count){
    for(int v:grafoTrasposto[stop].vic){
      if (dist == 0 && erdos[v] == 0){
        count ++;
        return count;
      }
      else if (erdos[v] == dist){
         count++;
         percorso(via,v,dist-1,count);
      }
    }
}
*/

/*int percorso(int N,int via,int stop,int dist){
  if (max == dist){
    return 1;
  }
  else if (erdos[via] >= erdos[stop]){
    return 0;
  }
  else {
    int perc = 0;
    for(int v:grafoTrasposto[stop].vic){
      if (erdos[v] == dist-1){
        if (percorso(N,via,v,dist) != 0){
          perc += percorso(N,via,v,dist);
        }
      }
    }
    //return perc;
  }
}*/



