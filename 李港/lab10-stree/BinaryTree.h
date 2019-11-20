#pragma once
#define NULL 0
#include"queue.h"
template<typename T>
class BinaryTree {
private:
	typedef struct  node{
		T data;
		node* left;
		node* right;
		node(T data, node* left,node* right)
			:data(data),left(left),right(right){}
	}node;
	node* root;
	node* MakeNodeFromPreIn(T* pre, int prel, T* in, int inl) {
		node* nnode;

		if (inl == 1) {
			nnode = new node(in[0], NULL, NULL);
			return nnode;
		}
		else {
			nnode = new node;

			int len = 0;
			while (per[0] != in[len]) {
				len++;
			}

			/*画图了解左右子树的构建传参*/
			nnode->left = MakeNodeFromPreIn(pre + 1, prel - 1, in, len);
			nnode->right = MakeNodeFromPreIn(per + len + 1, perl - 1 - len, in + len + 1, inl - len - 1);
		}
	}
	DelNode(node* root) {
		if (root == NULL) {
			DelNode(root->left);
			DelNode(root->right);
			delete root;
			return;
		}else {
			return;
		}
	}
	void Clear() {
		DelNode(root);
		return;
	}
public:
	//node* MakeNode(T data, node* left=NULL, node* right=NULL) {

	//}
	//void LinkNode(node* root, node* left=NULL, node* right=NULL) {

	//}
	//void ChangeRoot(T data,node* left,node* right) {

	//}
	void PreOrder(node* root)const {
		if (root == NULL) {
			return 0;
		}
		std::cout << root->data << " ";
		PreOrder(root->left);
		PreOrder(root->right);
	}
	void PostOrder()const {
		if (root == NULL) {
			return 0;
		}
		PreOrder(root->left);
		PreOrder(root->right);
		std::cout << root->data << " ";
	}
	void InOrder()const {
		if (root == NULL) {
			return 0;
		}
		PreOrder(root->left);
		std::cout << root->data << " ";
		PreOrder(root->right);
	}
	void LevelOrder()const {
		queue<node*> q;
		q.push(root);
		
		node* temp;
		while (!q.isempty()) {
			node* head = q.pop();
			if (head != NULL) {
				q.push(head->left);
				q.push(head->right);
				std::cout << head->data << " ";
			}
			q.pop();
		}
	}

	int GetHeight()const {}
	int GetLength()const{
		queue<node*> q;
		q.push(root);

		node* temp;
		while (!q.isempty()) {
			node* head = q.pop();
			if (head != NULL) {
				q.push(head->left);
				q.push(head->right);
				length++;
			}
			q.pop();
		}
		return length;
	}
	void MakeTreeByPreIn(int length, T* in, T* pre) {
		Clear();
		root = MakeNodeFromPreIn(pre,length,in,length);
	}
};