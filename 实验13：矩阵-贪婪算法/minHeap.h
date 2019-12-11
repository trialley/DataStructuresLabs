#pragma once
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

		//���µ�ͷ��Ԫ����������ƶ��������ƶ������ӻ������ӣ�������Ҫ�ж�
		//������һ��������������Ҫ<=
		while (child_index <= _size) {
			//������ӱ����Ӵ����Ӧ�������ӽ�����ʹ�¸�С���������Ա�����С������
			//���������������sizeλ�ã�˵��û��������������Ѱ����������С��Ԫ��
			if (child_index < _size && _head[child_index] > _head[child_index + 1]) {
				child_index++;
			}
			//������������Ӷ�С����ֱ���˳������ˣ������ٽ���
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
