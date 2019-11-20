#include<iostream>
#include"adjacencyWGraph.h"
#include"linkedWGraph.h"
#define noEdge 1000000
using namespace std;

/*int main1()
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
	if( AWGraph.connected() ==true) cout<<"本图是连通的。"<<endl;
	else{
		int c[n+1];
		cout<<"连通分支数是："<<AWGraph.labelComponents(c)<<endl;
		for(int i=1;i<=n;i++)
		   cout<<"顶点"<<i<<"属于第"<<c[i]<<"连通分支"<<endl;
	}
	cout<<"请输入一个顶点序号："; int num; cin>>num;
	int reach[n+1];
	cout<<"BFS序列：";   AWGraph.print_bfs(num,reach);
	cout<<"DFS序列：";   AWGraph.print_dfs(num,reach);  cout<<endl;
	
	
	int predecessor[n+1]; cout<<"请输入起始点和结束点：";  int start,dest;  cin>>start>>dest; 
	cout<<endl<<"最短路："<<AWGraph.Dijkstra(start,dest,predecessor)<<endl;
	cout<<"最短路径为："; 
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
	cout<<"请输入图的顶点数n和边数e"<<endl;
	int n,e;  cin>>n>>e;
	linkedWGraph<int> LWGraph(n);
	cout<<"请以顶点对(顶点1,顶点2，权值)的形式输入图的每一条边"<<endl;
	for(int i=0;i<e;i++)
	{
		int v1,v2,w;  cin>>v1>>v2>>w;
		edge<int> *Edge=new edge<int> (v1,v2,w);
		LWGraph.insertEdge(Edge);
	}
	cout<<"邻接链表各节点内容为："<<endl;
	LWGraph.output();
	if( LWGraph.connected() ==true) cout<<"本图是连通的。"<<endl;
	else{
		int c[n+1];
		cout<<"连通分支数是："<<LWGraph.labelComponents(c)<<endl;
		for(int i=1;i<=n;i++)
		   cout<<"顶点"<<i<<"属于第"<<c[i]<<"连通分支"<<endl;
	}
	cout<<"请输入一个顶点序号："; int num; cin>>num;
	int reach[n+1];
	cout<<"BFS序列：";   LWGraph.print_bfs(num,reach);
	cout<<"DFS序列：";   LWGraph.print_dfs(num,reach);  cout<<endl;
	
	
	int predecessor[n+1]; cout<<"请输入起始点和结束点：";  int start,dest;  cin>>start>>dest; 
	cout<<endl<<"最短路："<<LWGraph.Dijkstra(start,dest,predecessor)<<endl;
	cout<<"最短路径为："; 
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
