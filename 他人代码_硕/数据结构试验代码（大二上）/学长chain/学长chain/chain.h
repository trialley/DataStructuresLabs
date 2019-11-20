#pragma once

#include "chainNode.h"
//#include <iterator>

template<class T>
class iterator
{
public:
	//typedef forward_iterator_tag iterator_category;
	//typedef T value_type;
	//typedef ptrdiff_t difference_type;
	//typedef T* pointer;
	//typedef T& reference;

	iterator(chainNode<T>* theNode = NULL)
	{
		node = theNode;
	}

	T& operator*() const { return node->element; }
	T* operator->() const { return &node->element; }

	// increment
	iterator& operator++()
	{
		node = node->next; return *this;
	}
	iterator operator++(int)
	{
		iterator old = *this;
		node = node->next;
		return old;
	}

	bool operator!=(const iterator right) const
	{
		return node != right.node;
	}
	bool operator==(const iterator right) const
	{
		return node == right.node;
	}
protected:
	chainNode<T>* node;
};


template<class T>
class chain
{
private:
	chainNode<T>* firstNode;
	int listSize;

	chainNode<T>* preMerge(chainNode<T>* pa, chainNode<T>* pb);//递归merge调用的实际递归函数

public:
	chain();
	chain(const chain<T>& c);
	~chain();

	bool isEmpty() { return listSize == 0; }
	int size() { return listSize; }

	T& get(int index) const;
	int indexOf(T& element);
	void erase(int index);
	void insert(int index, const T& element);
	void clear();//清除链表所有节点
	void push_front(const T& element);
	void push_back(const T& element);
	void merge(chain<T> &a, chain<T> &b);//合并两有序链表
	void mergeWithRecursion(chain<T> &a, chain<T> &b);//递归方法合并两有序链表
	void mergeWithIterator(chain<T> &a, chain<T> &b);//利用链表合并两有序链表
	void initFromArray(const T* arr, int size);//由数组元素转换为链表
	void reverse();//链表原地逆序

	iterator<T> begin() {return iterator<T>(firstNode);}
	iterator<T> end() {return iterator<T>(NULL);}

	friend istream& operator >> (istream &is, chain<T> *c)
	{
		int size;
		cout << "Input size:";
		is >> size;
		c->listSize = size;
		cout << "Input element:";
		T element;
		cin >> element;
		c->firstNode = new chainNode<T>(element);
		c->firstNode->next = nullptr;
		if (size >= 1) {
			chainNode<T>* currNode = c->firstNode;
			for (int i = 1;i < size;i++) {
				is >> element;
				currNode->next = new chainNode<T>(element);
				currNode = currNode->next;
			}
			currNode->next = nullptr;
		}

		return is;
	}
	friend ostream& operator<<(ostream &os,const chain<T>* c)
	{

		for (chainNode<T>* currNode = c->firstNode;currNode != nullptr;currNode = currNode->next) {
			os << currNode->element << " ";
		}
		return os;
	}
};

