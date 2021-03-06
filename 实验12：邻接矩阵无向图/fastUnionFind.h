#pragma once
#include <iostream>
using namespace std;

class UnionFind {//用树的链表描述来表示并查集，用到模拟指针 
public:
	UnionFind (int numberOfElements) {
		parent = new int[numberOfElements + 1];
		for (int e = 1; e <= numberOfElements; e++)
			parent[e] = 0;
	}
	int find (int ele) {//返回ele元素所在的树根 
		while (parent[ele] != 0) {
			ele = parent[ele];
		}
		return ele;
	}
	void unite (int rootA, int rootB) {
		parent[rootB] = rootA;
	}

private:
	int* parent;
};


/************一下是应用了重量规则和路径紧缩优化的快速并查集算法**************/
struct UnionFindNode {
	UnionFindNode () {
		parent = 1;  root = true;
	}
	int parent;   //若为根节点，则parent是树的重量，否则是父节点的模拟指针 
	bool root;    //标志是否为根节点 

};

class fastUnionFind {
	//用重量规则和路径紧缩来优化并查集
public:
	fastUnionFind (int numberOfElements) {
		_nodes = new UnionFindNode[numberOfElements + 1];
	}
	int find (int ele) {//路径紧缩增加了单个查找的操作时间，但它减少了此后查找操作的时间 
		int theRoot = ele;   //theRoot是最终的根节点 
		while (!_nodes[theRoot].root) {
			theRoot = _nodes[theRoot].parent;
		}
		//下面是紧缩路径
		int currentNode = ele;     //从ele开始 
		while (currentNode != theRoot) {
			int k = _nodes[currentNode].parent;
			_nodes[currentNode].parent = theRoot;   //让模拟指针直接指向根节点 
			currentNode = k;
		}
		return theRoot;
	}
	void unite (int rootA, int rootB) {//用重量规则合并根不同的数rootA和rootB
		if (_nodes[rootA].parent < _nodes[rootB].parent) {//A比较轻，把A作为子树 
			_nodes[rootB].parent += _nodes[rootA].parent;
			_nodes[rootA].parent = rootB;
			_nodes[rootA].root = false;
		} else {
			_nodes[rootA].parent += _nodes[rootB].parent;
			_nodes[rootB].parent = rootA;
			_nodes[rootB].root = false;
		}
	}


private:
	UnionFindNode* _nodes;
};
