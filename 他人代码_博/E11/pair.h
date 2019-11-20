
#pragma once
#include<iostream>
using namespace std;
//?���?��������?a?���?������?3��?����?��?o????����D?����a��? 
template<class K,class E>
class Pair
{
	public:
	   K first;   //1??����? 
	   E second;  //?�� 
	   int leftSize;  //?�¨�y?t2????�¨��¨�?��?�����������¦�??a??��y 
	   Pair() 
	   {	   
	      first=0;  second=0;  leftSize=0;
	   }
	   Pair(K fir,E sec)
	   {
	   	  first=fir;  second=sec;  leftSize=0;
	   }
	   Pair(const Pair<K,E> &x)
	   {
	   	  first=x.first;  second=x.second;  leftSize=x.leftSize;
	   }
	   void operator=(const Pair<K,E> &x)
	   {
	   	  first=x.first;  second=x.second;  leftSize=x.leftSize;
	   }
       friend ostream& operator << (ostream& out,Pair<K,E> Pair)
       {
       	  out<<"Key="<<Pair.first<<" value="<<Pair.second<<" leftSize="<<Pair.leftSize;
       	  return out;
	   }
};
