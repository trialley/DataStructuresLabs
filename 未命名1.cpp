#include<iostream>
#include<cstdlib>
#define until(re) while(!(re))
#include<cstring>
using namespace std;

template<class T>
/*?????*/
class minHeap {
public:
	typedef enum { min_head_empty }err;
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
	void initialize (T* arri, int sizei) {
		_clearAndInit ();
		for (int i = 1; i <= sizei; i++) {
			push (arri[i]);
		}
	}
	~minHeap () { _clear (); }
	void _clearAndInit () {
		_clear ();
		_length = 11;
		_head = new T[11];
		_size = 0;
	}
	const T& getTop () {
		if (_size == 0)
			throw min_head_empty;
		return _head[1];
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
		T getTo_be_insert = _head[_size--];
		int insert_index = 1,
			child_index = 2;  // child_index of current_node

		//?????????????,??????????????????
		//????????,???<=
		while (child_index <= _size) {
			//????????,?????????,????,???????????
			//????????size??,???????,????????????
			if (child_index < _size && _head[child_index] > _head[child_index + 1]) {
				child_index++;
			}
			//?????????,????????,?????
			if (getTo_be_insert <= _head[child_index]) {
				break;
			}
			_head[insert_index] = _head[child_index];
			insert_index = child_index;
			child_index *= 2;
		}
		_head[insert_index] = getTo_be_insert;
	}
	void push (const T& datai) {
		//??????
		if (_size == _length - 1) {
			_extLength ();
		}

		int insert_index = ++_size;

		while (insert_index != 1 && _head[insert_index / 2] > datai) {//???????????????,??????
			_head[insert_index] = _head[insert_index / 2]; //???????????
			insert_index /= 2;//??????????????,????????,???????????

			//???????????
		}

		_head[insert_index] = datai;
	}
	void pushShow (const T& datai) {
		//??????
		if (_size == _length - 1) {
			_extLength ();
		}

		int insert_index = ++_size;
		_head[insert_index] = datai;
		for (int i = 1; i <= _size; i++) {
			cout << _head[i] << " ";
		}
		cout << "\n";

		while (insert_index != 1 && _head[insert_index / 2] > datai) {//???????????????,??????
			_head[insert_index] = _head[insert_index / 2]; //???????????
			insert_index /= 2;//??????????????,????????,???????????
			_head[insert_index] = datai;

			//???????????
			for (int i = 1; i <= _size; i++) {
				cout << _head[i] << " ";
			}
			cout << "\n";
		}



		_head[insert_index] = datai;
	}
	ostream& out (ostream& out) {
		for (int i = 1; i <= _size; i++) {
			out << _head[i] << " ";
		}

		return out;
	}
	bool empty () const { return _size == 0; }
	int size () const { return _size; }
};


template<class T>
class queue {
public:
	queue (int initialCapacity = 10) {//???? 
		if (initialCapacity < 0) {
			////std::cerr << "????????0!" << std::endl;
		} else {
			_queue = new T[initialCapacity];
			arrayLength = initialCapacity;
			qFront = qBack = 0;  //????_queue[1]?????? 
		}
	}
	~queue () { delete[] _queue; }
	bool empty () const {
		if (qFront == qBack) return true;
		else return false;
	}
	int size () const {
		return (arrayLength + qBack - qFront) % arrayLength;
	}
	T& front () {
		if (empty () != true)
			return _queue[(qFront + 1) % arrayLength];
		else {
			//std::cerr << "????" << std::endl;
		}
	}
	T& back () {
		if (empty () != true)
			return _queue[qBack];
		else {
			//std::cerr << "????" << std::endl; exit (1);
		}
	}
	T pop () {//??????? 
		T* p = &front (); //????????????? 
		T temp = (*p);
		qFront = (qFront + 1) % arrayLength;
		(*p).~T ();  //???????????int???...,???????????????
		return temp;
	}
	void push (const T& ele) {//??????? 
		if ((qBack + 1) % arrayLength == qFront) {//????,?????? 
			T* new_queue = new T[2 * arrayLength];
			int start = (qFront + 1) % arrayLength;
			if (start == 0 || start == 1) {//???? 
				std::copy (_queue + start, _queue + qBack + 1, new_queue);
			} else {//???? 
				std::copy (_queue + start, _queue + arrayLength, new_queue);
				//???2?(start,????,?????) 
				std::copy (_queue, _queue + qBack + 1, new_queue + (arrayLength - start));
				//???1?(?????,qback,????arraylength-start???) 
			}
			qFront = (arrayLength) * 2 - 1;
			qBack = arrayLength - 1 - 1;//???????? 
			arrayLength = arrayLength * 2;
			delete[] _queue;
			_queue = new_queue;
		}
		//??????????
		qBack = (qBack + 1) % arrayLength;
		_queue[qBack] = ele;

	}
	void output () {
		for (int i = qFront; i < qBack; i++)
			std::cout << _queue[i];
		std::cout << std::endl;
	}
private:
	int qFront;  //?????????????? 
	int qBack;//??????????? 
	int arrayLength;  //????? 
	T* _queue;	 //???? 
};


