#include<iostream>
#include"stack.h"
#include"queue.h"
#include"chain.h"
#include"minHeap.h"
#include"fastUnionFind.h"
#include"edge.h"

using namespace std;

//加权无向图,可称成为同权无向图 
template<class T>
class linkedWGraph {
protected:
	int _vertex_num;                 //顶点数 
	int _edge_num;                 //边数 
	chain<T>* _chain_heads;  //邻接表 
	int* _reach;  //数组指针 
	int _label = 1;

	void _dfs (int _head) {//递归实现深度优先搜索
		_reach[_head] = _label;  int u;
		//cout<<"当前走到顶点："<<v<<endl;
		myIterator* iv = iterator (_head);  //这里加<T>就会报错，为什么？？ 
		while ((u = iv->next ()) != 0) {//以v的下一个邻接点u为新起点递归搜索 
		//cout<<v<<"的下一个邻接点是："<<u<<" "<<endl;
			if (_reach[u] != _label)
				_dfs (u);  //u是一个没有到达过的顶点 
		}
		delete iv;
		return;
	}

public:
	void output (ostream& out) {
		for (int i = 1; i <= _vertex_num; i++) {
			out << "_chain_heads[" << i << "]="; _chain_heads[i].output ();
			out << endl;
		}
	}
	linkedWGraph (int _head) {
		_vertex_num = _head;
		_edge_num = 0;
		_chain_heads = new chain<int>[_vertex_num + 1];
	}
	~linkedWGraph () {
		delete[] _chain_heads;  //这样就会自己调用chain的析构函数吗？ 
	}
	int numberOfVertices () const { return _vertex_num; }
	int numberOfEdges () const { return _edge_num; }
	bool directed () const { return false; }
	bool weight () const { return true; }
	void _checkVertex (int theVertex) const {//确认是有效顶点 
		if (theVertex<1 || theVertex>_vertex_num) {
			cerr << "the vertex:" << theVertex << " is not permissible";
			exit (1);
		} else return;
	}
	void insertEdge (int v1, int v2, int weight) {
		if (v1<1 || v2<1 || v1>_vertex_num || v2>_vertex_num || v1 == v2) {//越界处理 
			cerr << "(" << v1 << "," << v2 << ") is not a permissible edge" << endl;
			exit (1);
		}
		if (_chain_heads[v1].indexOf (v2) == -1) {//新边 
			_chain_heads[v1].insert (0, v2, weight);
			_chain_heads[v2].insert (0, v1, weight);
			_edge_num++;
		}
	}
	void eraseEdge (int i, int j) {
		if (i > 1 && j > 1 && i <= _vertex_num && j <= _vertex_num) {
			int* _head = _chain_heads[i].eraseElement (j);
			int* j = _chain_heads[j].eraseElement (i);  //v,j一定同时为空或者非空，不然说明一致性出了问题 
			if (_head != nullptr && j != nullptr)   _edge_num--;   //该边存在
		}
	}
	int degree (int Vertex) {
		_checkVertex (Vertex);
		return _chain_heads[Vertex].size ();
	}

