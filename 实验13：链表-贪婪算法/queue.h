
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
