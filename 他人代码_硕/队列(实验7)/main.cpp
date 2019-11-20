#include<iostream>
#include"linkedQueue.h"
#include"扑克牌.h"
using namespace std;

int main()
{
	poker<int> Poker;  int num;
	cout<<"请输入牌堆中牌的数量"<<endl;
	cin>>num;
	Poker.discard(num);
	
	
	return 0;
}
