#pragma once
#include<iostream>
using namespace std;
//模板类作为模板类的成员变量好像就有问题？ 
template<class K,class E>
class Pair
{
	public:
	   K first;
	   E second;
	   Pair() {	   }
	   Pair(K fir,E sec)
	   {
	   	  first=fir;  second=sec;
	   }
	   Pair(const Pair<K,E> &x)
	   {
	   	  first=x.first;  second=x.second;
	   }
	   void operator=(Pair<K,E> &x)
	   {
	   	  first=x.first;  second=x.second;
	   }
       friend ostream& operator<<(ostream& out,Pair<K,E> Pair)
       {
       	  out<<Pair.first<<" "<<Pair.second;
       	  return out;
	   }
};

template<class K,class E>
class PairNode
{
	public:
	       Pair<K,E> element;
	       PairNode<K,E>* next;
	PairNode(Pair<K,E> &thePair,PairNode<K,E> *p)
	{
		element=thePair;
		next=p;
	}
	friend ostream& operator<<(ostream& out,PairNode<K,E> Pair)
	{
		out<<"Key:"<<Pair.element.first<<"\tValue:"<<Pair.element.second;
		return out;
	}
};

