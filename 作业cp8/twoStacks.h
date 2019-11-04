#pragma once
#include<cstring>
#include<cstdlib>
using namespace std;

/*twoStacks��

public:
	enum stack_err;					��������
protected:
	void _exLength ();				��չ����������
	int stackTop1;					ջ���±�
	int stackTop2;					ջ���±�
	int bufferLength;				����������
	T* head;						ջ����ͷ��
public:
	stack ( int initialCapacity = 10 );			���캯����Ĭ�ϳ���10
	~stack () ;									�����������ͷŻ�����
	bool empty1 () const ;						�����Ƿ��
	bool empty2 () const ;						�����Ƿ��
	int size1 () const ;						���س���
	int size2 () const ;						���س���
	T top1 ();									����ջ��Ԫ��
	T top2 ();									����ջ��Ԫ��
	void pop1 ();								����ջ��Ԫ�أ�һ�㲻�᷵��ֵ
	void pop2 ();								����ջ��Ԫ�أ�һ�㲻�᷵��ֵ
	void push1 ( const T theElement );			ѹ��Ԫ��
	void push2 ( const T theElement );			ѹ��Ԫ��
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
		//�ж��Ƿ�Ϊ��
		//�е�ʵ�ְ汾��top�������ã�ջ���򷵻�ԭ��ֵ�������ܲ�����ְ��һԭ��
		if ( empty1 () ) {
			throw twoStacks1_empty;
		}
		return head[twoStacksTop1];
	}
	T top2 () {
		//�ж��Ƿ�Ϊ��
		//�е�ʵ�ְ汾��top�������ã�ջ���򷵻�ԭ��ֵ�������ܲ�����ְ��һԭ��
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
		//�жϻ��������Ȳ����󻺳���
		if ( twoStacksTop1 + 1 == twoStacksTop2 ) {
			_exLength ();
		}
		head[++twoStacksTop1] = theElement;
	}
	void push2 ( const T theElement ) {
		//�жϻ��������Ȳ����󻺳���
		if ( twoStacksTop1 + 1 == twoStacksTop2 ) {
			_exLength ();
		}
		head[--twoStacksTop2] = theElement;
	}
};
