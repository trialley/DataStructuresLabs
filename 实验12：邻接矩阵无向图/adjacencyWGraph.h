#pragma once
#include<iostream>
#include"edge.h"
#include"queue.h"
#include"stack.h"
#include<string.h>
using namespace std;


int Minium (int L[], bool S[], int n) {
	//在L[1:n]数组中返回不在顶点集S中最小的元素 
	int min = 100000;
	for (int i = 1; i <= n; i++) {
		if (L[i] < min && S[i] == false)
			min = L[i];
	}
	return min;
}

template<class T>
class adjacencyWGraph {//加权无向图 
protected:
	int n;       //顶点个数 
	int e;       //边的个数 
	T** a;       //邻接数组 
	T noEdge;    //表示不存在的边
	int* reach;  //数组指针 
	int label = 1;

	void rDfs (int v) {//递归实现深度优先搜索
		reach[v] = label;  int u;
		//cout<<"当前走到顶点："<<v<<endl;
		myIterator* iv = iterator (v);  //这里加<T>就会报错，为什么？？ 
		while ((u = iv->next ()) != 0) {//以v的下一个邻接点u为新起点递归搜索 
		//cout<<v<<"的下一个邻接点是："<<u<<" "<<endl;
			if (reach[u] != label)
				rDfs (u);  //u是一个没有到达过的顶点 
		}
		delete iv;
		return;
	}

public:
	adjacencyWGraph (int v = 0, T theNoEdge = 0) {//构造函数
		if (v < 0) cerr << "请检验顶点数的合法性！" << endl;
		n = v;
		noEdge = theNoEdge;
		e = 0;

		a = new T * [n + 1];
		for (int i = 0; i < n + 1; i++) {//分配空间 
			a[i] = new T[n + 1];
		}
		for (int i = 1; i <= n; i++)  //初始化邻接矩阵 
		{
			for (int j = 1; j <= n; j++) {
				a[i][j] = noEdge;
			}
		}
	}
	~adjacencyWGraph () {
		for (int i = 0; i < n + 1; i++) {
			delete[] a[i];
		}
		delete[] a;
		a = NULL;  //不置为NULL的话会变野指针，但是这里也没事 
	}
	class myIterator {
	public:
		myIterator (T* theRow, T theEdge, int v) {
			Row = theRow;
			noEdge = theEdge;
			n = v;
			currentVertex = 1;
		}
		~myIterator () {}
		int next (T& theWeight) {//返回指定顶点的下一个邻接点和它的的权值 
			for (int i = currentVertex; i <= n; i++) {
				if (Row[i] != noEdge) {//发现一个邻接点 
					currentVertex = i + 1;
					theWeight = Row[i];
					return i;
				}
			}
			//不存在下一个邻接点了 
			currentVertex = n + 1;
			return 0;
		}
		int next () {//返回指定顶点的下一个邻接点 
			for (int i = currentVertex; i <= n; i++) {
				if (Row[i] != noEdge) {//发现一个邻接点 
					currentVertex = i + 1;
					//cout<<"i="<<i<<endl;
					return i;
				}
			}
			//不存在下一个邻接点了 
			currentVertex = n + 1;
			return 0;
		}
	protected:
		T* Row;              //邻接矩阵的的行 
		T noEdge;            //theRow[i]==noEdge，当且仅当没有关联与顶点i的边 
		int n;               //顶点数 
		int currentVertex;   //当前搜索的顶点 
	};
	myIterator* iterator (int theVertex) {//返回顶点theVertex的迭代器 
		checkVertex (theVertex); //cout<<"a[theVertex]="<<a[theVertex];
		return new myIterator (a[theVertex], noEdge, n);
	}
	void checkVertex (int theVertex) const {//确认是有效顶点 
		if (theVertex<1 || theVertex>n) {
			cerr << "the vertex:" << theVertex << " is not permissible";
			exit (1);
		} else return;
	}
	bool directed () const { return false; }
	void insertEdge (edge<T>* theEdge) {
		//插入边，如果该边已存在，则用theEdge->weight()修改边的权
		int v1 = theEdge->vertex1 ();
		int v2 = theEdge->vertex2 ();
		if (v1<1 || v2<1 || v1>n || v2>n || v1 == v2) {//越界处理 
			cerr << "(" << v1 << "," << v2 << ") is not a permissible edge" << endl;
			exit (1);
		}
		if (a[v1][v2] == noEdge)  //新边 
			e++;
		a[v2][v1] = a[v1][v2] = theEdge->weight ();
	}
	void eraseEdge (int i, int j) {//删除边(i,j),如果不存在该边就什么也不做 
		if (i >= 1 && j >= 1 && i <= n && j <= n && a[i][j] != noEdge) {
			a[i][j] = a[j][i] = noEdge;
			e--;
		}
	}
	int Degree (int Vertex) {//计算顶点Vertex的度
		checkVertex (Vertex);
		int sum = 0;
		for (int j = 1; j <= n; j++)
			if (a[Vertex][j] != noEdge)  //遍历第Vertex行 
				sum++;
		return sum;
	}
	bool connected () {//判断无向图是否连通 
		if (directed ()) {
			cerr << "本图是无向图！" << endl;  exit (2);
		}

		reach = new int[n + 1];
		for (int i = 1; i <= n; i++)
			reach[i] = 0;

		dfs (1, reach, 1); //给邻接于顶点1的可达顶点做标记

		for (int i = 1; i <= n; i++) {//检查所有顶点是否已做标记
			if (reach[i] == 0)
				return false;
		}
		return true;
	}
	void bfs (int v, int reach[], int label) {//广度优先算法，reach[i]用来标记所有邻接于顶点v的可到达的顶点 
		queue<int> q (10);
		reach[v] = label;
		q.push (v);

		while (q.empty () != true) {
			int vertex = q.front ();
			q.pop ();

			for (int j = 1; j <= n; j++) {
				if (a[vertex][j] != noEdge && reach[j] == 0) {
					q.push (j);	reach[j] = label;
				}
			}
		}
	}
	void dfs (int v, int reach[], int label) {
		reach = reach;
		label = label;
		rDfs (v);
	}
	int labelComponents (int c[]) {//返回连通分支数，c[i]是顶点i所属的分支序号 
		int i = 0;
		for (i = 0; i <= n; i++)
			c[i] = 0;

		int label = 0;  //最后一个构建的编号 
		for (i = 1; i <= n; i++) {
			if (c[i] == 0) {//对所有未到达的顶点，都进行一次bfs标记 
				label++;
				bfs (i, c, label);  //给新分支做标记 
			}
		}
		return label;
	}
	void print_bfs (int v, int reach[]) {
		memset (reach, 0, sizeof (int) * (n + 1));
		int label = 1; reach[v] = label;
		queue<int> q (10);
		q.push (v);

		while (q.empty () != true) {
			int vertex = q.front ();
			cout << vertex << " ";
			q.pop ();

			for (int j = 1; j <= n; j++) {
				if (a[vertex][j] != noEdge && reach[j] == 0) {
					q.push (j);	reach[j] = label;
				}
			}
		}
	}
	void print_dfs (int v, int reach[]) {
		stack<int> s (10);  int u;
		memset (reach, 0, sizeof (int) * (n + 1));
		reach[v] = label;
		s.push (v);  cout << v << " ";

		while (!s.empty ()) //当stack不空时 
		{
			int w = s.top ();
			s.pop ();
			myIterator* iv = iterator (w);	  u = iv->next ();
			while (u != 0)  //对上一个到达的点w的所有邻接点 
			{
				if (reach[u] != label) //如果存在一个未标记的点j 
				{
					reach[u] = label;
					s.push (u);
					cout << u << " ";
					iv = iterator (u);	//让iv指向以u为起点的迭代器 
				} else {//该顶点已被标记
					u = iv->next ();
					if (u == 0 && s.empty () != true)  s.pop (); //该顶点没有其他邻接点了
				}
			}
		}
	}
	/*	void bfSpanningTree(int v)
		{//生成以v顶点的BFS生成树
			queue<int> q(10);
			reach[v]=label;
			q.push(v);
			TreeNode Node(v);  TreeNode *root=&Node;

			while(q.empty()!=true)
			{
				int vertex=q.front();  TreeNode *pp=Tree_search(vetrex,root);  //这里应该写一个在树中搜索关键字的函数，返回指向节点的指针
				q.pop();

				for(int j=1;j<=n;j++)
				{
					if( a[vertex][j]!=noEdge && reach[j]==0 )
					{  q.push(j);
					   reach[j]=label;
					   TreeNode *p=new TreeNode(j);  //这里建一个新节点
					   linkNode(pp,p);    //将pp与p连接起来
					}
				}
			}
		}*/
	int Dijkstra (int start, int dest, int predecessor[]) {//返回最短路长，记录下最短路的路径，predecessor是从start到dest路径中dest前的那个顶点 
		int* L = new int[n + 1];  //L[i]就是从start点到顶点i的距离 
		for (int i = 1; i <= n; i++)  L[i] = a[start][i];  L[start] = 0;
		bool* S = new bool[n + 1];
		for (int i = 1; i <= n; i++)  S[i] = false;  //S[i]表示start到顶点i的最短路已求得 
		for (int i = 1; i <= n; i++) {
			if (L[i] == noEdge)    //对不邻接的点 
				predecessor[i] = -1;
			else
				predecessor[i] = start;  //邻接点的前驱就是start 
		}
		predecessor[start] = 0;    //源顶点没有前驱 
	  /*…………以上是初始化操作…………*/

		while (S[dest] != true) {/*下面找一个不在顶点集S中的u且L[u]标号最小，可以借助一下线性表吗？*/
			int u;
			for (u = 1; u <= n; u++) {
				if (S[u] == false && L[u] == Minium (L, S, n))  //这里找一个不在顶点集S且标号最小的点，复杂度可以降到O(1)吗？ 
				{//这里比较粗暴，直接扫描了所有顶点，其实可以用一个collected数组优化成扫描所有已收录顶点
				 //按我的写法复杂度好像是O(n^3)，可以通过把两个循环判断条件糅合来降低复杂度嘛？不，你的复杂度是O(N^2) 
					S[u] = true;  //把u加入顶点集S中
					for (int v = 1; v <= n; v++) {//对每一个不属于S的顶点v 
						if (S[v] == false && L[u] + a[u][v] < L[v]) {
							L[v] = L[u] + a[u][v];
							predecessor[v] = u;   //顶点v的前驱是u 
						}
					}
					break;  //跳到最外层的while循环 
				}
			}
		}
		return L[dest];
	}

};


