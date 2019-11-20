#pragma once
#include<iostream>
using namespace std;

template<class T>
class maxHeap
{
	public:
		maxHeap(const int initialCapacity=10)
		{
			heap=new T [initialCapacity];
			arrayLength=heapSize=0;
		}
		~maxHeap()
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
	    {//�������Ԫ�ص����� 
	    	return heap[1];
		}
	    void pop()
	    {//ɾ�����Ԫ�� ,����ֻ�ǰ����һ��Ԫ���߳�heapSize�ķ�Χ���ǲ�û��ɾ������������ 
	       	if(heapSize==0)
	       	{
	       		cerr<<"��Ϊ�գ�"<<endl;
	       		return;
			}
	       	heap[1].~T();  //ɾ�����Ԫ�� 
	       	
	       	T lastElement=heap[heapSize-1];  //ɾ��һ��Ԫ�أ�Ȼ�����½��� 
	       	//���¶ѻ����Ӹ���ʼ��Ϊ���һ��Ԫ��Ѱ��λ�� 
	       	int currentNode=1,child=2;
	       	while(child<=heapSize)
	       	{//����ѡ��currentNode�ϴ�ĺ��ӣ�Ȼ�󿴿��ܲ��ܲ��� 
	       		if(child<heapSize && heap[child]<heap[child+1] )
	       		   child++;
	       		if( heap[currentNode]<heap[child]   )
	       		{
	       			heap[currentNode]=heap[child];
	       			currentNode=child;
	       			child*=2;
				}
				if(heap[currentNode]>=heap[child])
				   break;  //�ҵ�һ�����Բ����λ�ã�����ѭ�� 
			}
	       	heap[currentNode]=lastElement;
	       	heapSize--; 
		}
	    void push(const T& theElement)
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
	       while( pos!=1 && heap[pos/2]<theElement )
	       {//���ڵ��С��û���ߵ��� 
		       heap[pos]=heap[pos/2];  //��Ԫ�������ƶ� 
	       	   pos/=2;                 //���ڵ�����һ�� 
		   }
	       heap[pos]=theElement;
	       heapSize++;  
		}
		void initialize(T *theHeap,int theSize)
		{//������theHeap[1:theSize]�н������ 
		 //�����ջ�ԭheap�ռ� 
		 delete [] heap;
		 heap=theHeap;
		 heapSize=theSize;
		 
		 //����Ҷ�ڵ�Ľڵ㿪ʼ�ѻ� 
		 for(int root=heapSize/2;root>=1;root--)
		 {
		 	T lastElement=heap[root];
		 	int child=root*2; //child��root���ӽڵ�
			int currentNode=root;
			 while(child<=heapSize)   //��֤��rootΪ���ڵ�����Ǵ���� 
			 {
			 	if(child<heapSize && heap[child] < heap[child+1] )
			 	   child++;   //��֤child�ǽϴ��ӽڵ� 
				if(heap[child]>heap[currentNode])
				{
					heap[currentNode]=heap[child];  //�Ѻ��������� 
					currentNode=child;
					child*=2;
				}
				if(heap[child]<=heap[currentNode])
				   break;
			  } 
		 	heap[currentNode]=lastElement;
		 }	
		}
	    friend ostream& operator<<(ostream &out,maxHeap &x)
		{
			for(int i=0;i<x.heapSize;i++)
			{
				out<<x.heap[i];
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
 //�������Ͻ��������
   maxHeap<T> heap;
   heap.initialize(a,n);
   
   //����Ӵ��������ȡԪ�أ���С�������� 
   for(int i=n-1;i>=1;i--)
   {
   	  T x=heap.top();
   	  heap.pop();
   	  a[i+1]=x;
   } 
   heap.deactiveArray();  //�Ӷѵ����������б�������a 
}








