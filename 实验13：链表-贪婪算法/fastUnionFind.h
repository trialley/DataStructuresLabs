#pragma once
#include <iostream>
using namespace std;

class UnionFind {//������������������ʾ���鼯���õ�ģ��ָ�� 
public:
	UnionFind (int numberOfElements) {
		parent = new int[numberOfElements + 1];
		for (int i = 1; i <= numberOfElements; i++) {
			parent[i] = 0;
		}
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
	int parent;//��Ϊ���ڵ㣬��parent�����������������Ǹ��ڵ������ ��һ��ʼ��1������˵1�����ĸ��ף�����˵1����������Ľڵ���
	bool root; //��־�Ƿ�Ϊ���ڵ� 
	UnionFindNode ():parent(1),root(true) {}
};

class fastUnionFind {//�����������·���������Ż����鼯
public:
	fastUnionFind (int numberOfElements) {
		node = new UnionFindNode[numberOfElements + 1];
	}

	int find (int ele) { 
		int theRoot = ele;//theRoot�����յĸ��ڵ� 

		/*����Ѱ��*/
		while (!node[theRoot].root) {
			theRoot = node[theRoot].parent;
		}
		
		/*·������*/
		//�����ǽ���·����һ·�����С����ڵ㡱�����¡��ϵ���
		//·�����������˵������ҵĲ���ʱ�䣬���������˴˺���Ҳ�����ʱ��
		int currentNode = ele;  //��ele��ʼ 
		while (currentNode != theRoot) {
			int k = node[currentNode].parent;
			node[currentNode].parent = theRoot;//��ģ��ָ��ֱ��ָ����ڵ� 
			currentNode = k;
		}

		return theRoot;
	}
	void unite (int rootA, int rootB) {
		//����������ϲ�����ͬ����rootA��rootB��Ҳ���Ǳ�Ŵ�İְֳ�Ϊ�°ְ�
		if (node[rootA].parent < node[rootB].parent) {
			//A�Ƚ��ᣬ��A��Ϊ����
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
