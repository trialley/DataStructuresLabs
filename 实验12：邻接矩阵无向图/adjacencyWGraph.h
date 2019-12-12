#pragma once
#include<iostream>
#include"edge.h"
#include"queue.h"
#include"stack.h"
#include"minHeap.h"
#include"fastUnionFind.h"
using namespace std;
#define until(re) while(!(re))

template<class W>
class adjacencyWGraph {
	//加权无向图 
protected:
	int _vertex_num;       //顶点个数 
	int _edge_num;       //边的个数 
	W** _weights;       //邻接数组 
	W _no_edge;    //表示不存在的边
	int* _reach;  //数组指针 
	int _label = 1;

	void _dfs (int v) {
		//递归实现深度优先搜索
		_reach[v] = _label;  int u;
		//cout<<"当前走到顶点："<<v<<endl;
		myIterator* iv = iterator (v);  //这里加<T>就会报错，为什么？？ 
		while ((u = iv->next ()) != 0) {
			//以v的下一个邻接点u为新起点递归搜索 
			if (_reach[u] != _label) {
				_dfs (u);  //u是一个没有到达过的顶点 
			}
		}

		delete iv;
		return;
	}

public:
	adjacencyWGraph (int v = 0, W no_edgei = 0) {
		//构造函数
		if (v < 0) cerr << "请检验顶点数的合法性！" << endl;
		_vertex_num = v;
		_no_edge = no_edgei;
		_edge_num = 0;

		_weights = new W * [_vertex_num + 1];
		for (int i = 0; i < _vertex_num + 1; i++) {
			//分配空间 
			_weights[i] = new W[_vertex_num + 1];
		}
		for (int i = 1; i <= _vertex_num; i++) {
			//初始化邻接矩阵 
			for (int j = 1; j <= _vertex_num; j++) {
				_weights[i][j] = _no_edge;
			}
		}
	}
	~adjacencyWGraph () {
		for (int i = 0; i < _vertex_num + 1; i++) {
			delete[] _weights[i];
		}
		delete[] _weights;
		_weights = NULL;  //不置为NULL的话会变野指针，但是这里也没事 
	}
	class myIterator {
	public:
		myIterator (W* theRow, W theEdge, int v) {
			_row = theRow;
			_no_edge = theEdge;
			_vertex_num = v;
			_current_vertex = 1;
		}
		~myIterator () {}
		int next (W& theWeight) {
			//返回指定顶点的下一个邻接点和它的的权值 
			for (int i = _current_vertex; i <= _vertex_num; i++) {
				if (_row[i] != _no_edge) {
					//发现一个邻接点 
					_current_vertex = i + 1;
					theWeight = _row[i];
					return i;
				}
			}
			//不存在下一个邻接点了 
			_current_vertex = _vertex_num + 1;
			return 0;
		}
		int next () {
			//返回指定顶点的下一个邻接点 
			for (int i = _current_vertex; i <= _vertex_num; i++) {
				if (_row[i] != _no_edge) {//发现一个邻接点 
					_current_vertex = i + 1;
					//cout<<"i="<<i<<endl;
					return i;
				}
			}
			//不存在下一个邻接点了 
			_current_vertex = _vertex_num + 1;
			return 0;
		}
	protected:
		W* _row;              //邻接矩阵的的行 
		W _no_edge;            //theRow[i]==noEdge，当且仅当没有关联与顶点i的边 
		int _vertex_num;               //顶点数 
		int _current_vertex;   //当前搜索的顶点 
	};
	myIterator* iterator (int indexi) {
		//返回顶点indexi的迭代器 
		_checkVertex (indexi);
		return new myIterator (_weights[indexi], _no_edge, _vertex_num);
	}
	void _checkVertex (int theVertex) const {
		//确认是有效顶点 
		if (theVertex<1 || theVertex>_vertex_num) {
			cerr << "the vertex:" << theVertex << " is not permissible";
			exit (1);
		} else return;
	}
	bool directed () const { return false; }
	void insertEdge (edge<W>* theEdge) {
		//插入边，如果该边已存在，则用theEdge->weight()修改边的权
		int v1 = theEdge->getFrom ();
		int v2 = theEdge->getTo ();
		if (v1<1 || v2<1 || v1>_vertex_num || v2>_vertex_num || v1 == v2) {
			//越界处理 
			cerr << "(" << v1 << "," << v2 << ") is not a permissible edge" << endl;
			exit (1);
		}
		if (_weights[v1][v2] == _no_edge) {
			_edge_num++;
		}
		_weights[v2][v1] = _weights[v1][v2] = theEdge->weight ();
	}
	void eraseEdge (int i, int j) {
		//删除边(i,j),如果不存在该边就什么也不做 
		if (i >= 1 && j >= 1 && i <= _vertex_num && j <= _vertex_num && _weights[i][j] != _no_edge) {
			_weights[i][j] = _weights[j][i] = _no_edge;
			_edge_num--;
		}
	}
	int Degree (int Vertex) {
		//计算顶点Vertex的度
		_checkVertex (Vertex);
		int sum = 0;
		for (int j = 1; j <= _vertex_num; j++) {
			if (_weights[Vertex][j] != _no_edge) {
				sum++;
			}
		}
		return sum;
	}
	bool connected () {
		//判断无向图是否连通 
		if (directed ()) {
			cerr << "本图是无向图！" << endl;
			exit (2);
		}

		_reach = new int[_vertex_num + 1];
		for (int i = 1; i <= _vertex_num; i++) {
			_reach[i] = 0;
		}

		dfs (1, _reach, 1); //给邻接于顶点1的可达顶点做标记

		for (int i = 1; i <= _vertex_num; i++) {
			//检查所有顶点是否已做标记
			if (_reach[i] == 0) {
				return false;
			}
		}

		return true;
	}
	void bfs (int v, int reach[], int label) {
		//广度优先算法，reach[i]用来标记所有邻接于顶点v的可到达的顶点 
		queue<int> q;
		reach[v] = label;
		q.push (v);

		until (q.empty ()) {
			int vertex = q.front ();
			q.pop ();

			for (int j = 1; j <= _vertex_num; j++) {
				if (_weights[vertex][j] != _no_edge && reach[j] == 0) {
					q.push (j);
					reach[j] = label;
				}
			}
		}
	}
	void dfs (int v, int _reach[], int _label) {
		_reach = _reach;
		_label = _label;
		_dfs (v);
	}
	int labelComponents (int c[]) {
		//返回连通分支数，c[i]是顶点i所属的分支序号 
		int i = 0;
		for (i = 0; i <= _vertex_num; i++) {
			c[i] = 0;
		}

		int label = 0;  //最后一个构建的编号 
		for (i = 1; i <= _vertex_num; i++) {
			if (c[i] == 0) {
				//对所有未到达的顶点，都进行一次bfs标记 
				label++;
				bfs (i, c, label);  //给新分支做标记 
			}
		}
		return label;
	}
	void print_bfs (int v, int reach[]) {
		fill (reach, reach + _vertex_num + 1, 0);
		int label = 1;
		reach[v] = label;
		queue<int> q;
		q.push (v);

		while (q.empty () != true) {
			int vertex = q.front ();
			cout << vertex << " ";
			q.pop ();

			for (int j = 1; j <= _vertex_num; j++) {
				if (_weights[vertex][j] != _no_edge && reach[j] == 0) {
					q.push (j);	reach[j] = label;
				}
			}
		}
	}
	void print_dfs (int v, int reach[]) {
		stack<int> s (10);  int u;
		memset (reach, 0, sizeof (int) * (_vertex_num + 1));
		reach[v] = _label;
		s.push (v);  cout << v << " ";

		while (!s.empty ()) //当stack不空时 
		{
			int w = s.top ();
			s.pop ();
			myIterator* iv = iterator (w);	  u = iv->next ();
			while (u != 0)  //对上一个到达的点w的所有邻接点 
			{
				if (reach[u] != _label) //如果存在一个未标记的点j 
				{
					reach[u] = _label;
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
	int Dijkstra (int start, int dest, int path[]) {
		//返回最短路长，记录下最短路的路径，predecessor是从start到dest路径中dest前的那个顶点 
		
		int* L = new int[_vertex_num + 1];  //L[i]就是从start点到顶点i的距离 
		for (int i = 1; i <= _vertex_num; i++)  L[i] = _weights[start][i];  L[start] = 0;
		bool* S = new bool[_vertex_num + 1];
		for (int i = 1; i <= _vertex_num; i++)  S[i] = false;  //S[i]表示start到顶点i的最短路已求得 
		for (int i = 1; i <= _vertex_num; i++) {
			path[i] = (L[i] == _no_edge) ?-1 : start;
		}
		path[start] = 0;    //源顶点没有前驱 
		for (int i = 1; i <= _vertex_num; i++) {

			auto Minium = [](int L[], bool S[], int n) {
				//在L[1:n]数组中返回不在顶点集S中最小的元素 
				int min = 100000;
				for (int i = 1; i <= n; i++) {
					if (L[i] < min && S[i] == false) {
						min = L[i];
					}
				}
				return min;
			};

			if (S[i] == false && L[i] == Minium (L, S, _vertex_num)) {
				S[i] = true;  //把u加入顶点集S中

				//重新计算路径长度
				for (int j = 1; j <= _vertex_num; j++) {//对每一个不属于S的顶点v 
					if (S[j] == false && L[i] + _weights[i][j] < L[j]) {
						L[j] = L[i] + _weights[i][j];
						path[j] = i;   //顶点v的前驱是u 
					}
				}
			}
		}
		return L[dest];
	}
	bool kruskal (edge<W>* spanningTreeEdges) {
		//求最小生成树，若该图连通则返回true，且sTE[0:n-2]中存有最小生成树的边 
		//注意，需要用并查集防止回路，每次寻找最小变，形成环就不去查找
		//用堆取得每次最小边

		edge<W>* Edge = new edge<W>[_edge_num + 1];
		int k = 1;  //数组Edge的索引 

		//下面对edge数组初始化：把所有边加入edge数组
		for (int i = 1; i <= _vertex_num; i++) {//取所有关联顶点i的边 
			myIterator* ii = iterator (i);
			int j; W w;
			while ((j = ii->next (w)) != 0) {
				if (i < j) { //避免重复加边 
					Edge[k++] = edge<int> (i, j, w);
				}
			}
		}
		//用小根堆表示边集的效率较好
		minHeap<edge<W>> heap;

		heap.initialize (Edge, _edge_num);  //cout<<heap<<endl;
		fastUnionFind uf (_vertex_num);
		k = 0;  //索引
		while (_edge_num > 0 && k < _vertex_num - 1) {

			//生成树没有完成并且还有边存在 
			edge<W> x = heap.top ();
			heap.pop ();
			_edge_num--;
			int a = uf.find (x.getFrom ());
			int b = uf.find (x.getTo ());
			if (a != b) {//保证在没有环路的情况下选取边x 
				spanningTreeEdges[k++] = x;
				uf.unite (a, b);
			}
		}
		return (k == _vertex_num - 1);
	}
	bool prim (edge<W>* spanningTreeEdges) {
		//spanningTreeEdges是已经入选的边集 
		minHeap<edge<W>> heap;

		bool* TV = new bool[_vertex_num + 1];      //TV是已在树中的顶点集
		for (int i = 1; i <= _vertex_num; i++)
			TV[i] = false;
		TV[1] = true;

		myIterator* i = iterator (1);
		int j;
		W w;

		//对顶点距离进行排序，构建小根堆
		while ((j = i->next (w)) != 0) {
			edge<W> tem (1, j, w);
			heap.push (tem);
		}


		int k = 0;   //表示边集中索引 
		while (!heap.empty () && k < _vertex_num - 1) {
			edge<W> x = heap.top ();  //弹出的边是最小的 
			heap.pop ();
			int a = x.getFrom ();
			int b = x.getTo ();
			if (TV[b] == false) { //这里TV[a]==true 
				spanningTreeEdges[k++] = edge<W> (a, b, x.weight ());
			}
			TV[b] = true;
			i = iterator (b);
			while ((j = i->next (w)) != 0) {
				if (j > b) {
					//保证不重复加入边 
					edge<W> tem (b, j, w);
					heap.push (tem);
				}
			}
		}
		delete[] TV;      //TV是已在树中的顶点集

		return (k == _vertex_num - 1);
	}

};


