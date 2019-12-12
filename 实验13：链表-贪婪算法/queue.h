
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
