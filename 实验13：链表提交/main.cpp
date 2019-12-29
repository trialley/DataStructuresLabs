#include<iostream>
#include<cstdlib>
#define until(re) while(!(re))
using namespace std;

template<class T>
/*�ֲ�ʽ����*/
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

		//���µ�ͷ��Ԫ����������ƶ��������ƶ������ӻ������ӣ�������Ҫ�ж�
		//������һ��������������Ҫ<=
		while (child_index <= _size) {
			//������ӱ����Ӵ����Ӧ�������ӽ�����ʹ�¸�С���������Ա�����С������
			//���������������sizeλ�ã�˵��û��������������Ѱ����������С��Ԫ��
			if (child_index < _size && _head[child_index] > _head[child_index + 1]) {
				child_index++;
			}
			//������������Ӷ�С����ֱ���˳������ˣ������ٽ���
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
		//����Խ����
		if (_size == _length - 1) {
			_extLength ();
		}

		int insert_index = ++_size;

		while (insert_index != 1 && _head[insert_index / 2] > datai) {//����Ԫ�صĸ�Ԫ�ز�С�ڲ���Ԫ�أ�˵����Ҫ����
			_head[insert_index] = _head[insert_index / 2]; //�ø�Ԫ�طŵ��ӽڵ�λ��
			insert_index /= 2;//�ӽڵ�λ��ָ��ԭ���ڵ�����ȥ��Ҳ���������ӽ�����ֻ������Ԫ�ػ�û�в���

			//����ѭ���鿴�µĸ��ڵ�
		}

		_head[insert_index] = datai;
	}
	void pushShow (const T& datai) {
		//����Խ����
		if (_size == _length - 1) {
			_extLength ();
		}

		int insert_index = ++_size;
		_head[insert_index] = datai;
		for (int i = 1; i <= _size; i++) {
			cout << _head[i] << " ";
		}
		cout << "\n";

		while (insert_index != 1 && _head[insert_index / 2] > datai) {//����Ԫ�صĸ�Ԫ�ز�С�ڲ���Ԫ�أ�˵����Ҫ����
			_head[insert_index] = _head[insert_index / 2]; //�ø�Ԫ�طŵ��ӽڵ�λ��
			insert_index /= 2;//�ӽڵ�λ��ָ��ԭ���ڵ�����ȥ��Ҳ���������ӽ�����ֻ������Ԫ�ػ�û�в���
			_head[insert_index] = datai;

			//����ѭ���鿴�µĸ��ڵ�
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
	queue (int initialCapacity = 10) {//���캯�� 
		if (initialCapacity < 0) {
			////std::cerr << "���г��ȱ������0��" << std::endl;
		} else {
			_queue = new T[initialCapacity];
			arrayLength = initialCapacity;
			qFront = qBack = 0;  //�����Ǵ�_queue[1]��ʼ����Ԫ�� 
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
			//std::cerr << "����Ϊ��" << std::endl;
		}
	}
	T& back () {
		if (empty () != true)
			return _queue[qBack];
		else {
			//std::cerr << "����Ϊ��" << std::endl; exit (1);
		}
	}
	T pop () {//�Ӷ���ɾ��Ԫ�� 
		T* p = &front (); //�����Ѿ��ж��˶����Ƿ�Ϊ�� 
		T temp = (*p);
		qFront = (qFront + 1) % arrayLength;
		(*p).~T ();  //������Ԫ�غ����ܱ�ʾint��ɾ��...�������޷��ָ�����ʼ����ǰ��״̬
		return temp;
	}
	void push (const T& ele) {//�Ӷ�β���Ԫ�� 
		if ((qBack + 1) % arrayLength == qFront) {//���н������ӱ����鳤�� 
			T* new_queue = new T[2 * arrayLength];
			int start = (qFront + 1) % arrayLength;
			if (start == 0 || start == 1) {//δ�γɻ� 
				std::copy (_queue + start, _queue + qBack + 1, new_queue);
			} else {//�γ��˻� 
				std::copy (_queue + start, _queue + arrayLength, new_queue);
				//���Ƶ�2��(start,����ĩ�ˣ��¶�����㣩 
				std::copy (_queue, _queue + qBack + 1, new_queue + (arrayLength - start));
				//���Ƶ�1�Σ�ԭ�����׶ˣ�qback,�¶��е�arraylength-start��λ�ã� 
			}
			qFront = (arrayLength) * 2 - 1;
			qBack = arrayLength - 1 - 1;//����������β�α� 
			arrayLength = arrayLength * 2;
			delete[] _queue;
			_queue = new_queue;
		}
		//��Ԫ�ز�����е�β��
		qBack = (qBack + 1) % arrayLength;
		_queue[qBack] = ele;

	}
	void output () {
		for (int i = qFront; i < qBack; i++)
			std::cout << _queue[i];
		std::cout << std::endl;
	}
private:
	int qFront;  //�����е�һ��Ԫ�ص�ǰһ��δ֪ 
	int qBack;//�������һ��Ԫ�ص�λ�� 
	int arrayLength;  //���е����� 
	T* _queue;	 //����Ԫ�� 
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
		//�ж��Ƿ�Ϊ��
		//�е�ʵ�ְ汾��getTop�������ã�ջ���򷵻�ԭ��ֵ�������ܲ�����ְ��һԭ��
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

		/*������С�������Ĵ���*/
		if (size () < bufferLength / 4) {
			_shLength ();
		}
	}
	void push (const T theElement) {
		//�жϻ��������Ȳ����󻺳���
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
	node& operator=(node& A) {//��㸳ֵ 
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
			for (int i = 1; i < initialCapacity; i++) {  //����1�Ļ�ǰ���Ѿ���������һ���ڵ� 
				p2 = new node<T>;
				p2->data = A[i];
				p1->next = p2;
				p1 = p2;
			}
			_size = initialCapacity;
		}
		if (initialCapacity <= 0) cerr << "��ʼ���ȹ�С��" << endl;
	}
	chain (const chain<T>& A) {
		_size = A._size;
		if (_size == 0) {//�˱�Ϊ�� 
			_head = nullptr;
		} else {//TargetNodeָ��A�Ľڵ㣬SourceNodeָ�������Ľڵ�
				//ֱ�ӽڵ㸳ֵ����ǳ���ƣ�ciao! 
			node<T>* SourceNode = new node<T>;
			node<T>* pre_node, * TargetNode;
			_head = SourceNode;
			TargetNode = A._head;
			SourceNode->data = TargetNode->data;

			for (int i = 1; i < _size; i++) {  //����1�Ļ�ǰ���Ѿ���������һ���ڵ�
				TargetNode = TargetNode->next;
				pre_node = new node<T> (TargetNode->data);  //�����pre_node������һ���¿ռ䲢��ʼ�� 
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
	T& get (int theIndex) const {//����������theIndex�ڵ��data���� 
		_checkIndex (theIndex);
		node<T>* cur_node = _head;
		for (int i = 0; i < theIndex; i++) {
			cur_node = cur_node->next;
		}
		return cur_node->data;
	}
	T getWeight (int ele) const {//����Ԫ����ele�ڵ��weight
		node<T>* cur_node;
		cout << "vetrex=" << ele;
		for (cur_node = _head; cur_node != nullptr; cur_node = cur_node->next) {
			if (cur_node->data == ele)
				return cur_node->weight;
		}
		return -1;
	}
	int indexOf (T& theElement) const {//���ؽڵ�Ԫ��������theElement�Ľڵ���������δ�ҵ��򷵻�-1 
		node<T>* cur_node = _head;
		for (int i = 0; i < _size; i++) {
			if (cur_node->data == theElement)
				return i;
			else
				cur_node = cur_node->next;
		}
		return -1;
	}
	node<T>* eraseByElement (int theVertex) {//�����������Ҷ������theVertex��Ԫ�أ����ҵ���ɾ�������������Ԫ�ص�ָ�� 
		node<T>* p = _head, * tp = nullptr;
		while (p != nullptr) {
			if (p->data == theVertex) {
				if (p == _head) //ɾͷ��� 
					_head = _head->next;
				else {
					tp->next = p->next;
					delete p;
					return p;
				}
			} else {//Ԫ�ز�����theVertex 
				tp = p;
				p = p->next;
			}
		}
		return nullptr;  //�Ҳ����Ļ�����nullptr 
	}

	void eraseByIndex (int theIndex) {//��������ɾ������ΪtheIndex�Ľڵ� 
		_checkIndex (theIndex);
		node<T>* deletenode;
		if (theIndex == 0) {//ɾ��ͷ��� 
			deletenode = _head;
			_head = _head->next;
		} else {
			node<T>* p = _head;
			for (int i = 0; i < theIndex - 1; i++) {
				p = p->next;
			}
			//��ʱ�Ѿ��ҵ�Ҫɾ���Ľ���ǰ���ڵ� 
			deletenode = p->next;
			p->next = p->next->next;
		}
		_size--;
		delete deletenode;
	}
	void insertAfterIndex (int theIndex, const T& ele, T weight) {//��eleԪ�ز�������ΪtheIndexλ�õ��½ڵ� 
		_checkIndex (theIndex);
		if (theIndex == 0) {//����ͷ�ڵ� 
			node<T>* p = new node<T> (ele, weight, _head);
			_head = p;
		} else {
			node<T>* p = new node<T> (ele, weight);//������ڵ�
			node<T>* cur_node = _head;
			for (int i = 0; i < theIndex - 1; i++) {
				cur_node = cur_node->next;
			}
			//��ʱ�Ѿ��ҵ�Ҫ����Ľ���ǰ���ڵ� 
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

	void clear () {//������ 
		node<T>* deletenode, * p = _head;
		for (int i = 0; i < _size; i++) {
			deletenode = p;
			p = p->next;
			delete deletenode;
		}
		_head = nullptr;
		_size = 0;
	}
	friend ostream& operator<<(ostream& out, const chain<T> A) {//����Ҫ���ø��ƹ��캯�� 
		if (A._size == 0) { out << "null" << endl;  return out; } else {
			node<T>* p = A._head;
			for (int i = 0; i < A._size; i++) {
				out << p->data << " " << p->weight << " ";
				p = p->next;
			}
			return out;
		}
	}
	class iterator {//���캯����*&��ǰ���Լӡ���=��== 
	protected:
		node<T>* _node = nullptr;
	public:
		iterator (node<T>* theNode) {
			_node = theNode;
		}
		iterator () {}

		T& operator*() { return _node->data; }  //ȡ�������������Ϊ���÷��� 
		T* operator->() { return &(_node->data); }  //ȡ��ַ���������Ϊָ�뷵�� 
		iterator& operator++() {//ǰ�� 
			_node = _node->next;
			return *this;
		}
		iterator operator++(int) {//��� 
			iterator temp = *this;
			_node = _node->next;
			return temp;
		}
		bool operator!=(const iterator I)const {
			if (_node == I._node) return false;  //������û�ж���_node��==��Ϊʲôû�б��� 
			else return true;
		}
		bool operator==(const iterator I)const {
			if (_node == I._node) return true;
			else return false;
		}

	};

	//protected:
	void _checkIndex (int theIndex) const {//ȷ����������Ч�ԣ���ֹԽ��
		if (theIndex<0 || theIndex>_size) {
			cerr << "index=" << theIndex << ",listSize=" << _size << "������������Ч�ԣ�" << endl;
		}
	}
	node<T>* _head; //ָ�������һ��Ԫ�ص�ָ�� 
	int _size;//�����Ԫ�ظ��� 	
};

class UnionFind {//������������������ʾ���鼯���õ�ģ��ָ�� 
public:
	UnionFind (int numberOfElements) {
		parent = new int[numberOfElements + 1];
		for (int i = 1; i <= numberOfElements; i++) {
			parent[i] = 0;
		}
	}

	int find (int ele) {//����eleԪ�����ڵ����� 
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
/************һ����Ӧ�������������·�������Ż��Ŀ��ٲ��鼯�㷨**************/
struct UnionFindNode {
	int parent;//��Ϊ���ڵ㣬��parent�����������������Ǹ��ڵ������ ��һ��ʼ��1������˵1�����ĸ��ף�����˵1����������Ľڵ���
	bool root; //��־�Ƿ�Ϊ���ڵ� 
	UnionFindNode () :parent (1), root (true) {}
};

class fastUnionFind {//�����������·���������Ż����鼯
public:
	fastUnionFind (int numberOfElements) {
		node = new UnionFindNode[numberOfElements + 1];
	}

	int find (int ele) {
		int theRoot = ele;//theRoot�����յĸ��ڵ� 

		/*����Ѱ��*/
		while (!node[theRoot].root) {
			theRoot = node[theRoot].parent;
		}

		/*·������*/
		//�����ǽ���·����һ·�����С����ڵ㡱�����¡��ϵ���
		//·�����������˵������ҵĲ���ʱ�䣬���������˴˺���Ҳ�����ʱ��
		int currentNode = ele;  //��ele��ʼ 
		while (currentNode != theRoot) {
			int k = node[currentNode].parent;
			node[currentNode].parent = theRoot;//��ģ��ָ��ֱ��ָ����ڵ� 
			currentNode = k;
		}

		return theRoot;
	}
	void unite (int rootA, int rootB) {
		//����������ϲ�����ͬ����rootA��rootB��Ҳ���Ǳ�Ŵ�İְֳ�Ϊ�°ְ�
		if (node[rootA].parent < node[rootB].parent) {
			//A�Ƚ��ᣬ��A��Ϊ����
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
		//heap�а����˻�δ�����������ı�
		//fastUnionFind�а������Ѿ����뵽�������ĵ�

		//С���� ��ʾ�߼���Ч�ʽϺ�,�˴���ʼ�����б߼���
		minHeap<edge<T>> heap;
		for (int i = 1; i <= _vertex_num; i++) {
			myIterator* ii = iterator (i);
			int j;
			T w;
			while ((j = ii->moveNext (w)) != 0) {
				//ȥ�أ�����ͼ��һ���߻��������
				if (i < j) {
					heap.push (edge<int> (i, j, w));
				}
			}
		}

		//���鼯 ���⻷·�����鼯��uniteΪ������뼯�ϣ�find���Ҹĵ㼯�ϵı��
		fastUnionFind S (_vertex_num);
		int k = 0;  //����
		while (_edge_num > 0 && k < _vertex_num - 1) {//������û����ɲ��һ��бߴ���
			edge<T> x = heap.getTop (); heap.pop ();
			_edge_num--;
			int seta = S.find (x.getFrom ());
			int setb = S.find (x.getTo ());
			//��֤��û�л�·�������ѡȡ��x 
			//�������ڲ�ͬ���ϣ���������֮ǰû����������Ҳ��ѡȡ��ǰ�߲����γɻ�·
			if (seta != setb) {
				spanningTreeEdges[k++] = x;
				S.unite (seta, setb);
			}
		}

		//������ڵ�����һ����ȣ���˵����ͼ����ͨ���޷��γ�������������
		return (k == _vertex_num - 1);
	}

	//ʹ��С���ѵ�prim�㷨�������ڱ߶��ͼ
	bool prim (edge<T>* spanningTreeEdges) {
		//��ʼ��С���ѣ�ע���k��ͬ����������Ĳ������бߣ����ǵ�ǰ���ϵ���һ���������е��ֱ�Ӿ���
		minHeap<edge<T>> heap;
		myIterator* i = iterator (1);
		int j;  T w;
		while ((j = i->moveNext (w)) != 0) {
			edge<T> tem (1, j, w);
			heap.push (tem);
		}

		bool* S = new bool[_vertex_num + 1];//S �������еĶ��㼯
		fill (S, S + _vertex_num + 1, false);
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

//��Ȩ����ͼ 
template<class W>
class adjacencyWGraph {
protected:
	int _vertex_num;       //������� 
	int _edge_num;       //�ߵĸ��� 
	W** _weights;       //�ڽ����� 
	W _no_edge;    //��ʾ�����ڵı�
	int* _reach;  //����ָ�� 
	int _label = 1;

	void _dfs (int v) {
		//�ݹ�ʵ�������������
		_reach[v] = _label;  int u;
		//cout<<"��ǰ�ߵ����㣺"<<v<<endl;
		myIterator* iv = iterator (v);  //�����<T>�ͻᱨ��Ϊʲô���� 
		while ((u = iv->next ()) != 0) {
			//��v����һ���ڽӵ�uΪ�����ݹ����� 
			if (_reach[u] != _label) {
				_dfs (u);  //u��һ��û�е�����Ķ��� 
			}
		}

		delete iv;
		return;
	}

public:
	adjacencyWGraph (int v = 0, W no_edgei = 0) {
		//���캯��
		if (v < 0) cerr << "����鶥�����ĺϷ��ԣ�" << endl;
		_vertex_num = v;
		_no_edge = no_edgei;
		_edge_num = 0;

		_weights = new W * [_vertex_num + 1];
		for (int i = 0; i < _vertex_num + 1; i++) {
			//����ռ� 
			_weights[i] = new W[_vertex_num + 1];
		}
		for (int i = 1; i <= _vertex_num; i++) {
			//��ʼ���ڽӾ��� 
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
		_weights = NULL;  //����ΪNULL�Ļ����Ұָ�룬��������Ҳû�� 
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
			//����ָ���������һ���ڽӵ�����ĵ�Ȩֵ 
			for (int i = _current_vertex; i <= _vertex_num; i++) {
				if (_row[i] != _no_edge) {
					//����һ���ڽӵ� 
					_current_vertex = i + 1;
					theWeight = _row[i];
					return i;
				}
			}
			//��������һ���ڽӵ��� 
			_current_vertex = _vertex_num + 1;
			return 0;
		}
		int next () {
			//����ָ���������һ���ڽӵ� 
			for (int i = _current_vertex; i <= _vertex_num; i++) {
				if (_row[i] != _no_edge) {//����һ���ڽӵ� 
					_current_vertex = i + 1;
					//cout<<"i="<<i<<endl;
					return i;
				}
			}
			//��������һ���ڽӵ��� 
			_current_vertex = _vertex_num + 1;
			return 0;
		}
	protected:
		W* _row;              //�ڽӾ���ĵ��� 
		W _no_edge;            //theRow[i]==noEdge�����ҽ���û�й����붥��i�ı� 
		int _vertex_num;               //������ 
		int _current_vertex;   //��ǰ�����Ķ��� 
	};
	myIterator* iterator (int indexi) {
		//���ض���indexi�ĵ����� 
		_checkVertex (indexi);
		return new myIterator (_weights[indexi], _no_edge, _vertex_num);
	}
	void _checkVertex (int theVertex) const {
		//ȷ������Ч���� 
		if (theVertex<1 || theVertex>_vertex_num) {
			cerr << "the vertex:" << theVertex << " is not permissible";
			exit (1);
		} else return;
	}
	bool directed () const { return false; }
	void insertEdge (edge<W>* theEdge) {
		//����ߣ�����ñ��Ѵ��ڣ�����theEdge->weight()�޸ıߵ�Ȩ
		int v1 = theEdge->getFrom ();
		int v2 = theEdge->getTo ();
		if (v1<1 || v2<1 || v1>_vertex_num || v2>_vertex_num || v1 == v2) {
			//Խ�紦�� 
			cerr << "(" << v1 << "," << v2 << ") is not a permissible edge" << endl;
			exit (1);
		}
		if (_weights[v1][v2] == _no_edge) {
			_edge_num++;
		}
		_weights[v2][v1] = _weights[v1][v2] = theEdge->weight;
	}
	void eraseEdge (int i, int j) {
		//ɾ����(i,j),��������ڸñ߾�ʲôҲ���� 
		if (i >= 1 && j >= 1 && i <= _vertex_num && j <= _vertex_num && _weights[i][j] != _no_edge) {
			_weights[i][j] = _weights[j][i] = _no_edge;
			_edge_num--;
		}
	}
	int Degree (int Vertex) {
		//���㶥��Vertex�Ķ�
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
		//�ж�����ͼ�Ƿ���ͨ 
		if (directed ()) {
			cerr << "��ͼ������ͼ��" << endl;
			exit (2);
		}

		_reach = new int[_vertex_num + 1];
		for (int i = 1; i <= _vertex_num; i++) {
			_reach[i] = 0;
		}

		dfs (1, _reach, 1); //���ڽ��ڶ���1�Ŀɴﶥ�������

		for (int i = 1; i <= _vertex_num; i++) {
			//������ж����Ƿ��������
			if (_reach[i] == 0) {
				return false;
			}
		}

		return true;
	}
	void bfs (int v, int reach[], int label) {
		//��������㷨��reach[i]������������ڽ��ڶ���v�Ŀɵ���Ķ��� 
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
		//������ͨ��֧����c[i]�Ƕ���i�����ķ�֧��� 
		int i = 0;
		for (i = 0; i <= _vertex_num; i++) {
			c[i] = 0;
		}

		int label = 0;  //���һ�������ı�� 
		for (i = 1; i <= _vertex_num; i++) {
			if (c[i] == 0) {
				//������δ����Ķ��㣬������һ��bfs��� 
				label++;
				bfs (i, c, label);  //���·�֧����� 
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

		while (!s.empty ()) //��stack����ʱ 
		{
			int w = s.top ();
			s.pop ();
			myIterator* iv = iterator (w);	  u = iv->next ();
			while (u != 0)  //����һ������ĵ�w�������ڽӵ� 
			{
				if (reach[u] != _label) //�������һ��δ��ǵĵ�j 
				{
					reach[u] = _label;
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
	/*��ÿ��������·����·��*/
	int Dijkstra (int start, int dest, int path[]) {
		//�������·������¼�����·��·����path�Ǵ�start��dest·����destǰ���Ǹ����� 

		int* L = new int[_vertex_num + 1];  //L[i]���Ǵ�start�㵽����i�ľ��� 
		for (int i = 1; i <= _vertex_num; i++)  L[i] = _weights[start][i];  L[start] = 0;
		bool* S = new bool[_vertex_num + 1];
		for (int i = 1; i <= _vertex_num; i++)  S[i] = false;  //S[i]��ʾstart������i�����·����� 
		for (int i = 1; i <= _vertex_num; i++) {
			path[i] = (L[i] == _no_edge) ? -1 : start;
		}
		path[start] = 0;    //Դ����û��ǰ�� 
		for (int i = 1; i <= _vertex_num; i++) {

			auto Minium = [](int L[], bool S[], int n) {
				//��L[1:n]�����з��ز��ڶ��㼯S����С��Ԫ�� 
				int min = 100000;
				for (int i = 1; i <= n; i++) {
					if (L[i] < min && S[i] == false) {
						min = L[i];
					}
				}
				return min;
			};

			if (S[i] == false && L[i] == Minium (L, S, _vertex_num)) {
				S[i] = true;  //��u���붥�㼯S��

				//���¼���·������
				for (int j = 1; j <= _vertex_num; j++) {//��ÿһ��������S�Ķ���v 
					if (S[j] == false && L[i] + _weights[i][j] < L[j]) {
						L[j] = L[i] + _weights[i][j];
						path[j] = i;   //����v��ǰ����u 
					}
				}
			}
		}
		return L[dest];
	}
	bool kruskal (edge<W>* spanningTreeEdges) {
		//����С������������ͼ��ͨ�򷵻�true����sTE[0:n-2]�д�����С�������ı� 
		//ע�⣬��Ҫ�ò��鼯��ֹ��·��ÿ��Ѱ����С�䣬�γɻ��Ͳ�ȥ����
		//�ö�ȡ��ÿ����С��

		edge<W>* Edge = new edge<W>[_edge_num + 1];
		int k = 1;  //����Edge������ 

		//�����edge�����ʼ���������б߼���edge����
		for (int i = 1; i <= _vertex_num; i++) {//ȡ���й�������i�ı� 
			myIterator* ii = iterator (i);
			int j; W w;
			while ((j = ii->next (w)) != 0) {
				if (i < j) { //�����ظ��ӱ� 
					Edge[k++] = edge<int> (i, j, w);
				}
			}
		}
		//��С���ѱ�ʾ�߼���Ч�ʽϺ�
		minHeap<edge<W>> heap;

		heap.initialize (Edge, _edge_num);  //cout<<heap<<endl;
		fastUnionFind uf (_vertex_num);
		k = 0;  //����
		while (_edge_num > 0 && k < _vertex_num - 1) {

			//������û����ɲ��һ��бߴ��� 
			edge<W> x = heap.top ();
			heap.pop ();
			_edge_num--;
			int a = uf.find (x.getFrom ());
			int b = uf.find (x.getTo ());
			if (a != b) {//��֤��û�л�·�������ѡȡ��x 
				spanningTreeEdges[k++] = x;
				uf.unite (a, b);
			}
		}
		return (k == _vertex_num - 1);
	}
	bool prim (edge<W>* spanningTreeEdges) {
		//spanningTreeEdges���Ѿ���ѡ�ı߼� 
		minHeap<edge<W>> heap;

		bool* TV = new bool[_vertex_num + 1];      //TV���������еĶ��㼯
		for (int i = 1; i <= _vertex_num; i++)
			TV[i] = false;
		TV[1] = true;

		myIterator* i = iterator (1);
		int j;
		W w;

		//�Զ������������򣬹���С����
		while ((j = i->next (w)) != 0) {
			edge<W> tem (1, j, w);
			heap.push (tem);
		}


		int k = 0;   //��ʾ�߼������� 
		while (!heap.empty () && k < _vertex_num - 1) {
			edge<W> x = heap.top ();  //�����ı�����С�� 
			heap.pop ();
			int a = x.getFrom ();
			int b = x.getTo ();
			if (TV[b] == false) { //����TV[a]==true 
				spanningTreeEdges[k++] = edge<W> (a, b, x.weight ());
			}
			TV[b] = true;
			i = iterator (b);
			while ((j = i->next (w)) != 0) {
				if (j > b) {
					//��֤���ظ������ 
					edge<W> tem (b, j, w);
					heap.push (tem);
				}
			}
		}
		delete[] TV;      //TV���������еĶ��㼯

		return (k == _vertex_num - 1);
	}

};



int main () {
#pragma warning(disable:4996)
	freopen ("input.txt", "r", stdin);
	int n, m, q;//�� �� ��
	cin >> n >> m>>q;

	//��ʼ���ڽ���������ͼ
	adjacencyWGraph<int> g (n);

	//��ʼ������
	for (int i = 0; i < m; i++) {
		int v1, v2, w;  
		cin >> v1 >> v2 >> w;
		edge<int>* Edge = new edge<int> (v1, v2, w);
		//g.insertEdge (v1, v2, w);
		g.insertEdge (Edge);
	}

	//������С�����������
	edge<int>* STE = new edge<int>[n - 1];

	for (int i = 0; i < q; i++) {
		int count1 = 0;
		//cout << "kruskal��С��������ÿ����(v1,v2,w)����:" << endl;
		if (g.kruskal (STE) == true) {
			for (int i = 0; i <= n - 2; i++)
				//cout << STE[i] << endl;
				count1 += STE[i].getWeight ();

		}
		cout << count1 << "\n";
	}
	//cout << "prim��С��������ÿ����(v1,v2,w)����:" << endl;

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