#include <fstream>
using namespace std;
int maxFun(int a,int b){
  if(a>b)
    return a;
  else
    return b;
}
int main(){
  int max=0;
  int here=0;
  int n;
  ifstream in("input.txt");
  in>>n;
  int array[n];
  for(int i = 0; i<n; i++){
    in>>array[i];
  }
  for(int i = 0; i<n; i++){
    here = maxFun(here+array[i],0);
    max = maxFun(here,max);
  }
  ofstream out("output.txt");
  out<<max<<"\n";
  return 0;
}
