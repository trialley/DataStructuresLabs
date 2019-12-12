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
	struct _nodes;					//结点类型
	_nodes* _head;					//头结点指针
	_nodes* _end;						//尾结点指针，指向NULL
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
template<typename W>
class queue {
public:
	enum queue_err { queue_empty };
private:
	typedef struct _nodes {
		W data;
		_nodes* next;
		_nodes () { next = nullptr; }
	}_nodes;
	_nodes* _head;
	_nodes* _end;
	int _length;
public:
	queue () {
		_head = new _nodes;
		_end = _head;
		_length = 0;
	}
	~queue () {
		while (_head->next != NULL) {
			_nodes* temp = _head;
			_head = _head->next;
			delete temp;
		}
		delete _head;
	}

	void push (const W& in) {
		_length++;
		_nodes* n_end = new _nodes;
		n_end->data = in;
		n_end->next = NULL;

		_end->next = n_end;
		_end = n_end;
	}
	W front () {
		if (empty ()) {
			throw queue_empty;
		}
		return _head->next->data;
	}
	void pop () {
		if (empty ()) {
			throw queue_empty;
		}
		_nodes* n_head = _head->next;
		delete _head;

		_head = n_head;

		_length--;
		return;
	}
	bool empty ()const { return _head == _end; }
	int size ()const { return _length; }
};