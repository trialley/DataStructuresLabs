
/*queue
public:
	enum queue_err { queue_empty };  //常见的错误
private:
	struct node;					//结点类型
	node* _head;					//头结点指针
	node* _end;						//尾结点指针，指向NULL
	int _length;					//元素个数
public:
	queue ();						//构造函数
	~queue ();						//析构函数
	void push ( const T& in );		//入队列
	T front ();						//获得首元素
	void pop ();					//弹出首元素
	bool empty ()const;			//是否为空
	int size ()const;				//获取元素个数
*/
template<typename T>
class queue {
public:
	enum queue_err { queue_empty };
private:
	typedef struct node {
		T data;
		node* next;
		node () { next = nullptr; }
	}node;
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
		while (_head->next != NULL) {
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
		n_end->next = NULL;

		_end->next = n_end;
		_end = n_end;
	}
	T front () {
		if (empty ()) {
			throw queue_empty;
		}
		return _head->next->data;
	}
	void pop () {
		if (empty ()) {
			throw queue_empty;
		}
		node* n_head = _head->next;
		delete _head;

		_head = n_head;

		_length--;
		return;
	}
	bool empty ()const { return _head == _end; }
	int size ()const { return _length; }
};
