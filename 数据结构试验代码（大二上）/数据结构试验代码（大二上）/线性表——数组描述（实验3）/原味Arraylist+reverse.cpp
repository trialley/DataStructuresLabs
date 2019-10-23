#include<iostream>
#include<string>
using namespace std;

template<class T>
class linearlist //抽象类线性表 
{
	public:
		virtual ~linearlist() {	}
		virtual bool empty() const=0;
		virtual int size() const=0;
		virtual T& get(int theIndex) const=0;
		virtual int indexOf(T& theElement) const=0;
		virtual void erase(int theIndex)=0;
		virtual void insert(int theIndex,const T& theElement)=0;
		virtual void output() const = 0;
};

template<class T>
class Arraylist :public linearlist<T>
{
	public:
		Arraylist(int initialCapacity=10)
		{//不考虑智障用户输负数 
			element=new T [initialCapacity];  //这里已经初始化了一遍。 
			arrayLength=initialCapacity;
			listSize=0;
			for(int i=0;i<initialCapacity;i++)
			{
				element[i]=i;
			}
			listSize=initialCapacity;
		}
		
		Arraylist(const Arraylist<T>& A)
		{
			listSize=A.listSize;
			arrayLength=A.arrayLength;
			element=new T [arrayLength];
			for(int i=0;i<listSize;i++)
			{
				element[i]=A.element[i];
			}
		}
		~Arraylist() { delete [] element;	}
		
		//ADT方法
		bool empty() const
		{    return listSize==0;   }
		int size() const 
		{    return listSize;	   }
		T& get(int theIndex) const
		{//实现随机存储，效率极高 O(1) 
	       checkIndex(theIndex);
	       return element[theIndex];
        }
		int indexOf(T& x) const
		{//返回元素x第一次出现时的索引;若不存在，则返回-1 
	         for(int i=0;i<listSize;i++)
	         {
		       if(x==element[i])  return i;
	         }
	          return -1;
        }

		void erase(int theIndex)
		{//从表中删除索引为theIndex的元素 
	       for(int i=theIndex;i<listSize-1;i++)
	       {
		      element[i]=element[i+1];
	       }
	       //cout<<"right!"<<endl;
	       element[--listSize].~T();  //调用析构函数。？？verstehen. 单个类对象的析构，并不是动态调用 
        }
		void insert(int theIndex,const T& theElement)
		{
	       if(theIndex<0||theIndex>listSize)
	       cerr<<"请输入正确索引！"<<endl;
	  
		   if(listSize==arrayLength)
		   {//数组空间已满 
			    T *p=new T[2*arrayLength];
			    for(int i=0;i<listSize;i++)
		       	{
	       			p[i]=element[i];
	       		}
	       		delete [] element;
	       		element=p;
	       		arrayLength*=2;
	       }
	       cout<<"listSize is "<<listSize<<endl;
	       for(int i=listSize-1;i>=theIndex;i--)
	       {
	     	  element[i+1]=element[i];   //第二次调用插入函数错误出在这里,注意数组下标是从0开始的 
	       }
	       	  element[theIndex]=theElement;
	       	  listSize++;
	    }
		void output() const
		{//输出该线性表 
		  for(int i=0;i<listSize;i++)
		  {
			  cout<<element[i];
		  }
	    }
		int capacity() const 
		{   return arrayLength;		}
		friend ostream& operator<< (ostream& out,const Arraylist<T> &A)  //模板类的友元函数声明与输出不能分离 
		{
        	for(int i=0;i<A.listSize;i++)
         	{   out<<A.element[i];  }
        	return out;
        }
		void reverse()
		{
				T temp;
			for(int i=0;i<(listSize-1)/2;i++)
			{
				temp=element[i];
				element[i]=element[listSize-1-i];
				element[listSize-1-i]=temp;
			}
		}
		protected:
			void checkIndex(int theIndex)  const
			{//确定索引的有效性，防止越界
                if(theIndex<0||theIndex>=listSize)
	            {
		          cerr<<"请检查索引的有效性！"<<endl;
	            }
            }
			//若索引无效，则抛出异常 
			T *element;  //存储线性表元素的一维数组 
			int arrayLength;  //一维数组的容量 
			int listSize;  //线性表的元素个数 
		
};
template<class T>
void reverse(Arraylist<T> &A)
{
	int size=A.size();
	T temp;
	for(int i=0;i<(size-1)/2;i++)
	{
		temp=A.get(i);
		A.get(i)=A.get(size-1-i);
		A.get(size-1-i)=temp;
	}
}

int main()
{
	Arraylist<int> A(10);
	cout<<A<<endl;
	A.reverse(); cout<<A<<endl;
	reverse(A); cout<<A<<endl;

	return 0;
}
