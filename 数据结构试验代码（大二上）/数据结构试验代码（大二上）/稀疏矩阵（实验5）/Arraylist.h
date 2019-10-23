#pragma once
#include<iostream>

template<class T>
class Arraylist 
{
	public:
		Arraylist(int initialCapacity=10);		
		Arraylist(const Arraylist<T>& A);
		~Arraylist() { delete [] element;	}
		
		void reSet(int newSize);
		void set(int Index,T ele);
		void clear();
		bool empty() const
		{    return listSize==0;   }
		int size() const 
		{    return listSize;	   }
		T& get(int theIndex) const
		{//ʵ������洢��Ч�ʼ��� O(1) 
	       checkIndex(theIndex);
	       return element[theIndex];
        }
		int indexOf(T& x) const;
		void erase(int theIndex);
		void insert(int theIndex,const T& theElement);
		void output() const;
		int capacity() const 
		{   return arrayLength;		}
		friend std::ostream& operator<< (std::ostream& out,const Arraylist<T> &A)  //ģ�������Ԫ����������������ܷ��� 
		{
        	for(int i=0;i<A.listSize;i++)
         	{   out<<A.element[i];  }
        	return out;
        }
		class iterator
		{
			public:
				iterator(T *postion=0)
				{
					pos=postion;
				}
				T& operator*() const { return *pos; }
				T* operator->() const { return &*pos; }
				iterator& operator++() { ++pos; return *this;	}
				iterator operator++(int) { iterator old=*this; ++pos; return old;	}
				bool operator!=(const iterator right) const{ return pos!=right.pos;  }
				bool operator==(const iterator right) const{ return pos==right.pos; }
			protected:
			    T *pos;	
		};
		iterator begin()
		{
			return iterator(element);
		}
		iterator end()
		{
			return iterator(element+listSize);
		}			
		int Term_search(T& x)
		{//ϡ�����ר��search,����ҵ���x,�򷵻��������������򷵻�-1 
		//std::cout<<"listSize is  "<<listSize<<std::endl;
			for(int i=0;i<listSize;i++)
	        {
		       if(x.row==element[i].row&&x.col==element[i].col)  return i;
	        }
	        return -1;
		}
		void matrixTerm_sort()
		{
			for(int i=0;i<listSize;i++)
			{
				for(int j=i;j<listSize;j++)
				{
					if(element[i]>element[j])
					  swap(element[i],element[j]);
					else  ;
				}
			}
		}
		void swap(T &A,T &B)
		{
		    int temp;
			temp=A.row;  A.row=B.row;  B.row=temp;
			temp=A.col;  A.col=B.col;  B.col=temp;
			temp=A.value;  A.value=B.value;  B.value=temp;
				
		} 
		//protected:
			void checkIndex(int theIndex)  const
			{//ȷ����������Ч�ԣ���ֹԽ��
                if(theIndex<0||theIndex>=listSize)
	            {
		          std::cerr<<"������������Ч�ԣ�"<<std::endl;
	            }
            }
			//��������Ч�����׳��쳣 
			T *element;  //�洢���Ա�Ԫ�ص�һά���� 
			int arrayLength;  //һά��������� 
			int listSize;  //���Ա��Ԫ�ظ��� 
};

