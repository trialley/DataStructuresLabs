#pragma once
#include<iostream>
#include"queue.h"

using std::ostream;

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
		node (T datai )
			:data(datai),left (nullptr), right (nullptr) {}
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
	ostream& _postOut (ostream& out, node* rootin) {
		if (rootin == nullptr) {
			return out;
		} else {
			_postOut (out, rootin->left);
			_postOut (out, rootin->right);
			out << rootin->data << " ";
			return out;
		}
	}
	/*本题目第二三个小任务的核心函数，计算每个节点为根的树的层数与节点数*/
	void _cal (node* rootin, int* sizes, int* deepthes) {
		//如果传入空则直接返回
		if (rootin) {
			//首先递归计算节点为根的树的节点数与层数，所有子节点全部计算完毕后再计算当前元素
			_cal (rootin->left, sizes, deepthes);
			_cal (rootin->right, sizes, deepthes);

			//对于该节点
			//若当前元素没有子节点，则以其为根的树的节点数与层数均为1
			if (rootin->left == nullptr && rootin->right == nullptr) {
				sizes[rootin->data] = 1;
				deepthes[rootin->data] = 1;
				//cout << deepthes[rootin->data] << " " << sizes[rootin->data] << "都无\n";

			//若当前元素有左子树，则以其为根的树的节点数与层数为左子树相应数据加1
			} else if (rootin->left != nullptr && rootin->right == nullptr) {
				sizes[rootin->data] = sizes[rootin->left->data] + 1;
				deepthes[rootin->data] = deepthes[rootin->left->data] + 1;
				//cout << deepthes[rootin->data] << " " << sizes[rootin->data] << "左有\n";

			//若当前元素有右子树，则以其为根的树的节点数与层数为右子树相应数据加1
			} else if (rootin->left == nullptr && rootin->right != nullptr) {
				sizes[rootin->data] = sizes[rootin->right->data] + 1;
				deepthes[rootin->data] = deepthes[rootin->right->data] + 1;
				//cout << deepthes[rootin->data] << " " << sizes[rootin->data] << "右都有\n";

			//若当前元素有左右子树，则以其为根的树的节点数与层数为左右子树相应数据相加再加1
			} else if (rootin->left != nullptr && rootin->right != nullptr) {
				sizes[rootin->data] = sizes[rootin->right->data] + sizes[rootin->left->data] + 1;
				deepthes[rootin->data] = max (deepthes[rootin->right->data], deepthes[rootin->left->data]) + 1;
				//cout << deepthes[rootin->data] <<" "<< sizes[rootin->data] << "左右都有\n";
			}
		}
		return;
	}
public:
	btree () {
		_root = nullptr;
		_size = 0;
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
		if (_root) {
			if (_root->left)deleteNodes (_root->left);
			if (_root->right)deleteNodes (_root->right);
			delete _root;
		}
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
	ostream& postOut (ostream& out) {
		if (_root == nullptr) {
			return out;
		} else {
			_postOut (out, _root->left);
			_postOut (out, _root->right);
			out << _root->data << " ";
			return out;
		}
	}
	ostream& levelOut (ostream& out) {
		queue<node* > q;
		node* t = _root;
		q.push (t);
		//通过队列存储待打印元素，这样一层的数据会相邻在一起
		while (!q.empty ()) {
			t = q.front ();
			q.pop ();
			out << t->data << " ";
			if (t->left != nullptr) {
				q.push (t->left);
			}
			if (t->right != nullptr) {
				q.push (t->right);
			}
		}
		return out;
	}
	void setRoot (node* rootin) {
		clear ();
		_root = rootin;
		return;
	}
	void makeTree (T datai, btree& lefttreei, btree& righttreei) {
		_root = new node;
		_root->data = datai;
		_root->left = lefttreei._root;
		_root->right = righttreei._root;
		lefttreei._root = nullptr;
		righttreei._root = nullptr;
	}

	int getHeight () {
		int* sizes = new int[_size + 1];
		int* deepthes = new int[_size+1];
		_cal (_root, sizes, deepthes);

		return deepthes[0];
	}
};