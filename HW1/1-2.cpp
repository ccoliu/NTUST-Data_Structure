#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

int sum(vector<int> s){
	int time = 0;
	for(auto i:s){
		time += i;
	}
	return time;
}

int main(){
	int counter;
	cin >> counter;
	vector<vector<int>> countertime(10,vector<int>());
	vector<pair<int,int>> totaltime;
	int num_c[10] = {0};
	string name;
	vector<string> N;
	vector<int> A;
	vector<int> P;
	int arrive,process;
	while(cin >> name >> arrive >> process){
		N.push_back(name);
		A.push_back(arrive);
		P.push_back(process);
	}
  	int use_counter[N.size()] = {-1};
	for(int i=0;i<N.size();i++){
		int minPeople = 9999;
		int curr_counter = 0;
		if (i != 0) {
			for(int j=0;j<counter;j++){	
				int x = A[i] - A[i-1];
				if (!countertime[j].empty()){
					while(!countertime[j].empty() && x >= countertime[j][0]){
						x -= countertime[j][0];
						countertime[j].erase(countertime[j].begin()+0);
					}
					if (x > 0) countertime[j][0] -= x;
				}
			}
		}
		for(int j=0;j<counter;j++){
			if (minPeople > countertime[j].size()){
				minPeople = countertime[j].size();
				curr_counter = j;
			}
		}
		countertime[curr_counter].push_back(P[i]);
		totaltime.push_back(make_pair(sum(countertime[curr_counter]) + A[i],i));
		use_counter[i] = curr_counter;
	}
	for(int i=0;i<totaltime.size()-1;i++){
		for(int j=0;j<totaltime.size()-1-i;j++){
			if (totaltime[j].first > totaltime[j+1].first || (totaltime[j].first == totaltime[j+1].first && use_counter[totaltime[j].second] > use_counter[totaltime[j+1].second])){
				pair<int,int> temp = totaltime[j];
				totaltime[j] = totaltime[j+1];
				totaltime[j+1] = temp;
			}
		}
	}
	for(int i=0;i<totaltime.size();i++){
		cout << N[totaltime[i].second] << " " << totaltime[i].first << " " << use_counter[totaltime[i].second] << endl;
	}
}
