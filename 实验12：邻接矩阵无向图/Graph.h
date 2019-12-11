#ifndef GRAPH_H
#define GRAPH_H
#define until(re) while(!(re))
#include<set>
#include<queue>
#include <iostream>
using namespace std;

const int MAX_VERTEX_NUM = 20;                      //һ�����ͼ����󶥵���(vertex:����)
const int MAX_WEIGHT = 10000;                       //���ֵ


template <class T, class E>//TΪ����ֵ�����ͣ�EΪȨֵ������
class Graph {
public:
	Graph (int thistype = 1, int sz = MAX_VERTEX_NUM);	//�ڽӾ���0���ޱߣ�MAX_WEIGHT�����Լ��Ĺ�ϵ��typeΪ1������ͼ��typeΪ2������ͼ��Ĭ������ͼ����
	~Graph ();

	friend istream& operator>>(istream& in, Graph<T, E>& G)//����
	{
		int i, n, m;
		T e1, e2;
		cout << "�����붥�����ͱ�����";
		in >> n >> m;//���붥�����ͱ���
		cout << endl << "������" << n << "�����㣺";
		for (i = 0; i < n; i++) {
			in >> e1;
			G.insertVertex (e1);
		}
		cout << endl << "������" << m << "���ߣ�";
		i = 0;
		while (i < m) {
			in >> e1 >> e2;
			if (G.insert_edges (e1, e2)) { i++; } else cout << "�����˵���Ϣ�����������룡" << endl;
		}
		return in;
	}

	friend ostream& operator<<(ostream& out, Graph<T, E>& G) {
		//TODO:��������غ��������ڹ��캯����type�޷�ʹ�ã�ʹ������ͼ������ͼ�޷�ֱ�ӿ���
		cout << "\n\n";
		int i, j, n, m;//����ͼ
		T e1, e2;
		E w;
		n = G.NumberOfVertices ();
		m = G.NumberOf_edgess ();
		out << n << ',' << m << endl;
		for (i = 0; i < n; i++)
			for (j = i + 1; j < n; j++) {
				w = G.getWeight (i, j);
				if (w > 0 && w < MAX_WEIGHT) {
					e1 = G.getValue (i);
					e2 = G.getValue (j);
					out << "(" << e1 << "," << e2 /*<< "," << w */ << ")" << endl;
				}
			}
		return out;

	}

	bool GraphEmpty ()const;							//�ж�ͼ�շ�
	int NumberOfVertices ();							//���ض�����
	int NumberOf_edgess ();							//���ر���
	E getWeight (int v1, int v2);					//ȡ��v1,v2��Ȩֵ
	T getValue (int i);								//ȡλ��i��ֵ����������0
	int getFirstNeighbor (T k);                      //ȡ����Ϊk�ĵ�һ���ڽӽڵ�
	int getFirstNeighbor (int k, char type);          //ȡ����λ��Ϊk�ĵ�һ���ڽӽڵ�
	int getNextNeighbor (int k, int w);				//ȡ����Ϊk���ڽӶ���λ��w����һ���ڽӶ���λ�ã��±궨λ���㣩
	int getNextNeighbor (T k, int w, char type);		//ȡ����λ��Ϊk���ڽӶ���λ��w����һ���ڽӶ���λ��(�������ݶ�λ���㣩
	bool insertVertex (const T& vertex);				//����һ������
	bool insert_edges (T n1, T n2, E cost = 1);		//�����(n1,n2)��ȨֵΪcost����ֻ��һ�������ɸ��ǣ��ظ�������ͬ�ߡ�����������Լ����Լ��ı�
	bool removeVertex (T v1);						//ɾ������v1����֮��صıߡ���ɾ�����һ�����㡣
	bool remove_edges (T n1, T n2);					//ɾ���ߣ�n1,n2��
	int outdegree (T v);								//����(����ͼ���ȵ�����ȣ�
	int indegree (T v);								//���
	void DFS (const T& v);
	void BFS (const T& v);             //��ȱ�������v��ʼ
	void shortestPaths (int sourceVertex,int target) {
		const int INF = 1000000000;
		int* pre = new int[numberVertices];
		int* dis=new int[numberVertices];
		bool* vis=new bool[numberVertices];
		fill (dis, dis + numberVertices, INF);
		fill (pre, pre + numberVertices, 0);
		fill (vis, vis + numberVertices, 0);
		dis[sourceVertex] = 0;

		for (int i = 0; i < numberVertices; i++) {
			int u = -1, MIN = INF;

			for (int j = 0; j < numberVertices; j++) {
				if (vis[j] == false && dis[j] < MIN) {
					u = j;
					MIN = dis[j];
				}
			}

			if (u == -1) return;

			vis[u] = true;
			for (int v = 0; v < numberVertices; v++) {
				if (vis[v] == false && _edges[u][v] != INF && dis[u] + _edges[u][v] < dis[v]) {
					dis[v] = _edges[u][v] + dis[u];
					pre[v] = u;
				}
			}



		}

		int v = target;
		cout << v << "<-";
		do  {
			cout << pre[v]<<"<-";
			v = pre[v];
		}until (sourceVertex == v);
		//cout << sourceVertex;
	}

