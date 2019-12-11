#include<cstring>//memcpy
#include<cstdlib>//min
#include<iostream>
#include<algorithm>
#include"stack.h"
#include"queue.h"
#include"chain.h"
#include"minHeap.h"
#include"fastUnionFind.h"
#include"edge.h"

using namespace std;

//��Ȩ����ͼ,�ɳƳ�ΪͬȨ����ͼ 
template<class T>
class linkedWGraph {
protected:
	int n;                 //������ 
	int e;                 //���� 
	chain<T>* _chain_heads;  //�ڽӱ� 
	int* reach;  //����ָ�� 
	int label = 1;

	void rDfs (int v) {//�ݹ�ʵ�������������
		reach[v] = label;  int u;
		//cout<<"��ǰ�ߵ����㣺"<<v<<endl;
		myIterator* iv = iterator (v);  //�����<T>�ͻᱨ��Ϊʲô���� 
		while ((u = iv->next ()) != 0) {//��v����һ���ڽӵ�uΪ�����ݹ����� 
		//cout<<v<<"����һ���ڽӵ��ǣ�"<<u<<" "<<endl;
			if (reach[u] != label)
				rDfs (u);  //u��һ��û�е�����Ķ��� 
		}
		delete iv;
		return;
	}

public:
	void output (ostream& out) {
		for (int i = 1; i <= n; i++) {
			out << "_chain_heads[" << i << "]="; _chain_heads[i].output ();
			out << endl;
		}
	}
	linkedWGraph (int v) {
		n = v;
		e = 0;
		_chain_heads = new chain<int>[n + 1];
	}
	~linkedWGraph () {
		delete[] _chain_heads;  //�����ͻ��Լ�����chain������������ 
	}
	int numberOfVertices () const { return n; }
	int numberOfEdges () const { return e; }
	bool directed () const { return false; }
	bool weight () const { return true; }
	void checkVertex (int theVertex) const {//ȷ������Ч���� 
		if (theVertex<1 || theVertex>n) {
			cerr << "the vertex:" << theVertex << " is not permissible";
			exit (1);
		} else return;
	}
	void insertEdge (int v1, int v2, int weight) {
		if (v1<1 || v2<1 || v1>n || v2>n || v1 == v2) {//Խ�紦�� 
			cerr << "(" << v1 << "," << v2 << ") is not a permissible edge" << endl;
			exit (1);
		}
		if (_chain_heads[v1].indexOf (v2) == -1) {//�±� 
			_chain_heads[v1].insert (0, v2, weight);
			_chain_heads[v2].insert (0, v1, weight);
			e++;
		}
	}
	void eraseEdge (int i, int j) {
		if (i > 1 && j > 1 && i <= n && j <= n) {
			int* v = _chain_heads[i].eraseElement (j);
			int* j = _chain_heads[j].eraseElement (i);  //v,jһ��ͬʱΪ�ջ��߷ǿգ���Ȼ˵��һ���Գ������� 
			if (v != nullptr && j != nullptr)   e--;   //�ñߴ���
		}
	}
	int Degree (int Vertex) {
		checkVertex (Vertex);
		return _chain_heads[Vertex].size ();
	}

	class myIterator {
	public:
		myIterator (chain<T>* theVertex) {
			v = theVertex;
			currentVertex = v->firstnode;
		}
		~myIterator () {}
		int next (T& theWeight) {//����ָ���������һ���ڽӵ����ź����ĵ�Ȩֵ 
			if (currentVertex != nullptr) {
				theWeight = currentVertex->weight;
				int vertex = currentVertex->data;
				currentVertex = currentVertex->next;
				return vertex;
			} else
				return 0;
		}
		int next () {//����ָ���������һ���ڽӵ� 

			if (currentVertex != nullptr) {
				int vertex = currentVertex->data;
				currentVertex = currentVertex->next;
				return vertex;
			}
			return 0;
		}
	protected:
		chain<T>* v;    //�ڽӱ�ĵ� 
		node<T>* currentVertex;   //��ǰ�����Ķ��� 
	};
	myIterator* iterator (int theVertex) {
		checkVertex (theVertex);
		return new myIterator (&_chain_heads[theVertex]);
	}

