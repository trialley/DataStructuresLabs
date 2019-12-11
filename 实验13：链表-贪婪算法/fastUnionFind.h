#pragma once
#include <iostream>
using namespace std;

class UnionFind {//������������������ʾ���鼯���õ�ģ��ָ�� 
public:
	UnionFind (int n) {
		initialize (n);
	}
	void initialize (int numberOfElements) {
		parent = new int[numberOfElements + 1];
		for (int e = 1; e <= numberOfElements; e++)
			parent[e] = 0;
	}
	int find (int ele) {//����eleԪ�����ڵ����� 
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
/************һ����Ӧ�������������·�������Ż��Ŀ��ٲ��鼯�㷨**************/
struct UnionFindNode {
	UnionFindNode () {
		parent = 1;  root = true;
	}
	int parent;   //��Ϊ���ڵ㣬��parent�����������������Ǹ��ڵ��ģ��ָ�� 
	bool root;    //��־�Ƿ�Ϊ���ڵ� 

};

class fastUnionFind {//�����������·���������Ż����鼯
public:
	fastUnionFind (int n) {
		initialize (n);
	}
	void initialize (int numberOfElements) {
		node = new UnionFindNode[numberOfElements + 1];
	}
	int find (int ele) {//·�����������˵������ҵĲ���ʱ�䣬���������˴˺���Ҳ�����ʱ�� 
		int theRoot = ele;   //theRoot�����յĸ��ڵ� 
		while (!node[theRoot].root) {
			theRoot = node[theRoot].parent;
		}
		//�����ǽ���·��
		int currentNode = ele;     //��ele��ʼ 
		while (currentNode != theRoot) {
			int k = node[currentNode].parent;
			node[currentNode].parent = theRoot;   //��ģ��ָ��ֱ��ָ����ڵ� 
			currentNode = k;
		}
		return theRoot;
	}
	void unite (int rootA, int rootB) {//����������ϲ�����ͬ����rootA��rootB
		if (node[rootA].parent < node[rootB].parent) {//A�Ƚ��ᣬ��A��Ϊ���� 
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
