/*****************************************************************************
*  stack.h                                                                   *
*  Copyright (C) 2019.10.25 TriAlley  lg139@139.com                          *
*  @brief    ջ                                                              *
*  @license  GNU General Public License (GPL)                                *
*****************************************************************************/
#pragma once
#include<cstring>//memcpy
#include<cstdlib>//min
using namespace std;


/*stack��
public:
	enum stack_err;			��������
protected:
	void _exLength ();				��չ����������
	void _shLength ();				ѹ������������
	int stackTop;					ջ���±�
	int bufferLength;				����������
	T* head;						ջ����ͷ��
public:
	stack ( int initialCapacity = 10 );		���캯����Ĭ�ϳ���10
	~stack () { delete[] head; }				�����������ͷŻ�����
	bool empty () const { return stackTop == -1; }	�����Ƿ��
	int size () const { return stackTop + 1; }		���س���
	T top ();										����ջ��Ԫ��
	void pop ();									����ջ��Ԫ�أ�һ�㲻�᷵��ֵ
	void push ( const T theElement );				ѹ��Ԫ��

*/
template<class W>
class stack {
public:
	typedef enum { pointer_is_null, newLength_less_than_zero, stack_empty } stack_err;
protected:
	void _exLength () {
		W* temp = new W[bufferLength * 2];
		memcpy (temp, head, bufferLength * sizeof (W));
		delete[] head;
		head = temp;
		bufferLength = bufferLength * 2;
	}
	void _shLength () {
		W* temp = new W[bufferLength / 2];
		memcpy (temp, head, bufferLength / 2 * sizeof (W));
		delete[] head;
		head = temp;
		bufferLength = bufferLength / 2;
	}
	int stackTop;
	int bufferLength;
	W* head;
public:
	stack (int initialCapacity = 10) {
		bufferLength = initialCapacity;
		head = new W[bufferLength];
		stackTop = -1;
	}
	~stack () { delete[] head; }
	bool empty () const { return stackTop == -1; }
	int size () const { return stackTop + 1; }
	W top () {
		//�ж��Ƿ�Ϊ��
		//�е�ʵ�ְ汾��top�������ã�ջ���򷵻�ԭ��ֵ�������ܲ�����ְ��һԭ��
		if (stackTop == -1) {
			throw stack_empty;
		}
		return head[stackTop];
	}
	void pop () {
		if (stackTop == -1) {
			throw stack_empty;
		}
		head[stackTop--].~T ();

		/*������С�������Ĵ���*/
		if (size () < bufferLength / 4) {
			_shLength ();
		}
	}
	void push (const W theElement) {
		//�жϻ��������Ȳ����󻺳���
		if (stackTop == bufferLength - 1) {
			_exLength ();
		}
		head[++stackTop] = theElement;
	}
};
