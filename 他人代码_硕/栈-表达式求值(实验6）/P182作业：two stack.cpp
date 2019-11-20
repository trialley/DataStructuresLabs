#include<iostream>
using namespace std;

template<class T>
twoStacks
{
	public:
	twoStacks(int initialCapacity=10)
	{
			if(initialCapacity<1)
			{
				cerr<<"初始化非法！"<<endl;
			}
			stack=new T[initialCapacity];
			Top1=-1;  
			Top2=initialCapacity;      //代表该栈中没有元素 
			arrayLength=initialCapacity;
	}
	~twoStacks()
	{
	   delete [] stack;	
	}
	bool empty1() const
	{
		if(Top1==-1) return true;
		else return false;
	}
	bool empty2() const
	{
		if(Top2==arrayLength) return true;
		else return false;
	}
	int size1() const
	{
		return (Top1+1);
	}
    int size2() const
	{
		return (arrayLength-Top2);
	}
	T& top1()
		{//返回前栈顶元素的引用 
		    if(Top1==-1)
		    {//如果为空栈 
		    	cerr<<"前栈为空"<<endl;
		    	exit(1);
			}
			return stack[Top1];
		}
	T& top2()
		{//返回后栈顶元素的引用 
		    if(Top2==arrayLength)
		    {//如果为空栈 
		    	cerr<<"后栈为空"<<endl;
		    	exit(1);
			}
			return stack[Top2];
		}
	void pop1()
		{//删除前栈顶元素
			if(Top1==-1)
		    {//如果为空栈 
		    	std::cerr<<"本栈为空"<<std::endl;
		    	exit(1);
			}
			stack[Top1].~T(); //这里有一个问题，如果是int型变量也会被顺利删除么？ 
			Top1--;
		}
	void pop2()
		{//删除后栈顶元素
			if(Top2==arrayLength)
		    {//如果为空栈 
		    	std::cerr<<"本栈为空"<<std::endl;
		    	exit(1);
			}
			stack[Top2].~T(); //这里有一个问题，如果是int型变量也会被顺利删除么？ 
			Top2++;
		}
	void push1(const T& ele)
		{//将元素ele压入前栈顶 
		    if(Top1==Top2-1)
		    {//空间不足,容量加倍 
		    	T *temp=new T[2*arrayLength];
		    	  for(int i=0;i<=Top1;i++)
		    	  {  temp[i]=stack[i]; 	}
		    	  for(int i=Top2;i<arrayLength;i++)
		    	  {
		    	  	temp[arrayLength+i]=stack[i];
				  }
				delete [] stack;
		    	stack=temp;
			    arrayLength*=2;
			}
			Top1++;
			stack[Top1]=ele;
		}		
	void push2(const T& ele)
		{//将元素ele压入前栈顶 
		    if(Top1==Top2-1)
		    {//空间不足,容量加倍 
		    	T *temp=new T[2*arrayLength];
		    	  for(int i=0;i<=Top1;i++)
		    	  {  temp[i]=stack[i]; 	}
		    	  for(int i=Top2;i<arrayLength;i++)
		    	  {
		    	  	temp[arrayLength+i]=stack[i];
				  }
				delete [] stack;
		    	stack=temp;
			    arrayLength*=2;
			}
			Top2--;
			stack[Top2]=ele;
		}			
	private:
		int arrayLength;  //栈总容量 
		T* stack;         //元素数组 
		int Top1;         //前栈顶 
		int Top2;         //后栈顶 
};

