/*插入、删除操作输出完成后的二叉搜索树；查找操作输出查找过程中依次比较的元素*/
#pragma once
#define NULL 0
#include"queue.h"
template<typename T>
class BinarySearchTree {
private:
	typedef struct  node {
		T data;
		node* left;
		node* right;
		node(T data, node* left, node* right)
			:data(data), left(left), right(right) {}
	}node;
	node* root;
public:
	insert();
	DelEle(node* node);
	DelIndex(node* node);
	FindEle();
	FindIndex();
	void PrintTree();
	int GetHeight()const;
	void MakeTreeByIn(int length, T* in);
};