//zjslib.h
//构造说明：
//0层：	数组；单链表、双链表、带头节点的循环链表、二叉链表、跳链表、异质链表；散列表；（全泛型实现）
//1层：	线性表		抽象基类		list
//		数组线性表	数组			arrlist				常用
//		链式线性表	单链表		chainlist_oneway	
//		链式线性表	双链表		chainlist 			常用
//		链式线性表	单链表		chainlist_cycle		
////	异质线性表	异质链表		Hchainlist
//		二叉树		抽象基类		bintree
//		二叉树		链表实现 	chainbintree		常用
//		二叉树		数组实现		arrbintree			
//2层：	矩阵			抽象基类 	matrix
//		矩阵			链表实现		chainmatrix
//		矩阵			数组实现		arrmatrix			常用
//		栈 			抽象基类		stack
//		栈 			链表实现 	chainstack			常用
//		栈			数组实现		arrstack			常用
//		堆 			抽象基类		heap
//		堆 			链表实现		chainheap			
//		堆 			数组实现		arrheap				常用
//		队列			抽象基类		queue
//		队列			链表实现		chainqueue			常用
//		队列			数组实现		arrqueue			常用
//		跳表			基本类型		skipl
//		散列表		基本类型		hashl
//		字典			抽象基类		dic
//		字典			跳表实现		skipdic				常用
//		字典			散列实现		hashdic				常用
//		优先级队列 	抽象基类		pque
//		优先级队列	链表实现		chainpque
//		优先级队列	数组实现		arrpque
//		优先级队列	堆实现		heappque			常用
#ifndef ZJSLIB_H
#define ZJSLIB_H
#include<iostream>
using namespace std;
#include "zjsexc.h"	//与zjslib配套的自定义异常类头文件，全称为zjs_exception.h
#include "changeLength1D.h"
/////////////////////////////////////////////////////////////////////////////

template<typename T>
class list{
public:
	virtual ~list(){};	//这里为什么会有一个分号 见说明文档(1) 从此以后将“见说明文档”省略，只标数字
	virtual bool empty() const = 0;	//函数后面加const表什么意思，纯虚函数相关知识概述 (2)(3)
		//空则返回true					//类的继承相关知识 (4)
	virtual int size() const = 0;
	virtual T& get(int _index) const = 0;	//为什么是引用 (5)
	virtual int indexof(const T& _element) const = 0;
	virtual void erase(int _index) = 0;
	virtual void insert(int _index, const T& _element) = 0;
		//将_element插入到线性表_index的位置上，被插元素后移
	virtual void output(ostream& out) const = 0;	
		//把线性表元素插入输出流	//输出流相关知识 (6)
	virtual void clear() = 0;
		//清表
	virtual void push_back(const T& _element) = 0;
	//virtual void push_front(const T& _element) = 0;
	//virtual void pop_back() = 0;
	//virtual void pop_front() = 0;
};

template<typename T>
class arrlist: public list<T>{	//单层继承，所以选择public
protected:	//设置为protected，以便被用户自定义的其他类继承
	void checkindex(int _index) const;	//C++异常 (7)
		//定义异常处理函数，若_index无效则抛出异常
	T* element;	//存储该线性表元素的一维数组
	int arrlen;	//数组的长度
	int listsize;	//该线性表元素的个数，也就是数组中有效元素的个数
public:
	//BASIC:
	arrlist(int initial_arrlen = 10);	//这里为什么没有默认构造函数？ 
	arrlist(const arrlist<T>&);	//为什么函数声明可以没有参数名字，只有类型 (8)
	~arrlist(){delete[]element;}
	//ADT:
	bool empty() const;
	int size() const;
	T& get(int _index) const;
	int indexof(const T& _element) const;
	void erase(int _index);						//回收操作
	void insert(int _index, const T& _element);	//扩增操作
	void output(ostream& out) const;	
	void clear();								//回收操作
	void push_back(const T& _element);			//扩增操作
	//virtual void push_front(const T& _element);
	//virtual void pop_back();
	//virtual void pop_front();
	//ELSE:
	int capacity() const{return arrlen;}
	void mutiple();	//扩增操作(满员时扩增一倍)
	void divide();	//回收操作(四分之一时缩小一半)		//虚\普通\纯虚函数有关知识 (9)
	void bubblesort();	//最好再定义一个enum来实现up或down
	void ranksort();
	void insertionsort();
	void selectionsort();
	void quicksort();
};

template<typename T>
class chainlist_oneway{
protected:
public:
};


