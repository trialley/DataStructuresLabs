#include<iostream>
#include"stack.h"
#include"queue.h"
#include"chain.h"
#include"minHeap.h"
#include"fastUnionFind.h"
#include"edge.h"
#define until(re) while(!(re))

using namespace std;

//�ڽ������Ȩ����ͼ
template<class T>
class linkedWGraph {
protected:
	int _vertex_num;			//�ܶ����� 
	int _edge_num;				//�ܱ��� 
	chain<T>* _chain_heads;		//��������
	int* visited;				//��Ϊ�ݹ����ʱ�ı��
	int _label = 1;				//Ĭ�ϱ��

	//�ݹ������������
	void _dfs (int head) {
		visited[head] = _label;

		int u;
		myIterator* iv = iterator (head);

		//�Ըý��ĺ�̽����б���
		while ((u = iv->moveNext ()) != 0) {
			if (visited[u] != _label)
				_dfs (u);
		}

		delete iv;
		return;
	}
	void _checkVertex (int theVertex) const {//ȷ������Ч���� 
		if (theVertex<1 || theVertex>_vertex_num) {
			cerr << "the vertex:" << theVertex << " is not permissible";
			exit (1);
		} else return;
	}
public:

	//�����������
	void output (ostream& out) {
		for (int i = 1; i <= _vertex_num; i++) {
			out << "_chain_heads[" << i << "]="; _chain_heads[i].output ();
			out << endl;
		}
	}

