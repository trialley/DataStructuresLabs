//zjslib.h
//构造说明：
//0层：数组；单链表、双链表、带头节点的循环链表、二叉链表、跳链表、异质链表；散列表；（全泛型实现）
//1层：	线性表、		抽象基类		linearlist
//		数组线性表、	数组			arrlist
//		链式线性表、	双链表		chainlist	当前进度，下一步需要将单链表实现改成双链表实现
//		异质线性表、	异质链表		Hchainlist
//		二叉树、		抽象基类		?
//		数组二叉树、	数组 		?
//		链式二叉树、	二叉链表		?
//2层：	矩阵、		数组线性表 	matrix
//		栈、			链式线性表 	chainstack
//								arrstack
//		队列、		链式线性表   chainqueue
//								arrqueue
//		跳表字典、	跳表 		skipdic
//		散列表字典、	散列表 		hashdic
#ifndef ZJSLIB_H
#define ZJSLIB_H

#include "zjsexc.h"	//与zjslib配套的自定义异常类头文件，全称为zjs_exception.h
#include "changeLength1D.h"

template<typename T>
class linearlist{
public:
	virtual ~linearlist(){};	//这里为什么会有一个分号 见说明文档(1) 从此以后将“见说明文档”省略，只标数字
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
class arrlist: public linearlist<T>{	//单层继承，所以选择public
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
class chainlist: public linearlist<T>{
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

//异质链表
//二叉树
//数组二叉树
//链式二叉树

template<typename T>
class matrix{
protected:
	
};

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

#endif //ZJSLIB_H
