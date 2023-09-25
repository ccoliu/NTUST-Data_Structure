#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;


int main(){
	int M;
	int dir[4][2] = {{0,1},{-1,0},{0,-1},{1,0}};
	char di[] = {'E','N','W','S'};
	queue<pair<int,int>> ans;
	cin >> M;
	vector<vector<int> > maze(M+1,vector<int>(M+1,0));
	vector<vector<string> > MZ (M+1,vector<string>(M+1,""));
	vector<vector<bool> > visit(M+1,vector<bool>(M+1,0));
	for(int i=0;i<M;i++){
		for(int j=0;j<M;j++){
			cin >> maze[i][j]; 
		}
	}
	int x,y;
	ans.push({0,0});
	while(ans.size() != 0){
		x = ans.front().first;
		y = ans.front().second;
		if (visit[x][y] == 1){
			ans.pop();
			continue;
		}
		visit[x][y] = 1;
		if (x == M-1 && y == M-1){
			break;
		}
		for (int i=0;i<4;i++){
			if (x+dir[i][0] >= 0 && x+dir[i][0] < M && y+dir[i][1] >= 0 && y+dir[i][1] < M && maze[x+dir[i][0]][y+dir[i][1]] == 1){
				ans.push({x+dir[i][0],y+dir[i][1]});
				MZ[x+dir[i][0]][y+dir[i][1]] = MZ[x][y] + di[i];
			}
		}
		ans.pop();	
	}
	cout << MZ[M-1][M-1] << endl;
}
