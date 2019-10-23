#pragma once
#include"Arraylist.h"
template<class T>
Arraylist<T>:: Arraylist(int initialCapacity)
{//不考虑智障用户输负数 
    element=new T [initialCapacity];  //这里已经初始化了一遍。 
	arrayLength=initialCapacity;
	listSize=0;
}
template<class T>		
Arraylist<T>:: Arraylist(const Arraylist<T>& A)
{
	listSize=A.listSize;
	arrayLength=A.arrayLength;
	element=new T [arrayLength];
		for(int i=0;i<listSize;i++)
		{
			element[i]=A.element[i];
		}
}
template<class T>
int Arraylist<T>:: indexOf(T& x) const
{//返回元素x第一次出现时的索引;若不存在，则返回-1 
	for(int i=0;i<listSize;i++)
	{
		if(x==element[i])  return i;
	}
	return -1;
}
template<class T>
void Arraylist<T>:: erase(int theIndex)
{//从表中删除索引为theIndex的元素 
	for(int i=theIndex;i<listSize-1;i++)
	{
		element[i]=element[i+1];
	}
	element[--listSize].~T();  //调用析构函数。？？verstehen. 单个类对象的析构，并不是动态调用 
}
template<class T>
void Arraylist<T>:: insert(int theIndex,const T& theElement)
{
	if(theIndex<0||theIndex>listSize)
	std::cerr<<"请输入正确索引！"<<std::endl;
	//std::cout<<listSize<<" "<<arrayLength<<std::endl;
	if(listSize==arrayLength&&arrayLength!=0)
	{//数组空间已满 
		 T *p=new T[2*arrayLength];
		        for(int i=0;i<listSize;i++)
		       	{
	       			p[i]=element[i];
	       		}
	       		delete [] element;
	       		element=p;
	       		arrayLength*=2;
	}
	if(arrayLength==0)
	{//数组为空 
		element=new T[2];
	}
	//std::cout<<"listSize is "<<listSize<<std::endl;
	for(int i=listSize-1;i>=theIndex;i--)
	{
	    element[i+1]=element[i];   //第二次调用插入函数错误出在这里,注意数组下标是从0开始的 
	}
	element[theIndex]=theElement;
    listSize++;
}
template<class T>
void Arraylist<T>:: output() const
{//输出该线性表 
	for(int i=0;i<listSize;i++)
	{
		std::cout<<element[i];
	}
}
template<class T>
void Arraylist<T>::reSet(int newSize)
{//把数组的元素个数改为newSize 
	if(arrayLength<newSize)
	{//不够的话扩大数组容量 
		 T *p=new T[newSize];
		        for(int i=0;i<listSize;i++)
		       	{
	       			p[i]=element[i];
	       		}
	       		delete [] element;
	       		element=p;
	      arrayLength=newSize;
	}
	listSize=newSize;
}
template<class T>
void Arraylist<T>::set(int Index,T ele)
{
	if(Index<0||Index>listSize)
	std::cerr<<"请输入正确索引！"<<std::endl;
	
	else{
		element[Index]=ele;
	}
}
template<class T>
void Arraylist<T>::clear()
{
	delete [] element;
	arrayLength=listSize=0;
}


