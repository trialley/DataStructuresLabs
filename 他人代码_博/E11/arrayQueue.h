
#pragma once
#include<iostream>
#include<cstdlib> 
#include<algorithm>
template<class T>
class arrayQueue
{
	public:
		arrayQueue(int initialCapacity = 10)
		{//11?��o����y 
			if(initialCapacity<0) std::cerr<<"?����D3��?����?D?�䨮����0��?"<<std::endl;
			else{
				Queue=new T[initialCapacity];
				arrayLength=initialCapacity;
				qFront=qBack=0;     //?a��?��?�䨮Queue[1]?a��?2?��??a?? 
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
			  {  std::cerr<<"?����D?a??"<<std::endl; exit(1);  }
		}
        T& back()
        {
        	if(empty()!=true)
        	  return Queue[qBack];
        	else
		      {  std::cerr<<"?����D?a??"<<std::endl; exit(1);  }
		}
        T pop()
        {//�䨮?��������?3y?a?? 
        	T *p=&front(); //?a��?��??-?D??��??����D��?��??a?? 
        	T temp=(*p);
        	qFront=(qFront+1)%arrayLength;
        	(*p).~T();  //??11����?a??o???2??��������?int��?��?3y...��??����??T����???���?3?��??����??���?���䨬?
			return temp; 
		}
        void push(const T& ele)
        {//�䨮?��?2����?��?a?? 
        	if( (qBack+1)%arrayLength==qFront )
        	{//?����D???����??����?��y����3��?�� 
        		T *newQueue=new T[2*arrayLength];
        		int start=(qFront+1)%arrayLength;
        		if(start==0||start==1)
        		{//?��D?3��?�� 
        			std::copy(Queue+start,Queue+qBack+1,newQueue);
				}
				else
				{//D?3����??�� 
					std::copy(Queue+start,Queue+arrayLength,newQueue); 
					//?��??�̨�2??(start,?����D????��?D??����D?e��?��? 
					std::copy(Queue,Queue+qBack+1,newQueue+(arrayLength-start));
					//?��??�̨�1??�ꡧ?-?����D����??��?qback,D??����D�̨�arraylength-start??????��? 
				}
				qFront=(arrayLength)*2-1;
			    qBack=arrayLength-1-1;   //??D?����??����?2��?���� 
				arrayLength=arrayLength*2;
				delete [] Queue;
				Queue=newQueue;
			}
			//��??a??2?��??����D��??22?
			qBack=(qBack+1)%arrayLength;
			Queue[qBack]=ele;
			
		}
		void output()
		{
			for(int i=qFront;i<qBack;i++)
			   std::cout<<Queue[i];
			std::cout<<std::endl;   
		} 
	private:
		int qFront;  //?����D?D�̨���????a??��??�㨰????��?a 
		int qBack;   //?����D��?o����????a??��????? 
		int arrayLength;  //?����D��?��Y��? 
		T *Queue;	 //?����D?a?? 
};
