/*
1.创建无向图类。存储结构分别使用邻接矩阵和邻接链表。提供操作：
1.插入一条边
2.删除一条边
3.遍历：BFS、DFS。

2.键盘输入图中顶点的个数n和边的数目e，以顶点对（i，j）形式
依次输入图的每一条边或随机生成含e条边的图，其中（i,j）表示
顶点i和顶点j之间有边相连，建立图。-

3.判断图是否连通。若不连通，输出该图的连通分量的个数及每个
连通分量中的顶点；-

4.对建立好的连通图，键盘输入一顶点，输出从该顶点开始的一个
DFS序列和BFS序列；一个DFS生成树和BFS生成树（树可以文本形式
输出）

5.键盘输入两顶点，输出两顶点之间的最短路径。-
*/

#include<iostream>
#include"linkedWGraph.h"
#define noEdge 1000000
using namespace std;

int main(){
#pragma warning(disable:4996)
	//freopen ("input.txt", "r", stdin);

	cout<<"请输入图的顶点数n和边数e"<<endl;
	int n,e;  
	cin>>n>>e;
	linkedWGraph<int> g(n);
	cout<<"请以顶点对 顶点1 顶点2 权值 的形式输入图的每一条边"<<endl;

	for(int i=0;i<e;i++){
		int v1,v2,w; 
		cin>>v1>>v2>>w;
		g.insertEdge(v1,v2,w);
	}
	//cout<<"邻接链表各节点内容为："<<endl;
	//g.output(cout);
	if (g.connected () == true) {
		cout << "本图是连通的。" << endl;
	} else {
		int* c = new int[n + 1];
		int ltfzs = g.getCC (c);
		cout << "连通分支数是：" << ltfzs << endl;
		for (int i = 1; i <= ltfzs; i++) {
			for (int j = 1; j <= n; j++)
				if (c[j] == i)cout << j << " ";
			cout << "\n";
		}


		delete[] c;
	}
	cout<<"请输入一个顶点序号："; int num; cin>>num;
	cout<<"BFS序列：";   g.printBfs (num);
	cout<<"DFS序列：";   g.printDfs (num);  cout<<endl;
	
	int* path=new int[n+1]; 
	cout<<"请输入起始点和结束点：";  int start,dest;  cin>>start>>dest; 
	cout<<endl<<"最短路："<<g.dijkstra(start,dest,path)<<endl;
	cout<<"最短路径为："; 
	n=dest;  cout<<dest<<" ";
	while(path[n]!=0){
		cout<<path[n]<<" ";
		n=path[n];
	}
	delete[] path;

	return 0;
}