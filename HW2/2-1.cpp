#include <iostream>
#include <string>
using namespace std;

string IO = "";
string PRO = "";
string PO = "";

class TreeNode {
	public:	
		TreeNode *left;
		TreeNode *right;
		int data;
		TreeNode(int d){
			data = d;
			left = NULL;
			right = NULL;
		}
};

string tostring(int i){
	string s = "";
	while(i > 0){
		char t = ((i%10)+'0');
		s = t + s;
		i /= 10;
	}
	return s;
}

void inorder(TreeNode *root){
	if (root != NULL){	
		inorder(root->left);
		IO += tostring(root->data) + " ";
		inorder(root->right);
	}
}

void preorder(TreeNode *root){
	if (root != NULL){
		PRO += tostring(root->data) + " ";		
		preorder(root->left);
		preorder(root->right);
	}
}

void postorder(TreeNode *root){
	if (root != NULL){
		postorder(root->left);
		postorder(root->right);
		PO += tostring(root->data) + " ";
	}
}


int main(){
	int d;
	cin >> d;
	TreeNode *tree = new TreeNode(d);
	while(cin >> d){
		TreeNode *ptr = tree;
		while(true){
			if (d > ptr->data){
				if (ptr->right != NULL){
					ptr = ptr->right;
				}
				else break;
			}
			else {
				if (ptr->left != NULL){
					ptr = ptr->left;
				}
				else break;
			}
			}
			if (d > ptr->data){
				ptr->right = new TreeNode(d);
			} else {
				ptr->left = new TreeNode(d);
			}
		}
		inorder(tree);
		cout << IO.substr(0,IO.length()-1) << endl;
		preorder(tree);
		cout << PRO.substr(0,PRO.length()-1) << endl;
		postorder(tree);
		cout << PO.substr(0,PO.length()-1);
}