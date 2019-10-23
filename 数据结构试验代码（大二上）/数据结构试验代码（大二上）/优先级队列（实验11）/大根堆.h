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
	    {//返回最大元素的引用 
	    	return heap[1];
		}
	    void pop()
	    {//删除最大元素 ,这里只是把最后一个元素踢出heapSize的范围但是并没有删除，有隐患？ 
	       	if(heapSize==0)
	       	{
	       		cerr<<"堆为空！"<<endl;
	       		return;
			}
	       	heap[1].~T();  //删除最大元素 
	       	
	       	T lastElement=heap[heapSize-1];  //删除一个元素，然后重新建堆 
	       	//重新堆化：从根开始，为最后一个元素寻找位置 
	       	int currentNode=1,child=2;
	       	while(child<=heapSize)
	       	{//首先选出currentNode较大的孩子，然后看看能不能插入 
	       		if(child<heapSize && heap[child]<heap[child+1] )
	       		   child++;
	       		if( heap[currentNode]<heap[child]   )
	       		{
	       			heap[currentNode]=heap[child];
	       			currentNode=child;
	       			child*=2;
				}
				if(heap[currentNode]>=heap[child])
				   break;  //找到一个可以插入的位置，跳出循环 
			}
	       	heap[currentNode]=lastElement;
	       	heapSize--; 
		}
	    void push(const T& theElement)
	    {//把元素theElement加入堆 
	       if(heapSize == arrayLength-1)
	       {//快满的时候倍长数组 
	       	  T *p=new T[2*arrayLength];
			  for(int i=0;i<heapSize;i++)
		      {
	       		 p[i]=heap[i];
	       	  }
	       	  delete [] heap;
	       	  heap=p;
	       	  arrayLength*=2;
		   }
	       //为元素寻找插入位置 
	       int pos = heapSize+1;
	       while( pos!=1 && heap[pos/2]<theElement )
	       {//父节点较小且没有走到根 
		       heap[pos]=heap[pos/2];  //把元素向下移动 
	       	   pos/=2;                 //检查节点向上一层 
		   }
	       heap[pos]=theElement;
	       heapSize++;  
		}
		void initialize(T *theHeap,int theSize)
		{//在数组theHeap[1:theSize]中建大根堆 
		 //首先收回原heap空间 
		 delete [] heap;
		 heap=theHeap;
		 heapSize=theSize;
		 
		 //从有叶节点的节点开始堆化 
		 for(int root=heapSize/2;root>=1;root--)
		 {
		 	T lastElement=heap[root];
		 	int child=root*2; //child是root的子节点
			int currentNode=root;
			 while(child<=heapSize)   //保证以root为根节点的树是大根堆 
			 {
			 	if(child<heapSize && heap[child] < heap[child+1] )
			 	   child++;   //保证child是较大子节点 
				if(heap[child]>heap[currentNode])
				{
					heap[currentNode]=heap[child];  //把孩子向上移 
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
		T *heap;             //保存堆中元素的数组，从1开始存放 
		int arrayLength;     //数组heap的容量 
		int heapSize;        //堆的元素个数 
};

template<class T>
void heapSort(T a[],int n)
{//使用堆排序方法给a[1:n]排序 
 //在数组上建立大根堆
   maxHeap<T> heap;
   heap.initialize(a,n);
   
   //逐个从大根堆中提取元素，从小到大排序 
   for(int i=n-1;i>=1;i--)
   {
   	  T x=heap.top();
   	  heap.pop();
   	  a[i+1]=x;
   } 
   heap.deactiveArray();  //从堆的析构函数中保留数组a 
}








