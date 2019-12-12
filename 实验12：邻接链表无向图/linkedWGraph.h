#include<iostream>
#include"stack.h"
#include"queue.h"
#include"chain.h"
#include"minHeap.h"
#include"fastUnionFind.h"
#include"edge.h"
#define until(re) while(!(re))

using namespace std;

//邻接链表加权无向图
template<class T>
class linkedWGraph {
protected:
	int _vertex_num;			//总顶点数 
	int _edge_num;				//总边数 
	chain<T>* _chain_heads;		//链表数组
	int* visited;				//作为递归遍历时的标记
	int _label = 1;				//默认标记

	//递归深度优先搜索
	void _dfs (int head) {
		visited[head] = _label;

		int u;
		myIterator* iv = iterator (head);

		//对该结点的后继结点进行遍历
		while ((u = iv->moveNext ()) != 0) {
			if (visited[u] != _label)
				_dfs (u);
		}

		delete iv;
		return;
	}
	void _checkVertex (int theVertex) const {//确认是有效顶点 
		if (theVertex<1 || theVertex>_vertex_num) {
			cerr << "the vertex:" << theVertex << " is not permissible";
			exit (1);
		} else return;
	}
public:

	//输出所有链表
	void output (ostream& out) {
		for (int i = 1; i <= _vertex_num; i++) {
			out << "_chain_heads[" << i << "]="; _chain_heads[i].output ();
			out << endl;
		}
	}

	//初始化
	linkedWGraph (int vnum) {
		_vertex_num = vnum;
		_edge_num = 0;
		_chain_heads = new chain<int>[_vertex_num + 1];
	}
	//析构
	~linkedWGraph () {
		delete[] _chain_heads;  //这样就会自己调用chain的析构函数吗？ 
	}
	int numberOfVertices () const { return _vertex_num; }
	int numberOfEdges () const { return _edge_num; }
	bool directed () const { return false; }
	bool weight () const { return true; }
	void insertEdge (int v1, int v2, int weight) {
		if (v1<1 || v2<1 || v1>_vertex_num || v2>_vertex_num || v1 == v2) {//越界处理 
			cerr << "(" << v1 << "," << v2 << ") is not a permissible edge" << endl;
			exit (1);
		}

		//若此边不存在，则插入
		if (_chain_heads[v1].indexOf (v2) == -1) {
			_chain_heads[v1].insertAfterIndex (0, v2, weight);
			_chain_heads[v2].insertAfterIndex (0, v1, weight);
			_edge_num++;
		}
	}
	void eraseEdge (int i, int j) {
		if (i > 1 && j > 1 && i <= _vertex_num && j <= _vertex_num) {
			int* _head = _chain_heads[i].eraseByElement (j);
			int* j = _chain_heads[j].eraseByElement (i);

			//v,j一定同时为空或者非空，不然说明一致性出了问题 
			if (_head != nullptr && j != nullptr) {
				_edge_num--;//该边存在
			}
		}
	}

	//返回一个结点的后继结点数
	int degree (int Vertex) {
		_checkVertex (Vertex);
		return _chain_heads[Vertex].size ();
	}

	class myIterator {
	protected:
		chain<T>* _head; //邻接表的点 
		node<T>* _current_vertex;//当前搜索的顶点 
	public:
		myIterator (chain<T>* theVertex) {
			_head = theVertex;
			_current_vertex = _head->_head;
		}
		~myIterator () {}
		//移动到下一个结点，返回索引，修改权重
		int moveNext (T& theWeight) {
			if (_current_vertex != nullptr) {
				theWeight = _current_vertex->weight;
				int vertex = _current_vertex->data;
				_current_vertex = _current_vertex->next;
				return vertex;
			} else {
				return 0;
			}
		}
		int moveNext () {
			//返回指定顶点的下一个结点的索引，迭代器也自动前移
			if (_current_vertex != nullptr) {
				int vertex = _current_vertex->data;
				_current_vertex = _current_vertex->next;
				return vertex;
			}
			return 0;
		}
	};
	myIterator* iterator (int theVertex) {
		_checkVertex (theVertex);
		return new myIterator (&_chain_heads[theVertex]);
	}

	//判断无向图是否连通 
	bool connected () {

		visited = new int[_vertex_num + 1];
		for (int i = 1; i <= _vertex_num; i++) {
			visited[i] = 0;
		}

		//给邻接于顶点1的可达顶点做标记
		dfs (1, visited, 1);

		//检查所有顶点是否已做标记，全标记为连通，否则不连通
		for (int i = 1; i <= _vertex_num; i++) {
			if (visited[i] == 0) {
				return false;
			}
		}
		return true;
	}

	//广度优先算法，_reach[i]用来标记所有邻接于顶点v的可到达的顶点 
	void bfs (int _head, int visited[], int label) {
		queue<int> q (10);
		visited[_head] = label;
		q.push (_head);

		while (q.empty () != true) {
			int vertex = q.front ();
			q.pop ();

			for (node<int>* u = _chain_heads[vertex]._head; u != nullptr; u = u->next) {
				if (visited[u->data] == 0) {
					q.push (u->data);	visited[u->data] = label;
				}
			}
		}
	}

	void dfs (int _head, int visited[], int label) {
		visited = visited;
		label = label;
		_dfs (_head);
	}

