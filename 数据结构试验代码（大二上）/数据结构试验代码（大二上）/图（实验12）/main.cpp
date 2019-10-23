#include<iostream>
#include"adjacencyWGraph.h"
#include"linkedWGraph.h"
#define noEdge 1000000
using namespace std;

/*int main1()
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
	if( AWGraph.connected() ==true) cout<<"��ͼ����ͨ�ġ�"<<endl;
	else{
		int c[n+1];
		cout<<"��ͨ��֧���ǣ�"<<AWGraph.labelComponents(c)<<endl;
		for(int i=1;i<=n;i++)
		   cout<<"����"<<i<<"���ڵ�"<<c[i]<<"��ͨ��֧"<<endl;
	}
	cout<<"������һ��������ţ�"; int num; cin>>num;
	int reach[n+1];
	cout<<"BFS���У�";   AWGraph.print_bfs(num,reach);
	cout<<"DFS���У�";   AWGraph.print_dfs(num,reach);  cout<<endl;
	
	
	int predecessor[n+1]; cout<<"��������ʼ��ͽ����㣺";  int start,dest;  cin>>start>>dest; 
	cout<<endl<<"���·��"<<AWGraph.Dijkstra(start,dest,predecessor)<<endl;
	cout<<"���·��Ϊ��"; 
	n=dest;  cout<<dest<<" ";
	while(predecessor[n]!=0)
	{
		cout<<predecessor[n]<<" ";
		n=predecessor[n];
	}
	return 0;
}*/
int main2()
{
	cout<<"������ͼ�Ķ�����n�ͱ���e"<<endl;
	int n,e;  cin>>n>>e;
	linkedWGraph<int> LWGraph(n);
	cout<<"���Զ����(����1,����2��Ȩֵ)����ʽ����ͼ��ÿһ����"<<endl;
	for(int i=0;i<e;i++)
	{
		int v1,v2,w;  cin>>v1>>v2>>w;
		edge<int> *Edge=new edge<int> (v1,v2,w);
		LWGraph.insertEdge(Edge);
	}
	cout<<"�ڽ�������ڵ�����Ϊ��"<<endl;
	LWGraph.output();
	if( LWGraph.connected() ==true) cout<<"��ͼ����ͨ�ġ�"<<endl;
	else{
		int c[n+1];
		cout<<"��ͨ��֧���ǣ�"<<LWGraph.labelComponents(c)<<endl;
		for(int i=1;i<=n;i++)
		   cout<<"����"<<i<<"���ڵ�"<<c[i]<<"��ͨ��֧"<<endl;
	}
	cout<<"������һ��������ţ�"; int num; cin>>num;
	int reach[n+1];
	cout<<"BFS���У�";   LWGraph.print_bfs(num,reach);
	cout<<"DFS���У�";   LWGraph.print_dfs(num,reach);  cout<<endl;
	
	
	int predecessor[n+1]; cout<<"��������ʼ��ͽ����㣺";  int start,dest;  cin>>start>>dest; 
	cout<<endl<<"���·��"<<LWGraph.Dijkstra(start,dest,predecessor)<<endl;
	cout<<"���·��Ϊ��"; 
	n=dest;  cout<<dest<<" ";
	while(predecessor[n]!=0)
	{
		cout<<predecessor[n]<<" ";
		n=predecessor[n];
	}
	
	return 0;
}

int main()
{
//	main1();
	main2();
	return 0;
}
