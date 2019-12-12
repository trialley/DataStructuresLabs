/*实验十三  贪婪算法
一、实验目的
掌握最小生成树的Prim算法和Kruskal算法的及其实现。
二、实验内容
1、创建加权无向图类。设图没有重边和自环，存储结构分别使用邻接矩阵或邻接链表。提供必要的基本操作；
2、键盘输入图中顶点的个数n和边的数目e，以三元组（i,j,w）形式依次输入图的每一条边或随机生成含e条边的图，其中（i,j,w）表示顶点i和顶点j之间拥有权值为w的边，建立图。
3. 对建立好的图，分别使用Prim算法和Kruskal算法求最小生成树，输出求得的最小生成树（以文本形式输出生成树中的各条边及对应的权值）。
*/
#include<iostream>
#include"adjacencyWGraph.h"
#define noEdge 1000000
#define until(re) while(!(re))

using namespace std;

int main () {
#pragma warning(disable:4996)
	freopen ("input.txt", "r", stdin);
	cout << "请输入图的顶点数n和边数e" << endl;
	int n, e;  cin >> n >> e;
	adjacencyWGraph<int> g (n, noEdge);
	cout << "请以顶点对(顶点1,顶点2，权值)的形式输入图的每一条边" << endl;

	for (int i = 0; i < e; i++) {
		int _from, _to, _w;  cin >> _from >> _to >> _w;
		edge<int>* Edge = new edge<int> (_from, _to, _w);
		g.insertEdge (Edge);
	}

	edge<int>* STE = new edge<int>[n - 1];
	cout << "kruskal最小生成树中每条边(v1,v2,w)如下:" << endl;
	if (g.kruskal (STE) == true) {
		for (int i = 0; i <= n - 2; i++)
			cout << STE[i] << endl;
	}
	cout << "prim最小生成树中每条边(v1,v2,w)如下:" << endl;
	if (g.prim (STE) == true) {
		for (int i = 0; i <= n - 2; i++) {
			cout << STE[i] << endl;
		}
	}
	return 0;
}
