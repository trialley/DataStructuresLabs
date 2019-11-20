#pragma once
#include<iostream>
#include"pair.h"
#include "hash.h"
using namespace std;

template<class K,class E>
class sortedChain
{//有序的关键在于insert函数 
   public:
      sortedChain() 
	  {
	    firstNode = NULL; 
		dSize = 0;
	  }
      ~sortedChain()
      {
      //	 PairNode<K,E> *p1=firstNode->next,*p2=firstNode;  //这里firtstnode根本没有next! 
      	 while(firstNode!=NULL)
      	 {//还是这样用吧... 
      	 	PairNode<K,E>* nextNode=firstNode->next;
      	 	delete firstNode;
      	 	firstNode=nextNode;
		 }
	  }

      bool empty() const {return dSize == 0;}
      int size() const {return dSize;}
      Pair<K, E>* find(const K &Key) const
      {//返回匹配数对的指针，若不存在则返回NULL
	     PairNode<K,E>* curNode=firstNode;
		 while(curNode!=NULL&&curNode->element.first!=Key)
		 {
		 	curNode=curNode->next;
		 }
		 //判断是否匹配
		 if(curNode!=NULL&&curNode->element.first==Key)
		    return &(curNode->element);
		 else
		    return NULL;
	  }
      void erase(K &Key)
      { 
      	 PairNode<K,E> *p=firstNode,*tp=NULL;  //tp在p后
		  while(p!=NULL&& Key < p->element.first)
	      {
	      	 tp=p;
	      	 p=p->next;
		  }
		 if(p==NULL||Key!=p->element.first)
		 {//说明已走完或者无匹配 
		 	cout<<"no match,erase failed."<<endl;
		 }
		 else
		 {
		 	if(p==firstNode)
			     firstNode=NULL;
		 	else
		 	     tp->next=p->next;
		 	delete p;
		 	dSize--;
		  } 
	  }
      void insert(Pair<K,E> &thePair)
      {//向字典中插入thePair，若thePair的key已经存在，则覆盖
	      PairNode<K,E> *p=firstNode;
		  PairNode<K,E> *tp=NULL;    //tp跟在p后 
	      while(p!=NULL&& thePair.first < p->element.first)
	      {
	      	 tp=p;
	      	 p=p->next;
		  }
		  if(p!=NULL&&thePair.first==p->element.first)
		  {    
		      p->element.second=thePair.second;  //覆盖
		      return; 
		  } 
		  else
		  {//加入一个新节点，在合适的位置 
		  	 PairNode<K,E> *k=new PairNode<K,E>(thePair,p);
		  	 if(tp==NULL)  
			    firstNode=k;
			 else
			    tp->next=k;   /* tp...k...p  */
			  // cout<<(*k)<<endl;
			 dSize++;
	      }	   
	  }
      void output() const
      {
      	for (PairNode<K,E>* curNode = firstNode;curNode != NULL;curNode = curNode->next)
      	{
      		cout<<(*curNode)<<'|';
		}
	  }

   protected:
      PairNode<K,E>* firstNode;  // 指向首节点 
      int dSize;                 // 节点数量	
};