template<typename T>
class chainlist: public list<T>{
protected:
	struct chainnode{
		T element;
		chainnode* next;
		chainnode* prev;
		chainnode(){}
		chainnode(const T& _element){element = _element;}	//struct的默认构造函数与析构函数 (10)
		chainnode(const T& _element, chainnode* _next){
			element = _element;
			next = _next;
		}	//这个构造函数为什么要存在？
	};
	void checkindex(int _index) const;	//这是干什么用的？
	chainnode* head;
	int listsize;
public:
	//BASIC:
	chainlist();
	chainlist(const chainlist<T>&);
	~chainlist();	//需要实现
	//ADT:
	bool empty() const;
	int size() const;
	T& get(int _index) const;
	int indexof(const T& _element) const;
	void erase(int _index);
	void insert(int _index, const T& _element);
	void output(ostream& out) const;
	void clear();
	void push_back(const T& _element);
	//virtual void push_front(const T& _element);
	//virtual void pop_back();
	//virtual void pop_front();
	//ELSE:
	void binsort();
	void radixsort();	//基数排序可以对于float来排序吗？
};

template<typename T>
class chainlist_cycle{
protected:
public:
};

template<typename T>
class Hchainlist{
protected:
public:
};

/////////////////////////////////////////////////////////////////////////////

template<typename T>
class bintree{
protected:
public:
};

template<typename T>
class chainbintree{
protected:
public:
};

template<typename T>
class arrbintree{
protected:
public:
};

/////////////////////////////////////////////////////////////////////////////

template<typename T>
class matrix{
protected:
public:
};

template<typename T>
class chainmatrix{
protected:
public:
};

template<typename T>
class arrmatrix{
protected:
public:
};

/////////////////////////////////////////////////////////////////////////////

template<typename T>
class stack{	//虚基类栈
public:
	virtual ~stack(){}
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual T& top() = 0;
	virtual void pop() = 0;
	virtual void push(const T& _element) = 0;
};

template<typename T>
class chainstack{	//虚基类栈
protected:
public:
};

template<typename T>
class arrstack: public stack<T> {
private:
	int stacktop;	//当前栈顶
	int arrlen;		//栈的容量
	T* stack;		//元素数组
public:
	arrstack(int initial_arrlen = 10){// Constructor.
//	   	if(initial_arrlen < 1){
//			ostream s;
//		    s << "Initial capacity = " << initial_arrlen << " Must be > 0";
//			throw illegalParameterValue(s.str());
//		}
	   	arrlen = initial_arrlen;
	   	stack = new T[arrlen];
	   	stacktop = -1;
	}
    ~arrstack(){
    	delete[] stack;
    }
    bool empty() const{
    	return stacktop == -1;
    }
    int size() const{
    	return stacktop + 1;
    }
    T& top(){
      	if (stacktop == -1)
        throw stackEmpty();
        return stack[stacktop];
    }
    void pop(){
        if (stacktop == -1)
        throw stackEmpty();
        stack[stacktop--].~T();  // destructor for T
    }
    void push(const T& _element){// Add theElement to stack.
	   	if(stacktop == arrlen - 1){// no space, double capacity
	         changeLength1D(stack, arrlen, 2 * arrlen);
	         arrlen *= 2;
	    }
	   	// add at stack top
	   	stack[++stacktop] = _element;
	}
};

/////////////////////////////////////////////////////////////////////////////

template<typename T>
class heap{
protected:
public:
};

template<typename T>
class chainheap{
protected:
public:
};

template<typename T>
class arrheap{
protected:
public:
};

/////////////////////////////////////////////////////////////////////////////

template<typename T>
class queue{
protected:
public:
};

template<typename T>
class chainqueue{
protected:
public:
};

template<typename T>
class arrqueue{
protected:
public:
};

/////////////////////////////////////////////////////////////////////////////

template<typename T>
class skipl{
protected:
public:
};

template<typename T>
class hashl{
protected:
public:
};

/////////////////////////////////////////////////////////////////////////////

template<typename T>
class dic{
protected:
public:
};

template<typename T>
class skipdic{
protected:
public:
};

template<typename T>
class hashdic{
protected:
public:
};

/////////////////////////////////////////////////////////////////////////////

template<typename T>
class pque{
protected:
public:
};

template<typename T>
class chainpque{
protected:
public:
};

template<typename T>
class arrpque{
protected:
public:
};

template<typename T>
class heappque{
protected:
public:
};

/////////////////////////////////////////////////////////////////////////////

#endif //ZJSLIB_H
