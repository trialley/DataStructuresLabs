#include"../实验4：链表/chain.h"
#include"../实验三：数组描述线性表/vector.h"
#include<iostream>
using namespace std;
using namespace TA;

/*
* brief：将链表转换为数组线性表
* in:
*     chain<T>& raw    传入链表引用
* out:
*     arrayList<T>*    返回复制后数组线性表的指针
*/
template<class T>
arrayList<T>* chainToListGet ( chain<T>& raw ) {
	/*建立列表*/
	arrayList<T>* temp = new arrayList<T>;

	/*进行循环复制*/
	int size = raw.listSize ();
	for ( int i = 0; i < size; i++ ) {
		temp->insert ( i, raw.get ( i ) );
	}

	/*返回列表指针*/
	return temp;
}


/*
* brief：将链表转换为数组线性表
* in:
*     chain<T>& raw    传入链表引用
* out:
*     arrayList<T>*    返回复制后数组线性表的指针
*/
template<class T>
arrayList<T>* chainToListIterator ( chain<T>& raw ) {
	/*建立列表*/
	arrayList<T>* temp = new arrayList<T>;

	/*进行循环复制*/
	int size = raw.listSize ();

	//要遍历 size 个值，迭代器要自增 size-1 ，因此首先对第一个元素进行复制
	chain<int>::iterator it = raw.begin ();
	temp->insert ( 0, *it );

	//再对剩余元素进行复制
	for ( int i = 1; i < size; i++ ) {
		it++;
		temp->insert ( i, *it );
	}

	/*返回列表指针*/
	return temp;
}

/*
* brief：建立新的翻转链表，使指针指向新链表
* in:
*     chain<int>& a    传入的两个链表
*     chain<int>& b    
* out: 
*     chain<int>*      为减少复制的资源消耗，此处返回指针
*/
chain<int>* merge ( chain<int>& chain1, chain<int>& chain2) {
	/*复制准备部分*/
	//
	chain<int>* temp = new chain<int>;
	chain<int>::iterator it1 = chain1.begin ();
	chain<int>::iterator it2 = chain2.begin ();

	/*复制主体部分*/
	//两链表长度未知，因此有一条复制完毕即结束交替复制
	//再之后，单独判断并复制未复制完的链表
	while ( ( it1 != chain1.end () ) && ( it2 != chain1.end () ) ) {
		if ( *it1 <= *it2 ) {
			temp->insert ( temp->listSize (), *it1 );
			it1++;
		} else {
			temp->insert ( temp->listSize (), *it2 );
			it2++;
		}
	}

	/*复制扫尾部分*/
	//如果index等于listsize，说明该数组复制完毕；否则未复制完毕，继续复制剩余元素。
	//chain1，chain2线性表必只剩一个没有复制完毕，因此此处两个判断只有一个能执行
	if ( it1 != chain1.end () ) {
		while ( it1 != chain1.end () ) {
			temp->insert ( temp->listSize (), *it1 );
			it1++;
		}
	}
	if ( it2 != chain1.end () ) {
		while ( it2 != chain1.end () ) {
			temp->insert ( temp->listSize (), *it2 );
			it2++;

		}
	}

	return temp;
}


/*
* brief：建立新的翻转链表，使指针指向新链表
* in:  chain<T>** in
* out: void 
*/
template<class T>
void reverse ( chain<T>** in ) {       //需要传入指针的指针，通过指针的指针对指针进行操作；
	chain<T>* temp = new chain<T>;

	/*翻转复制的主体部分*/
	int size = ( *in )->listSize ();
	chain<int>::iterator it = ( *in )->begin ();
	temp->insert ( 0, *it );           //使用迭代器，访问 size 个元素需要自增 size-1 次
	                                   //因此提前复制一次，接下来自增与复制操作循环 size-1 次即可

	for ( int i = 1; i < size; i++ ) { //自增与复制操作循环 size-1 次
		it++;
		temp->insert ( 0, *it );
	}

	/*翻转复制的扫尾部分*/
	delete ( *in );                    //删除指针指向的旧链表，并让它指向新链表
	*in = temp;
	return;
}
int main () {
	chain<int>* raw = ( new chain<int> );
	for ( int i = 0; i < 10; i++ ) {
		raw->insert ( 0, i );
	}
	cout <<"原始链表："<< *raw << endl;


	//raw->reverse ();
	//cout << "成员函数翻转：" << *raw << endl;
	//reverse ( &raw );
	//cout << "外部函数再次翻转：" << *raw << endl;
	chain<int> a;
	//cout << "成员函数合并：" << a.merge ( *raw, *raw )<<endl;
	cout << "外部函数合并：" << *merge ( *raw, *raw );
	//arrayList<int>* temp = chainToListIterator<int>(*raw);
	//cout << "新数组线性表：";
	//for (int i = 0; i < 10; i++) {
	//	cout << (*temp)[i] << " ";
	//}
	//raw->clear ();
	//cout << endl << raw->listSize ();
	delete raw;
	//delete temp;
	return 0;
}





