/*
???  ?????
??????
??????????,??????;?????????
??????
1?????????????????????????:??????????????????????????????????????
2?????????,???????,?????????
3????????????????????(???????),????????????


*/

#pragma once
#include<iostream>
using namespace std;
template<class T>
class btree {
public:
	typedef enum {} err;
	typedef struct node {
		T data;
		node* left;
		node* right;
		node (T data, node* left, node* right)
			:data (data), left (left), right (right) {}
		node ()
			:left (nullptr), right (nullptr) {}

	} node;
protected:
	node* _root;
	int _size;

	void deleteNodes (node* root) {
		if (root) {
			//cout << "delete" << root->data << "\n";
			if (root->left)deleteNodes (root->left);
			if (root->right)deleteNodes (root->right);
			delete root;
		}
	}
	node* _makeNodeFromPreIn (T* pre, T* in, int in_length) {
		node* new_node;

		if (in_length == 0) {
			//cout << "leaf node\n";
			return nullptr;
		} else {
			new_node = new node;

			int len = 0;
			while (pre[0] != in[len]) {
				len++;
			}
			new_node->data = pre[0];
			//cout << pre[0] << "make in \n";
			new_node->left = _makeNodeFromPreIn (pre + 1, in, len);
			new_node->right = _makeNodeFromPreIn (pre + len + 1, in + len + 1, in_length - len - 1);
			return new_node;
		}
	}
	ostream& _preOut (ostream& out, node* rootin) {
		if (rootin == nullptr) {
			return out;
		} else {
			out << rootin->data << " ";
			_preOut (out, rootin->left);
			_preOut (out, rootin->right);
			return out;
		}
	}
public:
	btree () {
		_root = nullptr;
	}
	~btree () {
		//cout << "dis\n";
		if (_root) {
			if (_root->left)deleteNodes (_root->left);
			if (_root->right)deleteNodes (_root->right);
			delete _root;
		}
	}
	void clear () {
		~btree ();
	}
	void buildFromPreIn (T* pre_head_in, T* in_head_in, int length_in) {
		_root = _makeNodeFromPreIn (pre_head_in, in_head_in, length_in);
	}
	ostream& preOut (ostream& out) {
		if (_root == nullptr) {
			return out;
		} else {
			out << _root->data << " ";
			_preOut (out, _root->left);
			_preOut (out, _root->right);
			return out;
		}

	}
};
