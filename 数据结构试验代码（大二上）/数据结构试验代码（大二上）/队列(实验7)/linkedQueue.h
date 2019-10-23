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
	{//��㸳ֵ 
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
		{//���캯�� 
			queueFront=queueBack=NULL;
			queueSize=0;
		}
        ~linkedQueue() 
		{//�������� 
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
		      {  std::cerr<<"����Ϊ��"<<std::endl; exit(1);  }
		}
        T& back()
        {
        	if(queueSize!=0)
        	  return queueBack->element;
        	else
		      {  std::cerr<<"����Ϊ��"<<std::endl; exit(1);  }
		}
        T pop()
        {//�Ӷ���ɾ��Ԫ�� 
        	if(queueSize==0)
			{//����Ϊ�� 
				std::cerr<<"����Ϊ�գ���ֹɾ��"<<std::endl;
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
        {//�Ӷ�β���Ԫ�� 
        	chainNode<T> *p=new chainNode<T>(ele,NULL);  //��ʼ�� 
			
			if(queueSize==0)
			{//����Ϊ�� 
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
	    chainNode<T>* queueFront;  // ��Ԫ��ָ�� 
        chainNode<T>* queueBack;   // βԪ��ָ�� 
        int queueSize;             // ���д�С 
};



