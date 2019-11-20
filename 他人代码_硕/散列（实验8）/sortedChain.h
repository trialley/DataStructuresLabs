#pragma once
#include<iostream>
#include"pair.h"
#include "hash.h"
using namespace std;

template<class K,class E>
class sortedChain
{//����Ĺؼ�����insert���� 
   public:
      sortedChain() 
	  {
	    firstNode = NULL; 
		dSize = 0;
	  }
      ~sortedChain()
      {
      //	 PairNode<K,E> *p1=firstNode->next,*p2=firstNode;  //����firtstnode����û��next! 
      	 while(firstNode!=NULL)
      	 {//���������ð�... 
      	 	PairNode<K,E>* nextNode=firstNode->next;
      	 	delete firstNode;
      	 	firstNode=nextNode;
		 }
	  }

      bool empty() const {return dSize == 0;}
      int size() const {return dSize;}
      Pair<K, E>* find(const K &Key) const
      {//����ƥ�����Ե�ָ�룬���������򷵻�NULL
	     PairNode<K,E>* curNode=firstNode;
		 while(curNode!=NULL&&curNode->element.first!=Key)
		 {
		 	curNode=curNode->next;
		 }
		 //�ж��Ƿ�ƥ��
		 if(curNode!=NULL&&curNode->element.first==Key)
		    return &(curNode->element);
		 else
		    return NULL;
	  }
      void erase(K &Key)
      { 
      	 PairNode<K,E> *p=firstNode,*tp=NULL;  //tp��p��
		  while(p!=NULL&& Key < p->element.first)
	      {
	      	 tp=p;
	      	 p=p->next;
		  }
		 if(p==NULL||Key!=p->element.first)
		 {//˵�������������ƥ�� 
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
      {//���ֵ��в���thePair����thePair��key�Ѿ����ڣ��򸲸�
	      PairNode<K,E> *p=firstNode;
		  PairNode<K,E> *tp=NULL;    //tp����p�� 
	      while(p!=NULL&& thePair.first < p->element.first)
	      {
	      	 tp=p;
	      	 p=p->next;
		  }
		  if(p!=NULL&&thePair.first==p->element.first)
		  {    
		      p->element.second=thePair.second;  //����
		      return; 
		  } 
		  else
		  {//����һ���½ڵ㣬�ں��ʵ�λ�� 
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
      PairNode<K,E>* firstNode;  // ָ���׽ڵ� 
      int dSize;                 // �ڵ�����	
};