	bool isCC () {
		auto getCCByP = [&](int i) {
			set<int> all_point;
			bool iscc = false;

			int thisvisited[MAX_VERTEX_NUM] = { 0 };
			//ʹ��pos�ṹ���ʾһ��״̬
			//cur��ʾ��ǰ�������Ľ��
			//from��ʾ�Ӵ��ĸ������ʵ��˵�ǰ��� ����ֵ���ڷ�ֹ��һ��·��һ��һ����ɴ���ġ���·��

			typedef struct pos {
				int from;
				int cur;
				pos (int fromi, int toi) :from (fromi), cur (toi) {

				}
			} pos;
			queue<pos> q;  //�����ʶ���
			q.push (pos (0, i));
			thisvisited[i] = 1;
			all_point.insert (i);

			while (!q.empty ()) {
				pos cur_pos = q.front ();
				q.pop ();
				for (int i = 1; i <= numberVertices; i++) {
					//�����������ڵģ�����Դ���Ľ��
					if (_edges[cur_pos.cur][i] != 0 && i != cur_pos.from) {
						if (thisvisited[i] == 1) {
							iscc = true;
						} else {
							q.push (pos (cur_pos.cur, i));
							all_point.insert (i);
							thisvisited[i] = 1;
						}
					}
				}
			}
			return all_point;
		};

		auto points = getCCByP (0);
		if (points.size () != numberVertices) {
			return false;
		} else {
			return true;
		}
	}
	void outAllConnectedComponents (ostream& out) {
		int allvisited[MAX_VERTEX_NUM] = { 0 };
		auto getCCByP = [&](int i) {
			set<int> all_point;
			if (allvisited[i]) {
				return all_point;
			}
			bool iscc = false;

			int thisvisited[MAX_VERTEX_NUM] = { 0 };
			//ʹ��pos�ṹ���ʾһ��״̬
			//cur��ʾ��ǰ�������Ľ��
			//from��ʾ�Ӵ��ĸ������ʵ��˵�ǰ��� ����ֵ���ڷ�ֹ��һ��·��һ��һ����ɴ���ġ���·��

			typedef struct pos {
				int from;
				int cur;
				pos (int fromi, int toi) :from(fromi), cur (toi){

				}
			} pos;
			queue<pos> q;  //�����ʶ���
			q.push (pos (0, i));
			thisvisited[i] = 1;
			allvisited[i] = 1;
			all_point.insert (i);

			while (!q.empty ()) {
				pos cur_pos = q.front ();
				q.pop ();
				for (int i = 1; i <= numberVertices; i++) {
					//�����������ڵģ�����Դ���Ľ��
					if (_edges[cur_pos.cur][i] != 0 && i != cur_pos.from) {
						if (thisvisited[i] == 1) {
							iscc= true;
						} else {
							q.push (pos (cur_pos.cur, i));
							all_point.insert (i);
							thisvisited[i] = 1;
							allvisited[i] = 1;


						}
					}
				}
			}
			return all_point;
		};
	vector<set<int>> all;
	int nums = 0;

	for (int i = 0; i < numberVertices; i++) {
		auto items = getCCByP (i);
		if (!items.empty()) {
			all.push_back (items);
			nums++;
		}

	}
	cout << nums << "\n";
	for (auto&& item : all) {
		cout << "{ ";
		for (auto&& i : item) {
			cout << i << " ";
		}
		cout << " }\n";
	}
}

private:
	int type;										//typeΪ1������ͼ��typeΪ2������ͼ

	int maxVertices;								//ͼ����󶥵���
	int number_edgess;								//��ǰ����
	int numberVertices;								//��ǰ������

	T* VerticesList;								//������޳�ʼ������maxVertices����ʹ��
	E** _edges;										//�ڽӾ��󡣳�ʼ����0λ�ޱߣ�MAX_WEIGHT�����Լ��Ĺ�ϵnumberVertices

	int getVertexPos (T vertex);						//��������vertex��ͼ�е�λ��
	void DFS (Graph& G, int v, bool visited[]);
};



