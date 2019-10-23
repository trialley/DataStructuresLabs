#pragma once
#include"Arraylist.h"
template<class T>
Arraylist<T>:: Arraylist(int initialCapacity)
{//�����������û��为�� 
    element=new T [initialCapacity];  //�����Ѿ���ʼ����һ�顣 
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
{//����Ԫ��x��һ�γ���ʱ������;�������ڣ��򷵻�-1 
	for(int i=0;i<listSize;i++)
	{
		if(x==element[i])  return i;
	}
	return -1;
}
template<class T>
void Arraylist<T>:: erase(int theIndex)
{//�ӱ���ɾ������ΪtheIndex��Ԫ�� 
	for(int i=theIndex;i<listSize-1;i++)
	{
		element[i]=element[i+1];
	}
	element[--listSize].~T();  //������������������verstehen. ���������������������Ƕ�̬���� 
}
template<class T>
void Arraylist<T>:: insert(int theIndex,const T& theElement)
{
	if(theIndex<0||theIndex>listSize)
	std::cerr<<"��������ȷ������"<<std::endl;
	//std::cout<<listSize<<" "<<arrayLength<<std::endl;
	if(listSize==arrayLength&&arrayLength!=0)
	{//����ռ����� 
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
	{//����Ϊ�� 
		element=new T[2];
	}
	//std::cout<<"listSize is "<<listSize<<std::endl;
	for(int i=listSize-1;i>=theIndex;i--)
	{
	    element[i+1]=element[i];   //�ڶ��ε��ò��뺯�������������,ע�������±��Ǵ�0��ʼ�� 
	}
	element[theIndex]=theElement;
    listSize++;
}
template<class T>
void Arraylist<T>:: output() const
{//��������Ա� 
	for(int i=0;i<listSize;i++)
	{
		std::cout<<element[i];
	}
}
template<class T>
void Arraylist<T>::reSet(int newSize)
{//�������Ԫ�ظ�����ΪnewSize 
	if(arrayLength<newSize)
	{//�����Ļ������������� 
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
	std::cerr<<"��������ȷ������"<<std::endl;
	
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


