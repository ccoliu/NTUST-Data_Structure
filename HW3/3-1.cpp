#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

vector<int> red;
vector<int> black;
struct TreeNode {
	public:
		TreeNode *parent;
		TreeNode *left;
		TreeNode *right;
		int data;
		int color;
		TreeNode(){
			data = 0;
			left = 0;
			right = 0;
			color = 1;
			parent = 0; 
		}
		TreeNode(int d){
			data = d;
			left = 0;
			right = 0;
			color = 1;
			parent = 0; 
		}
};

class RedBlackTree{
	public:
	TreeNode *root;
	TreeNode *nil;
	RedBlackTree(){
		nil = new TreeNode();
		nil->color = 0;
		root = nil;
		root->parent = nil;
	};
	void insert(int d);
	void insertion(TreeNode *n);
	void colorcheck(TreeNode *node);
	void leftrotate(TreeNode *node);
	void rightrotate(TreeNode *node);
	void colorcheckr(TreeNode *n);
};

int height(TreeNode *root){
	if (root == NULL){
		return 0;
	}
	else {
		int leftheight = height(root->left);
		int rightheight = height(root->right);
		return ((leftheight >= rightheight)) ? leftheight+1 : rightheight+1;
	}
}

void st(TreeNode *root,int lvl){
	if (root == NULL){
		return;
	}
	if (root->data != 0 && lvl == 1){
		if (root->color == 0){
			black.push_back(root->data);
		}
		else red.push_back(root->data);
	}
	else {
		st(root->left,lvl-1);
		st(root->right,lvl-1);
	}
}

void levelorder(TreeNode *root){
	for(int i=1;i<=height(root);i++){
		st(root,i);
	}
}

void RedBlackTree::rightrotate(TreeNode *node){
	TreeNode *lnode = node->left;
   	node->left = lnode->right;
    if (lnode->right != nil) {
      lnode->right->parent = node;
    }
    lnode->parent = node->parent;
    if (node->parent == nil){
    	root = lnode;
	}
    else if (node == node->parent->left) {
      node->parent->left = lnode;
    } else {
      node->parent->right = lnode;
    }
    lnode->right = node;
    node->parent = lnode;
}

void RedBlackTree::leftrotate(TreeNode *node){
	TreeNode *rnode = node->right;
	node->right = rnode->left;
	if(rnode->left != nil){
		rnode->left->parent = node;
	}
	rnode->parent = node->parent;
	if (node->parent == nil){
		root = rnode;
	}
	else if (node == node->parent->left) {
      node->parent->left = rnode;
    } else {
      node->parent->right = rnode;
    }
    rnode->left = node;
    node->parent = rnode;
}


void RedBlackTree::colorcheck(TreeNode *node){
	if (node->left->color == 1 && node->right->color == 1){
		node->color = 1;
		node->left->color = 0;
		node->right->color = 0;
		colorcheckr(node);
	}
	else if (node->left->color == 1){
		if (node->left->left->color == 1){
			node = node->left->left;
			node->parent->color = 0;
			node->parent->parent->color = 1;
			rightrotate(node->parent->parent);
		}
		else if (node->left->right->color == 1) {
			node = node->left;
			leftrotate(node);
			node->parent->color = 0;
			node->parent->parent->color = 1;
			rightrotate(node->parent->parent);
		}
	}
	else if (node->right->color == 1) {
		if (node->right->right->color == 1){
			node = node->right->right;
			node->parent->color = 0;
			node->parent->parent->color = 1;
			leftrotate(node->parent->parent);
		}
		else if (node->right->left->color == 1) {
			node = node->right;
			rightrotate(node);
			node->parent->color = 0;
			node->parent->parent->color = 1;
			leftrotate(node->parent->parent);
		}
	}
	root->color = 0;
}

