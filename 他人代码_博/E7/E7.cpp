#include<iostream>
using namespace std;
#include"../zjslib/zjslib.h"

int main(){
	int n = 0;
	printf("input n = ");
	scanf("%d",&n);
	arrqueue<int> arrpoker(n);
	int i=1;
	for(;i<=n;i++)
		arrpoker.push(i);
	i = 1;
	while(arrpoker.size()>1){
		printf("No.%d throw %d\n",i,arrpoker.top());
		i++;
		arrpoker.pop();
		int save = arrpoker.top();
		arrpoker.pop();
		arrpoker.push(save);
	}
	printf("Last.%d throw %d\n",i,arrpoker.top());
	//////////////////////////////////////////////
	int m = 0;
	printf("input m = ");
	scanf("%d",&m);
	chainqueue<int> chainpoker;
	int x=1;
	for(;x<=m;x++)
		chainpoker.push(x);
	x = 1;
	while(chainpoker.size()>1){
		printf("No.%d throw %d\n",x,chainpoker.top());
		x++;
		chainpoker.pop();
		int save = chainpoker.top();
		chainpoker.pop();
		chainpoker.push(save);
	}
	printf("Last.%d throw %d\n",x,chainpoker.top());
	return 0;
}