template<class T>
class stack {
public:
	typedef enum { pointer_is_null, newLength_less_than_zero, stack_empty } stack_err;
protected:
	void _exLength () {
		T* temp = new T[bufferLength * 2];
		memcpy (temp, head, bufferLength * sizeof (T));
		delete[] head;
		head = temp;
		bufferLength = bufferLength * 2;
	}
	void _shLength () {
		T* temp = new T[bufferLength / 2];
		memcpy (temp, head, bufferLength / 2 * sizeof (T));
		delete[] head;
		head = temp;
		bufferLength = bufferLength / 2;
	}
	int stackTop;
	int bufferLength;
	T* head;
public:
	stack (int initialCapacity = 10) {
		bufferLength = initialCapacity;
		head = new T[bufferLength];
		stackTop = -1;
	}
	~stack () { delete[] head; }
	bool empty () const { return stackTop == -1; }
	int size () const { return stackTop + 1; }
	T top () {
		//??????
		//???????getTop????,????????,????????????
		if (stackTop == -1) {
			throw stack_empty;
		}
		return head[stackTop];
	}
	void pop () {
		if (stackTop == -1) {
			throw stack_empty;
		}
		head[stackTop--].~T ();

		/*??????????*/
		if (size () < bufferLength / 4) {
			_shLength ();
		}
	}
	void push (const T theElement) {
		//?????????????
		if (stackTop == bufferLength - 1) {
			_exLength ();
		}
		head[++stackTop] = theElement;
	}
};

template <class T>
class edge {
protected:
    int from;
    int to;
public:
    T weight;
    edge () {}
    edge (int v1, int v2, T weight) :from (v1), to (v2), weight (weight) {}
    ~edge () {};

    int getFrom () const { return from; }
    int getTo () const { return to; }
    T getWeight () const { return weight; }
    operator T() const { return weight; }


    friend ostream& operator<<(ostream& out, const edge<T> A) {
        //out << "(" << A.from << ", " << A.to << ", " << A.w << ")";
        return out;
    }
};


#include<iostream>
using namespace std;
template<class T>
struct node {
	T data;
	T weight;
	node* next = nullptr;

