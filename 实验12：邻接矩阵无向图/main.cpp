/*
1.创建无向图类。存储结构分别使用邻接矩阵和邻接链表。提供操作：
1.插入一条边
2.删除一条边
3.遍历：BFS、DFS。
2.键盘输入图中顶点的个数n和边的数目e，以顶点对（i，j）形式依次输入图的每一条边或随机生成含e条边的图，其中（i,j）表示顶点i和顶点j之间有边相连，建立图。
3.判断图是否连通。若不连通，输出该图的连通分量的个数及每个连通分量中的顶点；
4.对建立好的连通图，键盘输入一顶点，输出从该顶点开始的一个DFS序列和BFS序列；一个DFS生成树和BFS生成树（树可以文本形式输出）
5.键盘输入两顶点，输出两顶点之间的最短路径。
*/


#include <iostream>
#include "Graph.h"

using namespace std;

int main(){
	#pragma warning(disable:4996)
	freopen ("input.txt", "r", stdin);
	Graph<int,int> a;
	cin >> a;
	cout << a;
	return 0;
	/*目录：
	<<                                              //格式化输出（如果在输出时改动边数或顶点数，需要单独为其写一个cout输出命令）
	>>                                              //格式化输入
	bool GraphEmpty()const;							//判断图空否
	int NumberOfVertices();							//返回顶点数
	int NumberOfEdges();							//返回边数
	E getWeight(int v1, int v2);					//取边v1,v2的权值
	T getValue(int i);								//取位置i的值，不合理返回0
	int getFirstNeighbor(T k);                      //取顶点为k的第一个邻接节点
	int getFirstNeighbor(int k,char type);          //取顶点位置为k的第一个邻接节点
	int getNextNeighbor(int k, int w);				//取顶点为k的邻接顶点位置w的下一个邻接顶点位置（下标定位顶点）
	int getNextNeighbor(T k, int w, char type);		//取顶点位置为k的邻接顶点位置w的下一个邻接顶点位置(顶点数据定位顶点）
	bool insertVertex(const T& vertex);				//插入一个顶点
	bool insertEdge(T n1, T n2, E cost = 1);		//插入边(n1,n2)，权值为cost。边只有一条，不可覆盖，重复插入相同边。不允许插入自己与自己的边
	bool removeVertex(T v1);						//删除顶点v1和与之相关的边。可删除最后一个顶点。
	bool removeEdge(T n1, T n2);					//删除边（n1,n2）
	int outdegree(T v);								//出度(无向图出度等于入度）
	int indegree(T v);								//入度
	void DFS(Graph&G, const T&v);					//深度遍历，从v开始
	void BFS(Graph<T,E>&G, const T &v);             //广度遍历，从v开始
	*/
}
