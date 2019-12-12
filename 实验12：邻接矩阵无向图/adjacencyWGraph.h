#pragma once
#include<iostream>
#include"edge.h"
#include"queue.h"
#include"stack.h"
#include<string.h>
using namespace std;



template<class N,class W>
class adjacencyWGraph {//加权无向图 
protected:
	N* _vertexes;
	int _vertex_num;       //顶点个数 
	int _edge_num;       //边的个数 
	W** _edges;       //邻接数组 
	W _no_edge;    //表示不存在的边
	int* _reach;  //数组指针 
	int _label = 1;

	void rDfs (int v) {//递归实现深度优先搜索
		_reach[v] = _label;  int u;
		//cout<<"当前走到顶点："<<v<<endl;
		myItertor* iv = itertor (v);  //这里加<W>就会报错，为什么？？ 
		while ((u = iv->next ()) != 0) {//以v的下一个邻接点u为新起点递归搜索 
			if (_reach[u] != _label)
				rDfs (u);  //u是一个没有到达过的顶点 
		}
		delete iv;
		return;
	}

public:
	adjacencyWGraph (int v = 0, W theNoWdge = 0) {//构造函数
		if (v < 0) cerr << "请检验顶点数的合法性！" << endl;
		_vertex_num = v;
		_no_edge = theNoWdge;
		_edge_num = 0;

		_edges = new W * [_vertex_num + 1];
		for (int i = 0; i < _vertex_num + 1; i++) {//分配空间 
			_edges[i] = new W[_vertex_num + 1];
		}
		for (int i = 1; i <= _vertex_num; i++){  //初始化邻接矩阵 
			for (int j = 1; j <= _vertex_num; j++) {
				_edges[i][j] = _no_edge;
			}
		}
	}
	~adjacencyWGraph () {
		for (int i = 0; i < _vertex_num + 1; i++) {
			delete[] _edges[i];
		}
		delete[] _edges;
		_edges = nullptr;  //不置为nullptr的话会变野指针，但是这里也没事 
	}
	class myItertor {
	public:
		myItertor (W* theRow, W theWdge, int v) {
			Row = theRow;
			_no_edge = theWdge;
			_vertex_num = v;
			currentVertex = 1;
		}
		~myItertor () {}
		int next (W& theWeight) {//返回指定顶点的下一个邻接点和它的的权值 
			for (int i = currentVertex; i <= _vertex_num; i++) {
				if (Row[i] != _no_edge) {//发现一个邻接点 
					currentVertex = i + 1;
					theWeight = Row[i];
					return i;
				}
			}
			//不存在下一个邻接点了 
			currentVertex = _vertex_num + 1;
			return 0;
		}
		int next () {//返回指定顶点的下一个邻接点 
			for (int i = currentVertex; i <= _vertex_num; i++) {
				if (Row[i] != _no_edge) {//发现一个邻接点 
					currentVertex = i + 1;
					//cout<<"i="<<i<<endl;
					return i;
				}
			}
			//不存在下一个邻接点了 
			currentVertex = _vertex_num + 1;
			return 0;
		}
	protected:
		W* Row;              //邻接矩阵的的行 
		W _no_edge;            //theRow[i]==_no_edge，当且仅当没有关联与顶点i的边 
		int _vertex_num;               //顶点数 
		int currentVertex;   //当前搜索的顶点 
	};
	myItertor* itertor (int theVertex) {//返回顶点theVertex的迭代器 
		checkVertex (theVertex); //cout<<"_edges[theVertex]="<<_edges[theVertex];
		return new myItertor (_edges[theVertex], _no_edge, _vertex_num);
	}
	void checkVertex (int theVertex) const {//确认是有效顶点 
		if (theVertex<1 || theVertex>_vertex_num) {
			cerr << "the vertex:" << theVertex << " is not permissible";
			exit (1);
		} else return;
	}
	bool directed () const { return false; }
	void insertEdge (edge<W>* theWdge) {
		//插入边，如果该边已存在，则用theWdge->weight()修改边的权
		int v1 = theWdge->vertex1 ();
		int v2 = theWdge->vertex2 ();
		if (v1<1 || v2<1 || v1>_vertex_num || v2>_vertex_num || v1 == v2) {//越界处理 
			cerr << "(" << v1 << "," << v2 << ") is not _edges permissible edge" << endl;
			exit (1);
		}
		if (_edges[v1][v2] == _no_edge)  //新边 
			_edge_num++;
		_edges[v2][v1] = _edges[v1][v2] = theWdge->weight ();
	}
	void er_edgesseWdge (int i, int j) {//删除边(i,j),如果不存在该边就什么也不做 
		if (i >= 1 && j >= 1 && i <= _vertex_num && j <= _vertex_num && _edges[i][j] != _no_edge) {
			_edges[i][j] = _edges[j][i] = _no_edge;
			_edge_num--;
		}
	}
	int Degree (int Vertex) {//计算顶点Vertex的度
		checkVertex (Vertex);
		int sum = 0;
		for (int j = 1; j <= _vertex_num; j++)
			if (_edges[Vertex][j] != _no_edge)  //遍历第Vertex行 
				sum++;
		return sum;
	}
	bool connected () {//判断无向图是否连通 
		if (directed ()) {
			cerr << "本图是无向图！" << endl;  exit (2);
		}

		_reach = new int[_vertex_num + 1];
		for (int i = 1; i <= _vertex_num; i++)
			_reach[i] = 0;

		dfs (1, _reach, 1); //给邻接于顶点1的可达顶点做标记

		for (int i = 1; i <= _vertex_num; i++) {//检查所有顶点是否已做标记
			if (_reach[i] == 0)
				return false;
		}
		return true;
	}
	void bfs (int v, int _reach[], int _label) {//广度优先算法，_reach[i]用来标记所有邻接于顶点v的可到达的顶点 
		queue<int> q (10);
		_reach[v] = _label;
		q.push (v);

		while (q.empty () != true) {
			int vertex = q.front ();
			q.pop ();

			for (int j = 1; j <= _vertex_num; j++) {
				if (_edges[vertex][j] != _no_edge && _reach[j] == 0) {
					q.push (j);	_reach[j] = _label;
				}
			}
		}
	}
	void dfs (int v, int _reach[], int _label) {
		_reach = _reach;
		_label = _label;
		rDfs (v);
	}
	int labelComponents (int c[]) {//返回连通分支数，c[i]是顶点i所属的分支序号 
		int i = 0;
		for (i = 0; i <= _vertex_num; i++)
			c[i] = 0;

		int _label = 0;  //最后一个构建的编号 
		for (i = 1; i <= _vertex_num; i++) {
			if (c[i] == 0) {//对所有未到达的顶点，都进行一次bfs标记 
				_label++;
				bfs (i, c, _label);  //给新分支做标记 
			}
		}
		return _label;
	}
	void print_bfs (int v, int _reach[]) {
		memset (_reach, 0, sizeof (int) * (_vertex_num + 1));
		int _label = 1; _reach[v] = _label;
		queue<int> q (10);
		q.push (v);

		while (q.empty () != true) {
			int vertex = q.front ();
			cout << vertex << " ";
			q.pop ();

			for (int j = 1; j <= _vertex_num; j++) {
				if (_edges[vertex][j] != _no_edge && _reach[j] == 0) {
					q.push (j);	_reach[j] = _label;
				}
			}
		}
	}
	void print_dfs (int v, int _reach[]) {
		stack<int> s (10);  int u;
		memset (_reach, 0, sizeof (int) * (_vertex_num + 1));
		_reach[v] = _label;
		s.push (v);  cout << v << " ";

		while (!s.empty ()) //当stack不空时 
		{
			int w = s.top ();
			s.pop ();
			myItertor* iv = itertor (w);	  u = iv->next ();
			while (u != 0)  //对上一个到达的点w的所有邻接点 
			{
				if (_reach[u] != _label) //如果存在一个未标记的点j 
				{
					_reach[u] = _label;
					s.push (u);
					cout << u << " ";
					iv = itertor (u);	//让iv指向以u为起点的迭代器 
				} else {//该顶点已被标记
					u = iv->next ();
					if (u == 0 && s.empty () != true)  s.pop (); //该顶点没有其他邻接点了
				}
			}
		}
	}