	node (T ele, T w, node* p = nullptr) :data (ele), weight (w), next (p) {}
	node () {}
	node& operator=(node& A) {//???? 
		data = A.data;
		weight = A.weight;
		next = A.next;
		return *this;
	}
};
/*template<class T>
class chain {
protected:
	void _checkIndex (int theIndex) const;
public:
	chain ();
	chain (int initialCapacity, T A[]);
	chain (const chain<T>& A);
	~chain ();
	bool empty () const;
	int size () const;
	T& get (int theIndex) const;
	T get_Weight (int ele) const;
	int indexOf (T& theElement) const;
	node<T>* eraseByElement (int theVertex);
	void eraseByIndex (int theIndex);
	void insertAfterIndex (int theIndex, const T& ele, T weight);
	void output () const;
	void i_print () const;
	void clear ();
	friend ostream& operator<<(ostream& out, const chain<T> A);
	class iterator;
*/
template<class T>
class chain {
public:
	chain () {
		_head = nullptr;
		_size = 0;
	}
	chain (int initialCapacity, T A[]) {
		if (initialCapacity > 0) {
			_head = new node<T>;
			_head->data = A[0];
			node<T>* p1 = _head, * p2;
			for (int i = 1; i < initialCapacity; i++) {  //??1?????????????? 
				p2 = new node<T>;
				p2->data = A[i];
				p1->next = p2;
				p1 = p2;
			}
			_size = initialCapacity;
		}
		if (initialCapacity <= 0) cerr << "??????!" << endl;
	}
	chain (const chain<T>& A) {
		_size = A._size;
		if (_size == 0) {//???? 
			_head = nullptr;
		} else {//TargetNode??A???,SourceNode????????
				//????????????,ciao! 
			node<T>* SourceNode = new node<T>;
			node<T>* pre_node, * TargetNode;
			_head = SourceNode;
			TargetNode = A._head;
			SourceNode->data = TargetNode->data;

			for (int i = 1; i < _size; i++) {  //??1??????????????
				TargetNode = TargetNode->next;
				pre_node = new node<T> (TargetNode->data);  //???pre_node???????????? 
				SourceNode->next = pre_node;
				SourceNode = pre_node;
			}
		}
	}
	~chain () {
		while (_head != nullptr) {
			node<T>* nextnode = _head->next;
			delete _head;
			_head = nextnode;
		}
	}
	bool empty () const { return _size == 0; }
	int size () const { return _size; }
	T& get (int theIndex) const {//?????theIndex???data?? 
		_checkIndex (theIndex);
		node<T>* cur_node = _head;
		for (int i = 0; i < theIndex; i++) {
			cur_node = cur_node->next;
		}
		return cur_node->data;
	}
	T getWeight (int ele) const {//?????ele???weight
		node<T>* cur_node;
		cout << "vetrex=" << ele;
		for (cur_node = _head; cur_node != nullptr; cur_node = cur_node->next) {
			if (cur_node->data == ele)
				return cur_node->weight;
		}
		return -1;
	}
	int indexOf (T& theElement) const {//?????????theElement?????,???????-1 
		node<T>* cur_node = _head;
		for (int i = 0; i < _size; i++) {
			if (cur_node->data == theElement)
				return i;
			else
				cur_node = cur_node->next;
		}
		return -1;
	}
	node<T>* eraseByElement (int theVertex) {//???????????theVertex???,????????????????? 
		node<T>* p = _head, * tp = nullptr;
		while (p != nullptr) {
			if (p->data == theVertex) {
				if (p == _head) //???? 
					_head = _head->next;
				else {
					tp->next = p->next;
					delete p;
					return p;
				}
			} else {//?????theVertex 
				tp = p;
				p = p->next;
			}
		}
		return nullptr;  //???????nullptr 
	}

	void eraseByIndex (int theIndex) {//?????????theIndex??? 
		_checkIndex (theIndex);
		node<T>* deletenode;
		if (theIndex == 0) {//????? 
			deletenode = _head;
			_head = _head->next;
		} else {
			node<T>* p = _head;
			for (int i = 0; i < theIndex - 1; i++) {
				p = p->next;
			}
			//????????????????? 
			deletenode = p->next;
			p->next = p->next->next;
		}
		_size--;
		delete deletenode;
	}
	void insertAfterIndex (int theIndex, const T& ele, T weight) {//?ele???????theIndex?????? 
		_checkIndex (theIndex);
		if (theIndex == 0) {//????? 
			node<T>* p = new node<T> (ele, weight, _head);
			_head = p;
		} else {
			node<T>* p = new node<T> (ele, weight);//?????
			node<T>* cur_node = _head;
			for (int i = 0; i < theIndex - 1; i++) {
				cur_node = cur_node->next;
			}
			//????????????????? 
			p->next = cur_node->next;
			cur_node->next = p;
		}
		_size++;
	}
	void output () const {
		if (_size == 0) { cout << "null" << endl;  return; } else {
			node<T>* p = _head;
			for (int i = 0; i < _size; i++) {
				cout << "vertex=" << p->data << ",weight=" << p->weight << "";
				p = p->next;
			}
		}
	}