void RedBlackTree::colorcheckr(TreeNode *node){
	if (node->parent->color == 1){
		if (node->parent == node->parent->parent->left){
			if (node == node->parent->right){
					node = node->parent;
					leftrotate(node);
				}
				node->parent->color = 0;
				node->parent->parent->color = 1;
				rightrotate(node->parent->parent);
		}
		else {
			if (node == node->parent->left){
					node = node->parent;
					rightrotate(node);
				}
				node->parent->color = 0;
				node->parent->parent->color = 1;
				leftrotate(node->parent->parent);
		}
	}
	root->color = 0;
}


void RedBlackTree::insertion(TreeNode *new_node){
	new_node->left = nil;
	new_node->right = nil;
	new_node->color = 1;
}

void RedBlackTree::insert(int d){	
	TreeNode *ptr = nil;
	TreeNode *rt = root;
	//cout << root->data << endl;
	TreeNode *new_node = new TreeNode(d);
	while (rt != nil){
			ptr = rt;
			colorcheck(rt);
			if (new_node->data < rt->data){
				rt = rt->left;
			}
			else rt = rt->right;
		}
	new_node->parent = ptr;
	if (ptr == nil){
		this->root = new_node;
	}
	else if (new_node->data < ptr->data){
		ptr->left = new_node;
	} else ptr->right = new_node;
	insertion(new_node);
	colorcheckr(new_node);
}


int main(){
	RedBlackTree *tree = new RedBlackTree();
	int data;
	cin >> data;
	tree->insert(data);
	while(cin >> data){
		tree->insert(data);
	}
	levelorder(tree->root);
	vector<int> red_sort = red;
	vector<int> black_sort = black;
	int sz = red.size();
	int bsz = black.size();
	if (sz < 4 or bsz < 4) {
		cout << "No game";
	}
	else {
		for(int i=0;i<sz-1;i++){
			for(int j=0;j<sz-i-1;j++){
				if (red_sort[j] > red_sort[j+1]){
					int temp = red_sort[j+1];
					red_sort[j+1] = red_sort[j];
					red_sort[j] = temp;
				}
			}
		}
		cout << "Red team: ";
		for(int i=0;i<sz;i++){
			if (i != sz-1){
				cout << red_sort[i] << ",";
			}
			else cout << red_sort[i] << endl;
		}
		vector<int> red_of;
		cout << "outfield: ";
		int rof = 1;
		while(rof < 4){
			red_of.push_back(red[sz-rof]);
			rof++;
		}
		int of = red_of.size();
		for(int i=0;i<of-1;i++){
			for(int j=0;j<of-i-1;j++){
				if (red_of[j] > red_of[j+1]){
					int temp = red_of[j+1];
					red_of[j+1] = red_of[j];
					red_of[j] = temp;
				}
			}
		}
		for(int i=0;i<of;i++){
			if (i != of-1){
				cout << red_of[i] << ",";
			}
			else cout << red_of[i] << endl;
		}
		cout << "jump ball: " << red[0] << endl;
		
		for(int i=0;i<bsz-1;i++){
			for(int j=0;j<bsz-i-1;j++){
				if (black_sort[j] > black_sort[j+1]){
					int temp = black_sort[j+1];
					black_sort[j+1] = black_sort[j];
					black_sort[j] = temp;
				}
			}
		}
		cout << "Black team: ";
		for(int i=0;i<bsz;i++){
			if (i != bsz-1){
				cout << black_sort[i] << ",";
			}
			else cout << black_sort[i] << endl;
		}
		vector<int> black_of;
		cout << "outfield: ";
		int bf = 1;
		while(bf < 4){
			black_of.push_back(black[bsz-bf]);
			bf++;
		}
		int bof = black_of.size();
		for(int i=0;i<bof-1;i++){
			for(int j=0;j<bof-i-1;j++){
				if (black_of[j] > black_of[j+1]){
					int temp = black_of[j+1];
					black_of[j+1] = black_of[j];
					black_of[j] = temp;
				}
			}
		}
		for(int i=0;i<bof;i++){
			if (i != bof-1){
				cout << black_of[i] << ",";
			}
			else cout << black_of[i] << endl;
		}
		cout << "jump ball: " << black[0];
	}
}

