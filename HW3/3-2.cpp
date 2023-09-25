#include <iostream>
#include <string.h>
using namespace std;

int main(){
	int data[100000] = {0};
	int data1[100000] = {0};
	int data2[100000] = {0};
	int bubble1 = 0, bubble2 = 0;
	int t = 0;
	int num;
	while(cin >> num){
		data[t] = num;
		data1[t] = num;
		data2[t] = num; 
		t++;
	}
	int swapseq = 1;
	for(int i=0;i<t-1;i++){
		for(int j=0;j<t-i-1;j++){
			if (data[j] > data[j+1]){
				int temp = data[j+1];
				data[j+1] = data[j];
				data[j] = temp;
				if (swapseq == 5){
					cout << "Bubble: " << data[j] << ", " << data[j+1] << "; ";
					for(int i=0;i<t;i++){
					if (i == t-1){
						cout << data[i] << endl;
					}
					else cout << data[i] << " ";
					}
				}
				swapseq++;
			}
		}
	}
	for(int i=0;i<t-1;i++){
		int k = data1[i];
		int j = i-1;
		while((j >= 0) && (data1[j] > k)){
			data1[j+1] = data1[j];
			j--;
		}
		data1[j+1] = k;
		if (i==4){
			cout << "Insertion: ";
			for(int i=0;i<t;i++){
				if (i == t-1){
					cout << data1[i] << endl;
				}
				else cout << data1[i] << " ";
			}
		}
	}
	for(int i=0;i<t-1;i++){
		int small = i;
		for(int j=i+1;j<t;j++){
			if (data2[j] < data2[small]){
				small = j;
			}
		}
		int temp = data2[i];
		data2[i] = data2[small];
		data2[small] = temp;
		if (i == 4){
			cout << "Selection: " << data2[i] << "; ";
			for(int i=0;i<t;i++){
				if (i == t-1){
					cout << data2[i] << endl;
				}
				else cout << data2[i] << " ";
			}
		}
	}
	for(int i=0;i<t;i++){
		if (i == t-1){
			cout << data[i];
		}
		else cout << data[i] << " ";
	}
}

