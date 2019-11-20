#pragma once
#include<iostream>
using namespace std;

template<class T>
class minHeap
{//用数组描述的二叉树表示 
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
	    {//返回最小元素的引用 
	    	return heap[1];
		}
	    void pop()
	    {//删除最小元素 ,这里只是把最后一个元素踢出heapSize的范围但是并没有删除，有隐患？ 
	       	if(heapSize==0)
	       	{
	       		cerr<<"堆为空！"<<endl;
	       		return;
			}
	       	heap[1].~T();  //删除最小元素，这句话根本没用啊？ 
	       	//cout<<"heap[1] is"<<heap[1]<<endl;
	       	T lastElement=heap[heapSize];   //删除一个元素，然后重新建堆 
	       	
			//重新堆化：从根开始，为最后一个元素寻找位置 
	       	int currentNode=1,child=2;
	       	while(child<=heapSize)
	       	{//首先选出currentNode较小的孩子，然后看看能不能插入 
	       		if(child<heapSize && heap[child]>heap[child+1] )
	       		   child++;
			    if(lastElement<=heap[child])
				   break;  //找到一个可以插入的位置，跳出循环 
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
	       while( pos!=1 && heap[pos/2]>theElement )
	       {//父节点较大且没有走到根 
		       heap[pos]=heap[pos/2];  //把元素向下移动 
	       	   pos/=2;                 //检查节点向上一层 
		   }
	       heap[pos]=theElement;
	       heapSize++;  
		}
		void erase(T element)
		{//删除方法：首先在二叉树中找到element对应的位置，然后类似pop操作即可。
		    int i; 
			for(i=1;i<=heapSize;i++)
			{
				if(element==heap[i])
				   break;
			}  
			if(i>heapSize) {  cerr<<"erase failed."<<endl;	return;	}  
			//成功找到对应位置的情况
			heap[i].~T();
			T lastElement=heap[heapSize];
			
			int currentNode=i,child=2*i;
			while(child<=heapSize)
			{
				if(child<heapSize && heap[child]>heap[child+1] )
	       		   child++;  //这是较小的孩子 
			    if(lastElement<=heap[child])
				   break;  //找到一个可以插入的位置，跳出循环 
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
		{//在数组theHeap[1:theSize]中建小根堆 
		 //首先收回原heap空间 
		 delete [] heap;
		 heap=theHeap;
		 heapSize=theSize;
		 
		 //从有叶节点的节点开始堆化 
		 for(int root=heapSize/2;root>=1;root--)
		 {
		 	T rootElement=heap[root];
		 	int child=root*2; //child是root的左孩子 
			int currentNode=root;
			 while(child<=heapSize)   //保证以root为根节点的树是小根堆 
			 {
			 	if(child<heapSize && heap[child] > heap[child+1] )
			 	   child++;   //保证child是较小子节点 
				if(heap[child]>=rootElement)
				   break;
				if(heap[child]<rootElement)      //相对顺序有讲究的！这里也只能写rootElement，不能写成heap[currentNode]，因为在循环中cur的值会改变 
				{
					heap[currentNode]=heap[child];  //把孩子向上移 
					currentNode=child;
					child*=2;
				}
			  } 
		 	heap[currentNode]=rootElement;
		 }	
		}
	    void deactivateArray()
        {//从析构函数中保留heap 
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
		T *heap;             //保存堆中元素的数组，从1开始存放 
		int arrayLength;     //数组heap的容量 
		int heapSize;        //堆的元素个数 
};

template<class T>
void heapSort(T a[],int n)
{//使用堆排序方法给a[1:n]排序 
 //在数组上建立小根堆
   minHeap<T> heap(1);
   heap.initialize(a,n);
   T b[n+1];   //保存变量的临时数组 
   
   //逐个从小根堆中提取元素，从大到小排序 
   for(int i=1;i<=n-1;i++)
   {
   	  T x=heap.top();
   	  heap.pop();
	  b[i]=x;   //把最小元素放在b数组中
	  
	  cout<<"第"<<i<<"次排序后的结果是：";
	    for(int j=1;j<=i;j++)
           cout<<b[j]<<" ";
      cout<<endl;
   }
    for(int i=1;i<=n-1;i++)
       a[i]=b[i];
   heap.deactivateArray();  //从堆的析构函数中保留数组a 
}


