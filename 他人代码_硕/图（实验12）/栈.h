//Question:~int()
#pragma once
#include<iostream>
template<class T>
class arrayStack
{
	public:
		arrayStack(int initialCapacity=10)
		{//���캯�� 
			if(initialCapacity<1)
			{
				std::cerr<<"��ʼ���Ƿ���"<<std::endl;
			}
			stack=new T[initialCapacity];
			stackTop=-1;  //�����ջ��û��Ԫ�� 
			arrayLength=initialCapacity;
		}
		~arrayStack()
		{//�������� 
			delete [] stack;
		}
		bool empty() const
		{//����true�����ҽ���ջΪ�� 
			if(stackTop==-1) return true;
			else return false;
		}
		int size() const
		{//����ջ��Ԫ�ظ��� 
			return (stackTop+1);
		}
		T& top()
		{//����ջ��Ԫ�ص����� 
		    if(stackTop==-1)
		    {//���Ϊ��ջ 
		    	std::cerr<<"��ջΪ��"<<std::endl;
		    	exit(1);
			}
			return stack[stackTop];
		}
		T pop()
		{//ɾ��ջ��Ԫ��,�ṩ�Ľ����ԣ���pop������ջ��Ԫ�ؼ��ٵ�����ԭ��1/4ʱ������������ 
			if(stackTop==-1)
		    {//���Ϊ��ջ 
		    	std::cerr<<"��ջΪ��"<<std::endl;
		    	exit(1);
			}
			T Return=stack[stackTop];
			stack[stackTop].~T(); //������һ�����⣬�����int�ͱ���Ҳ�ᱻ˳��ɾ��ô�� 
			stackTop--;
			
			  if(stackTop<arrayLength/4)
			  {//�ռ���࣬�������� 
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
		{//��Ԫ��eleѹ��ջ�� 
		    if(stackTop==arrayLength-1)
		    {//�ռ䲻��,�����ӱ� 
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
		int stackTop;     //��ǰջ�� 
		int arrayLength;  //ջ���� 
		T* stack;         //Ԫ������ 
};
