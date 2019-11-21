#pragma once
#include"btree.h"
#include"minHeap.h"

template<class T>
struct huffmanNode {
	btree<T>* tree;
	int weight;

	operator int () const { return weight; }
	bool operator <(huffmanNode& b) const { return weight < b.weight; }
	bool operator >(huffmanNode& b) const { return weight > b.weight; }
};

template <class T>
btree<T>* huffmanTree (int weight[],T* datas,int n) {
	huffmanNode<T>* hNode = new huffmanNode<T>[n + 1];
	btree<T> emptyTree;
	for (int i = 1; i <= n; i++) {
		hNode[i].weight = weight[i];
		hNode[i].tree = new btree<T>;
		hNode[i].tree->makeTree (datas[i], emptyTree, emptyTree);
	}

	// make node array into a min heap
	minHeap<huffmanNode<T> > heap (1);
	heap.initialize (hNode + 1, n);

	// repeatedly combine trees from min heap
	// until only one tree remains
	huffmanNode<T> w, x, y;
	btree<T>* z;
	for (int i = 1; i < n; i++) {
		// remove two lightest trees from the min heap
		x = heap.top (); heap.pop ();
		y = heap.top (); heap.pop ();

		// combine into a single tree
		z = new btree<T>;
		z->makeTree (0, *x.tree, *y.tree);
		w.weight = x.weight + y.weight;
		w.tree = z;
		heap.push (w);
		delete x.tree;
		delete y.tree;
	}

	// destructor for min heap deletes hNode
	return heap.top ().tree;
}


int calHlen (char* si) {
	//统计字符串中各字符的长度
	int char_count[128] = { 0 };
	int type_length = 0;
	int str_length = 0;
	for (int i = 0; si[i] != '\0'; i++) {
		str_length++;
		if (char_count[si[i]] == 0) {
			type_length++;
		}
		char_count[si[i]]++;
	}
	minHeap<int>q;
	for (int i = 0; i < 128; i++) {
		int val = char_count[i];
		if (val > 0) {
			q.push (val);
		}
	}

	if (q.size () == 1)//只有1个节点情况
		return q.top ();

	int sum = 0;//初值0，涵盖了空串情况

	//不断选择集合中权值最小的两个点，计算和 再插入
	while (q.size () > 1) {
		int v1 = q.top (); q.pop ();
		v1 += q.top (); q.pop ();
		sum += v1;
		q.push (v1);
	}
	return sum;
}