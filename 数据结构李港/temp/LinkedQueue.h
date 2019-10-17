#pragma once

template<class T>
class LinkedQueue;

template<class T>
class Node
{
public:
	friend LinkedQueue<T>;
private:
	T data;
	Node<T>* link;
};

template<class T>
class LinkedQueue
{
public:
	LinkedQueue() { front = rear = 0; }
	~LinkedQueue(void) {}
	bool IsEmpty()const { return ((front) ? false : true); }
	bool IsFull();
	T First() const;
	T Last() const;
	LinkedQueue<T>& Add(const T& x);
	LinkedQueue<T>& Delele(T& x);
private:
	Node<T>* front;
	Node<T>* rear;
};

template<class T>
bool LinkedQueue<T>::IsFull()
{
	try
	{
		Node* p = new Node;
		delete p;
		return false;
	}
	catch (char* ch) {
		return true;
	}
}

template<class T>
T LinkedQueue<T>::Last() const
{
	if (IsEmpty())
		throw "wrong";
	return rear->data;
}

template<class T>
T LinkedQueue<T>::First() const
{
	if (IsEmpty())
		throw "wrong";
	return front->data;
}

template<class T>
LinkedQueue<T>& LinkedQueue<T>::Add(const T& x)
{
	Node<T>* p = new Node<T>;
	p->data = x;
	p->link = 0;
	if (front)
		rear->link = p;
	else
		front = p;
	rear = p;

	return *this;
}

template<class T>
LinkedQueue<T>& LinkedQueue<T>::Delele(T& x)
{
	if (IsEmpty())
		throw "wrong";
	x = front->data;

	Node<T>* p = front;
	front = front->link;
	delete p;

	return *this;
}