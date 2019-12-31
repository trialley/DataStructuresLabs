#include<iostream>
using namespace std;
template<class T>
class minHeap {
	public:
		typedef enum { min_head_empty } err;
	private:
		int _size;
		int _length;
		T* _head;
		void _extLength () {
			T* temp = new T[_length * 2];
			copy (_head, _head + _length, temp);
			delete[] _head;
			_length *= 2;
			_head = temp;
		}
		void _clear () {
			/*delete[] _head;*/
		}
	public:
		minHeap (int lengthi = 10) {
			_length = lengthi + 1;
			_head = new T[_length];
			_size = 0;
		}
		~minHeap () {
			_clear ();
		}
		void _clearAndInit () {
			_clear ();
			_length = 11;
			_head = new T[11];
			_size = 0;
		}
		const T& top () {
			if (_size == 0)
				throw min_head_empty;
			return _head[1];
		}
		void pop () {
			if (_size == 0) {
				throw min_head_empty;
			}
			_head[1].~T ();
			T to_be_insert = _head[_size--];
			int insert_index = 1,
			    child_index = 2;     // child_index of current_node

			//将新的头部元素逐层向下移动，向下移动到左子还是右子？这里需要判断
			//起码有一个左子树，所以要<=
			while (child_index <= _size) {
				//如果左子比右子大，则根应当与右子交换，使新根小，这样可以保持最小堆特性
				//如果左子树卡到了size位置，说明没有右子树，不必寻找左右中最小的元素
				if (child_index < _size && _head[child_index] > _head[child_index + 1]) {
					child_index++;
				}
				//如果根比两个子都小，那直接退出就行了，不必再交换
				if (to_be_insert <= _head[child_index]) {
					break;
				}
				_head[insert_index] = _head[child_index];
				insert_index = child_index;
				child_index *= 2;
			}
			_head[insert_index] = to_be_insert;
		}
		void push (const T& datai) {
			//进行越界检查
			if (_size == _length - 1) {
				_extLength ();
			}

			int insert_index = ++_size;

			while (insert_index != 1 && _head[insert_index / 2] > datai) {//插入元素的父元素不小于插入元素，说明需要调整
				_head[insert_index] = _head[insert_index / 2]; //该父元素放到子节点位置
				insert_index /= 2;//子节点位置指向原父节点那里去，也即发生父子交换，只不过子元素还没有插入

				//继续循环查看新的父节点
			}

			_head[insert_index] = datai;
		}

		bool empty () const {
			return _size == 0;
		}
		int size () const {
			return _size;
		}
};

template<typename T>
class queue {
	public:
		enum queue_err { queue_empty };
	private:
		typedef struct node {
			T data;
			node* next;
			node () {
				next = nullptr;
			}
		} node;
		node* _head;
		node* _end;
		int _length;
	public:
		queue () {
			_head = new node;
			_end = _head;
			_length = 0;
		}
		~queue () {
			while ( _head->next != nullptr ) {
				node* temp = _head;
				_head = _head->next;
				delete temp;
			}
			delete _head;
		}

		void push ( const T& in ) {
			_length++;
			node* n_end = new node;
			n_end->data = in;
			n_end->next = nullptr;

			_end->next = n_end;
			_end = n_end;
		}
		T front () {
			if ( isempty () ) {
				throw queue_empty;
			}
			return _head->next->data;
		}
		void pop () {
			if ( isempty () ) {
				throw queue_empty;
			}
			node* n_head = _head->next;
			delete _head;

			_head = n_head;

			_length--;
			return;
		}
		bool isempty ()const {
			return _head == _end;
		}
		int size ()const {
			return _length;
		}
};

class edge {
	public:
		int v1;
		int v2;
		int w;
		edge () {}
		edge (int v1, int v2, int weight):v1(v1),v2(v2),w(weight) {}
		~edge () {};

		int getFrom () const {
			return v1;
		}
		int getTo () const {
			return v2;
		}
		int getWeight () const {
			return w;
		}
		operator int() const {
			return w;
		}


		friend ostream& operator<<(ostream& out, const edge A) {
			out << "(" << A.v1 << ", " << A.v2 << ", " << A.w << ")";
			return out;
		}

		bool operator > (const edge& x) {
			return (this->w > x.w);
		}
		bool operator < (const edge& x) {
			return (this->w < x.w);
		}
};

template<class T>
struct node { //实现的顶点类
	T vertex;
	int weight;
	node<T>* next;

	node() {
		next = nullptr;
	}
	node(T v, int w) {
		vertex = v;
		weight = w;
		next = nullptr;
	}
	node(T v, int w, node<T>* theNext) {
		vertex = v;
		weight = w;
		next = theNext;
	}
	void push(T v) {
		vertex = v;
	}
	void push(node<T>* theNode) {
		vertex = theNode->vertex;
		next = theNode->next;
	}

	bool operator<= (node<T>& GNode) {
		return (this->weight <= GNode.weight);
	}
	bool operator>= (node<T>& GNode) {
		return (this->weight >= GNode.weight);
	}
	bool operator> (node<T>& GNode) {
		return (this->weight > GNode.weight);
	}
	bool operator< (node<T>& GNode) {
		return (this->weight < GNode.weight);
	}
	void set(T element) {
		weight = element;
	}
	T& get() {
		return weight;
	}
};

class UnionFind {
	public:
		UnionFind (int numberOfElements) {
			parent = new int[numberOfElements + 1];
			for (int i = 1; i <= numberOfElements; i++) {
				parent[i] = 0;
			}
		}

		int find (int ele) {
			while (parent[ele] != 0) {
				ele = parent[ele];
			}
			return ele;
		}
		void unite (int rootA, int rootB) {
			parent[rootB] = rootA;
		}

