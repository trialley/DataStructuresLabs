/*
1.��������ͼ�ࡣ�洢�ṹ�ֱ�ʹ���ڽӾ�����ڽ������ṩ������
1.����һ����
2.ɾ��һ����
3.������BFS��DFS��

2.��������ͼ�ж���ĸ���n�ͱߵ���Ŀe���Զ���ԣ�i��j����ʽ
��������ͼ��ÿһ���߻�������ɺ�e���ߵ�ͼ�����У�i,j����ʾ
����i�Ͷ���j֮���б�����������ͼ��-

3.�ж�ͼ�Ƿ���ͨ��������ͨ�������ͼ����ͨ�����ĸ�����ÿ��
��ͨ�����еĶ��㣻-

4.�Խ����õ���ͨͼ����������һ���㣬����Ӹö��㿪ʼ��һ��
DFS���к�BFS���У�һ��DFS��������BFS���������������ı���ʽ
�����

5.�������������㣬���������֮������·����-
*/

#include<iostream>
#include"linkedWGraph.h"
#define noEdge 1000000
using namespace std;

int main(){
#pragma warning(disable:4996)
	freopen ("input.txt", "r", stdin);

	cout<<"������ͼ�Ķ�����n�ͱ���e"<<endl;
	int n,e;  
	cin>>n>>e;
	linkedWGraph<int> LWGraph(n);
	cout<<"���Զ���� ����1 ����2 Ȩֵ ����ʽ����ͼ��ÿһ����"<<endl;

	for(int i=0;i<e;i++){
		int v1,v2,w; 
		cin>>v1>>v2>>w;
		LWGraph.insertEdge(v1,v2,w);
	}
	cout<<"�ڽ�������ڵ�����Ϊ��"<<endl;
	LWGraph.output(cout);
	if( LWGraph.connected() ==true) cout<<"��ͼ����ͨ�ġ�"<<endl;
	else{
		int* c=new int[n+1];
		cout<<"��ͨ��֧���ǣ�"<<LWGraph.labelComponents(c)<<endl;
		for(int i=1;i<=n;i++)
		   cout<<"����"<<i<<"���ڵ�"<<c[i]<<"��ͨ��֧"<<endl;
		
		delete[] c;
	}
	cout<<"������һ��������ţ�"; int num; cin>>num;
	int* reach=new int[n+1];
	cout<<"BFS���У�";   LWGraph.print_bfs(num,reach);
	cout<<"DFS���У�";   LWGraph.print_dfs(num,reach);  cout<<endl;
	delete[] reach;
	
	int* predecessor=new int[n+1]; 
	cout<<"��������ʼ��ͽ����㣺";  int start,dest;  cin>>start>>dest; 
	cout<<endl<<"���·��"<<LWGraph.Dijkstra(start,dest,predecessor)<<endl;
	cout<<"���·��Ϊ��"; 
	n=dest;  cout<<dest<<" ";
	while(predecessor[n]!=0)
	{
		cout<<predecessor[n]<<" ";
		n=predecessor[n];
	}
	delete[] predecessor;

	return 0;
}