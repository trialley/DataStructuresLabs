#pragma once
#include<iostream>
#include"arrayQueue.h"
using namespace std;

template<class T>
class poker
{
	public:
		void discard(int num)
		{//num��������
		    for(int i=1;i<=num;i++)
		    {//���ƶѽ��г�ʼ�� 
		    	card_pile.push(i);
			}
		    while(card_pile.size()>=2)
		    {
		    	cout<<card_pile.pop()<<" ";  //�ӵ���һ�ţ������ 
			    T temp=card_pile.pop();
			    card_pile.push(temp);  //�ѵڶ��Ų嵽���     
			}
			cout<<"ʣ�µ����ǣ�"; card_pile.output();
		}
		void output()
		{//����ƶ��е�Ԫ�� 
			card_pile.output();
		} 
	private:
		arrayQueue<T> card_pile;
	
};
