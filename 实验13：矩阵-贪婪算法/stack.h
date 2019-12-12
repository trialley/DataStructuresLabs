/*****************************************************************************
*  stack.h                                                                   *
*  Copyright (C) 2019.10.25 TriAlley  lg139@139.com                          *
*  @brief    栈                                                              *
*  @license  GNU General Public License (GPL)                                *
*****************************************************************************/
#pragma once
#include<cstring>//memcpy
#include<cstdlib>//min
using namespace std;


/*stack类
public:
	enum stack_err;			常见错误
protected:
	void _exLength ();				扩展缓冲区长度
	void _shLength ();				压缩缓冲区长度
	int stackTop;					栈顶下标
	int bufferLength;				缓冲区长度
	T* head;						栈数组头部
public:
	stack ( int initialCapacity = 10 );		构造函数，默认长度10
	~stack () { delete[] head; }				析构函数，释放缓冲区
	bool empty () const { return stackTop == -1; }	返回是否空
	int size () const { return stackTop + 1; }		返回长度
	T top ();										返回栈顶元素
	void pop ();									弹出栈顶元素，一般不会返回值
	void push ( const T theElement );				压入元素

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
		//判断是否为空
		//有的实现版本中top输入引用，栈空则返回原数值，这样很不符合职责单一原则
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

		/*用于缩小缓冲区的代码*/
		if (size () < bufferLength / 4) {
			_shLength ();
		}
	}
	void push (const W theElement) {
		//判断缓冲区长度并扩大缓冲区
		if (stackTop == bufferLength - 1) {
			_exLength ();
		}
		head[++stackTop] = theElement;
	}
};