	void clear () {//???? 
		node<T>* deletenode, * p = _head;
		for (int i = 0; i < _size; i++) {
			deletenode = p;
			p = p->next;
			delete deletenode;
		}
		_head = nullptr;
		_size = 0;
	}
	friend ostream& operator<<(ostream& out, const chain<T> A) {//??????????? 
		if (A._size == 0) { out << "null" << endl;  return out; } else {
			node<T>* p = A._head;
			for (int i = 0; i < A._size; i++) {
				out << p->data << " " << p->weight << " ";
				p = p->next;
			}
			return out;
		}
	}
	class iterator {//?????*&??????!=?== 
	protected:
		node<T>* _node = nullptr;
	public:
		iterator (node<T>* theNode) {
			_node = theNode;
		}
		iterator () {}

		T& operator*() { return _node->data; }  //??????,?????? 
		T* operator->() { return &(_node->data); }  //??????,?????? 
		iterator& operator++() {//?? 
			_node = _node->next;
			return *this;
		}
		iterator operator++(int) {//?? 
			iterator temp = *this;
			_node = _node->next;
			return temp;
		}
		bool operator!=(const iterator I)const {
			if (_node == I._node) return false;  //???????_node?==,???????? 
			else return true;
		}
		bool operator==(const iterator I)const {
			if (_node == I._node) return true;
			else return false;
		}

	};

	//protected:
	void _checkIndex (int theIndex) const {//????????,????
		if (theIndex<0 || theIndex>_size) {
			cerr << "index=" << theIndex << ",listSize=" << _size << "?????????!" << endl;
		}
	}
	node<T>* _head; //???????????? 
	int _size;//??????? 	
};

class UnionFind {//?????????????,?????? 
public:
	UnionFind (int numberOfElements) {
		parent = new int[numberOfElements + 1];
		for (int i = 1; i <= numberOfElements; i++) {
			parent[i] = 0;
		}
	}

