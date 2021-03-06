/*
实验十三  贪婪算法
一、实验目的
掌握最小生成树的Prim算法和Kruskal算法的及其实现。
二、实验内容
1、创建加权无向图类。设图没有重边和自环，存储结构分别使用邻接矩阵或邻接链表。提供必要的基本操作；
2、键盘输入图中顶点的个数n和边的数目e，以三元组（i,j,w）形式依次输入图的每一条边或随机生成含e条边的图，其中（i,j,w）表示顶点i和顶点j之间拥有权值为w的边，建立图。
3. 对建立好的图，分别使用Prim算法和Kruskal算法求最小生成树，输出求得的最小生成树（以文本形式输出生成树中的各条边及对应的权值）。
*/

#include<iostream>
#include"linkedWGraph.h"
#include"edge.h"
#define noEdge 1000000
using namespace std;

int main(){
#pragma warning(disable:4996)
	freopen ("input.txt", "r", stdin);
	cout << "请输入图的顶点数n和边数e" << endl;
	int n, e;
	cin >> n >> e;

	//初始化邻接链表无向图
	linkedWGraph<int> g (n);
	cout << "请以顶点对(顶点1,顶点2，权值)的形式输入图的每一条边" << endl;

	//初始化各边
	for (int i = 0; i < e; i++) {
		int v1, v2, w;  cin >> v1 >> v2 >> w;
		edge<int>* Edge = new edge<int> (v1, v2, w);
		g.insertEdge (v1,v2,w);
	}

	//进行最小生成树的求解
	edge<int>* STE = new edge<int>[n - 1];
	//cout << "kruskal最小生成树中每条边(v1,v2,w)如下:" << endl;
	//if (g.kruskal (STE) == true) {
	//	for (int i = 0; i <= n - 2; i++)
	//		cout << STE[i] << endl;
	//}
	//cout << "prim最小生成树中每条边(v1,v2,w)如下:" << endl;
	if (g.prim (STE) == true) {
		for (int i = 0; i <= n - 2; i++)
			cout << STE[i] << endl;
	}

	//cout << "邻接链表各节点内容为：" << endl;
	//g.output (cout);
	//if (g.connected () == true) cout << "本图是连通的。" << endl;
	//else {
	//	int* lables = new int[n + 1];
	//	cout << "连通分支数是：" << g.getCC (lables) << endl;
	//	for (int i = 1; i <= n; i++)
	//		cout << "顶点" << i << "属于第" << lables[i] << "连通分支" << endl;

	//	delete[] lables;
	//}
	//int* reach = new int[n + 1];
	//fill (reach, reach + n + 1, 0);

	//cout << "BFS序列：";   g.printBfs (1);
	//cout << "DFS序列：";   g.printDfs (1);
	//cout << endl;
	//delete[] reach;

	//int* predecessor = new int[n + 1];
	//cout << "请输入起始点和结束点：";  int start, dest;  cin >> start >> dest;
	//cout << endl << "最短路：" << g.dijkstra (start, dest, predecessor) << endl;
	//cout << "最短路径为：";
	//n = dest;  cout << dest << " ";
	//while (predecessor[n] != 0) {
	//	cout << predecessor[n] << " ";
	//	n = predecessor[n];
	//}
	//delete[] predecessor;

	return 0;
}