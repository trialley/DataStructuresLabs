/*实验七  队列
一、实验目的
1、掌握队列结构的定义与实现；
2、掌握队列结构的使用。
二、实验内容
1、创建队列类，采用链式描述；
2、实现卡片游戏
假设桌上有一叠扑克牌，依次编号为1-n（从最上面开始）。
当至少还有两张的时候，可以进行操作：把第一张牌扔掉，然后把新的第一张放到整叠牌的最后。
输入n，输出每次要扔掉的牌，以及最后剩下的牌。
*/
#include<iostream>
using namespace std;
#define NDEBUG
#ifdef DEBUG
#define dprintf printf
#else
#define dprintf /\
/ printf
#endif

/*****************************************************************************
*  queue.h                                                                   *
*  Copyright (C) 2019.10.30 TriAlley  lg139@139.com                          *
*  @brief    链表队列的实现                                                   *
*  @license  GNU General Public License (GPL)                                *
*****************************************************************************/
#pragma once


/*queue
public:
	enum queue_err { queue_empty };  //常见的错误
private:
	struct node;					//结点类型
	node* _head;					//头结点指针
	node* _end;						//尾结点指针，指向NULL
	int _length;					//元素个数
public:
	queue ();						//构造函数
	~queue ();						//析构函数
	void push ( const T& in );		//入队列
	T front ();						//获得首元素
	void pop ();					//弹出首元素
	bool isempty ()const;			//是否为空
	int size ()const;				//获取元素个数
*/
template<typename T>
class queue {
public:
	enum queue_err { queue_empty };
private:
	typedef struct node {
		T data;
		node* next;
	}node;
	node* _head;
	node* _end;
	int _length;
public:
	queue () {
		_head = new node;
		_end = _head;
		_length = 0;
	}
	~queue () {
		while ( _head->next != NULL ) {
			node* temp = _head;
			_head = _head->next;
			delete temp;
		}
		delete _head;
	}

	void push ( const T& in ) {
		_length++;
		node* n_end = new node;
		n_end->data = in;
		n_end->next = NULL;

		_end->next = n_end;
		_end = n_end;
	}
	T front () {
		if ( isempty () ) {
			throw queue_empty;
		}
		return _head->next->data;
	}
	void pop () {
		if ( isempty () ) {
			throw queue_empty;
		}
		node* n_head = _head->next;
		delete _head;
		_head = n_head;

		_length--;
		return;
	}
	bool isempty ()const { return _head == _end; }
	int size ()const { return _length; }
};

int main () {
	try {
		queue<int> q;
		int n;
		cin >> n;

		for ( int i = 1; i <= n; i++ ) {
			q.push ( i );
		}
		dprintf ( "扔掉：\n");
		while ( q.size () >= 2 ) {
			dprintf ( "%d\n", q.front () );
			q.pop ();
			q.push ( q.front () );
			q.pop ();

		}
		dprintf ( "剩余：\n" );
		while ( !q.isempty () ) {
			cout << q.front () << endl;
			q.pop ();
		}
	} catch ( queue<int>::queue_err e ) {
		cout << endl << e << endl;
	}
}