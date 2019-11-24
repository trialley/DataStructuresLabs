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
	/*����Ŀ�ڶ�����С����ĺ��ĺ���������ÿ���ڵ�Ϊ�������Ĳ�����ڵ���*/
	void _cal (node* rootin, int* sizes, int* deepthes) {
		//����������ֱ�ӷ���
		if (rootin) {
			//���ȵݹ����ڵ�Ϊ�������Ľڵ���������������ӽڵ�ȫ��������Ϻ��ټ��㵱ǰԪ��
			_cal (rootin->left, sizes, deepthes);
			_cal (rootin->right, sizes, deepthes);

			//���ڸýڵ�
			//����ǰԪ��û���ӽڵ㣬������Ϊ�������Ľڵ����������Ϊ1
			if (rootin->left == nullptr && rootin->right == nullptr) {
				sizes[rootin->data] = 1;
				deepthes[rootin->data] = 1;
				//cout << deepthes[rootin->data] << " " << sizes[rootin->data] << "����\n";

			//����ǰԪ������������������Ϊ�������Ľڵ��������Ϊ��������Ӧ���ݼ�1
			} else if (rootin->left != nullptr && rootin->right == nullptr) {
				sizes[rootin->data] = sizes[rootin->left->data] + 1;
				deepthes[rootin->data] = deepthes[rootin->left->data] + 1;
				//cout << deepthes[rootin->data] << " " << sizes[rootin->data] << "����\n";

			//����ǰԪ������������������Ϊ�������Ľڵ��������Ϊ��������Ӧ���ݼ�1
			} else if (rootin->left == nullptr && rootin->right != nullptr) {
				sizes[rootin->data] = sizes[rootin->right->data] + 1;
				deepthes[rootin->data] = deepthes[rootin->right->data] + 1;
				//cout << deepthes[rootin->data] << " " << sizes[rootin->data] << "�Ҷ���\n";

			//����ǰԪ��������������������Ϊ�������Ľڵ��������Ϊ����������Ӧ��������ټ�1
			} else if (rootin->left != nullptr && rootin->right != nullptr) {
				sizes[rootin->data] = sizes[rootin->right->data] + sizes[rootin->left->data] + 1;
				deepthes[rootin->data] = max (deepthes[rootin->right->data], deepthes[rootin->left->data]) + 1;
				//cout << deepthes[rootin->data] <<" "<< sizes[rootin->data] << "���Ҷ���\n";
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
		//ͨ�����д洢����ӡԪ�أ�����һ������ݻ�������һ��
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