#pragma once
#include<iostream>
using namespace std;
//模板类作为模板类的成员变量好像就有问题？ 
template<class K,class E>
class Pair
{
	public:
	   K first;   //关键字 
	   E second;  //值 
	   
	   Pair() 
	   {	   
	      first=0;  second=0;  
	   }
	   Pair(K fir,E sec)
	   {
	   	  first=fir;  second=sec;  
	   }
	   Pair(const Pair<K,E> &x)
	   {
	   	  first=x.first;  second=x.second;  
	   }
	   void operator=(const Pair<K,E> &x)
	   {
	   	  first=x.first;  second=x.second; 
	   }
       friend ostream& operator << (ostream& out,Pair<K,E> Pair)
       {
       	  out<<"Key="<<Pair.first<<" value="<<Pair.second;
       	  return out;
	   }
};

