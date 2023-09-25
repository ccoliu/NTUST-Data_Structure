#include <iostream>
#include <cstring> 
#include <vector>
#include <algorithm>
using namespace std;

struct node {
	char a,b;
	int weight;
};

bool DFS(char cur,char dst,vector<struct node> graph,int sz,bool visited[]){
	visited[cur] = true;
	for(int i=0;i<sz;i++){ 
		if (cur == graph[i].a){
			if (graph[i].b == dst){
				return true;
			}
			if (visited[graph[i].b] != true){
				return DFS(graph[i].b,dst,graph,sz,visited);
			}
		}
	}
	return false;
}

void kruskal(struct node graph[], int sz, int vertex) {
   	vector<char> S;
    vector<node> M;
    for(int i=0;i<sz;i++){
    	char u = graph[i].a;
    	char v = graph[i].b;
    	if (find(S.begin(),S.end(),u) == S.end() && find(S.begin(), S.end(), v) == S.end()){
    		S.push_back(u);
    		S.push_back(v);
    		M.push_back(graph[i]);
		}
    	else if (find(S.begin(),S.end(),u) != S.end() && find(S.begin(), S.end(), v) == S.end()){
    		S.push_back(v);
    		M.push_back(graph[i]);
		}
    	else if (find(S.begin(),S.end(),u) == S.end() && find(S.begin(), S.end(), v) != S.end()){
    		S.push_back(u);
    		M.push_back(graph[i]);
		}	
		for(int i=0;i<M.size();i++){
			bool visited[100] = {false};
		}
	}
	int totalweight = 0;
	for (int i = 0; i < M.size(); i++) {
	  totalweight += M[i].weight;
	}
	cout << totalweight << endl; 
	for (int i = 0; i < M.size(); i++) {
	  cout << M[i].a << " " << M[i].b << " " << M[i].weight << endl;
	}
}


int main(){
	int n,e;
	cin >> n >> e;
	int graph[256][256] = {0};
	int numedge = 0;
	char m = '{';
	vector<char> s1;
	vector<char> s2;
	vector<int> weight;
	for(int i=0;i<e;i++){
		char c,d;
		int w;
		cin >> c >> d >> w;
		m = min(m,min(c,d));
		graph[c][d] = w;
		graph[d][c] = w;
	}
	int selected[256];
	memset(selected, false, 256);
	selected[m] = true;
	numedge = m;
	while(numedge < m+n-1){
		int min = 999999;
		int x=0,y=0;
		for(int i=m;i<m+n;i++){
			if (selected[i] != 0){
				for(int j=m;j<m+n;j++){
					if (selected[j] == false && graph[i][j] != 0){
						if (min > graph[i][j]){
							min = graph[i][j];
							x = i;
							y = j;
						}
					}
				}
			}
		}
		selected[y] = true;
		numedge++;
		weight.push_back(graph[x][y]);
		if (x > y){
			int temp = x;
			x = y;
			y = temp;
		}
		s1.push_back((char)x);
		s2.push_back((char)y);
	}
	for (int i = 0; i < weight.size() - 1; i++) {
	  for(int j = 0; j < weight.size() - i - 1; j++) {
	    if (weight[j] > weight[j+1] || (weight[j] == weight[j+1] && s1[j] > s1[j+1]) || (weight[j] == weight[j+1] && s1[j] == s1[j+1] && s2[j] > s2[j+1])) {
	      int temp = weight[j];
	      weight[j] = weight[j+1];
	      weight[j+1] = temp;
	
	      char tempi = s1[j];
	      s1[j] = s1[j+1];
	      s1[j+1] = tempi;
	
	      char tempj = s2[j];
	      s2[j] = s2[j+1];
	      s2[j+1] = tempj;
	    }
	  }
	}
	int totalweight = 0;
	for (int i = 0; i < weight.size(); i++) {
	  totalweight += weight[i];
	}
	cout << totalweight << endl;
	for(int i=0;i<s1.size();i++){
		cout << s1[i] << " " << s2[i] << " " << weight[i] << endl;
	}
}
