#pragma once
#include<iostream>
#include<cstdlib> 
#include<algorithm>

template<class T>
struct chainNode
{
	T element;
	chainNode *next=NULL;
	
	chainNode(T ele,chainNode *p)
	{
		element=ele;
		next=p;
	}
	chainNode(T ele)
	{
		element=ele;
	}
	chainNode() {	}
	chainNode& operator=(chainNode &A)
	{//结点赋值 
		element=A.element;
		next=A.next;
		return *this;
	}
};

template<class T>
class linkedQueue
{
	public:
		linkedQueue()
		{//构造函数 
			queueFront=queueBack=NULL;
			queueSize=0;
		}
        ~linkedQueue() 
		{//析构函数 
		    chainNode<T>* deleteNode = queueFront;
		    chainNode<T>* stepNode;
		    while (deleteNode != NULL)
            {
            	stepNode=deleteNode->next;
            	delete deleteNode;
                stepNode = deleteNode;
            }
		}
        bool empty() const
        {
        	if(queueSize==0) return true;
        	else return false;
		}
        int size() const
        {
        	return queueSize;
		}
        T& front()
        {
        	if(queueSize!=0)
        	  return queueFront->element;
        	else
		      {  std::cerr<<"队列为空"<<std::endl; exit(1);  }
		}
        T& back()
        {
        	if(queueSize!=0)
        	  return queueBack->element;
        	else
		      {  std::cerr<<"队列为空"<<std::endl; exit(1);  }
		}
        T pop()
        {//从队首删除元素 
        	if(queueSize==0)
			{//队列为空 
				std::cerr<<"队列为空，禁止删除"<<std::endl;
				exit(1);
			}
			else
			{
				chainNode<T> *p=queueFront->next;
				delete queueFront;
				p=queueFront;
				queueSize--;
			}
		}
        void push(const T& ele)
        {//从队尾添加元素 
        	chainNode<T> *p=new chainNode<T>(ele,NULL);  //初始化 
			
			if(queueSize==0)
			{//队列为空 
				queueBack=queueFront=p;
			}
			else{
				queueBack->next=p;
			    queueBack=p;
			}
			queueSize++;
		}
		void output()
		{
			 chainNode<T>* curNode=queueFront;
			 for(int i=0;i<queueSize;i++)
			 {
			 	std::cout<<curNode.element<<" ";
			 } 
			 std::cout<<std::endl;
		} 
	private:
	    chainNode<T>* queueFront;  // 首元素指针 
        chainNode<T>* queueBack;   // 尾元素指针 
        int queueSize;             // 队列大小 
};



