#include <iostream>
using namespace std;

string s1 = "";
string s2 = "";
string s3 = "";
int rotation = 0;

class TreeNode{
	public:
		int data;
		TreeNode *left;
		TreeNode *right;
		int height;
		TreeNode(int d){
			data = d;
			left = NULL;
			right = NULL;
			height = 1;
		}
};

int height (TreeNode *root){
	return (root == NULL) ? 0 : root->height;
}

int balance(TreeNode *node){
	return (node == NULL) ? 0 : height(node->left) - height(node->right);
} 

TreeNode *rightrotate(TreeNode *node){
	TreeNode *lnode = node->left;
	TreeNode *rlnode = lnode->right;
	lnode->right = node;
	node->left = rlnode;
	node->height = max(height(node->left),height(node->right)) + 1;
	lnode->height = max(height(lnode->left),height(lnode->right)) + 1;
	return lnode;
}

TreeNode *leftrotate(TreeNode *node){
	TreeNode *rnode = node->right;
	TreeNode *lrnode = rnode->left;
	rnode->left = node;
	node->right = lrnode;
	node->height = max(height(node->left),height(node->right)) + 1;
	rnode->height = max(height(rnode->left),height(rnode->right)) + 1;
	return rnode;
}


TreeNode *minimum(TreeNode *node){
	TreeNode *ptr = node;
	while(ptr->left != NULL){
		ptr = ptr->left;
	}
	return ptr;
}

TreeNode *insert(TreeNode *node,int d){
	if (node == NULL){
		TreeNode *node = new TreeNode(d);
		return node;
	}
	if (d < node->data){
		node->left = insert(node->left,d);
	}
	else if (d > node->data){
		node->right = insert(node->right,d);
	} else return node;
	node->height = 1 + max(height(node->left),height(node->right));
	int balancefactor = balance(node);
	if (balancefactor > 1){
		if (d < node->left->data){
			++rotation;
			s3 += "LL,";
			return rightrotate(node);
		}
		else if (d > node->left->data){
			++rotation;
			s3 += "LR,";
			node->left = leftrotate(node->left);
			return rightrotate(node);
		}
	}
	if (balancefactor < -1){
		if (d > node->right->data){
			++rotation;
			s3 += "RR,";
			return leftrotate(node);
		}
		else if (d < node->right->data){
			++rotation;
			s3 += "RL,";
			node->right = rightrotate(node->right);
			return leftrotate(node);
		}
	}
	return node;
}

TreeNode *deletenode(TreeNode *node,int d){
	if (node == NULL) return node;
	if (d < node->data){
		node->left = deletenode(node->left,d);
	}
	else if (d > node->data){
		node->right = deletenode(node->right,d);
	}
	else {
		if ((node->left == NULL || node->right == NULL)){
			TreeNode *temp = (node->left) ? node->left : node->right; 
			if (temp == NULL){
				temp = node;
				node = NULL;
			} else {
				*node = *temp;
				free(temp);
			}
		}
		else {
			TreeNode *temp = minimum(node->right);
			node->data = temp->data;
			node->right = deletenode(node->right,temp->data);
		}
	}
	if (node == NULL) return node;
	node->height = 1 + max(height(node->left),height(node->right));
	int balancefactor = balance(node);
	if (balancefactor > 1){
		if (balance(node->left) >= 0){
			switch (balance(node->left)){
				case 0:
					s3 += "R0,";
					break;
				case 1:
					s3 += "R1,";
					break;
			}
			++rotation;
			return rightrotate(node);
		}
		else {
			++rotation;
			s3 += "R-1,";
			node->left = leftrotate(node->left);
			return rightrotate(node);
		}
	}
	if (balancefactor < -1){
		if (balance(node->right) <= 0){
			switch (balance(node->right)){
				case 0:
					s3 += "R0,";
					break;
				case -1:
					s3 += "R-1,";
					break;
			}
			++rotation;
			return leftrotate(node);
		}
		else {
			++rotation;
			s3 += "R1,";
			node->right = rightrotate(node->right);
			return leftrotate(node);
		}
	}
	return node;
}

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
		s1 += tostring(root->data) + " ";
		inorder(root->right);
	}
}

int toint(string s){
	int i = 0;
	int j = 0;
	while(j < s.length()){
		i = i*10;
		i = i + (s[j] - '0');
		j++;
	}
	return i;
}

int main(){
	TreeNode *tree = NULL;
	string s;
	cin >> s;
	int i = 0;
	int check = 0;
	while(i++ < s.length()){
		if (s[i] == ','){
			tree = insert(tree,toint(s.substr(check,i-check)));
			check = i+1;
		}
	}
	tree = insert(tree,toint(s.substr(check)));
	char m;
	int d = 0;
	while(cin >> m >> d){
		if (m == 'I'){
			tree = insert(tree,d);
		}
		else {
			tree = deletenode(tree,d);
		}
	}
	inorder(tree);
	cout << s1.substr(0,s1.length()-1) << endl;
	cout << rotation << endl;
	cout << s3.substr(0,s3.length()-1);
}