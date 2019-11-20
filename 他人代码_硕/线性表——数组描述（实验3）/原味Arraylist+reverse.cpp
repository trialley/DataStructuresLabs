#include<iostream>
#include<string>
using namespace std;

template<class T>
class linearlist //���������Ա� 
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
		{//�����������û��为�� 
			element=new T [initialCapacity];  //�����Ѿ���ʼ����һ�顣 
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
		
		//ADT����
		bool empty() const
		{    return listSize==0;   }
		int size() const 
		{    return listSize;	   }
		T& get(int theIndex) const
		{//ʵ������洢��Ч�ʼ��� O(1) 
	       checkIndex(theIndex);
	       return element[theIndex];
        }
		int indexOf(T& x) const
		{//����Ԫ��x��һ�γ���ʱ������;�������ڣ��򷵻�-1 
	         for(int i=0;i<listSize;i++)
	         {
		       if(x==element[i])  return i;
	         }
	          return -1;
        }

		void erase(int theIndex)
		{//�ӱ���ɾ������ΪtheIndex��Ԫ�� 
	       for(int i=theIndex;i<listSize-1;i++)
	       {
		      element[i]=element[i+1];
	       }
	       //cout<<"right!"<<endl;
	       element[--listSize].~T();  //������������������verstehen. ���������������������Ƕ�̬���� 
        }
		void insert(int theIndex,const T& theElement)
		{
	       if(theIndex<0||theIndex>listSize)
	       cerr<<"��������ȷ������"<<endl;
	  
		   if(listSize==arrayLength)
		   {//����ռ����� 
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
	     	  element[i+1]=element[i];   //�ڶ��ε��ò��뺯�������������,ע�������±��Ǵ�0��ʼ�� 
	       }
	       	  element[theIndex]=theElement;
	       	  listSize++;
	    }
		void output() const
		{//��������Ա� 
		  for(int i=0;i<listSize;i++)
		  {
			  cout<<element[i];
		  }
	    }
		int capacity() const 
		{   return arrayLength;		}
		friend ostream& operator<< (ostream& out,const Arraylist<T> &A)  //ģ�������Ԫ����������������ܷ��� 
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
			{//ȷ����������Ч�ԣ���ֹԽ��
                if(theIndex<0||theIndex>=listSize)
	            {
		          cerr<<"������������Ч�ԣ�"<<endl;
	            }
            }
			//��������Ч�����׳��쳣 
			T *element;  //�洢���Ա�Ԫ�ص�һά���� 
			int arrayLength;  //һά��������� 
			int listSize;  //���Ա��Ԫ�ظ��� 
		
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
