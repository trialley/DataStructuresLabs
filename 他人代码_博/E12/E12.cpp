#include<iostream>
using namespace std;
#include<stdlib.h>
#include"adjacencyGraph.h"
#include"linkedGraph.h" 

int main()
{
	int n = 0;
	int e = 0;
	scanf("%d%d",&n,&e);
	adjacencyGraph zjs1(n);
	for(int k=0;k<e;k++){
		int i,j;
		scanf("%d%d",&i,&j);
		unweightedEdge _edge(i,j);
		edge<bool>*p = &_edge;
		zjs1.insertEdge(p);
	}
	if(zjs1.connected()) printf("connected!\n");
	else{
		printf("disconnected!\n");
	}
	//shortest path 
	printf("input 2 vertics\n");
	int i,j;
	scanf("%d%d",&i,&j);
	int _reach[100] = {0};
	zjs1.bfs(i,_reach,233);
//	while(1){
//		for(int x=)
//	}
	int *list = new int[n];
	int len = 0;
	int y = 0;
	for(int x=0;x<n;x++){
		if(_reach[x]==233)
			{
				list[y] = x;
				y++;
				len++;
			}
	}
	diy(list,len);
	for(int o=0;o<len;o++){
	printf("%d ",list[o]);
	}
	return 0;
}

//int main()
//{
//	int n = 0;
//	int e = 0;
//	scanf("%d%d",&n,&e);
//	linkedGraph zjs1(n);
//	for(int k=0;k<e;k++){
//		int i,j;
//		scanf("%d%d",&i,&j);
//		unweightedEdge _edge(i,j);
//		edge<bool>*p = &_edge;
//		zjs1.insertEdge(p);
//	}
//	if(zjs1.connected()) printf("connected!\n");
//	else{
//		printf("disconnected!\n");
//	}
//	//shortest path 
//	printf("input 2 vertics\n");
//	int i,j;
//	scanf("%d%d",&i,&j);
//	int _reach[100] = {0};
//	zjs1.bfs(i,_reach,233);
////	while(1){
////		for(int x=)
////	}
//	int *list = new int[n];
//	int len = 0;
//	int y = 0;
//	for(int x=0;x<n;x++){
//		if(_reach[x]==233)
//			{
//				list[y] = x;
//				y++;
//				len++;
//			}
//	}
//	diy(list,len);
//	for(int o=0;o<len;o++){
//	printf("%d ",list[o]);
//	}
//	return 0;
//}