	private:
		int* parent;
};

struct UnionFindNode {
	int parent;
	bool root;
	UnionFindNode ():parent(1),root(true) {}
};

class fastUnionFind {
	public:
		fastUnionFind (int numberOfElements) {
			node = new UnionFindNode[numberOfElements + 1];
		}

		int find (int ele) {
			int theRoot = ele;
			while (!node[theRoot].root) {
				theRoot = node[theRoot].parent;
			}
			int currentNode = ele;
			while (currentNode != theRoot) {
				int k = node[currentNode].parent;
				node[currentNode].parent = theRoot;
				currentNode = k;
			}
			return theRoot;
		}
		void unite (int rootA, int rootB) {
			if (node[rootA].parent < node[rootB].parent) {
				node[rootB].parent += node[rootA].parent;
				node[rootA].parent = rootB;
				node[rootA].root = false;
			} else {
				node[rootA].parent += node[rootB].parent;
				node[rootB].parent = rootA;
				node[rootB].root = false;
			}
		}


	private:
		UnionFindNode* node;
};

template <class T>//无向图
class graph {
	protected:
		node<T>** _chain_head;//
		edge*_edge_list;
		int* _reached;				//标记是否到达的数组
		int* _dfs_lables;
		int* _prim_sum_w;//用来存权重数组
		int _v_num;				//顶点个数
		int _e_num;				//边个数
		int _lable;				//到达标记

	public:
		graph(int initialize_v, int initialize_e) {
			_v_num = initialize_v;
			_e_num = initialize_e;
			_chain_head = new node<T> * [initialize_v + 1];
			_reached = new int[initialize_v + 1];
			_prim_sum_w = new int[initialize_v + 1];
			for (int i = 0; i <= initialize_v; i++) {
				_reached[i] = 0;
				_prim_sum_w[i] = 0;
			}
			for (int i = 1; i <= initialize_v; i++) {
				node<T>* head = new node<T>;
				_chain_head[i] = head;//不要忘记给这里赋值
			}
			_lable = 1;
			_dfs_lables = new int[_v_num + 1];
		}

		void init(edge* edgesi) {
			_edge_list = edgesi;
			for (int i = 1; i <= _e_num; i++) {
				_insertEdeg(_edge_list[i].v1, _edge_list[i].v2, _edge_list[i].w);
			}
		}
		void _insertEdeg(T v1, T v2, int TheWeight) {
			node<T>* p = _chain_head[v1];
			node<T>* newNode1 = new node<T>(v2, TheWeight);
			node<T>* temp;
			if (p->next == nullptr) {
				p->next = newNode1;
			} else {
				while (p->next != nullptr && v2 > p->next->vertex) {
					p = p->next;
				}
				temp = p->next;
				p->next = newNode1;
				newNode1->next = temp;
			}
			node<T>* q = _chain_head[v2];
			node<T>* newNode2 = new node<T>(v1, TheWeight);
			if (q->next == nullptr) {
				q->next = newNode2;
			} else {
				while (q->next != nullptr && v1 > q->next->vertex) {
					q = q->next;
				}
				temp = q->next;
				q->next = newNode2;
				newNode2->next = temp;
			}
		}

		void _dfs_lable(int v) {
			int x = ++_dfs_lables[0];
			_dfs_lables[x] = v;
			_reached[v] = _lable;
			node<T>* p = _chain_head[v];
			while ((p = p->next) != nullptr) {
				int u = p->vertex;
				if (_reached[u] == 0) {
					_dfs_lable(u);
				}
			}
			return;
		}


		//降低时间复杂度 对外暴露的函数
		int getMinW(int indexi) {
			if (_prim_sum_w[indexi] != 0) {

				return _prim_sum_w[indexi];
			} else {
				prim(indexi);
				return _prim_sum_w[indexi];
			}
		}

		//求解权重最重要的一个函数
		void prim(int s) {
			for (int i = 0; i <= _v_num; i++) {
				_reached[i] = 0;
				_dfs_lables[i] = 0;
			}


			int sum_weight = 0;

			fastUnionFind S(_v_num + 1);


			//初始化边表
			_dfs_lable(s);
			minHeap<edge> theHeap;
			for (int i = 1; i <= _e_num; i++) {
				int a = _edge_list[i].v1;
				int b = _edge_list[i].v2;
				if (_reached[a] != 0 && _reached[b] != 0) {
					theHeap.push(_edge_list[i]);
				}
			}
			cout << theHeap.size () << endl;


			//循环进行计算，从小到大找出边，个数是本连通分量边数
			int num_e = 1;
			while (num_e < _dfs_lables[0]) {
				edge temp = theHeap.top();
				theHeap.pop();
				int a = S.find(temp.v1);
				int b = S.find(temp.v2);
				if (a != b) {
					S.unite(a, b);
					sum_weight = sum_weight + temp.w;
					cout<<temp<<sum_weight<<"\n";
					num_e++;
				}
			}

			for (int i = 1; i <= _v_num; i++) {
				if (_reached[i] != 0) {
					_prim_sum_w[i] = sum_weight;
				}
			}
		}
};

int main() {
	freopen ("input.txt", "r", stdin);
	int n, m, q;//点 边 查询次数
	cin >> n >> m >> q;

	//初始化整个图
	graph<int> g(n, m);
	edge* edges = new edge[m + 1];
	for (int i = 1; i <= m; i++) {
		cin >> edges[i].v1 >> edges[i].v2 >> edges[i].w;
	}
	g.init(edges);


	//获取种子节点并输出最小长度
	for (int i = 0; i < q; i++) {
		int temp;
		cin>>temp;
		cout<<g.getMinW(temp)<<"\n";
	}


}
