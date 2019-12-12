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
	struct _nodes;					//�������
	_nodes* _head;					//ͷ���ָ��
	_nodes* _end;						//β���ָ�룬ָ��NULL
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