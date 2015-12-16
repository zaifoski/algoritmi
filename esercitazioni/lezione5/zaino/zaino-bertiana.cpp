#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

   

int C,N;
//T=vector<vector<int> >(N,vector<int>(M,-1));

int zaino(vector<int>& p, vector<int>& v, int i, int c, vector<vector<int> >& D);
int max(int a, int b);
int main() {
	
	ifstream in("input.txt");

	in >> C >> N;
	vector<int> peso(N);
	vector<int> valore(N);
	vector<vector<int> > T(N,vector<int>(C+1,-1));	

	for(int i=0;i<N;i++){
		in >> peso[i] >> valore[i];
	}

	int max = zaino(peso, valore, N-1, C, T);
	ofstream out("output.txt");
   		out << max; 
   	return 0;
}

int zaino(vector<int>& p, vector<int>& v, int i, int c, vector<vector<int> >& D){
	if (c< 0) return -10000000;	
	if (i == -1) return 0;
	if (c==0) return 0;	
	if (D[i][c] == -1) {
		D[i][c]= max((zaino(p, v, i-1, c, D)), (zaino(p, v,i-1,c-p[i], D) +v[i]));	
	}
	return D[i][c];
}

int max(int a, int b){
	if (a>=b) return a;
	else return b;
}