	bool connected () {//�ж�����ͼ�Ƿ���ͨ 
		if (directed ()) {
			cerr << "��ͼ������ͼ��" << endl;  exit (2);
		}

		reach = new int[n + 1];
		for (int i = 1; i <= n; i++)
			reach[i] = 0;

		dfs (1, reach, 1); //���ڽ��ڶ���1�Ŀɴﶥ�������

		for (int i = 1; i <= n; i++) {//������ж����Ƿ��������
			if (reach[i] == 0) {
				return false;
			}
		}
		return true;
	}
	void bfs (int v, int reach[], int label) {//��������㷨��reach[i]������������ڽ��ڶ���v�Ŀɵ���Ķ��� 
		queue<int> q (10);
		reach[v] = label;
		q.push (v);

		while (q.empty () != true) {
			int vertex = q.front ();
			q.pop ();

			for (node<int>* u = _chain_heads[vertex].firstnode; u != nullptr; u = u->next) {
				if (reach[u->data] == 0) {
					q.push (u->data);	reach[u->data] = label;
				}
			}
		}
	}
	void dfs (int v, int reach[], int label) {
		reach = reach;
		label = label;
		rDfs (v);
	}
	int labelComponents (int c[]) {//������ͨ��֧����c[i]�Ƕ���i�����ķ�֧��� 
		int i = 0;
		for (i = 0; i <= n; i++)
			c[i] = 0;

		int label = 0;
		for (i = 1; i <= n; i++) {
			if (c[i] == 0) {//������δ����Ķ��㣬������һ��bfs��� 
				label++;
				bfs (i, c, label);  //���·�֧����� 
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

			for (node<int>* u = _chain_heads[vertex].firstnode; u != nullptr; u = u->next) {
				if (reach[u->data] == 0) {
					q.push (u->data);	reach[u->data] = label;
				}
			}
		}
	}
	void print_dfs (int v, int reach[]) {//ʹ��ջʵ�ֵ�DFS�����㷨 
		stack<int> s (10);  int u;
		memset (reach, 0, sizeof (int) * (n + 1));
		reach[v] = label;
		s.push (v);  cout << v << " ";

		while (!s.empty ()) //��ջ����ʱ 
		{
			int w = s.top ();
			s.pop ();
			myIterator* iv = iterator (w);	  u = iv->next ();
			while (u != 0)  //����һ������ĵ�w�������ڽӵ� 
			{
				if (reach[u] != label) //�������һ��δ��ǵĵ�j 
				{
					reach[u] = label;
					s.push (u);
					cout << u << " ";
					iv = iterator (u);	//��ivָ����uΪ���ĵ����� 
				} else {//�ö����ѱ����
					u = iv->next ();
					if (u == 0 && s.empty () != true)  s.pop (); //�ö���û�������ڽӵ���
				}
			}
		}
	}
	int Dijkstra (int start, int dest, int predecessor[]) {//�������·������¼�����·��·����predecessor�Ǵ�start��dest·����destǰ���Ǹ����� 
		int* L = new int[n + 1];  //L[i]���Ǵ�start�㵽����i�ľ��� 
		for (int i = 1; i <= n; i++) {
			L[i] = 100000;  predecessor[i] = -1;
		}   L[start] = 0;
		for (node<int>* u = _chain_heads[start].firstnode; u != nullptr; u = u->next) {
			L[u->data] = u->weight;
			predecessor[u->data] = start;  //����start�ڽӵĵ� 
		}
		predecessor[start] = 0;    //Դ����û��ǰ��  
		bool* S = new bool[n + 1];
		for (int i = 1; i <= n; i++)  S[i] = false;  //S[i]��ʾstart������i�����·����� 

		/*�������������ǳ�ʼ��������������*/

		while (S[dest] != true) {/*������һ�����ڶ��㼯S�е�u��L[u]�����С�����Խ���һ�����Ա���*/
			int u, tag;
			for (u = 1; u <= n; u++) {
				auto Minium = [](int L[], bool S[], int n) {//��L[1:n]�����з��ز��ڶ��㼯S����С��Ԫ�� 
					int min = 100000;
					for (int i = 1; i <= n; i++) {
						if (L[i] < min && S[i] == false)
							min = L[i];
					}
					return min;
				};
				if (S[u] == false && L[u] == Minium (L, S, n))  //������һ�����ڶ��㼯S�ұ����С�ĵ㣬���Ӷȿ��Խ���O(1)�� 
				{                                        //���ҵ�д�����ӶȺ�����O(n^3)������ͨ��������ѭ���ж������ۺ������͸��Ӷ�� 
					S[u] = true;  //��u���붥�㼯S��
					tag = u;
					break;
				}
			}

			for (node<int>* u = _chain_heads[tag].firstnode; u != nullptr; u = u->next) {//�������ҵ��ĵ���ڽӵ�,�����û�б����ʹ����Ҿ���ɱ�����
			  //����д�����Ӷ���O(����)���Ϻ� 
				if (S[u->data] == false && L[tag] + (u->weight) < L[u->data]) {
					L[u->data] = L[tag] + u->weight;
					predecessor[u->data] = tag;    //����v��ǰ����u 
				}
			}
		}
		return L[dest];
	}

	bool kruskal (edge<T>* spanningTreeEdges) {//����С������������ͼ��ͨ�򷵻�true����sTE[0:n-2]�д�����С�������ı� 
//n��ͼ�еĶ�������e�Ǳ��� 
		int n = this->n;
		int e = this->e;
		edge<T>* Edge = new edge<T>[e + 1];
		int k = 1;  //����Edge������ 

		//�����edge�����ʼ���������б߼���edge����
		for (int i = 1; i <= n; i++) {//ȡ���й�������i�ı� 
			myIterator* ii = iterator (i);
			int j; T w;
			while ((j = ii->next (w)) != 0) {
				if (i < j)    //�����ظ��ӱ� 
				{
					Edge[k++] = edge<int> (i, j, w);
				}
			}
		}
		//��С���ѱ�ʾ�߼���Ч�ʽϺ�
		minHeap<edge<T> > heap (1);
		heap.initialize (Edge, e);  //cout<<heap<<endl;
		fastUnionFind uf (n);
		k = 0;  //����
		while (e > 0 && k < n - 1) {//������û����ɲ��һ��бߴ��� 
			edge<T> x = heap.top ();
			heap.pop ();
			e--;
			int a = uf.find (x.vertex1 ());
			int b = uf.find (x.vertex2 ());
			if (a != b) {//��֤��û�л�·�������ѡȡ��x 
				spanningTreeEdges[k++] = x;
				uf.unite (a, b);
			}
		}
		return (k == n - 1);
	}
	bool Prim (edge<T>* spanningTreeEdges) {//spanningTreeEdges���Ѿ���ѡ�ı߼� 
		int n = this->n;
		int e = this->e;
		minHeap< edge<T> > heap;

		bool* TV = new bool[n + 1];      //TV���������еĶ��㼯
		for (int i = 1; i <= n; i++)
			TV[i] = false;
		TV[1] = true;

		myIterator* i = iterator (1);
		int j;  T w;
		while ((j = i->next (w)) != 0) {
			edge<T> tem (1, j, w);
			heap.push (tem);
		}


		int k = 0;   //��ʾ�߼������� 
		while (!heap.empty () && k < n - 1) {
			edge<T> x = heap.top ();  //�����ı�����С�� 
			heap.pop ();
			int a = x.vertex1 ();
			int b = x.vertex2 ();
			if (TV[b] == false)  //����TV[a]==true 
				spanningTreeEdges[k++] = edge<T> (a, b, x.weight ());
			TV[b] = true;
			i = iterator (b);
			while ((j = i->next (w)) != 0) {
				if (j > b)  //��֤���ظ������ 
				{
					edge<T> tem (b, j, w);
					heap.push (tem);
				}
			}
		}
		delete[] TV;      //TV���������еĶ��㼯

		return (k == n - 1);

	}

};