	//��ʼ��
	linkedWGraph (int vnum) {
		_vertex_num = vnum;
		_edge_num = 0;
		_chain_heads = new chain<int>[_vertex_num + 1];
	}
	//����
	~linkedWGraph () {
		delete[] _chain_heads;  //�����ͻ��Լ�����chain������������ 
	}
	int numberOfVertices () const { return _vertex_num; }
	int numberOfEdges () const { return _edge_num; }
	bool directed () const { return false; }
	bool weight () const { return true; }
	void insertEdge (int v1, int v2, int weight) {
		if (v1<1 || v2<1 || v1>_vertex_num || v2>_vertex_num || v1 == v2) {//Խ�紦�� 
			cerr << "(" << v1 << "," << v2 << ") is not a permissible edge" << endl;
			exit (1);
		}

		//���˱߲����ڣ������
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

			//v,jһ��ͬʱΪ�ջ��߷ǿգ���Ȼ˵��һ���Գ������� 
			if (_head != nullptr && j != nullptr) {
				_edge_num--;//�ñߴ���
			}
		}
	}

	//����һ�����ĺ�̽����
	int degree (int Vertex) {
		_checkVertex (Vertex);
		return _chain_heads[Vertex].size ();
	}

	class myIterator {
	protected:
		chain<T>* _head; //�ڽӱ�ĵ� 
		node<T>* _current_vertex;//��ǰ�����Ķ��� 
	public:
		myIterator (chain<T>* theVertex) {
			_head = theVertex;
			_current_vertex = _head->_head;
		}
		~myIterator () {}
		//�ƶ�����һ����㣬�����������޸�Ȩ��
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
			//����ָ���������һ������������������Ҳ�Զ�ǰ��
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

	//�ж�����ͼ�Ƿ���ͨ 
	bool connected () {

		visited = new int[_vertex_num + 1];
		for (int i = 1; i <= _vertex_num; i++) {
			visited[i] = 0;
		}

		//���ڽ��ڶ���1�Ŀɴﶥ�������
		dfs (1, visited, 1);

		//������ж����Ƿ�������ǣ�ȫ���Ϊ��ͨ��������ͨ
		for (int i = 1; i <= _vertex_num; i++) {
			if (visited[i] == 0) {
				return false;
			}
		}
		return true;
	}

	//��������㷨��_reach[i]������������ڽ��ڶ���v�Ŀɵ���Ķ��� 
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

	//������ͨ��֧����lables[i]�Ƕ���i�����ķ�֧��� 
	int getCC (int* lables) {
		int i = 0;

		//���lable����������ͨ��֧��ǣ���������ͨ��֧��
		int label = 0;
		for (i = 1; i <= _vertex_num; i++) {
			if (lables[i] == 0) {//������δ����Ķ��㣬������һ��bfs��� 
				label++;
				bfs (i, lables, label);  //���·�֧����� 
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

	//��ӡDFS����
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
				//������ǰ��
				u = iv->moveNext ();
			}
		}
	}


	int dijkstra (int start, int dest, int pre[]) {
		//�������·������¼�����·��·����pre�Ǵ�start��dest·����destǰ���Ǹ����� 

		//L[i]���Ǵ�start�㵽����i�ľ��� 
		int* L = new int[_vertex_num + 1];
		fill (L, L + _vertex_num + 1, 100000);
		L[start] = 0;

		//���ó�ʼ�������ʼǰ�����
		for (node<int>* u = _chain_heads[start]._head; u != nullptr; u = u->next) {
			L[u->data] = u->weight;
			pre[u->data] = start;  //����start�ڽӵĵ� 
		}
		pre[start] = 0; //Դ����û��ǰ�� 

		//���÷��ʼ�¼��
		bool* S = new bool[_vertex_num + 1];
		fill (S, S + _vertex_num + 1, false);

		until (S[dest] == true) {
			int u, temp_head;
			//�����̾���ĺ���
			auto getMinDis = [](int L[], bool S[], int _vertex_num) {
				int min = 100000;
				for (int i = 1; i <= _vertex_num; i++) {
					if (L[i] < min && S[i] == false)
						min = L[i];
				}
				return min;
			};
			int min_dis = getMinDis (L, S, _vertex_num);
			//�ҵ��������������Ǹ���㣬���뵽S����
			for (u = 1; u <= _vertex_num; u++) {
				if (S[u] == false && L[u] == min_dis) {
					S[u] = true;
					temp_head = u;
					break;
				}
			}
			
			//�������ҵ��ĵ���ڽӵ�,�����û�б����ʹ����Ҿ���ɱ����£�����¾���
			for (node<int>* u = _chain_heads[temp_head]._head; u != nullptr; u = u->next) {
				if (S[u->data] == false && L[temp_head] + (u->weight) < L[u->data]) {
					L[u->data] = L[temp_head] + u->weight;
					pre[u->data] = temp_head; //����v��ǰ����u 
				}
			}
		}
		return L[dest];
	}

	//��Աߣ�������ϡ������k�㷨
	bool kruskal (edge<T>* spanningTreeEdges) {
		//��С���ѱ�ʾ�߼���Ч�ʽϺ�,�˴���ʼ�����б߼���
		minHeap<edge<T> > heap;
		for (int i = 1; i <= _vertex_num; i++) {
			myIterator* ii = iterator (i);
			int j;
			T w;
			while ((j = ii->moveNext (w)) != 0) {
				if (i < j){//�ж�ȥ��
					heap.push (edge<int> (i, j, w));
				}
			}
		}

		//���鼯���⻷·�����鼯��uniteΪ��Ϊ���ϣ�find���Ҽ��ϵı��
		fastUnionFind uf (_vertex_num);
		int k = 0;  //����
		while (_edge_num > 0 && k < _vertex_num - 1) {//������û����ɲ��һ��бߴ��� 
			edge<T> x = heap.getTop ();
			heap.pop ();
			_edge_num--;
			int seta = uf.find (x.getFrom ());
			int setb = uf.find (x.getTo ());
			if (seta != setb) {//��֤��û�л�·�������ѡȡ��x 
				spanningTreeEdges[k++] = x;
				uf.unite (seta, setb);
			}
		}
		return (k == _vertex_num - 1);
	}

	//ʹ��С���ѵ�prim�㷨�������ڱ߶��ͼ
	bool prim (edge<T>* spanningTreeEdges) { 
		//��ʼ��С���ѣ�ע���k��ͬ����������Ĳ������бߣ����ǵ�ǰ���ϵ���һ���������е��ֱ�Ӿ���
		minHeap< edge<T> > heap;
		myIterator* i = iterator (1);
		int j;  T w;
		while ((j = i->moveNext (w)) != 0) {
			edge<T> tem (1, j, w);
			heap.push (tem);
		}

		bool* S = new bool[_vertex_num + 1];//TV���������еĶ��㼯
		fill (S,S+ _vertex_num + 1,false);
		S[1] = true;
		

		int k = 0;
		while (!heap.empty () && k < _vertex_num - 1) {
			//���һ���㵽S����
			edge<T> x = heap.getTop ();
			heap.pop ();
			int a = x.getFrom ();
			int b = x.getTo ();
			if (S[b] == false) {
				spanningTreeEdges[k++] = edge<T> (a, b, x.getWeight ());
			}
			S[b] = true;
			
			
			//���¶ѣ�ע��ȥ��
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
