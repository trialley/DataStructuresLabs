#pragma once
#include <iostream>
using namespace std;

class UnionFind {//������������������ʾ���鼯���õ�ģ��ָ�� 
public:
	UnionFind (int numberOfElements) {
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

class fastUnionFind {
	//�����������·���������Ż����鼯
public:
	fastUnionFind (int numberOfElements) {
		_nodes = new UnionFindNode[numberOfElements + 1];
	}
	int find (int ele) {//·�����������˵������ҵĲ���ʱ�䣬���������˴˺���Ҳ�����ʱ�� 
		int theRoot = ele;   //theRoot�����յĸ��ڵ� 
		while (!_nodes[theRoot].root) {
			theRoot = _nodes[theRoot].parent;
		}
		//�����ǽ���·��
		int currentNode = ele;     //��ele��ʼ 
		while (currentNode != theRoot) {
			int k = _nodes[currentNode].parent;
			_nodes[currentNode].parent = theRoot;   //��ģ��ָ��ֱ��ָ����ڵ� 
			currentNode = k;
		}
		return theRoot;
	}
	void unite (int rootA, int rootB) {//����������ϲ�����ͬ����rootA��rootB
		if (_nodes[rootA].parent < _nodes[rootB].parent) {//A�Ƚ��ᣬ��A��Ϊ���� 
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
