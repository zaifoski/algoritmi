#include <fstream>
#include <vector>
#include <set>
using namespace std;


#define MAXN 20

int N,R;
int maxR;
vector<int> elementi;
vector<int> richieste;

vector<int> el[MAXN][MAXN];
set<int> solution;

void compute(){
  for(int i=0;i<N;i++)
    el[i][i].push_back(elementi[i]);
  set<int> current;
  for(int dim=2;dim<=N;dim++){
    for(int i=0;i<N-dim+1;i++){
      current.clear();
      int r=i+dim-1;
      for(int j=i;j+1<=r;j++){
	for(int left=0;left<el[i][j].size();left++){
	  int lel=el[i][j][left];
	  for(int right=0;right<el[j+1][r].size();right++){
	    int rel=el[j+1][r][right];
	    if(lel+rel<=maxR)
	      if(current.count(lel+rel)==0){
		current.insert(lel+rel);
		el[i][r].push_back(lel+rel);
	      }
	    if(lel*rel<=maxR)
	      if(current.count(lel*rel)==0){
		current.insert(lel*rel);
		el[i][r].push_back(lel*rel);
	      }
	  }	    
	}
      }
    }
  }
  for(int i=0;i<el[0][N-1].size();i++){
    solution.insert(el[0][N-1][i]);
  }
}

int main(void) {
  ifstream in("input.txt");
  ofstream out("output.txt");
  in >> N >> R;
  elementi.resize(N);
  richieste.resize(R);
  for(int i=0;i<N;i++)
    in>>elementi[i];
  for(int i=0;i<R;i++){
    in>>richieste[i];
    maxR=max(maxR,richieste[i]);
  }
  compute();
  for(int i=0;i<R;i++)
    if(solution.count(richieste[i])>0)
      out<<"SI"<<endl;
    else
      out<<"NO"<<endl;  
  return 0;
}

