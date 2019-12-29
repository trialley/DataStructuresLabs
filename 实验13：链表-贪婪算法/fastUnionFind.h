#pragma once
#include <iostream>
using namespace std;

class UnionFind {//用树的链表描述来表示并查集，用到模拟指针 
public:
	UnionFind (int numberOfElements) {
		parent = new int[numberOfElements + 1];
		for (int i = 1; i <= numberOfElements; i++) {
			parent[i] = 0;
		}
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
	int parent;//若为根节点，则parent是树的重量，否则是父节点的索引 ，一开始是1，不是说1是他的父亲，而是说1是他这颗树的节点数
	bool root; //标志是否为根节点 
	UnionFindNode ():parent(1),root(true) {}
};

class fastUnionFind {//用重量规则和路径紧缩来优化并查集
public:
	fastUnionFind (int numberOfElements) {
		node = new UnionFindNode[numberOfElements + 1];
	}

	int find (int ele) { 
		int theRoot = ele;//theRoot是最终的根节点 

		/*不断寻根*/
		while (!node[theRoot].root) {
			theRoot = node[theRoot].parent;
		}
		
		/*路径紧缩*/
		//下面是紧缩路径，一路上所有“父节点”都重新“认爹”
		//路径紧缩增加了单个查找的操作时间，但它减少了此后查找操作的时间
		int currentNode = ele;  //从ele开始 
		while (currentNode != theRoot) {
			int k = node[currentNode].parent;
			node[currentNode].parent = theRoot;//让模拟指针直接指向根节点 
			currentNode = k;
		}

		return theRoot;
	}
	void unite (int rootA, int rootB) {
		//用重量规则合并根不同的数rootA和rootB，也就是编号大的爸爸成为新爸爸
		if (node[rootA].parent < node[rootB].parent) {
			//A比较轻，把A作为子树
			node[rootB].parent += node[rootA].parent;
			node[rootA].parent = rootB;
			node[rootA].root = false;
		} else {
			node[rootA].parent += node[rootB].parent;
			node[rootB].parent = rootA;
			node[rootB].root = false;
		}
	}


private:
	UnionFindNode* node;
};
