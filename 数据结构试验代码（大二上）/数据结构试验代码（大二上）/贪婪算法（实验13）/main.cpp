#include<iostream>
#include"adjacencyWGraph.h"
#define noEdge 1000000
using namespace std;

int main()
{
	cout<<"������ͼ�Ķ�����n�ͱ���e"<<endl;
	int n,e;  cin>>n>>e;
	adjacencyWGraph<int> AWGraph(n,noEdge);
	cout<<"���Զ����(����1,����2��Ȩֵ)����ʽ����ͼ��ÿһ����"<<endl;
	
	for(int i=0;i<e;i++)
	{
		int v1,v2,w;  cin>>v1>>v2>>w;
		edge<int> *Edge=new edge<int> (v1,v2,w);
		AWGraph.insertEdge(Edge);
	}
	
	edge<int> *STE=new edge<int> [n-1];
	cout<<"��С��������ÿ����(v1,v2,w)����:"<<endl;
	if( AWGraph.kruskal(STE) ==true)
	{
		for(int i=0;i<=n-2;i++)
		  cout<<STE[i]<<endl;
	}
	
	return 0;
}
