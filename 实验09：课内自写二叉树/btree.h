/*
实验九  二叉树操作
一、实验目的
掌握二叉树的基本概念，链表描述方法；二叉树操作的实现。
二、实验内容
1、创建二叉树类。二叉树的存储结构使用链表。提供操作:前序遍历、中序遍历、后序遍历、层次遍历、计算二叉树结点数目、计算二叉树高度。
2、对建立好的二叉树，执行上述各操作，输出各操作的结果。
3、接收键盘录入的二叉树前序序列和中序序列(各元素各不相同)，输出该二叉树的后序序列。


*/

#pragma once

template<class T>
class btree {
public:
	typedef enum {}err;
	typedef struct node {
		T data;
		node* left;
		node* right;
	}node;
protected:
	node* _root;
	int _size;

	void deleteLeft (node* _root) {

	}
	void deleteRight (node* _root) {

	}
public:
	btree () {

	}
	~btree () {
		deleteLeft (_root);
		deleteRight (_root);
		delete _root;
	}
};