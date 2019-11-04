/*ʵ����  ����
һ��ʵ��Ŀ��
1�����ն��нṹ�Ķ�����ʵ�֣�
2�����ն��нṹ��ʹ�á�
����ʵ������
1�����������࣬������ʽ������
2��ʵ�ֿ�Ƭ��Ϸ
����������һ���˿��ƣ����α��Ϊ1-n���������濪ʼ����
�����ٻ������ŵ�ʱ�򣬿��Խ��в������ѵ�һ�����ӵ���Ȼ����µĵ�һ�ŷŵ������Ƶ����
����n�����ÿ��Ҫ�ӵ����ƣ��Լ����ʣ�µ��ơ�
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
*  @brief    ������е�ʵ��                                                   *
*  @license  GNU General Public License (GPL)                                *
*****************************************************************************/
#pragma once


/*queue
public:
	enum queue_err { queue_empty };  //�����Ĵ���
private:
	struct node;					//�������
	node* _head;					//ͷ���ָ��
	node* _end;						//β���ָ�룬ָ��NULL
	int _length;					//Ԫ�ظ���
public:
	queue ();						//���캯��
	~queue ();						//��������
	void push ( const T& in );		//�����
	T front ();						//�����Ԫ��
	void pop ();					//������Ԫ��
	bool isempty ()const;			//�Ƿ�Ϊ��
	int size ()const;				//��ȡԪ�ظ���
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
		dprintf ( "�ӵ���\n");
		while ( q.size () >= 2 ) {
			dprintf ( "%d\n", q.front () );
			q.pop ();
			q.push ( q.front () );
			q.pop ();

		}
		dprintf ( "ʣ�ࣺ\n" );
		while ( !q.isempty () ) {
			cout << q.front () << endl;
			q.pop ();
		}
	} catch ( queue<int>::queue_err e ) {
		cout << endl << e << endl;
	}
}