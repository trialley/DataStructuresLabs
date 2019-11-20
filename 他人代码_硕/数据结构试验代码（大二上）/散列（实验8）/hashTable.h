#include<iostream>
#include"hash.h"
#include"pair.h"
using namespace std;

template<class K,class E>
class hashTable  //ʹ������̽�鷽�� 
{
	public:
		hashTable(int theDivisor)
		{
			divisor=theDivisor;
			dSize=0;
			//�����Ͱ��b�ͳ���d��ͬ,��ÿ��Ͱ��ʼ��ΪNull 
			table = new Pair<K,E>* [divisor];
			for(int i=0;i<divisor;i++)
			   table[i]=NULL;
		}
		~hashTable()
		{
			for(int i=0;i<divisor;i++)
			{
				if(table[i]!=NULL)
				  delete [] table[i];
			}
		}
		bool empty() const {return dSize == 0;}
        int size() const {return dSize;}
		int search(const K& theKey) const
		{//����theKey��Ͱ����� 
		 //���ƥ������Դ��ڣ���������λ�ã��������ɢ�б�����
		 //�򷵻عؼ���ΪtheKey�����Կ��Բ����λ��
		   int i=(int)hash(theKey)%divisor; //��ʼͰ 
		   int j=i; 
		   do
		   {
		   	if(table[j]==NULL||table[j]->first==theKey)  //��ʼͰΪ�ջ����ҵ��ѱ�������Ͱ 
		   	  return j;
		   	else 
		   	  j=(j+1)%divisor;  //��һ��Ͱ
		   }while(i!=j);  //�������Ѿ�����һȦ 
		   
		   return j;    //���� 
		}
		Pair<K,E>* find(const K& theKey) const
		{//����ƥ�����Ե�ָ�룬���������򷵻�Null
		   int b=search(theKey);
		   if(table[b]==NULL||table[b]->first!=theKey)
		   {//��û��ƥ�� 
		   	  return NULL;
	       }
		   return table[b];   //�ҵ�ƥ�� 	
		}
		void insert(const Pair<K,E>& thePair)
		{//������thePair�����ֵ䣬�����ڹؼ�����ͬ���ԣ��򸲸�
		 //�������ֹ���� 
			int b=search(thePair.first);
			if(table[b]==NULL)
			{//��ʼͰΪ��
			    table[b]=new Pair<K,E> (thePair);  //resembles new int (5);
				dSize++;
			}
			else
			{//��Ϊ�յ������ 
			  if(table[b]->first==thePair.first)
			  {//���ظ������� 
				  table[b]->second=thePair.second;
			  }
			  if(table[b]->first!=thePair.first)
			  {//���� 
				  cerr<<"�������޷����롣"<<endl;
				  cout<<"table["<<b<<"]->first="<<table[b]->first;
				  cout<<"\tthePair.first="<<thePair.first<<endl;
			  }
		    }
		    //cout<<b<<endl;
		    //cout<<table[b]->first<<"\t"<<table[b]->second;
		}
		void erase(const K& theKey)
		{//ɾ���ؼ���ΪtheKey�����ԣ����û�о�ʲôҲ���� 
		 //��Ҫ���������ĳЩԪ����ǰ�ƶ�����ֱ���ص���ʼͰ���������գ� 
			int b=search(theKey);   //��ʼͰ 
			if(table[b]==NULL||table[b]->first!=theKey)
		   {//���Բ�����or���� 
		   	   cout<<"delete failed."<<endl; 
			   return ;
	       }
	       int pre=b,post;   //cout<<"pre is:"<<pre<<endl;
	       for(int i=b;i<=(divisor+b)%divisor;i++)
	       {//�ƶ���ʼͰ���key%divisor��theKey��ͬ��Ԫ�أ�ֱ���ص���ʼͰ       
	       	  if( table[i]!=NULL && (table[i]->first) % divisor==theKey%divisor)
	       	  {
				      post=i;
	       	  	      table[pre]=table[post];
	       	  	      pre=post;
			  }
		   }
	       //delete table[post];  
		   table[post]=NULL;
	       dSize--;
	       cout<<"erase succeed."<<endl;
	       //д�ıȽϴֱ������ӶȦ�(n) 
		}
		friend ostream& operator<<(ostream& out,const hashTable<K,E> &A)
		{//��ô���... 
			for(int i=0;i<A.divisor;i++)
			{
				if(A.table[i]==NULL) 
				  out<<"NO."<<i<<" bucket="<<"NULL"<<endl;
				else
				  out<<"NO."<<i<<" bucket=("<<A.table[i]->first<<","<<A.table[i]->second<<")"<<endl;
			}
			return out;
		}
	private:
		Pair<K,E>** table;        //ɢ�б� 
		hash<K> hash;             //������Kӳ�䵽һ���Ǹ����� 
		int dSize;                //�ֵ������Ը��� 
		int divisor;              //ɢ�к������� 
};
