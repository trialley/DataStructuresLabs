
#pragma once
#include<iostream>
using namespace std;
//?㏒～?角角℅¯?a?㏒～?角角米?3谷?㊣㊣?芍?o????赤車D?那足a㏒? 
template<class K,class E>
class Pair
{
	public:
	   K first;   //1??邦℅? 
	   E second;  //?米 
	   int leftSize;  //?¯辰y?t2????¯那¯車?米?℅車℅車那¯米??a??那y 
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
