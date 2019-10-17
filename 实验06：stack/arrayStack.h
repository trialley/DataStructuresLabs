#pragma once
#include<cstring>//memcpy
#include<cstdlib>//min
#include "stack.h"
#include <sstream>


template<class T>
class arrayStack : public stack<T> {
public:
	typedef enum { pointer_is_null, newLength_less_than_zero } arrayStack_err;
	arrayStack ( int initialCapacity = 10 );
	~arrayStack () { delete[] stack; }
	bool empty () const { return stackTop == -1; }
	int size () const {
		return stackTop + 1;
	}
	T& top () {
		if ( stackTop == -1 )
			throw stackEmpty ();
		return stack[stackTop];
	}
	void pop () {
		if ( stackTop == -1 )
			throw stackEmpty ();

		stack[stackTop--].~T ();

		/*增加的用于缩小stack空间的代码*/
		if ( size () < arrayLength / 4 ) {
			changeLength ( stack, arrayLength, arrayLength/2 );
		}
	}
	void push ( const T& theElement );
private:
	void changeLength ( T*& p, int oldLength, int newLength ) {
		/*错误检查*/
		//新长度小于0则报错
		if ( newLength < 0 ) {
			throw newLength_less_than_zero;
		}
		//指针为空则报错
		if ( p == NULL || p == nullptr ) {
			throw pointer_is_null;
		}

		/*进行复制*/
		T* temp = new T[newLength];
		memcpy ( temp, p, min ( oldLength, newLength ) * sizeof ( T ) );
		delete[] p;
		p = temp;
	}
	int stackTop;         // current top of stack
	int arrayLength;      // stack capacity
	T* stack;           // element array
};

template<class T>
arrayStack<T>::arrayStack ( int initialCapacity ) {// Constructor.
	if ( initialCapacity < 1 ) {
		ostringstream s;
		s << "Initial capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue ( s.str () );
	}
	arrayLength = initialCapacity;
	stack = new T[arrayLength];
	stackTop = -1;
}

template<class T>
void arrayStack<T>::push ( const T& theElement ) {// Add theElement to stack.
	if ( stackTop == arrayLength - 1 ) {// no space, double capacity
		changeLength1D ( stack, arrayLength, 2 * arrayLength );
		arrayLength *= 2;
	}

	// add at stack top
	stack[++stackTop] = theElement;
}
