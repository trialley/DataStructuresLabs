#pragma once
#include <iostream>
using namespace std;

template<class T>
struct chainNode
{
	T element;
	chainNode<T>* next;
	
	chainNode() {}
	chainNode(const T& element) { this->element = element; }
	chainNode(const T& element, chainNode<T>* next) 
	{
		this->element = element;
		this->next = next;
	}
	//friend ostream& operator<<(ostream& os, const chainNode<T>& node)
	//{
	//	os << node.element;
	//	return os;
	//}
};