//������ʹ��ӳ�乫ʽ��location(i)=(location(������Ԫ��)+i)%arrayLength  �����������ʾ��
#pragma once
#include<iostream>
#include<cstdlib> 
#include<algorithm>
template<class T>
class arrayQueue
{
	public:
		arrayQueue(int initialCapacity = 10)
		{//���캯�� 
			if(initialCapacity<0) std::cerr<<"���г��ȱ������0��"<<std::endl;
			else{
				Queue=new T[initialCapacity];
				arrayLength=initialCapacity;
				qFront=qBack=0;     //�����Ǵ�Queue[1]��ʼ����Ԫ�� 
			}
		}
        ~arrayQueue() {delete [] Queue;}
        bool empty() const
        {
        	if(qFront==qBack) return true;
        	else return false;
		}
        int size() const
        {
        	return (arrayLength+qBack-qFront)%arrayLength;
		}
        T& front()
        {
        	if(empty()!=true)
			  return Queue[(qFront+1)%arrayLength];
			else
			  {  std::cerr<<"����Ϊ��"<<std::endl; exit(1);  }
		}
        T& back()
        {
        	if(empty()!=true)
        	  return Queue[qBack];
        	else
		      {  std::cerr<<"����Ϊ��"<<std::endl; exit(1);  }
		}
        T pop()
        {//�Ӷ���ɾ��Ԫ�� 
        	T *p=&front(); //�����Ѿ��ж��˶����Ƿ�Ϊ�� 
        	T temp=(*p);
        	qFront=(qFront+1)%arrayLength;
        	(*p).~T();  //������Ԫ�غ����ܱ�ʾint��ɾ��...�������޷��ָ�����ʼ����ǰ��״̬
			return temp; 
		}
        void push(const T& ele)
        {//�Ӷ�β���Ԫ�� 
        	if( (qBack+1)%arrayLength==qFront )
        	{//���н������ӱ����鳤�� 
        		T *newQueue=new T[2*arrayLength];
        		int start=(qFront+1)%arrayLength;
        		if(start==0||start==1)
        		{//δ�γɻ� 
        			std::copy(Queue+start,Queue+qBack+1,newQueue);
				}
				else
				{//�γ��˻� 
					std::copy(Queue+start,Queue+arrayLength,newQueue); 
					//���Ƶ�2��(start,����ĩ�ˣ��¶�����㣩 
					std::copy(Queue,Queue+qBack+1,newQueue+(arrayLength-start));
					//���Ƶ�1�Σ�ԭ�����׶ˣ�qback,�¶��е�arraylength-start��λ�ã� 
				}
				qFront=(arrayLength)*2-1;
			    qBack=arrayLength-1-1;   //����������β�α� 
				arrayLength=arrayLength*2;
				delete [] Queue;
				Queue=newQueue;
			}
			//��Ԫ�ز�����е�β��
			qBack=(qBack+1)%arrayLength;
			Queue[qBack]=ele;
			
		}
		void output()
		{
			for(int i=qFront;i<qBack;i++)
			   std::cout<<Queue[i]<<" ";
			std::cout<<std::endl;   
		} 
	private:
		int qFront;  //�����е�һ��Ԫ�ص�ǰһ��δ֪ 
		int qBack;   //�������һ��Ԫ�ص�λ�� 
		int arrayLength;  //���е����� 
		T *Queue;	 //����Ԫ�� 
};