	int Dijkstra (int starti, int desti, int pre[]) {
		//返回最短路长，记录下最短路的路径，pre是从start到desti路径中desti前的那个顶点 


		bool* S = new bool[_vertex_num + 1];  //S[i]表示starti到顶点i的最短路已求得 
		fill (S, S + _vertex_num + 1, false);

		int* dis = new int[_vertex_num + 1];  //dis[i]是从starti点到顶点i的距离 

		/*初始化距离*/
		for (int i = 1; i <= _vertex_num; i++) {
			dis[i] = _edges[starti][i];
		}
		dis[starti] = 0;

		/*初始化前驱节点*/
		for (int i = 1; i <= _vertex_num; i++) {
			if (dis[i] == _no_edge)
				pre[i] = -1;    //对不邻接的点 
			else
				pre[i] = starti;//邻接点的前驱就是starti 
		}
		pre[starti] = 0;    //源顶点没有前驱 

		while (S[desti] != true) {
			int u;
			for (u = 1; u <= _vertex_num; u++) {

				auto minVertex = [](int dis[], bool S[], int n) {//在非S元素中找到距离S集合最近的那个 
					int min = 100000;
					for (int i = 1; i <= n; i++) {
						if (dis[i] < min && S[i] == false) {
							min = dis[i];
						}
					}
					return min;
				};

				if (!S[u] && dis[u] == minVertex (dis, S, _vertex_num)) {
					S[u] = true;  //把u加入顶点集S中
					
					//对每一个不属于S的顶点v ,更新他们到起点的距离
					for (int v = 1; v <= _vertex_num; v++) {
						if (!S[v] && dis[u] + _edges[u][v] < dis[v]) {
							dis[v] = dis[u] + _edges[u][v];
							pre[v] = u;   //顶点v的前驱是u 
						}
					}
				}
			}
		}
		return dis[desti];
	}

};


