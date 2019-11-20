#pragma once
#include<iostream>
using namespace std;

template<class T>
class minHeap
{//�����������Ķ�������ʾ 
	public:
		minHeap(const int initialCapacity=10)
		{
			heap=new T [initialCapacity];
			arrayLength=heapSize=0;
		}
		~minHeap()
		{
			delete [] heap;
		}
		bool empty() const
		{
			if(heapSize==0) return true;
			else return false;
		}
		int size() const
		{
			return heapSize;
		}
	    const T& top()
	    {//������СԪ�ص����� 
	    	return heap[1];
		}
	    void pop()
	    {//ɾ����СԪ�� ,����ֻ�ǰ����һ��Ԫ���߳�heapSize�ķ�Χ���ǲ�û��ɾ������������ 
	       	if(heapSize==0)
	       	{
	       		cerr<<"��Ϊ�գ�"<<endl;
	       		return;
			}
	       	heap[1].~T();  //ɾ����СԪ�أ���仰����û�ð��� 
	       	//cout<<"heap[1] is"<<heap[1]<<endl;
	       	T lastElement=heap[heapSize];   //ɾ��һ��Ԫ�أ�Ȼ�����½��� 
	       	
			//���¶ѻ����Ӹ���ʼ��Ϊ���һ��Ԫ��Ѱ��λ�� 
	       	int currentNode=1,child=2;
	       	while(child<=heapSize)
	       	{//����ѡ��currentNode��С�ĺ��ӣ�Ȼ�󿴿��ܲ��ܲ��� 
	       		if(child<heapSize && heap[child]>heap[child+1] )
	       		   child++;
			    if(lastElement<=heap[child])
				   break;  //�ҵ�һ�����Բ����λ�ã�����ѭ�� 
	       		if(lastElement>heap[child]   )
	       		{
	       			heap[currentNode]=heap[child];
	       			currentNode=child;
	       			child*=2;
				}	
			}
	       	heap[currentNode]=lastElement;
	       	heapSize--; 
		}	
	    void push(T& theElement)
	    {//��Ԫ��theElement����� 
	       if(heapSize == arrayLength-1)
	       {//������ʱ�򱶳����� 
	       	  T *p=new T[2*arrayLength];
			  for(int i=0;i<heapSize;i++)
		      {
	       		 p[i]=heap[i];
	       	  }
	       	  delete [] heap;
	       	  heap=p;
	       	  arrayLength*=2;
		   }
	       //ΪԪ��Ѱ�Ҳ���λ�� 
	       int pos = heapSize+1;
	       while( pos!=1 && heap[pos/2]>theElement )
	       {//���ڵ�ϴ���û���ߵ��� 
		       heap[pos]=heap[pos/2];  //��Ԫ�������ƶ� 
	       	   pos/=2;                 //���ڵ�����һ�� 
		   }
	       heap[pos]=theElement;
	       heapSize++;  
		}
		void erase(T element)
		{//ɾ�������������ڶ��������ҵ�element��Ӧ��λ�ã�Ȼ������pop�������ɡ�
		    int i; 
			for(i=1;i<=heapSize;i++)
			{
				if(element==heap[i])
				   break;
			}  
			if(i>heapSize) {  cerr<<"erase failed."<<endl;	return;	}  
			//�ɹ��ҵ���Ӧλ�õ����
			heap[i].~T();
			T lastElement=heap[heapSize];
			
			int currentNode=i,child=2*i;
			while(child<=heapSize)
			{
				if(child<heapSize && heap[child]>heap[child+1] )
	       		   child++;  //���ǽ�С�ĺ��� 
			    if(lastElement<=heap[child])
				   break;  //�ҵ�һ�����Բ����λ�ã�����ѭ�� 
	       		if(lastElement>heap[child]   )
	       		{
	       			heap[currentNode]=heap[child];
	       			currentNode=child;
	       			child*=2;
				}		
			}
			heap[currentNode]=lastElement;
	       	heapSize--;
		}
		void initialize(T *theHeap,int theSize)
		{//������theHeap[1:theSize]�н�С���� 
		 //�����ջ�ԭheap�ռ� 
		 delete [] heap;
		 heap=theHeap;
		 heapSize=theSize;
		 
		 //����Ҷ�ڵ�Ľڵ㿪ʼ�ѻ� 
		 for(int root=heapSize/2;root>=1;root--)
		 {
		 	T rootElement=heap[root];
		 	int child=root*2; //child��root������ 
			int currentNode=root;
			 while(child<=heapSize)   //��֤��rootΪ���ڵ������С���� 
			 {
			 	if(child<heapSize && heap[child] > heap[child+1] )
			 	   child++;   //��֤child�ǽ�С�ӽڵ� 
				if(heap[child]>=rootElement)
				   break;
				if(heap[child]<rootElement)      //���˳���н����ģ�����Ҳֻ��дrootElement������д��heap[currentNode]����Ϊ��ѭ����cur��ֵ��ı� 
				{
					heap[currentNode]=heap[child];  //�Ѻ��������� 
					currentNode=child;
					child*=2;
				}
			  } 
		 	heap[currentNode]=rootElement;
		 }	
		}
	    void deactivateArray()
        {//�����������б���heap 
		    heap = NULL; 
			arrayLength = heapSize = 0;
		}
		friend ostream& operator<<(ostream &out,minHeap &x)
		{
			for(int i=1;i<=x.heapSize;i++)
			{
				out<<x.heap[i]<<" ";
			}
			return out;
		}
		
		
	private:
		T *heap;             //�������Ԫ�ص����飬��1��ʼ��� 
		int arrayLength;     //����heap������ 
		int heapSize;        //�ѵ�Ԫ�ظ��� 
};

template<class T>
void heapSort(T a[],int n)
{//ʹ�ö����򷽷���a[1:n]���� 
 //�������Ͻ���С����
   minHeap<T> heap(1);
   heap.initialize(a,n);
   T b[n+1];   //�����������ʱ���� 
   
   //�����С��������ȡԪ�أ��Ӵ�С���� 
   for(int i=1;i<=n-1;i++)
   {
   	  T x=heap.top();
   	  heap.pop();
	  b[i]=x;   //����СԪ�ط���b������
	  
	  cout<<"��"<<i<<"�������Ľ���ǣ�";
	    for(int j=1;j<=i;j++)
           cout<<b[j]<<" ";
      cout<<endl;
   }
    for(int i=1;i<=n-1;i++)
       a[i]=b[i];
   heap.deactivateArray();  //�Ӷѵ����������б�������a 
}


