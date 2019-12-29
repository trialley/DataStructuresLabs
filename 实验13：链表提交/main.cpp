#include<iostream>
#include<cstdlib>
#define until(re) while(!(re))
using namespace std;

template<class T>
/*分布式排序*/
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

		//将新的头部元素逐层向下移动，向下移动到左子还是右子？这里需要判断
		//起码有一个左子树，所以要<=
		while (child_index <= _size) {
			//如果左子比右子大，则根应当与右子交换，使新根小，这样可以保持最小堆特性
			//如果左子树卡到了size位置，说明没有右子树，不必寻找左右中最小的元素
			if (child_index < _size && _head[child_index] > _head[child_index + 1]) {
				child_index++;
			}
			//如果根比两个子都小，那直接退出就行了，不必再交换
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
	void pushShow (const T& datai) {
		//进行越界检查
		if (_size == _length - 1) {
			_extLength ();
		}

		int insert_index = ++_size;
		_head[insert_index] = datai;
		for (int i = 1; i <= _size; i++) {
			cout << _head[i] << " ";
		}
		cout << "\n";

		while (insert_index != 1 && _head[insert_index / 2] > datai) {//插入元素的父元素不小于插入元素，说明需要调整
			_head[insert_index] = _head[insert_index / 2]; //该父元素放到子节点位置
			insert_index /= 2;//子节点位置指向原父节点那里去，也即发生父子交换，只不过子元素还没有插入
			_head[insert_index] = datai;

			//继续循环查看新的父节点
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
	queue (int initialCapacity = 10) {//构造函数 
		if (initialCapacity < 0) {
			////std::cerr << "队列长度必须大于0！" << std::endl;
		} else {
			_queue = new T[initialCapacity];
			arrayLength = initialCapacity;
			qFront = qBack = 0;  //这里是从_queue[1]开始插入元素 
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
			//std::cerr << "队列为空" << std::endl;
		}
	}
	T& back () {
		if (empty () != true)
			return _queue[qBack];
		else {
			//std::cerr << "队列为空" << std::endl; exit (1);
		}
	}
	T pop () {//从队首删除元素 
		T* p = &front (); //这里已经判断了队列是否为空 
		T temp = (*p);
		qFront = (qFront + 1) % arrayLength;
		(*p).~T ();  //析构首元素好像不能表示int的删除...，就是无法恢复到初始化以前的状态
		return temp;
	}
	void push (const T& ele) {//从队尾添加元素 
		if ((qBack + 1) % arrayLength == qFront) {//队列将满，加倍数组长度 
			T* new_queue = new T[2 * arrayLength];
			int start = (qFront + 1) % arrayLength;
			if (start == 0 || start == 1) {//未形成环 
				std::copy (_queue + start, _queue + qBack + 1, new_queue);
			} else {//形成了环 
				std::copy (_queue + start, _queue + arrayLength, new_queue);
				//复制第2段(start,队列末端，新队列起点） 
				std::copy (_queue, _queue + qBack + 1, new_queue + (arrayLength - start));
				//复制第1段（原队列首端，qback,新队列第arraylength-start个位置） 
			}
			qFront = (arrayLength) * 2 - 1;
			qBack = arrayLength - 1 - 1;//重新设置首尾游标 
			arrayLength = arrayLength * 2;
			delete[] _queue;
			_queue = new_queue;
		}
		//把元素插入队列的尾部
		qBack = (qBack + 1) % arrayLength;
		_queue[qBack] = ele;

	}
	void output () {
		for (int i = qFront; i < qBack; i++)
			std::cout << _queue[i];
		std::cout << std::endl;
	}
private:
	int qFront;  //队列中第一个元素的前一个未知 
	int qBack;//队列最后一个元素的位置 
	int arrayLength;  //队列的容量 
	T* _queue;	 //队列元素 
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
		//判断是否为空
		//有的实现版本中getTop输入引用，栈空则返回原数值，这样很不符合职责单一原则
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

		/*用于缩小缓冲区的代码*/
		if (size () < bufferLength / 4) {
			_shLength ();
		}
	}
	void push (const T theElement) {
		//判断缓冲区长度并扩大缓冲区
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
	node& operator=(node& A) {//结点赋值 
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
			for (int i = 1; i < initialCapacity; i++) {  //等于1的话前面已经创建好了一个节点 
				p2 = new node<T>;
				p2->data = A[i];
				p1->next = p2;
				p1 = p2;
			}
			_size = initialCapacity;
		}
		if (initialCapacity <= 0) cerr << "初始长度过小！" << endl;
	}
	chain (const chain<T>& A) {
		_size = A._size;
		if (_size == 0) {//此表为空 
			_head = nullptr;
		} else {//TargetNode指向A的节点，SourceNode指向此链表的节点
				//直接节点赋值会变成浅复制，ciao! 
			node<T>* SourceNode = new node<T>;
			node<T>* pre_node, * TargetNode;
			_head = SourceNode;
			TargetNode = A._head;
			SourceNode->data = TargetNode->data;

			for (int i = 1; i < _size; i++) {  //等于1的话前面已经创建好了一个节点
				TargetNode = TargetNode->next;
				pre_node = new node<T> (TargetNode->data);  //这里给pre_node创建了一个新空间并初始化 
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
	T& get (int theIndex) const {//返回索引是theIndex节点的data内容 
		_checkIndex (theIndex);
		node<T>* cur_node = _head;
		for (int i = 0; i < theIndex; i++) {
			cur_node = cur_node->next;
		}
		return cur_node->data;
	}
	T getWeight (int ele) const {//返回元素是ele节点的weight
		node<T>* cur_node;
		cout << "vetrex=" << ele;
		for (cur_node = _head; cur_node != nullptr; cur_node = cur_node->next) {
			if (cur_node->data == ele)
				return cur_node->weight;
		}
		return -1;
	}
	int indexOf (T& theElement) const {//返回节点元素内容是theElement的节点索引，若未找到则返回-1 
		node<T>* cur_node = _head;
		for (int i = 0; i < _size; i++) {
			if (cur_node->data == theElement)
				return i;
			else
				cur_node = cur_node->next;
		}
		return -1;
	}
	node<T>* eraseByElement (int theVertex) {//搜索链表并查找顶点等于theVertex的元素，若找到则删除它并返回这个元素的指针 
		node<T>* p = _head, * tp = nullptr;
		while (p != nullptr) {
			if (p->data == theVertex) {
				if (p == _head) //删头结点 
					_head = _head->next;
				else {
					tp->next = p->next;
					delete p;
					return p;
				}
			} else {//元素不等于theVertex 
				tp = p;
				p = p->next;
			}
		}
		return nullptr;  //找不到的话返回nullptr 
	}

	void eraseByIndex (int theIndex) {//从链表中删除索引为theIndex的节点 
		_checkIndex (theIndex);
		node<T>* deletenode;
		if (theIndex == 0) {//删除头结点 
			deletenode = _head;
			_head = _head->next;
		} else {
			node<T>* p = _head;
			for (int i = 0; i < theIndex - 1; i++) {
				p = p->next;
			}
			//此时已经找到要删除的结点的前驱节点 
			deletenode = p->next;
			p->next = p->next->next;
		}
		_size--;
		delete deletenode;
	}
	void insertAfterIndex (int theIndex, const T& ele, T weight) {//将ele元素插入索引为theIndex位置的新节点 
		_checkIndex (theIndex);
		if (theIndex == 0) {//插入头节点 
			node<T>* p = new node<T> (ele, weight, _head);
			_head = p;
		} else {
			node<T>* p = new node<T> (ele, weight);//待插入节点
			node<T>* cur_node = _head;
			for (int i = 0; i < theIndex - 1; i++) {
				cur_node = cur_node->next;
			}
			//此时已经找到要插入的结点的前驱节点 
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

	void clear () {//清表操作 
		node<T>* deletenode, * p = _head;
		for (int i = 0; i < _size; i++) {
			deletenode = p;
			p = p->next;
			delete deletenode;
		}
		_head = nullptr;
		_size = 0;
	}
	friend ostream& operator<<(ostream& out, const chain<T> A) {//这里要调用复制构造函数 
		if (A._size == 0) { out << "null" << endl;  return out; } else {
			node<T>* p = A._head;
			for (int i = 0; i < A._size; i++) {
				out << p->data << " " << p->weight << " ";
				p = p->next;
			}
			return out;
		}
	}
	class iterator {//构造函数、*&、前后自加、！=、== 
	protected:
		node<T>* _node = nullptr;
	public:
		iterator (node<T>* theNode) {
			_node = theNode;
		}
		iterator () {}

		T& operator*() { return _node->data; }  //取内容运算符，作为引用返回 
		T* operator->() { return &(_node->data); }  //取地址运算符，作为指针返回 
		iterator& operator++() {//前加 
			_node = _node->next;
			return *this;
		}
		iterator operator++(int) {//后加 
			iterator temp = *this;
			_node = _node->next;
			return temp;
		}
		bool operator!=(const iterator I)const {
			if (_node == I._node) return false;  //这里我没有定义_node的==，为什么没有报错？ 
			else return true;
		}
		bool operator==(const iterator I)const {
			if (_node == I._node) return true;
			else return false;
		}

	};

	//protected:
	void _checkIndex (int theIndex) const {//确定索引的有效性，防止越界
		if (theIndex<0 || theIndex>_size) {
			cerr << "index=" << theIndex << ",listSize=" << _size << "请检查索引的有效性！" << endl;
		}
	}
	node<T>* _head; //指向链表第一个元素的指针 
	int _size;//链表的元素个数 	
};

class UnionFind {//用树的链表描述来表示并查集，用到模拟指针 
public:
	UnionFind (int numberOfElements) {
		parent = new int[numberOfElements + 1];
		for (int i = 1; i <= numberOfElements; i++) {
			parent[i] = 0;
		}
	}

	int find (int ele) {//返回ele元素所在的树根 
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
/************一下是应用了重量规则和路径紧缩优化的快速并查集算法**************/
struct UnionFindNode {
	int parent;//若为根节点，则parent是树的重量，否则是父节点的索引 ，一开始是1，不是说1是他的父亲，而是说1是他这颗树的节点数
	bool root; //标志是否为根节点 
	UnionFindNode () :parent (1), root (true) {}
};

class fastUnionFind {//用重量规则和路径紧缩来优化并查集
public:
	fastUnionFind (int numberOfElements) {
		node = new UnionFindNode[numberOfElements + 1];
	}

	int find (int ele) {
		int theRoot = ele;//theRoot是最终的根节点 

		/*不断寻根*/
		while (!node[theRoot].root) {
			theRoot = node[theRoot].parent;
		}

		/*路径紧缩*/
		//下面是紧缩路径，一路上所有“父节点”都重新“认爹”
		//路径紧缩增加了单个查找的操作时间，但它减少了此后查找操作的时间
		int currentNode = ele;  //从ele开始 
		while (currentNode != theRoot) {
			int k = node[currentNode].parent;
			node[currentNode].parent = theRoot;//让模拟指针直接指向根节点 
			currentNode = k;
		}

		return theRoot;
	}
	void unite (int rootA, int rootB) {
		//用重量规则合并根不同的数rootA和rootB，也就是编号大的爸爸成为新爸爸
		if (node[rootA].parent < node[rootB].parent) {
			//A比较轻，把A作为子树
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
		//heap中包含了还未加入生成树的边
		//fastUnionFind中包含了已经加入到生成树的点

		//小根堆 表示边集的效率较好,此处初始化所有边集合
		minHeap<edge<T>> heap;
		for (int i = 1; i <= _vertex_num; i++) {
			myIterator* ii = iterator (i);
			int j;
			T w;
			while ((j = ii->moveNext (w)) != 0) {
				//去重，无向图中一条边会出现两次
				if (i < j) {
					heap.push (edge<int> (i, j, w));
				}
			}
		}

		//并查集 避免环路，并查集，unite为将点加入集合，find查找改点集合的编号
		fastUnionFind S (_vertex_num);
		int k = 0;  //索引
		while (_edge_num > 0 && k < _vertex_num - 1) {//生成树没有完成并且还有边存在
			edge<T> x = heap.getTop (); heap.pop ();
			_edge_num--;
			int seta = S.find (x.getFrom ());
			int setb = S.find (x.getTo ());
			//保证在没有环路的情况下选取边x 
			//两边属于不同集合，代表两点之前没有相连过，也即选取当前边不会形成环路
			if (seta != setb) {
				spanningTreeEdges[k++] = x;
				S.unite (seta, setb);
			}
		}

		//索引与节点数减一不相等，则说明该图不连通，无法形成完整的生成树
		return (k == _vertex_num - 1);
	}

	//使用小根堆的prim算法，适用于边多的图
	bool prim (edge<T>* spanningTreeEdges) {
		//初始化小根堆，注意跟k不同，这里堆里存的不是所有边，而是当前集合到另一个集合所有点的直接距离
		minHeap<edge<T>> heap;
		myIterator* i = iterator (1);
		int j;  T w;
		while ((j = i->moveNext (w)) != 0) {
			edge<T> tem (1, j, w);
			heap.push (tem);
		}

		bool* S = new bool[_vertex_num + 1];//S 已在树中的顶点集
		fill (S, S + _vertex_num + 1, false);
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

//加权无向图 
template<class W>
class adjacencyWGraph {
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
		_weights[v2][v1] = _weights[v1][v2] = theEdge->weight;
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
	/*到每个点的最短路长与路径*/
	int Dijkstra (int start, int dest, int path[]) {
		//返回最短路长，记录下最短路的路径，path是从start到dest路径中dest前的那个顶点 

		int* L = new int[_vertex_num + 1];  //L[i]就是从start点到顶点i的距离 
		for (int i = 1; i <= _vertex_num; i++)  L[i] = _weights[start][i];  L[start] = 0;
		bool* S = new bool[_vertex_num + 1];
		for (int i = 1; i <= _vertex_num; i++)  S[i] = false;  //S[i]表示start到顶点i的最短路已求得 
		for (int i = 1; i <= _vertex_num; i++) {
			path[i] = (L[i] == _no_edge) ? -1 : start;
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



int main () {
#pragma warning(disable:4996)
	freopen ("input.txt", "r", stdin);
	int n, m, q;//点 边 查
	cin >> n >> m>>q;

	//初始化邻接链表无向图
	adjacencyWGraph<int> g (n);

	//初始化各边
	for (int i = 0; i < m; i++) {
		int v1, v2, w;  
		cin >> v1 >> v2 >> w;
		edge<int>* Edge = new edge<int> (v1, v2, w);
		//g.insertEdge (v1, v2, w);
		g.insertEdge (Edge);
	}

	//进行最小生成树的求解
	edge<int>* STE = new edge<int>[n - 1];

	for (int i = 0; i < q; i++) {
		int count1 = 0;
		//cout << "kruskal最小生成树中每条边(v1,v2,w)如下:" << endl;
		if (g.kruskal (STE) == true) {
			for (int i = 0; i <= n - 2; i++)
				//cout << STE[i] << endl;
				count1 += STE[i].getWeight ();

		}
		cout << count1 << "\n";
	}
	//cout << "prim最小生成树中每条边(v1,v2,w)如下:" << endl;

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