template<class T, class E>
Graph<T, E>::Graph (int thistype, int sz) {
	type = thistype;
	maxVertices = sz;
	number_edgess = 0;
	numberVertices = 0;

	int i, j;
	VerticesList = new T[maxVertices];//�������������
	_edges = (E**)new E * [maxVertices];//�����ڽӾ�������  (E**)Ϊ��ʽת�����ɲ���
	for (i = 0; i < maxVertices; i++) {
		_edges[i] = new E[maxVertices];
	}
	for (i = 0; i < maxVertices; i++)
		for (j = 0; j < maxVertices; j++) {
			_edges[i][j] = (i == j) ? MAX_WEIGHT : 0;//�������Լ��ıߵ�Ȩֵ���޴�
		}
}

template<class T, class E>
Graph<T, E>::~Graph () {
	delete[]VerticesList;
	delete[]_edges;
}

template<class T, class E>
bool Graph<T, E>::GraphEmpty () const {
	if (number_edgess == 0)return true;
	else return false;
}

template<class T, class E>
int Graph<T, E>::NumberOfVertices () {
	return numberVertices;
}

template<class T, class E>
int Graph<T, E>::NumberOf_edgess () {
	return number_edgess;
}

template<class T, class E>
E Graph<T, E>::getWeight (int v1, int v2) {
	return v1 != -1 && v2 != -1 ? _edges[v1][v2] : 0;
}

template<class T, class E>
T Graph<T, E>::getValue (int i) {
	return i >= 0 && i <= numberVertices ? VerticesList[i] : NULL;
}

template<class T, class E>
int Graph<T, E>::getFirstNeighbor (T k) {
	int v = getVertexPos (k);
	if (v != -1) {
		for (int i = 0; i < numberVertices; i++)
			if (_edges[v][i] != 0 && _edges[v][i] != MAX_WEIGHT)return i;
	}
	return -1;
}

template<class T, class E>
int Graph<T, E>::getFirstNeighbor (int k, char type) {
	int v = k;
	if (v != -1) {
		for (int i = 0; i < numberVertices; i++)
			if (_edges[v][i] != 0 && _edges[v][i] != MAX_WEIGHT)return i;
	}
	return -1;
}

template<class T, class E>
int Graph<T, E>::getNextNeighbor (int k, int w) {
	if (k != -1 && w != -1) {
		for (int i = w + 1; i < numberVertices; i++)
			if (_edges[k][i] > 0 && _edges[k][i] < MAX_WEIGHT)return i;
	}
	return -1;
}

template<class T, class E>
int Graph<T, E>::getNextNeighbor (T k, int w, char t) {
	int v = getVertexPos (k);
	if (v != -1 && w != -1) {
		for (int i = w + 1; i < numberVertices; i++)
			if (_edges[v][i] > 0 && _edges[v][i] < MAX_WEIGHT)return i;
	}
	return -1;
}

template<class T, class E>
bool Graph<T, E>::insertVertex (const T& vertex) {
	if (numberVertices == maxVertices)return false;
	VerticesList[numberVertices++] = vertex;
	return true;
}

template<class T, class E>
bool Graph<T, E>::insert_edges (T n1, T n2, E cost) {
	if (type == 1) {
		if (cost > MAX_WEIGHT)return false;//Ȩֵ�������ޣ�����ʧ��
		int v1 = getVertexPos (n1);
		int v2 = getVertexPos (n2);
		if (v1 > -1 && v1 < numberVertices && v2 > -1 && v2 < numberVertices && _edges[v1][v2] == 0) {
			_edges[v1][v2] = cost;
			_edges[v2][v1] = cost;
			number_edgess++;
			return true;
		} else return false;
	} else {
		if (cost > MAX_WEIGHT)return false;//Ȩֵ�������ޣ�����ʧ��
		int v1 = getVertexPos (n1);
		int v2 = getVertexPos (n2);
		if (v1 > -1 && v1<numberVertices && v2>-1 && v2 < numberVertices && _edges[v1][v2] == 0) {
			_edges[v1][v2] = cost;
			number_edgess++;
			return true;
		} else return false;
	}
}

