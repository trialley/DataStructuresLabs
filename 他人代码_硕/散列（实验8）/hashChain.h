#pragma once
#include <iostream>
#include "hash.h"
#include "sortedChain.h"
using namespace std;

template<class K,class E>
class hashChain
{//ʹ������ɢ��
    public:
    	hashChain(int div)
    	{
    		divisor=div;
    		table=new sortedChain<K,E> [divisor];
		}
    	~hashChain()
    	{
    		delete [] table;
		}
		bool empty()
		{
			for(int i=0;i<divisor;i++)
			{
				if(table[i].size()!=0)
				   return false;
			}
			return true;
		}
		int size()
		{
			int sum=0;
			for(int i=0;i<divisor;i++)
			{
				sum+=table[i].size();
			}
			return sum;
		}
    	Pair<K,E>* find(const K& theKey) const
    	{//����ƥ�����Ե�ָ�룬���������򷵻�NULL
    		int pos= hash(theKey) %divisor;
    		return table[pos].find(theKey);
		}
        void insert(Pair<K,E>& thePair)
        {//���ȸ�������key�����pos��Ȼ��ֱ�ӵ���sortedChain��insert�������ɡ� 
        	int pos=hash(thePair.first)%divisor;  //cout<<"pos="<<pos<<' ';
        	table[pos].insert(thePair);
		}
        void erase(K &theKey)
        {
        	int pos=hash(theKey);
        	table[pos].erase(theKey);
		}
        friend ostream& operator<<(ostream& out,hashChain<K,E> &A)
        {
        	for(int i=0;i<A.divisor;i++)
        	{
			    if(A.table[i].size()==0)  out<<"NO."<<i<<" bucket:NULL"<<endl;
				else
				 {
				 	out<<"NO."<<i<<" bucket:"; 
					 A.table[i].output();
				 	out<<endl;
				  }   	 
			}
			return out;
		}
	private:
		sortedChain<K,E> *table;  
		int divisor;
		hash<K> hash;             //������Kӳ�䵽һ���Ǹ�����
		
};