	int find (int ele) {//??ele??????? 
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
/************?????????????????????????**************/
struct UnionFindNode {
	int parent;//?????,?parent?????,????????? ,????1,???1?????,???1?????????
	bool root; //???????? 
	UnionFindNode () :parent (1), root (true) {}
};

class fastUnionFind {//????????????????
public:
	fastUnionFind (int numberOfElements) {
		node = new UnionFindNode[numberOfElements + 1];
	}

	int find (int ele) {
		int theRoot = ele;//theRoot??????? 

		/*????*/
		while (!node[theRoot].root) {
			theRoot = node[theRoot].parent;
		}

		/*????*/
		//???????,?????“???”???“??”
		//????????????????,??????????????
		int currentNode = ele;  //?ele?? 
		while (currentNode != theRoot) {
			int k = node[currentNode].parent;
			node[currentNode].parent = theRoot;//???????????? 
			currentNode = k;
		}

		return theRoot;
	}
	void unite (int rootA, int rootB) {
		//????????????rootA?rootB,??????????????
		if (node[rootA].parent < node[rootB].parent) {
			//A???,?A????
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

//?????????
template<class T>
class linkedWGraph {
protected:
	int _vertex_num;			//???? 
	int _edge_num;				//??? 
	chain<T>* _chain_heads;		//????
	int* visited;				//??????????
	int _label = 1;				//????

	//????????
	void _dfs (int head) {
		visited[head] = _label;

		int u;
		myIterator* iv = iterator (head);

		//?????????????
		while ((u = iv->moveNext ()) != 0) {
			if (visited[u] != _label)
				_dfs (u);
		}

		delete iv;
		return;
	}
	void _checkVertex (int theVertex) const {//??????? 
		if (theVertex<1 || theVertex>_vertex_num) {
			cerr << "the vertex:" << theVertex << " is not permissible";
			exit (1);
		} else return;
	}
public:

	//??????
	void output (ostream& out) {
		for (int i = 1; i <= _vertex_num; i++) {
			out << "_chain_heads[" << i << "]="; _chain_heads[i].output ();
			out << endl;
		}
	}

	//???
	linkedWGraph (int vnum) {
		_vertex_num = vnum;
		_edge_num = 0;
		_chain_heads = new chain<int>[_vertex_num + 1];
	}
	//??
	~linkedWGraph () {
		delete[] _chain_heads;  //????????chain??????? 
	}
	int numberOfVertices () const { return _vertex_num; }
	int numberOfEdges () const { return _edge_num; }
	bool directed () const { return false; }
	bool weight () const { return true; }
	void insertEdge (int v1, int v2, int weight) {
		if (v1<1 || v2<1 || v1>_vertex_num || v2>_vertex_num || v1 == v2) {//???? 
			cerr << "(" << v1 << "," << v2 << ") is not a permissible edge" << endl;
			exit (1);
		}

		//??????,???
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

			//v,j??????????,??????????? 
			if (_head != nullptr && j != nullptr) {
				_edge_num--;//????
			}
		}
	}

	//????????????
	int degree (int Vertex) {
		_checkVertex (Vertex);
		return _chain_heads[Vertex].size ();
	}

	class myIterator {
	protected:
		chain<T>* _head; //????? 
		node<T>* _current_vertex;//??????? 
	public:
		myIterator (chain<T>* theVertex) {
			_head = theVertex;
			_current_vertex = _head->_head;
		}
		~myIterator () {}
		//????????,????,????
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
			//???????????????,????????
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

	//????????? 
	bool connected () {

		visited = new int[_vertex_num + 1];
		for (int i = 1; i <= _vertex_num; i++) {
			visited[i] = 0;
		}

		//??????1????????
		dfs (1, visited, 1);

		//????????????,??????,?????
		for (int i = 1; i <= _vertex_num; i++) {
			if (visited[i] == 0) {
				return false;
			}
		}
		return true;
	}

	//??????,_reach[i]???????????v??????? 
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

	//???????,lables[i]???i??????? 
	int getCC (int* lables) {
		int i = 0;

		//??,lable??????????,????????
		int label = 0;
		for (i = 1; i <= _vertex_num; i++) {
			if (lables[i] == 0) {//?????????,?????bfs?? 
				label++;
				bfs (i, lables, label);  //??????? 
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

	//??DFS??
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
				//?????
				u = iv->moveNext ();
			}
		}
	}


	int dijkstra (int start, int dest, int pre[]) {
		//??????,?????????,pre??start?dest???dest?????? 

		//L[i]???start????i??? 
		int* L = new int[_vertex_num + 1];
		fill (L, L + _vertex_num + 1, 100000);
		L[start] = 0;

		//?????????????
		for (node<int>* u = _chain_heads[start]._head; u != nullptr; u = u->next) {
			L[u->data] = u->weight;
			pre[u->data] = start;  //??start???? 
		}
		pre[start] = 0; //??????? 

		//???????
		bool* S = new bool[_vertex_num + 1];
		fill (S, S + _vertex_num + 1, false);

		until (S[dest] == true) {
			int u, temp_head;
			//?????????
			auto getMinDis = [](int L[], bool S[], int _vertex_num) {
				int min = 100000;
				for (int i = 1; i <= _vertex_num; i++) {
					if (L[i] < min && S[i] == false)
						min = L[i];
				}
				return min;
			};
			int min_dis = getMinDis (L, S, _vertex_num);
			//?????????????,???S??
			for (u = 1; u <= _vertex_num; u++) {
				if (S[u] == false && L[u] == min_dis) {
					S[u] = true;
					temp_head = u;
					break;
				}
			}

			//???????????,?????????,???????,?????
			for (node<int>* u = _chain_heads[temp_head]._head; u != nullptr; u = u->next) {
				if (S[u->data] == false && L[temp_head] + (u->weight) < L[u->data]) {
					L[u->data] = L[temp_head] + u->weight;
					pre[u->data] = temp_head; //??v????u 
				}
			}
		}
		return L[dest];
	}

	//???,????????k??
	bool kruskal (edge<T>* spanningTreeEdges) {
		//heap?????????????
		//fastUnionFind??????????????

		//??? ?????????,??????????
		minHeap<edge<T>> heap;
		for (int i = 1; i <= _vertex_num; i++) {
			myIterator* ii = iterator (i);
			int j;
			T w;
			while ((j = ii->moveNext (w)) != 0) {
				//??,????????????
				if (i < j) {
					heap.push (edge<int> (i, j, w));
				}
			}
		}

		//??? ????,???,unite???????,find?????????
		fastUnionFind S (_vertex_num);
		int k = 0;  //??
		while (_edge_num > 0 && k < _vertex_num - 1) {//??????????????
			edge<T> x = heap.getTop (); heap.pop ();
			_edge_num--;
			int seta = S.find (x.getFrom ());
			int setb = S.find (x.getTo ());
			//??????????????x 
			//????????,???????????,?????????????
			if (seta != setb) {
				spanningTreeEdges[k++] = x;
				S.unite (seta, setb);
			}
		}

		//???????????,????????,??????????
		return (k == _vertex_num - 1);
	}

	//??????prim??,???????
	bool prim (edge<T>* spanningTreeEdges) {
		//??????,???k??,???????????,????????????????????
		minHeap<edge<T>> heap;
		myIterator* i = iterator (1);
		int j;  T w;
		while ((j = i->moveNext (w)) != 0) {
			edge<T> tem (1, j, w);
			heap.push (tem);
		}

		bool* S = new bool[_vertex_num + 1];//S ????????
		fill (S, S + _vertex_num + 1, false);
		S[1] = true;


		int k = 0;
		while (!heap.empty () && k < _vertex_num - 1) {
			//??????S??
			edge<T> x = heap.getTop ();
			heap.pop ();
			int a = x.getFrom ();
			int b = x.getTo ();
			if (S[b] == false) {
				spanningTreeEdges[k++] = edge<T> (a, b, x.getWeight ());
			}
			S[b] = true;


			//???,????
			heap._clearAndInit ();
			for (int i = 1; i <= _vertex_num; i++) {
				if (S[i] == true) {
					myIterator* cur = iterator (i);
					while ((j = cur->moveNext (w)) != 0) {
						if (S[j] != true) {
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

//????? 
template<class W>
class adjacencyWGraph {
protected:
	int _vertex_num;       //???? 
	int _edge_num;       //???? 
	W** _weights;       //???? 
	W _no_edge;    //???????
	int* _reach;  //???? 
	int _label = 1;

	void _dfs (int v) {
		//??????????
		_reach[v] = _label;  int u;
		//cout<<"??????:"<<v<<endl;
		myIterator* iv = iterator (v);  //???<T>????,????? 
		while ((u = iv->next ()) != 0) {
			//?v???????u???????? 
			if (_reach[u] != _label) {
				_dfs (u);  //u??????????? 
			}
		}

		delete iv;
		return;
	}

public:
	adjacencyWGraph (int v = 0, W no_edgei = 0) {
		//????
		if (v < 0) cerr << "??????????!" << endl;
		_vertex_num = v;
		_no_edge = no_edgei;
		_edge_num = 0;

		_weights = new W * [_vertex_num + 1];
		for (int i = 0; i < _vertex_num + 1; i++) {
			//???? 
			_weights[i] = new W[_vertex_num + 1];
		}
		for (int i = 1; i <= _vertex_num; i++) {
			//??????? 
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
		_weights = NULL;  //???NULL???????,??????? 
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
			//??????????????????? 
			for (int i = _current_vertex; i <= _vertex_num; i++) {
				if (_row[i] != _no_edge) {
					//??????? 
					_current_vertex = i + 1;
					theWeight = _row[i];
					return i;
				}
			}
			//?????????? 
			_current_vertex = _vertex_num + 1;
			return 0;
		}
		int next () {
			//????????????? 
			for (int i = _current_vertex; i <= _vertex_num; i++) {
				if (_row[i] != _no_edge) {//??????? 
					_current_vertex = i + 1;
					//cout<<"i="<<i<<endl;
					return i;
				}
			}
			//?????????? 
			_current_vertex = _vertex_num + 1;
			return 0;
		}
	protected:
		W* _row;              //??????? 
		W _no_edge;            //theRow[i]==noEdge,???????????i?? 
		int _vertex_num;               //??? 
		int _current_vertex;   //??????? 
	};
	myIterator* iterator (int indexi) {
		//????indexi???? 
		_checkVertex (indexi);
		return new myIterator (_weights[indexi], _no_edge, _vertex_num);
	}
	void _checkVertex (int theVertex) const {
		//??????? 
		if (theVertex<1 || theVertex>_vertex_num) {
			cerr << "the vertex:" << theVertex << " is not permissible";
			exit (1);
		} else return;
	}
	bool directed () const { return false; }
	void insertEdge (edge<W>* theEdge) {
		//???,???????,??theEdge->weight()?????
		int v1 = theEdge->getFrom ();
		int v2 = theEdge->getTo ();
		if (v1<1 || v2<1 || v1>_vertex_num || v2>_vertex_num || v1 == v2) {
			//???? 
			cerr << "(" << v1 << "," << v2 << ") is not a permissible edge" << endl;
			exit (1);
		}
		if (_weights[v1][v2] == _no_edge) {
			_edge_num++;
		}
		_weights[v2][v1] = _weights[v1][v2] = theEdge->weight;
	}
	void eraseEdge (int i, int j) {
		//???(i,j),????????????? 
		if (i >= 1 && j >= 1 && i <= _vertex_num && j <= _vertex_num && _weights[i][j] != _no_edge) {
			_weights[i][j] = _weights[j][i] = _no_edge;
			_edge_num--;
		}
	}
	int Degree (int Vertex) {
		//????Vertex??
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
		//????????? 
		if (directed ()) {
			cerr << "??????!" << endl;
			exit (2);
		}

		_reach = new int[_vertex_num + 1];
		for (int i = 1; i <= _vertex_num; i++) {
			_reach[i] = 0;
		}

		dfs (1, _reach, 1); //??????1????????

		for (int i = 1; i <= _vertex_num; i++) {
			//????????????
			if (_reach[i] == 0) {
				return false;
			}
		}

		return true;
	}
	void bfs (int v, int reach[], int label) {
		//??????,reach[i]???????????v??????? 
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
		//???????,c[i]???i??????? 
		int i = 0;
		for (i = 0; i <= _vertex_num; i++) {
			c[i] = 0;
		}

		int label = 0;  //????????? 
		for (i = 1; i <= _vertex_num; i++) {
			if (c[i] == 0) {
				//?????????,?????bfs?? 
				label++;
				bfs (i, c, label);  //??????? 
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

		while (!s.empty ()) //?stack??? 
		{
			int w = s.top ();
			s.pop ();
			myIterator* iv = iterator (w);	  u = iv->next ();
			while (u != 0)  //????????w?????? 
			{
				if (reach[u] != _label) //???????????j 
				{
					reach[u] = _label;
					s.push (u);
					cout << u << " ";
					iv = iterator (u);	//?iv???u??????? 
				} else {//???????
					u = iv->next ();
					if (u == 0 && s.empty () != true)  s.pop (); //???????????
				}
			}
		}
	}
	/*????????????*/
	int Dijkstra (int start, int dest, int path[]) {
		//??????,?????????,path??start?dest???dest?????? 

		int* L = new int[_vertex_num + 1];  //L[i]???start????i??? 
		for (int i = 1; i <= _vertex_num; i++)  L[i] = _weights[start][i];  L[start] = 0;
		bool* S = new bool[_vertex_num + 1];
		for (int i = 1; i <= _vertex_num; i++)  S[i] = false;  //S[i]??start???i??????? 
		for (int i = 1; i <= _vertex_num; i++) {
			path[i] = (L[i] == _no_edge) ? -1 : start;
		}
		path[start] = 0;    //??????? 
		for (int i = 1; i <= _vertex_num; i++) {

			auto Minium = [](int L[], bool S[], int n) {
				//?L[1:n]??????????S?????? 
				int min = 100000;
				for (int i = 1; i <= n; i++) {
					if (L[i] < min && S[i] == false) {
						min = L[i];
					}
				}
				return min;
			};

			if (S[i] == false && L[i] == Minium (L, S, _vertex_num)) {
				S[i] = true;  //?u?????S?

				//????????
				for (int j = 1; j <= _vertex_num; j++) {//???????S???v 
					if (S[j] == false && L[i] + _weights[i][j] < L[j]) {
						L[j] = L[i] + _weights[i][j];
						path[j] = i;   //??v????u 
					}
				}
			}
		}
		return L[dest];
	}
	bool kruskal (edge<W>* spanningTreeEdges) {
		//??????,????????true,?sTE[0:n-2]?????????? 
		//??,??????????,???????,????????
		//?????????

		edge<W>* Edge = new edge<W>[_edge_num + 1];
		int k = 1;  //??Edge??? 

		//???edge?????:??????edge??
		for (int i = 1; i <= _vertex_num; i++) {//???????i?? 
			myIterator* ii = iterator (i);
			int j; W w;
			while ((j = ii->next (w)) != 0) {
				if (i < j) { //?????? 
					Edge[k++] = edge<int> (i, j, w);
				}
			}
		}
		//?????????????
		minHeap<edge<W>> heap;

		heap.initialize (Edge, _edge_num);  //cout<<heap<<endl;
		fastUnionFind uf (_vertex_num);
		k = 0;  //??
		while (_edge_num > 0 && k < _vertex_num - 1) {

			//?????????????? 
			edge<W> x = heap.top ();
			heap.pop ();
			_edge_num--;
			int a = uf.find (x.getFrom ());
			int b = uf.find (x.getTo ());
			if (a != b) {//??????????????x 
				spanningTreeEdges[k++] = x;
				uf.unite (a, b);
			}
		}
		return (k == _vertex_num - 1);
	}
	bool prim (edge<W>* spanningTreeEdges) {
		//spanningTreeEdges???????? 
		minHeap<edge<W>> heap;

		bool* TV = new bool[_vertex_num + 1];      //TV?????????
		for (int i = 1; i <= _vertex_num; i++)
			TV[i] = false;
		TV[1] = true;

		myIterator* i = iterator (1);
		int j;
		W w;

		//?????????,?????
		while ((j = i->next (w)) != 0) {
			edge<W> tem (1, j, w);
			heap.push (tem);
		}


		int k = 0;   //??????? 
		while (!heap.empty () && k < _vertex_num - 1) {
			edge<W> x = heap.top ();  //???????? 
			heap.pop ();
			int a = x.getFrom ();
			int b = x.getTo ();
			if (TV[b] == false) { //??TV[a]==true 
				spanningTreeEdges[k++] = edge<W> (a, b, x.weight ());
			}
			TV[b] = true;
			i = iterator (b);
			while ((j = i->next (w)) != 0) {
				if (j > b) {
					//???????? 
					edge<W> tem (b, j, w);
					heap.push (tem);
				}
			}
		}
		delete[] TV;      //TV?????????

		return (k == _vertex_num - 1);
	}

};



int main () {
#pragma warning(disable:4996)
	freopen ("input.txt", "r", stdin);
	int n, m, q;//? ? ?
	cin >> n >> m>>q;

	//??????????
	adjacencyWGraph<int> g (n);

	//?????
	for (int i = 0; i < m; i++) {
		int v1, v2, w;  
		cin >> v1 >> v2 >> w;
		edge<int>* Edge = new edge<int> (v1, v2, w);
		//g.insertEdge (v1, v2, w);
		g.insertEdge (Edge);
	}

	//??????????
	edge<int>* STE = new edge<int>[n - 1];

	for (int i = 0; i < q; i++) {
		int count1 = 0;
		//cout << "kruskal?????????(v1,v2,w)??:" << endl;
		if (g.kruskal (STE) == true) {
			for (int i = 0; i <= n - 2; i++)
				//cout << STE[i] << endl;
				count1 += STE[i].getWeight ();

		}
		cout << count1 << "\n";
	}
	//cout << "prim?????????(v1,v2,w)??:" << endl;

	//for (int i = 0; i < q; i++) {
	//	int count2 = 0;
	//	if (g.prim (STE) == true) {
	//		for (int i = 0; i <= n - 2; i++)
	//			count2 += STE[i].getWeight ();
	//	}
	//	cout << count2 << "\n";
	//}

	return 0;
}