	class myIterator {
	public:
		myIterator (chain<T>* theVertex) {
			_head = theVertex;
			_current_vertex = _head->_head;
		}
		~myIterator () {}
		int next (T& theWeight) {//返回指定顶点的下一个邻接点的序号和它的的权值 
			if (_current_vertex != nullptr) {
				theWeight = _current_vertex->weight;
				int vertex = _current_vertex->data;
				_current_vertex = _current_vertex->next;
				return vertex;
			} else
				return 0;
		}
		int next () {//返回指定顶点的下一个邻接点 

			if (_current_vertex != nullptr) {
				int vertex = _current_vertex->data;
				_current_vertex = _current_vertex->next;
				return vertex;
			}
			return 0;
		}
	protected:
		chain<T>* _head;    //邻接表的点 
		node<T>* _current_vertex;   //当前搜索的顶点 
	};
	myIterator* iterator (int theVertex) {
		_checkVertex (theVertex);
		return new myIterator (&_chain_heads[theVertex]);
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
			if (_reach[i] == 0) {
				return false;
			}
		}
		return true;
	}

	void bfs (int _head, int _reach[], int label) {//广度优先算法，_reach[i]用来标记所有邻接于顶点v的可到达的顶点 
		queue<int> q (10);
		_reach[_head] = label;
		q.push (_head);

		while (q.empty () != true) {
			int vertex = q.front ();
			q.pop ();

			for (node<int>* u = _chain_heads[vertex]._head; u != nullptr; u = u->next) {
				if (_reach[u->data] == 0) {
					q.push (u->data);	_reach[u->data] = label;
				}
			}
		}
	}

	void dfs (int _head, int _reach[], int label) {
		_reach = _reach;
		label = label;
		_dfs (_head);
	}
	int labelComponents (int c[]) {//返回连通分支数，c[i]是顶点i所属的分支序号 
		int i = 0;
		for (i = 0; i <= _vertex_num; i++)
			c[i] = 0;

		int label = 0;
		for (i = 1; i <= _vertex_num; i++) {
			if (c[i] == 0) {//对所有未到达的顶点，都进行一次bfs标记 
				label++;
				bfs (i, c, label);  //给新分支做标记 
			}
		}
		return label;
	}
	void print_bfs (int _head, int _reach[]) {
		memset (_reach, 0, sizeof (int) * (_vertex_num + 1));
		int label = 1; _reach[_head] = label;
		queue<int> q (10);
		q.push (_head);

		while (q.empty () != true) {
			int vertex = q.front ();
			cout << vertex << " ";
			q.pop ();

			for (node<int>* u = _chain_heads[vertex]._head; u != nullptr; u = u->next) {
				if (_reach[u->data] == 0) {
					q.push (u->data);	_reach[u->data] = label;
				}
			}
		}
	}
	void print_dfs (int _head, int _reach[]) {//使用栈实现的DFS搜索算法 
		stack<int> s (10);  int u;
		memset (_reach, 0, sizeof (int) * (_vertex_num + 1));
		_reach[_head] = _label;
		s.push (_head);  cout << _head << " ";

		while (!s.empty ()) //当栈不空时 
		{
			int w = s.top ();
			s.pop ();
			myIterator* iv = iterator (w);	  u = iv->next ();
			while (u != 0)  //对上一个到达的点w的所有邻接点 
			{
				if (_reach[u] != _label) //如果存在一个未标记的点j 
				{
					_reach[u] = _label;
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
	int Dijkstra (int start, int dest, int predecessor[]) {//返回最短路长，记录下最短路的路径，predecessor是从start到dest路径中dest前的那个顶点 
		int* L = new int[_vertex_num + 1];  //L[i]就是从start点到顶点i的距离 
		for (int i = 1; i <= _vertex_num; i++) {
			L[i] = 100000;  predecessor[i] = -1;
		}   L[start] = 0;
		for (node<int>* u = _chain_heads[start]._head; u != nullptr; u = u->next) {
			L[u->data] = u->weight;
			predecessor[u->data] = start;  //对于start邻接的点 
		}
		predecessor[start] = 0;    //源顶点没有前驱  
		bool* S = new bool[_vertex_num + 1];
		for (int i = 1; i <= _vertex_num; i++)  S[i] = false;  //S[i]表示start到顶点i的最短路已求得 

		/*…………以上是初始化操作…………*/

		while (S[dest] != true) {/*下面找一个不在顶点集S中的u且L[u]标号最小，可以借助一下线性表吗？*/
			int u, tag;
			for (u = 1; u <= _vertex_num; u++) {
				auto Minium = [](int L[], bool S[], int _vertex_num) {//在L[1:n]数组中返回不在顶点集S中最小的元素 
					int min = 100000;
					for (int i = 1; i <= _vertex_num; i++) {
						if (L[i] < min && S[i] == false)
							min = L[i];
					}
					return min;
				};
				if (S[u] == false && L[u] == Minium (L, S, _vertex_num))  //这里找一个不在顶点集S且标号最小的点，复杂度可以降到O(1)吗？ 
				{                                        //按我的写法复杂度好像是O(n^3)，可以通过把两个循环判断条件糅合来降低复杂度嘛？ 
					S[u] = true;  //把u加入顶点集S中
					tag = u;
					break;
				}
			}

			for (node<int>* u = _chain_heads[tag]._head; u != nullptr; u = u->next) {//遍历刚找到的点的邻接点,如果它没有被访问过，且距离可被更新
			  //这样写，复杂度是O(链表长)，较好 
				if (S[u->data] == false && L[tag] + (u->weight) < L[u->data]) {
					L[u->data] = L[tag] + u->weight;
					predecessor[u->data] = tag;    //顶点v的前驱是u 
				}
			}
		}
		return L[dest];
	}

	bool kruskal (edge<T>* spanningTreeEdges) {
		//求最小生成树，若该图连通则返回true，且sTE[0:n-2]中存有最小生成树的边 
		edge<T>* Edge = new edge<T>[_edge_num + 1];
		int k = 1;  //数组Edge的索引 

		//下面对edge数组初始化：把所有边加入edge数组
		for (int i = 1; i <= _vertex_num; i++) {//取所有关联顶点i的边 
			myIterator* ii = iterator (i);
			int j; T w;
			while ((j = ii->next (w)) != 0) {
				if (i < j)    //避免重复加边 
				{
					Edge[k++] = edge<int> (i, j, w);
				}
			}
		}
		//用小根堆表示边集的效率较好
		minHeap<edge<T> > heap (1);
		heap.initialize (Edge, _edge_num);  //cout<<heap<<endl;
		fastUnionFind uf (_vertex_num);
		k = 0;  //索引
		while (_edge_num > 0 && k < _vertex_num - 1) {//生成树没有完成并且还有边存在 
			edge<T> x = heap.getTop ();
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
	bool Prim (edge<T>* spanningTreeEdges) {//spanningTreeEdges是已经入选的边集 
		int e = this->_edge_num;
		minHeap< edge<T> > heap;

		bool* TV = new bool[_vertex_num + 1];      //TV是已在树中的顶点集
		for (int i = 1; i <= _vertex_num; i++)
			TV[i] = false;
		TV[1] = true;

		myIterator* i = iterator (1);
		int j;  T w;
		while ((j = i->next (w)) != 0) {
			edge<T> tem (1, j, w);
			heap.push (tem);
		}


		int k = 0;   //表示边集中索引 
		while (!heap.empty () && k < _vertex_num - 1) {
			edge<T> x = heap.getTop ();  //弹出的边是最小的 
			heap.pop ();
			int a = x.getFrom ();
			int b = x.getTo ();
			if (TV[b] == false)  //这里TV[a]==true 
				spanningTreeEdges[k++] = edge<T> (a, b, x.getWeight ());
			TV[b] = true;
			i = iterator (b);
			while ((j = i->next (w)) != 0) {
				if (j > b)  //保证不重复加入边 
				{
					edge<T> tem (b, j, w);
					heap.push (tem);
				}
			}
		}
		delete[] TV;      //TV是已在树中的顶点集

		return (k == _vertex_num - 1);

	}

};
