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
				qFront=qSize=0;
			
			}
		}
        ~arrayQueue() {delete [] Queue;}
        bool empty() const
        {
        	if(qSize==0) return true;
        	else return false;
		}
        int size() const
        {
        	return qSize;
		}
        T& front()
        {
        	if(empty()!=true)
			  return Queue[qFront];  //����qFront��¼�ľ��Ƕ�����Ԫ�ص�λ�� 
			else
			  {  std::cerr<<"����Ϊ��"<<std::endl; exit(1);  }
		}
        T& back()
        {
        	if(empty()!=true)
        	  return Queue[(qFront+qSize-1)%arraylength];
        	else
		      {  std::cerr<<"����Ϊ��"<<std::endl; exit(1);  }
		}
        void pop()
        {//�Ӷ���ɾ��Ԫ�� 
        	T *p=&front(); //�����Ѿ��ж��˶����Ƿ�Ϊ�� 
        	qFront=(qFront+1)%arrayLength;
        	(*p).~T();  //������Ԫ�غ����ܱ�ʾint��ɾ��...�������޷��ָ�����ʼ����ǰ��״̬ 
        	qSize--;
		}
        void push(const T& ele)
        {//�Ӷ�β���Ԫ�� 
        	if( qSize==arrayLength-1 )
        	{//���н������ӱ����鳤��
        		T *newQueue=new T[2*arrayLength];
        		int start=qFront;
        		if(start==0||start==1)
        		{//δ�γɻ� 
        			copy(Queue+start,Queue+arrayLength,newQueue);
				}
				else
				{//�γ��˻� 
					copy(Queue+start,Queue+arrayLength,newQueue); 
					//���Ƶ�2��(start,����ĩ�ˣ��¶�����㣩 
					copy(Queue,Queue+qSize-(arrayLength-start),newQueue+(arrayLength-start)); 
					//���Ƶ�1�Σ�ԭ�����׶ˣ�qback,�¶��е�arraylength-start��λ�ã� 
				}
				qFront=0;  //�����������α�           
				arrayLength=arrayLength*2;
				delete [] Queue;
				Queue=newQueue;
			}	
		
			//��Ԫ�ز�����е�β��
			  Queue[(qFront+qSize)%arrayLength]=ele;
			  qSize++; 
		}
	private:
		int qFront;  //�����е�һ��Ԫ�� 
		int Qsize;   //���е���Ԫ�ظ��� 
		int arrayLength;  //���е����� 
		T *Queue;	 //����Ԫ������ 
};
