#pragma once
#include<iostream>
#include"queue.h"
using std::cout;
using std::endl;
using std::ostream;

/*class btree
public:
	enum err;			常见错误
	struct node			节点结构体
protected:
	node* _root;		树根指针
	int _size;			树节点数量

	void deleteNodes (node* root)							删除以传入节点为根的树
	node* _makeNodeFromPreIn (T* pre, T* in, int in_length)	以输入的前序与中序序列递归生成一颗树
	ostream& _preOut (ostream& out, node* rootin)			前序遍历
	ostream& _postOut (ostream& out, node* rootin)			后续遍历
public:
	btree ()												构造函数
	~btree ()												析构函数，递归删除所有节点
	void clear ()											清空此树，根节点置为空
	void buildFromPreIn (T* pre_head_in, T* in_head_in, int length_in)暴露给外部的根据前序与中序序列生成树的函数
	ostream& preOut (ostream& out)							暴露给外界的前序遍历接口
	ostream& postOut (ostream& out)							暴露给外界的后序遍历接口
	ostream& levelOut (ostream& out)						暴露给外界的层次遍历接口
	void setRoot (node* rootin)								设置根节点
*/
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
	ostream& _midOut (ostream& out, node* rootin) {
		if (rootin == nullptr) {
			return out;
		} else {
			_midOut (out, rootin->left);
			out << rootin->data << " ";
			_midOut (out, rootin->right);
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
		if (_root) {
			if (_root->left)deleteNodes (_root->left);
			if (_root->right)deleteNodes (_root->right);
			delete _root;
		}
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
	ostream& midOut (ostream& out) {
		if (_root == nullptr) {
			return out;
		} else {
			_midOut (out, _root->left);
			out << _root->data << " ";
			_midOut (out, _root->right);
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
};
