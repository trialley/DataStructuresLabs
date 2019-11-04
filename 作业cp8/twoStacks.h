#pragma once
#include<cstring>
#include<cstdlib>
using namespace std;

/*twoStacks类

public:
	enum stack_err;					常见错误
protected:
	void _exLength ();				扩展缓冲区长度
	int stackTop1;					栈顶下标
	int stackTop2;					栈顶下标
	int bufferLength;				缓冲区长度
	T* head;						栈数组头部
public:
	stack ( int initialCapacity = 10 );			构造函数，默认长度10
	~stack () ;									析构函数，释放缓冲区
	bool empty1 () const ;						返回是否空
	bool empty2 () const ;						返回是否空
	int size1 () const ;						返回长度
	int size2 () const ;						返回长度
	T top1 ();									返回栈顶元素
	T top2 ();									返回栈顶元素
	void pop1 ();								弹出栈顶元素，一般不会返回值
	void pop2 ();								弹出栈顶元素，一般不会返回值
	void push1 ( const T theElement );			压入元素
	void push2 ( const T theElement );			压入元素
*/
template<class T>
class twoStacks {
public:
	typedef enum { twoStacks1_empty, twoStacks2_empty } twoStacks_err;
protected:
	void _exLength () {
		T* temp = new T[bufferLength * 2];
		memcpy ( temp, head, ( twoStacksTop1 + 1 ) * sizeof ( T ) );
		memcpy ( temp + bufferLength * 2 - ( bufferLength - twoStacksTop2 ),
			head + twoStacksTop2,
			( bufferLength - twoStacksTop2 ) * sizeof ( T ) );

		delete[] head;
		head = temp;
		twoStacksTop2 = bufferLength + twoStacksTop2;
		bufferLength = bufferLength * 2;
	}

	int twoStacksTop1;
	int twoStacksTop2;
	int bufferLength;
	T* head;
public:
	twoStacks ( int initialCapacity = 50 ) {
		bufferLength = initialCapacity;
		head = new T[bufferLength];
		twoStacksTop1 = -1;
		twoStacksTop2 = bufferLength;
	}
	~twoStacks () { delete[] head; }
	bool empty1 () const { return twoStacksTop1 == -1; }
	bool empty2 () const { return twoStacksTop2 == bufferLength; }
	int size1 () const { return twoStacksTop1 + 1; }
	int size2 () const { return bufferLength - twoStacksTop2; }
	T top1 () {
		//判断是否为空
		//有的实现版本中top输入引用，栈空则返回原数值，这样很不符合职责单一原则
		if ( empty1 () ) {
			throw twoStacks1_empty;
		}
		return head[twoStacksTop1];
	}
	T top2 () {
		//判断是否为空
		//有的实现版本中top输入引用，栈空则返回原数值，这样很不符合职责单一原则
		if ( empty2 () ) {
			throw twoStacks2_empty;
		}
		return head[twoStacksTop2];
	}
	void pop1 () {
		if ( empty1 () ) {
			throw twoStacks1_empty;
		}
		head[twoStacksTop1--].~T ();
	}
	void pop2 () {
		if ( empty2 () ) {
			throw twoStacks2_empty;
		}
		head[twoStacksTop2++].~T ();
	}
	void push1 ( const T theElement ) {
		//判断缓冲区长度并扩大缓冲区
		if ( twoStacksTop1 + 1 == twoStacksTop2 ) {
			_exLength ();
		}
		head[++twoStacksTop1] = theElement;
	}
	void push2 ( const T theElement ) {
		//判断缓冲区长度并扩大缓冲区
		if ( twoStacksTop1 + 1 == twoStacksTop2 ) {
			_exLength ();
		}
		head[--twoStacksTop2] = theElement;
	}
};