	//返回连通分支数，lables[i]是顶点i所属的分支序号 
	int getCC (int* lables) {
		int i = 0;

		//这里，lable不仅代表连通分支标记，还代表连通分支数
		int label = 0;
		for (i = 1; i <= _vertex_num; i++) {
			if (lables[i] == 0) {//对所有未到达的顶点，都进行一次bfs标记 
				label++;
				bfs (i, lables, label);  //给新分支做标记 
			}
		}

		return label;
	}
	void printBfs (int start) {
		bool* visited = new bool[_vertex_num + 1];
		memset (visited, 0, sizeof (bool) * (_vertex_num + 1));
		visited[start] = true;
		queue<int> q (10);
		q.push (start);

		while (q.empty () != true) {
			int vertex = q.front ();
			cout << vertex << " ";
			q.pop ();

			for (node<int>* u = _chain_heads[vertex]._head; u != nullptr; u = u->next) {
				if (visited[u->data] == 0) {
					q.push (u->data);
					visited[u->data] = true;
				}
			}
		}
	}

	//打印DFS遍历
	void printDfs (int start) {
		stack<int> s;
		bool* visited = new bool[_vertex_num + 1];
		memset (visited, 0, sizeof (bool) * (_vertex_num + 1));
		visited[start] = true;
		s.push (start);
		cout << start << " ";

		until (s.empty ()) {
			int cur = s.top ();
			s.pop ();
			myIterator* iv = iterator (cur);
			int u = iv->moveNext ();
			while (u != 0) {
				if (visited[u] != true) {
					visited[u] = true;
					s.push (u);
					cout << u << " ";
				}
				//迭代器前进
				u = iv->moveNext ();
			}
		}
	}


	int dijkstra (int start, int dest, int pre[]) {
		//返回最短路长，记录下最短路的路径，pre是从start到dest路径中dest前的那个顶点 

		//L[i]就是从start点到顶点i的距离 
		int* L = new int[_vertex_num + 1];
		fill (L, L + _vertex_num + 1, 100000);
		L[start] = 0;

		//设置初始距离与初始前驱结点
		for (node<int>* u = _chain_heads[start]._head; u != nullptr; u = u->next) {
			L[u->data] = u->weight;
			pre[u->data] = start;  //对于start邻接的点 
		}
		pre[start] = 0; //源顶点没有前驱 

		//设置访问记录表
		bool* S = new bool[_vertex_num + 1];
		fill (S, S + _vertex_num + 1, false);

		until (S[dest] == true) {
			int u, temp_head;
			//获得最短距离的函数
			auto getMinDis = [](int L[], bool S[], int _vertex_num) {
				int min = 100000;
				for (int i = 1; i <= _vertex_num; i++) {
					if (L[i] < min && S[i] == false)
						min = L[i];
				}
				return min;
			};
			int min_dis = getMinDis (L, S, _vertex_num);
			//找到距离起点最近的那个结点，加入到S集合
			for (u = 1; u <= _vertex_num; u++) {
				if (S[u] == false && L[u] == min_dis) {
					S[u] = true;
					temp_head = u;
					break;
				}
			}
			
			//遍历刚找到的点的邻接点,如果它没有被访问过，且距离可被更新，则更新距离
			for (node<int>* u = _chain_heads[temp_head]._head; u != nullptr; u = u->next) {
				if (S[u->data] == false && L[temp_head] + (u->weight) < L[u->data]) {
					L[u->data] = L[temp_head] + u->weight;
					pre[u->data] = temp_head; //顶点v的前驱是u 
				}
			}
		}
		return L[dest];
	}

	//针对边，适用于稀疏矩阵的k算法
	bool kruskal (edge<T>* spanningTreeEdges) {
		//用小根堆表示边集的效率较好,此处初始化所有边集合
		minHeap<edge<T> > heap;
		for (int i = 1; i <= _vertex_num; i++) {
			myIterator* ii = iterator (i);
			int j;
			T w;
			while ((j = ii->moveNext (w)) != 0) {
				if (i < j){//判断去重
					heap.push (edge<int> (i, j, w));
				}
			}
		}

		//并查集避免环路，并查集，unite为列为集合，find查找集合的编号
		fastUnionFind uf (_vertex_num);
		int k = 0;  //索引
		while (_edge_num > 0 && k < _vertex_num - 1) {//生成树没有完成并且还有边存在 
			edge<T> x = heap.getTop ();
			heap.pop ();
			_edge_num--;
			int seta = uf.find (x.getFrom ());
			int setb = uf.find (x.getTo ());
			if (seta != setb) {//保证在没有环路的情况下选取边x 
				spanningTreeEdges[k++] = x;
				uf.unite (seta, setb);
			}
		}
		return (k == _vertex_num - 1);
	}

	//使用小根堆的prim算法，适用于边多的图
	bool prim (edge<T>* spanningTreeEdges) { 
		//初始化小根堆，注意跟k不同，这里堆里存的不是所有边，而是当前集合到另一个集合所有点的直接距离
		minHeap< edge<T> > heap;
		myIterator* i = iterator (1);
		int j;  T w;
		while ((j = i->moveNext (w)) != 0) {
			edge<T> tem (1, j, w);
			heap.push (tem);
		}

		bool* S = new bool[_vertex_num + 1];//TV是已在树中的顶点集
		fill (S,S+ _vertex_num + 1,false);
		S[1] = true;
		

		int k = 0;
		while (!heap.empty () && k < _vertex_num - 1) {
			//添加一个点到S集合
			edge<T> x = heap.getTop ();
			heap.pop ();
			int a = x.getFrom ();
			int b = x.getTo ();
			if (S[b] == false) {
				spanningTreeEdges[k++] = edge<T> (a, b, x.getWeight ());
			}
			S[b] = true;
			
			
			//更新堆，注意去重
			heap._clearAndInit ();
			for (int i = 1; i <= _vertex_num; i++) {
				if (S[i] == true) {
					myIterator* cur = iterator (i);
					while ((j = cur->moveNext (w)) != 0) {
						if ( S[j]!=true) {
							edge<T> tem (i, j, w);
							heap.push (tem);
						}
					}
				}
			}

		}

		delete[] S;
		return (k == _vertex_num - 1);
	}

};
