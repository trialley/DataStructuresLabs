#pragma once
#include<iostream>
using namespace std;

template<class K,class E>
class pair
{
	K first;
	E second;
	
};

template<class K,class E>
class pairNode
{
	public:
	       pair<const K,E> element;
	       pairNode<K,E>* next;
	friend ostream& operator<<(ostream& out,const pairNode<K,E> Pair)
	{
		cout<<"Key:"<<element.first<<"\tValue:"<<element.second<<endl;
	}
};

template<class K,class E>
class sortedArraylist
{
	public:
		sortedArraylist(int intialCapacity=10)
		{
			if(intialCapacity<0) 
			{
				cerr<<"��ʼ���Ƿ���"<<endl;
				exit(1);
			}
			element=new pairNode<K,E> [intialCapacity];
			arrayLength=intialCapacity;
		}
		~sortedArraylist()
		{
			delete [] element;
		}
		bool empty() const;
		{
			if(dSize==0) return true;
			else return false;
		}
		int size() const;
		{
			return dSize;
		}
		int find(const K& theKey) const;
		{//����ƥ�������������е�������ʹ�ö��ֲ��� 
			int mid=dSize/2;
			int left=0;
			int right=dSize-1;
			while(1)
			{
				if(element[mid].first==theKey) return mid;
				if(element[mid].first>theKey)
				{
					mid=(mid-1+left)/2;
				}
				if(element[mid].first<theKey)
				{
					mid=(mid+1+right)/2;
				}
				if(mid==left||mid==right&&element[mid].first!=theKey)
				    break;
			}
			return -1;
		}
		void erase(const K& theKey)
		{//ɾ����һ���ؼ���ΪtheKey��Ԫ�� 
			int index=find(theKey);
			if(index==-1) return;
			else
			{
				for(int i=index;i<dSize;i++)
				{
					element[i]=element[i+1];
				}
				element[dSize-1].~pairNode<K,E>();  //������Ԫ������ 
				dSize--;
			}
		}
		void insert(const pair<const K,E>& thePair)
		{//���ֵ��б�֤����ز���thePair,������ظ��ؼ����򸲸�
		    int cursor;
			for(cursor=0;cursor<dSize;cursor++)
			{
				if(thePair.first==element[cursor].first)
				{//�ظ� 
					element[cursor].second=thePair.second;
				}
				if(thePair.first>element[cursor].first)
				{//��ƥ�����ԣ������¿ռ�
					if(dSize==arrayLength)
		            {//����ռ����� 
			            pairNode<K,E> *p=new T[2*arrayLength];
			            for(int i=0;i<dSize;i++)
		       	        {
	       		        	p[i]=element[i];
	       		        }
	       		        delete [] element;
	       		        element=p;
	       		        arrayLength*=2;
	                 }
					
					for(int i=dSize;i>cursor-1;i--)  //Ԫ�غ��� 
					{	element[i+1]=element[i];  }
					
					element[cursor]=thePair;    //��ֵ 
					dSize++;
				}
			 } 	
		}
		void output() const
		{
			for(int i=0;i<dSize;i++)
			{
				cout<<element[i];
			}
		}
	private:
	    pairNode<K,E>* element;   //������Ե�����ָ�� 
	    int dSize;                //�ֵ������Ե����� 
	    int arrayLength;          //�ֵ����� 
};


