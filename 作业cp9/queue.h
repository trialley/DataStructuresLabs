#pragma once
#include<cstdlib>
#include<cstdio>
#include<cstring>
using namespace std;

/*queue
public:
	typedef enum { queue_empty } queue_err;		代表常见错误
	typedef enum { POP, PUSH } lastOp_enum;		代表pop与push两种状态
private:
	int theFront;								队列头，在数组中指向队列头左侧空位
	int theBack;								队列尾，指向队列尾元素
	lastOp_enum lastOp;							保存上次操作
	int arrayLength;							数组长度
	T* head;									数组头部
	void _exLength ();							数组扩展函数，较为重要
public:
	queue ( int initialCapacity = 5 );			构造函数
	~queue ();									析构函数
	bool isfull () const;						判断是否满，是题目重点
	bool isempty ()const;						判断是否空，是题目重点
	int size () const;							返回队列长度
	T front ();									返回头部元素
	T back ();									返回尾部元素
	void pop ();								弹出头部元素
	void push ( const T& theElement );			元素入队列
*/
template<class T>
class queue {
public:
	typedef enum { queue_empty } queue_err;
	typedef enum { POP, PUSH } lastOp_enum;
private:
	int theFront;//为了完成题意，theFront指向队列左侧减一的位置
	int theBack;
	lastOp_enum lastOp;
	int arrayLength;
	T* head;
	void _exLength () {
		T* newhead = new T[2 * arrayLength];
		if ( theFront == arrayLength - 1 ) {
			/*整体复制到新数组左侧*/
			memcpy ( newhead + theFront + 1, head + theFront + 1,( theBack - theFront) * sizeof ( T ) );
			theFront = arrayLength * 2 - 1;
		} else {
			/*分别复制到新数组两边*/
			//右边
			int newf = arrayLength + theFront;
			memcpy ( newhead + newf + 1, head + theFront + 1, ( arrayLength - 1 - theFront )*sizeof(T) );
			//左边
			memcpy ( newhead, head, (theBack + 1) * sizeof ( T ) );
			theFront = newf;
			//一开始不小心忘记加sizeof，导致debug一段时间；
			//一开始-1-写成--1，造成VS出现从未见过的报错，复制到dev cpp中调试，发现是-1-写成了--1
		}
		arrayLength = arrayLength * 2;
		delete[] head;
		head = newhead;
	}
public:
	queue ( int initialCapacity = 5 ) {
		arrayLength = initialCapacity;
		head = new T[arrayLength];
		theFront = 0;
		theBack = 0;
		lastOp = POP;
	}
	~queue () { delete[] head; }

	/*如果push到 theBack == theFront 则满，如果pop到 theBack == theFront 则空*/
	bool isfull () const { return ( theBack == theFront ) && ( lastOp == PUSH ); }
	bool isempty ()const { return ( theBack == theFront ) && ( lastOp == POP ); }
	
	int size () const {
		/*返回长度也要判断当前处于 theBack == theFront 的哪种种情况*/
		if ( isfull () ) {
			return arrayLength;
		} else {
			return ( theBack + arrayLength - theFront ) % arrayLength;
		}
	}
	T front () {
		if ( isempty () )
			throw queue_empty;
		return head[( theFront + 1 ) % arrayLength];
	}
	T back () {
		if ( isempty () )
			throw queue_empty;
		return head[theBack];
	}
	void pop () {
		if ( isempty () )
			throw queue_empty;
		head[( theFront + 1 ) % arrayLength].~T ();
		theFront = ( theFront + 1 ) % arrayLength;
		lastOp = POP;
	}
	void push ( const T& theElement ) {
		if ( isfull () ) {
			_exLength ();
		}
		theBack = ( theBack + 1 ) % arrayLength;
		head[theBack] = theElement;
		lastOp = PUSH;
	}
};