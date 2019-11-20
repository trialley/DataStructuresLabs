#include<iostream>
#include"adjacencyWGraph.h"
#define noEdge 1000000
using namespace std;

int main()
{
	cout<<"请输入图的顶点数n和边数e"<<endl;
	int n,e;  cin>>n>>e;
	adjacencyWGraph<int> AWGraph(n,noEdge);
	cout<<"请以顶点对(顶点1,顶点2，权值)的形式输入图的每一条边"<<endl;
	
	for(int i=0;i<e;i++)
	{
		int v1,v2,w;  cin>>v1>>v2>>w;
		edge<int> *Edge=new edge<int> (v1,v2,w);
		AWGraph.insertEdge(Edge);
	}
	
	edge<int> *STE=new edge<int> [n-1];
	cout<<"最小生成树中每条边(v1,v2,w)如下:"<<endl;
	if( AWGraph.kruskal(STE) ==true)
	{
		for(int i=0;i<=n-2;i++)
		  cout<<STE[i]<<endl;
	}
	
	return 0;
}
