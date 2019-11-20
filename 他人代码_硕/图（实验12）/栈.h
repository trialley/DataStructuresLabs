//Question:~int()
#pragma once
#include<iostream>
template<class T>
class arrayStack
{
	public:
		arrayStack(int initialCapacity=10)
		{//构造函数 
			if(initialCapacity<1)
			{
				std::cerr<<"初始化非法！"<<std::endl;
			}
			stack=new T[initialCapacity];
			stackTop=-1;  //代表该栈中没有元素 
			arrayLength=initialCapacity;
		}
		~arrayStack()
		{//析构函数 
			delete [] stack;
		}
		bool empty() const
		{//返回true，当且仅当栈为空 
			if(stackTop==-1) return true;
			else return false;
		}
		int size() const
		{//返回栈中元素个数 
			return (stackTop+1);
		}
		T& top()
		{//返回栈顶元素的引用 
		    if(stackTop==-1)
		    {//如果为空栈 
		    	std::cerr<<"本栈为空"<<std::endl;
		    	exit(1);
			}
			return stack[stackTop];
		}
		T pop()
		{//删除栈顶元素,提供改进策略：当pop操作将栈中元素减少到不足原来1/4时，将容量减半 
			if(stackTop==-1)
		    {//如果为空栈 
		    	std::cerr<<"本栈为空"<<std::endl;
		    	exit(1);
			}
			T Return=stack[stackTop];
			stack[stackTop].~T(); //这里有一个问题，如果是int型变量也会被顺利删除么？ 
			stackTop--;
			
			  if(stackTop<arrayLength/4)
			  {//空间过多，容量减半 
			  	T *temp=new T[arrayLength/2];
		    	for(int i=0;i<=stackTop;i++)
		    	{  temp[i]=stack[i];  }
		    	delete [] stack;
		    	stack=temp;
		    	arrayLength=arrayLength/2;
			  }
		    return Return;
		}
		void push(const T& ele)
		{//将元素ele压入栈顶 
		    if(stackTop==arrayLength-1)
		    {//空间不足,容量加倍 
		    	T *temp=new T[2*arrayLength];
		    	for(int i=0;i<=stackTop;i++)
		    	{  temp[i]=stack[i];  }
		    	delete [] stack;
		    	stack=temp;
		    /*	 changeLengthlD(stack,arrayLength,2*arrayLength);  */ 
			    arrayLength*=2;
			}
			stackTop++;
			stack[stackTop]=ele;
		}
	private:
		int stackTop;     //当前栈顶 
		int arrayLength;  //栈容量 
		T* stack;         //元素数组 
};
