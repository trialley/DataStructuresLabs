#include<iostream>
#include"hash.h"
#include"pair.h"
using namespace std;

template<class K,class E>
class hashTable  //使用线性探查方法 
{
	public:
		hashTable(int theDivisor)
		{
			divisor=theDivisor;
			dSize=0;
			//这里的桶数b和除数d相同,把每个桶初始化为Null 
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
		{//搜索theKey返桶的序号 
		 //如果匹配的数对存在，返回它的位置，否则，如果散列表不满，
		 //则返回关键字为theKey的数对可以插入的位置
		   int i=(int)hash(theKey)%divisor; //起始桶 
		   int j=i; 
		   do
		   {
		   	if(table[j]==NULL||table[j]->first==theKey)  //起始桶为空或者找到已被填满的桶 
		   	  return j;
		   	else 
		   	  j=(j+1)%divisor;  //下一个桶
		   }while(i!=j);  //跳出则已经遍历一圈 
		   
		   return j;    //表满 
		}
		Pair<K,E>* find(const K& theKey) const
		{//返回匹配数对的指针，若不存在则返回Null
		   int b=search(theKey);
		   if(table[b]==NULL||table[b]->first!=theKey)
		   {//即没有匹配 
		   	  return NULL;
	       }
		   return table[b];   //找到匹配 	
		}
		void insert(const Pair<K,E>& thePair)
		{//把数对thePair插入字典，若存在关键字相同数对，则覆盖
		 //表满则禁止插入 
			int b=search(thePair.first);
			if(table[b]==NULL)
			{//起始桶为空
			    table[b]=new Pair<K,E> (thePair);  //resembles new int (5);
				dSize++;
			}
			else
			{//不为空的情况下 
			  if(table[b]->first==thePair.first)
			  {//有重复的数对 
				  table[b]->second=thePair.second;
			  }
			  if(table[b]->first!=thePair.first)
			  {//表满 
				  cerr<<"表满，无法插入。"<<endl;
				  cout<<"table["<<b<<"]->first="<<table[b]->first;
				  cout<<"\tthePair.first="<<thePair.first<<endl;
			  }
		    }
		    //cout<<b<<endl;
		    //cout<<table[b]->first<<"\t"<<table[b]->second;
		}
		void erase(const K& theKey)
		{//删除关键字为theKey的数对，如果没有就什么也不做 
		 //需要把它后面的某些元素向前移动，（直到回到初始桶或者遇到空） 
			int b=search(theKey);   //初始桶 
			if(table[b]==NULL||table[b]->first!=theKey)
		   {//数对不存在or表满 
		   	   cout<<"delete failed."<<endl; 
			   return ;
	       }
	       int pre=b,post;   //cout<<"pre is:"<<pre<<endl;
	       for(int i=b;i<=(divisor+b)%divisor;i++)
	       {//移动起始桶后的key%divisor与theKey相同的元素，直到回到初始桶       
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
	       //写的比较粗暴，复杂度Θ(n) 
		}
		friend ostream& operator<<(ostream& out,const hashTable<K,E> &A)
		{//怎么输出... 
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
		Pair<K,E>** table;        //散列表 
		hash<K> hash;             //把类型K映射到一个非负整数 
		int dSize;                //字典中数对个数 
		int divisor;              //散列函数除数 
};
