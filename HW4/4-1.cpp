#include <iostream>
#include <vector> 
using namespace std;

struct node {
	int a,b;
}; 


bool DFS(int cur,int dst,struct node graph[],int sz,bool visited[]){
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

int main(){
	int t;
	cin >> t;
	struct node graph[t];
	vector<int> vertex;
	bool cycle = false;
	for(int i=0;i<t;i++){
		int c,d;
		cin >> c >> d;
		graph[i].a = c;
		graph[i].b = d;
		int find = 0;
		for(int j=0;j<vertex.size();j++){
			if (vertex[j] == c){
				find = 1;
			}
		}
		if (find == 0){
			vertex.push_back(c);
		}
	}
	for(int i=0;i<vertex.size();i++){
		if (cycle == true) break;
		bool visited[t] = {false};
		cycle = DFS(vertex[i],vertex[i],graph,t,visited);
	}
	if (cycle == true){
		cout << "Cycle" << endl;
	} else cout << "No Cycle" << endl;
}

