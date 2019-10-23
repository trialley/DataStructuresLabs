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
				cerr<<"��ʼ���Ƿ���"<<endl;
			}
			stack=new T[initialCapacity];
			Top1=-1;  
			Top2=initialCapacity;      //�����ջ��û��Ԫ�� 
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
		{//����ǰջ��Ԫ�ص����� 
		    if(Top1==-1)
		    {//���Ϊ��ջ 
		    	cerr<<"ǰջΪ��"<<endl;
		    	exit(1);
			}
			return stack[Top1];
		}
	T& top2()
		{//���غ�ջ��Ԫ�ص����� 
		    if(Top2==arrayLength)
		    {//���Ϊ��ջ 
		    	cerr<<"��ջΪ��"<<endl;
		    	exit(1);
			}
			return stack[Top2];
		}
	void pop1()
		{//ɾ��ǰջ��Ԫ��
			if(Top1==-1)
		    {//���Ϊ��ջ 
		    	std::cerr<<"��ջΪ��"<<std::endl;
		    	exit(1);
			}
			stack[Top1].~T(); //������һ�����⣬�����int�ͱ���Ҳ�ᱻ˳��ɾ��ô�� 
			Top1--;
		}
	void pop2()
		{//ɾ����ջ��Ԫ��
			if(Top2==arrayLength)
		    {//���Ϊ��ջ 
		    	std::cerr<<"��ջΪ��"<<std::endl;
		    	exit(1);
			}
			stack[Top2].~T(); //������һ�����⣬�����int�ͱ���Ҳ�ᱻ˳��ɾ��ô�� 
			Top2++;
		}
	void push1(const T& ele)
		{//��Ԫ��eleѹ��ǰջ�� 
		    if(Top1==Top2-1)
		    {//�ռ䲻��,�����ӱ� 
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
		{//��Ԫ��eleѹ��ǰջ�� 
		    if(Top1==Top2-1)
		    {//�ռ䲻��,�����ӱ� 
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
		int arrayLength;  //ջ������ 
		T* stack;         //Ԫ������ 
		int Top1;         //ǰջ�� 
		int Top2;         //��ջ�� 
};