template<class T, class E>
bool Graph<T, E>::removeVertex (T v1) {
	if (type == 1) {
		int v = getVertexPos (v1);
		if (v < 0 || v >= numberVertices)return false;//v1����ͼ�У���ɾ��
		int i;
		VerticesList[v] = VerticesList[numberVertices - 1];//�ö�������һ��Ԫ�ش����ɾ��Ԫ��
		for (i = 0; i < numberVertices; i++)//ɾ��ָ��v1�ı�
		{
			if (_edges[i][v] > 0 && _edges[i][v] < MAX_WEIGHT)number_edgess--;
			_edges[i][v] = _edges[i][numberVertices - 1];
			_edges[i][numberVertices - 1] = 0;
		}
		for (i = 0; i < numberVertices - 1; i++)//ɾ��v1ָ���ı�
		{
			_edges[v][i] = _edges[numberVertices - 1][i];
			_edges[numberVertices - 1][i] = 0;
		}
		numberVertices--;
		return true;
	} else {
		int v = getVertexPos (v1);
		if (v < 0 || v >= numberVertices)return false;//v1����ͼ�У���ɾ��
		int i;
		VerticesList[v] = VerticesList[numberVertices - 1];//�ö�������һ��Ԫ�ش����ɾ��Ԫ��
		for (i = 0; i < numberVertices; i++)//ɾ��ָ��v1�ı�
		{
			if (_edges[i][v] > 0 && _edges[i][v] < MAX_WEIGHT)number_edgess--;
			_edges[i][v] = _edges[i][numberVertices - 1];
			_edges[i][numberVertices - 1] = 0;
		}
		for (i = 0; i < numberVertices - 1; i++)//ɾ��v1ָ���ı�
		{
			if (_edges[v][i] > 0 && _edges[v][i] < MAX_WEIGHT)number_edgess--;
			_edges[v][i] = _edges[numberVertices - 1][i];
			_edges[numberVertices - 1][i] = 0;
		}
		numberVertices--;
		return true;
	}
}

template<class T, class E>
bool Graph<T, E>::remove_edges (T n1, T n2) {
	if (type == 1) {
		int v1 = getVertexPos (n1);
		int v2 = getVertexPos (n2);
		if (v1 > -1 && v1<numberVertices && v2>-1 && v2 < numberVertices && _edges[v1][v2] != 0 && _edges[v1][v2] != MAX_WEIGHT) {
			_edges[v1][v2] = 0;
			_edges[v2][v1] = 0;
			number_edgess--;
			return true;
		} else return false;
	} else {
		int v1 = getVertexPos (n1);
		int v2 = getVertexPos (n2);
		if (v1 > -1 && v1<numberVertices && v2>-1 && v2 < numberVertices && _edges[v1][v2] != 0 && _edges[v1][v2] != MAX_WEIGHT) {
			_edges[v1][v2] = 0;
			number_edgess--;
			return true;
		} else return false;
	}
}

template<class T, class E>
int Graph<T, E>::outdegree (T v) {
	int k = 0;
	int n = getVertexPos (v);
	for (int i = 0; i < maxVertices; i++) {
		if (_edges[n][i] != 0 && _edges[n][i] != MAX_WEIGHT)k++;
	}
	return k;
}

template<class T, class E>
int Graph<T, E>::indegree (T v) {
	int k = 0;
	int n = getVertexPos (v);
	for (int i = 0; i < maxVertices; i++) {
		if (_edges[i][n] != 0 && _edges[i][n] != MAX_WEIGHT)k++;
	}
	return k;
}

template<class T, class E>
int Graph<T, E>::getVertexPos (T vertex) {
	for (int i = 0; i < numberVertices; i++) {
		if (VerticesList[i] == vertex)return i;
	}
	return -1;
}

template<class T, class E>
void Graph<T, E>::DFS (const T& v) {
	Graph<T, E>& G = *this;
	int i, loc, n = G.NumberOfVertices ();
	bool* visited = new bool[n];
	for (i = 0; i < n; i++)visited[i] = false;
	loc = G.getVertexPos (v);
	DFS (G, loc, visited);
	delete[] visited;
}

template<class T, class E>
void Graph<T, E>::DFS (Graph<T, E>& G, int v, bool visited[]) {
	cout << G.getValue (v) << ',';
	visited[v] = true;
	int w = G.getFirstNeighbor (G.getValue (v));
	while (w != -1) {
		if (visited[w] == false) {
			DFS (G, w, visited);
		}
		w = G.getNextNeighbor (v, w);
	}
}

template<class T, class E>
void Graph<T, E>::BFS (Graph<T, E>& G, const T& v) {
	int i, m, n = G.NumberOfVertices ();
	bool* visite = new bool[n];
	for (i = 0; i < n; i++)visite[i] = false;
	int loc = G.getVertexPos (v);
	cout << G.getValue (loc) << ' ';
	visite[loc] = true;
	queue<int> Q;           //��ĳ���±�
	Q.push (loc);            //��������У�ʵ�ֲַ����
	while (!Q.empty ()) {
		m = G.getFirstNeighbor (Q.front (), '1');
		for (; m != -1;)//��������������ڽӽڵ������
		{
			if (!visite[m]) {
				Q.push (m);
				visite[m] = true;
			}
			m = G.getNextNeighbor (Q.front (), m);
		}
		Q.pop ();
		if (!Q.empty ()) {
			cout << G.getValue (Q.front ()) << ' ';
		}
	}
}

#endif // GRAPH_H
