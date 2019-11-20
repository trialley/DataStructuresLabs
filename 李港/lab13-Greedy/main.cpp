#include<iostream>
#include"baseGraph.h"
using namespace std;

int main() {
	uniGraph<arrGraph<int>,int> g(10);



	g.SetNodeDate(0, 0);
	g.SetLinkValue(0, 0, 0);
	cout << g.GetNodeDate(0)<<" "<<g.GetLinkValue(0,0);
	return 0;
}