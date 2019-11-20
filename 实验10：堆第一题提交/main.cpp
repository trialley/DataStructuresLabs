#include <iostream>
#include <algorithm>
#include <iterator>
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

	void noOrderOutput (ostream& out)const {
		copy (_head + 1, _head + _size + 1, ostream_iterator<T> (cout, "  "));//���ǱȽϺ���ı�̷���
	}
	bool empty () const {return _size == 0; }
	int size () const {return _size;}
};

template <class T>
ostream& operator<<(ostream& out, const minHeap<T>& in) {
	in.noOrderOutput (out); return out;
}
int main (void) {
#pragma warning(disable:4996)
	//freopen ("input.txt", "r", stdin);

	minHeap<int> h;

	int size;
	cin >> size;
	for (int i = 0; i < size; i++) {
		int temp;
		cin >> temp;
		h.push (temp);
	}
	cout << h.top ()<<"\n";
	
	int times;
	cin >> times;
	for (int i = 0; i < times; i++) {
		int func_num;
		cin >> func_num;
		if (func_num == 1) {
			int temp;
			cin >> temp;
			h.push (temp);
			cout << h.top () << "\n";
		} else if (func_num == 2) {
			h.pop ();
			cout << h.top () << "\n";
		} else if (func_num == 3) {
			h._clearAndInit ();
			int size;
			cin >> size;
			for (int i = 0; i < size;i++) {
				int temp;
				cin >> temp;
				h.push (temp);
			}
			for (int i = 0; i < size; i++) {
				cout<<h.top ()<<" ";
				h.pop ();
			}
		}
	}
	return 0;
}
