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

		//½«ÐÂµÄÍ·²¿ÔªËØÖð²ãÏòÏÂÒÆ¶¯£¬ÏòÏÂÒÆ¶¯µ½×ó×Ó»¹ÊÇÓÒ×Ó£¿ÕâÀïÐèÒªÅÐ¶Ï
		//ÆðÂëÓÐÒ»¸ö×ó×ÓÊ÷£¬ËùÒÔÒª<=
		while (child_index <= _size) {
			//Èç¹û×ó×Ó±ÈÓÒ×Ó´ó£¬Ôò¸ùÓ¦µ±ÓëÓÒ×Ó½»»»£¬Ê¹ÐÂ¸ùÐ¡£¬ÕâÑù¿ÉÒÔ±£³Ö×îÐ¡¶ÑÌØÐÔ
			//Èç¹û×ó×ÓÊ÷¿¨µ½ÁËsizeÎ»ÖÃ£¬ËµÃ÷Ã»ÓÐÓÒ×ÓÊ÷£¬²»±ØÑ°ÕÒ×óÓÒÖÐ×îÐ¡µÄÔªËØ
			if (child_index < _size && _head[child_index] > _head[child_index + 1]) {
				child_index++;
			}
			//Èç¹û¸ù±ÈÁ½¸ö×Ó¶¼Ð¡£¬ÄÇÖ±½ÓÍË³ö¾ÍÐÐÁË£¬²»±ØÔÙ½»»»
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
		//½øÐÐÔ½½ç¼ì²é
		if (_size == _length - 1) {
			_extLength ();
		}

		int insert_index = ++_size;

		while (insert_index != 1 && _head[insert_index / 2] > datai) {//²åÈëÔªËØµÄ¸¸ÔªËØ²»Ð¡ÓÚ²åÈëÔªËØ£¬ËµÃ÷ÐèÒªµ÷Õû
			_head[insert_index] = _head[insert_index / 2]; //¸Ã¸¸ÔªËØ·Åµ½×Ó½ÚµãÎ»ÖÃ
			insert_index /= 2;//×Ó½ÚµãÎ»ÖÃÖ¸ÏòÔ­¸¸½ÚµãÄÇÀïÈ¥£¬Ò²¼´·¢Éú¸¸×Ó½»»»£¬Ö»²»¹ý×ÓÔªËØ»¹Ã»ÓÐ²åÈë

			//¼ÌÐøÑ­»·²é¿´ÐÂµÄ¸¸½Úµã
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
		while (_head->next != nullptr) {
			node* temp = _head;
			_head = _head->next;
			delete temp;
		}
		delete _head;
	}

	void push (const T& in) {
		_length++;
		node* n_end = new node;
		n_end->data = in;
		n_end->next = nullptr;

		_end->next = n_end;
		_end = n_end;
	}
	T front () {
		if (isempty ()) {
			throw queue_empty;
		}
		return _head->next->data;
	}
	void pop () {
		if (isempty ()) {
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
	edge (int v1, int v2, int weight) :v1 (v1), v2 (v2), w (weight) {}
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
	operator int () const {
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
struct node { //ÊµÏÖµÄ¶¥µãÀà
	T vertex;
	int weight;
	node<T>* next;

	node () {
		next = nullptr;
	}
	node (T v, int w) {
		vertex = v;
		weight = w;
		next = nullptr;
	}
	node (T v, int w, node<T>* theNext) {
		vertex = v;
		weight = w;
		next = theNext;
	}
	void push (T v) {
		vertex = v;
	}
	void push (node<T>* theNode) {
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
	void set (T element) {
		weight = element;
	}
	T& get () {
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
	UnionFindNode () :parent (1), root (true) {}
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
		}
		else {
			node[rootA].parent += node[rootB].parent;
			node[rootB].parent = rootA;
			node[rootB].root = false;
		}
	}


private:
	UnionFindNode* node;
};

template <class T>//ÎÞÏòÍ¼
class graph {
protected:
	node<T>** _chain_head;//
	edge* _edge_list;
	int* _reached;				//±ê¼ÇÊÇ·ñµ½´ïµÄÊý×é
	int* _dfs_lables;
	int* _prim_sum_w;//ÓÃÀ´´æÈ¨ÖØÊý×é
	int _v_num;				//¶¥µã¸öÊý
	int _e_num;				//±ß¸öÊý
	int _lable;				//µ½´ï±ê¼Ç

public:
	graph (int initialize_v, int initialize_e) {
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
			_chain_head[i] = head;//²»ÒªÍü¼Ç¸øÕâÀï¸³Öµ
		}
		_lable = 1;
		_dfs_lables = new int[_v_num + 1];
	}

	void init (edge* edgesi) {
		_edge_list = edgesi;
		for (int i = 1; i <= _e_num; i++) {
			_insertEdeg (_edge_list[i].v1, _edge_list[i].v2, _edge_list[i].w);
		}
	}
	void _insertEdeg (T v1, T v2, int TheWeight) {
		node<T>* p = _chain_head[v1];
		node<T>* newNode1 = new node<T> (v2, TheWeight);
		node<T>* temp;
		if (p->next == nullptr) {
			p->next = newNode1;
		}
		else {
			while (p->next != nullptr && v2 > p->next->vertex) {
				p = p->next;
			}
			temp = p->next;
			p->next = newNode1;
			newNode1->next = temp;
		}
		node<T>* q = _chain_head[v2];
		node<T>* newNode2 = new node<T> (v1, TheWeight);
		if (q->next == nullptr) {
			q->next = newNode2;
		}
		else {
			while (q->next != nullptr && v1 > q->next->vertex) {
				q = q->next;
			}
			temp = q->next;
			q->next = newNode2;
			newNode2->next = temp;
		}
	}

	void _dfs_lable (int v) {
		int x = ++_dfs_lables[0];
		_dfs_lables[x] = v;
		_reached[v] = _lable;
		node<T>* p = _chain_head[v];
		while ((p = p->next) != nullptr) {
			int u = p->vertex;
			if (_reached[u] == 0) {
				_dfs_lable (u);
			}
		}
		return;
	}


	//½µµÍÊ±¼ä¸´ÔÓ¶È ¶ÔÍâ±©Â¶µÄº¯Êý
	int getMinW (int indexi) {
		if (_prim_sum_w[indexi] != 0) {

			return _prim_sum_w[indexi];
		}
		else {
			prim (indexi);
			return _prim_sum_w[indexi];
		}
	}

	void prim (int s) {

		int j;
		T w;

		bool* S = new bool[_v_num + 1];
		fill (S, S + _v_num + 1, false);
		S[s] = true;

		int sum_weight = 0;
		int k = 0;
		while ( k < _v_num - 1) {
			edge min_edge (0, 0, 9999);
			for (int i = 1; i <= _v_num; i++) {
				if (S[i] == true) {
					node<T>* p = _chain_head[i];
					p = p->next;
					min_edge.v1 =i;

					while (p != nullptr) {
						if (S[p->vertex]==false && p->weight <= min_edge.w) {
							min_edge.v2 = p->vertex;
							min_edge.w = p->weight;
						}
						p = p->next;
					}
				}
			}

			int b = min_edge.v2;
			if (S[b] == false) {
				sum_weight += min_edge.w;
				k++;
			}
			S[b] = true;

		}
		_reached[s] = true;
		for (int i = 1; i <= _v_num; i++) {
			if (_reached[i] != 0) {
				_prim_sum_w[i] = sum_weight;
			}
		}
		delete[] S;
	}
};

int main () {
#pragma warning(disable:4996)

	freopen ("input.txt", "r", stdin);
	int n, m, q;//µã ±ß ²éÑ¯´ÎÊý
	cin >> n >> m >> q;

	//³õÊ¼»¯Õû¸öÍ¼
	graph<int> g (n, m);
	edge* edges = new edge[m + 1];
	for (int i = 1; i <= m; i++) {
		cin >> edges[i].v1 >> edges[i].v2 >> edges[i].w;
	}
	g.init (edges);


	//»ñÈ¡ÖÖ×Ó½Úµã²¢Êä³ö×îÐ¡³¤¶È
	for (int i = 0; i < q; i++) {
		int temp;
		cin >> temp;
		cout << g.getMinW (temp) << "\n";
	}


}