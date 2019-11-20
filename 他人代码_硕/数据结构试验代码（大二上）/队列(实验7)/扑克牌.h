#pragma once
#include<iostream>
#include"arrayQueue.h"
using namespace std;

template<class T>
class poker
{
	public:
		void discard(int num)
		{//num是总牌数
		    for(int i=1;i<=num;i++)
		    {//对牌堆进行初始化 
		    	card_pile.push(i);
			}
		    while(card_pile.size()>=2)
		    {
		    	cout<<card_pile.pop()<<" ";  //扔掉第一张，并输出 
			    T temp=card_pile.pop();
			    card_pile.push(temp);  //把第二张插到最后     
			}
			cout<<"剩下的牌是："; card_pile.output();
		}
		void output()
		{//输出牌堆中的元素 
			card_pile.output();
		} 
	private:
		arrayQueue<T> card_pile;
	
};
