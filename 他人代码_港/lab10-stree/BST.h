/*���롢ɾ�����������ɺ�Ķ��������������Ҳ���������ҹ��������αȽϵ�Ԫ��*/
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