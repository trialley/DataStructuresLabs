#include<iostream>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
#define LGRAND(min,max) ((rand()%(max-min+(int)1))+(int)min )

template<class T>
class chain {
public:
	typedef enum err { index_out_of_range }err;
	struct node {
		T data;
		node* next;
		node ( const T& data ) {
			this->data = data;
			this->next = nullptr;
		}
		node ( const T& data, node* next ) {
			this->data = data;
			this->next = next;
		}
	};
	/*��������ʵ��*/
	class chainiterator {
	public:

		chainiterator ( node* theNode = nullptr ) {
			inode = theNode;
		}

		// dereferencing operators
		T& operator*() const { return inode->data; }
		T* operator->() const { return &inode->data; }

		chainiterator& operator++() {

			inode = inode->next;
			return *this;
		}
		chainiterator operator++( int ) {
			chainiterator old = *this;
			inode = inode->next;
			return old;
		}
		chainiterator operator+( int i ) {
			for ( int j = 0; j < i; j++ ) inode = inode->next;
			return *this;
		}
		bool operator!=( const chainiterator right ) const {
			return inode != right.inode;
		}
		bool operator==( const chainiterator right ) const {
			return inode == right.inode;
		}
	protected:
		node* inode;
	};

	chain () {
		head = nullptr;
		size = 0;
	}
	chain ( const chain<T>& in_list ) {
		size = in_list.size;

		if ( size == 0 ) {
			head = nullptr;
			return;
		}

		/*���Ƶ�׼������*/
		node* source_node = in_list.head;
		head = new node ( source_node->data );
		source_node = source_node->next;
		node* target_node = head;

		/*���Ƶ����岿��*/
		while ( source_node != nullptr ) {
			target_node->next = new node ( source_node->data );
			target_node = target_node->next;
			source_node = source_node->next;
		}

		/*���Ƶ���β����*/
		target_node->next = nullptr;
	}
	~chain () {
		node* nextNode;
		while ( head != nullptr ) {
			nextNode = head->next;
			delete head;
			head = nextNode;
		}
	}
	void clear () {
		node* nextNode;
		while ( head != nullptr ) {
			nextNode = head->next;
			delete head;
			head = nextNode;
			size--;
		}
	}

	/*��ɾ�Ĳ鲿��*/
	void insert ( int index, const T& target ) {
		/*�����±�������size��ͬ���ʴ˴���ʹ��ͳһ���±��麯��*/
		if ( index < 0 || index > size ) {
			throw index_out_of_range;
		}else if ( index == 0 ) {//�����뵽0λ�ã���ֱ�ӽ����µĽ�㣬��ԭhead����Ϊ��head��next
			head = new node ( target, head );
		}else {//�����뵽����λ�ã���ѭ��������λ���ٽ����½��
			node* p = head;
			for ( int i = 0; i < index - 1; i++ ) {
				p = p->next;
			}
			p->next = new node ( target, p->next );
		}
		size++;
	}
	void del ( int index ) {
		_checkIndex ( index );
		node* delete_node;//��ɾ������ָ��
		if ( index == 0 ) {//��ɾ��0λ��������head��ֱ��ɾ����head
			delete_node = head;
			head = head->next;
		} else {//��ɾ������λ�ã���ѭ���ҵ�����Ԫ�ز�ɾ��
			node* p = head;
			for ( int i = 0; i < index - 1; i++ ) {
				p = p->next;
			}
			delete_node = p->next;
			p->next = p->next->next;
		}
		size--;
		delete delete_node;
	}
	/*���������ţ��ﵽ���ġ���Ŀ��*/
	T& operator []( int index ) const {
		_checkIndex ( index );

		node* current_node = head;
		for ( int i = 0; i < index; i++ )
			current_node = current_node->next;

		return current_node->data;
	}
	/*����Ŀ��Ԫ�ص��±꣬�Ҳ����򷵻�-1*/
	int find ( const T& target ) const {
		node* current_node = head;
		int index = 0;
		while ( current_node != nullptr &&
			current_node->data != target ) {
			current_node = current_node->next;
			index++;
		}
		if ( current_node == nullptr ) {
			return -1;
		} else {
			return index;
		}
	}

	/*���������Ƿ�Ϊ��*/
	bool empty () const { return size == 0; }
	/*����������*/
	int listSize () const { return size; }
	/*����ָ������ͷ�ĵ�����*/
	chainiterator begin () { return chainiterator ( head ); }
	/*����ָ������β�ĵ��������˴�Ϊnullptr��*/
	chainiterator end () { return chainiterator ( nullptr ); }

	/*������ת-ʹ�õ�����*/
	/*�����������Ӻ����ṩ����*/
	void reverse () {
		_reverse ( begin (), end () );
	}

	/*
	* brief�����������������ϲ�
	* in:
	*     chain<int>& a�����������֮һ
	*     chain<int>& b�����������֮һ
	* out:
	*     chain<int>&  �����غ��������ߵ�����
	*/
	chain<int>& merge ( chain<int>& a, chain<int>& b ) {

		clear ();

		/*�ϲ������岿��*/
		chain<int>::chainiterator ai = a.begin ();
		chain<int>::chainiterator bi = b.begin ();
		while ( ( ai != a.end () ) && ( bi != a.end () ) ) {
			if ( *ai <= *bi ) {
				insert ( listSize (), *ai );
				ai++;
			} else {
				insert ( listSize (), *bi );
				bi++;
			}
		}

		//���index����listsize��˵���������ƶ���ϣ�����δ������ϣ���������ʣ��Ԫ�ء�
		//a��b���Ա��ֻʣһ��û�и�����ϣ���˴˴������ж�ֻ��һ����ִ��
		if ( ai != a.end () ) {
			while ( ai != a.end () ) {
				insert ( listSize (), *ai );
				ai++;
			}
		}
		if ( bi != a.end () ) {
			while ( bi != a.end () ) {
				insert ( listSize (), *bi );
				bi++;
			}
		}
		return *this;
	}


	/*
	* brief�������������������
	* in:
	*     ostream& out   ����Ҫ���������������
	*     const chain& c ����Ҫ����������������
	* out:
	*     ostream&    ��������
	*/
	friend ostream& operator<<( ostream& out, const chain& c ) {
		node* current_node = c.head;
		for ( int i = 0; i < c.size; i++ ) {
			out << current_node->data << " ";
			current_node = current_node->next;
		}
		return out;
	}
protected:
	/*����±��Ƿ�Խ�磬Խ���� throw index_out_of_range*/
	void _checkIndex ( int index ) const {
		if ( index < 0 || index >= size ) {
			throw index_out_of_range;
		}
	}
	void _reverse ( chainiterator head, chainiterator end ) {
		if ( head != end ) {
			chain<int>::chainiterator temp = head;
			_reverse ( ++head, end );
			cout << *temp << " ";
		}
	}

	node* head;     //����ͷָ��
	int size;       //������
};
#pragma warning(disable:4996)//���ڽ�ֹvs�Ķ��౨��
int main () {
	FILE* fileh =freopen("input.txt", "r", stdin);
	int num = 0;
	cin >> num;
	chain<int> c;
	chain<int> c61;
	chain<int> c62;
	chain<int> merged;
 	chain<int>* temp;
	for ( int i = 0; i < num; i++ ) {
		int funcnum;
		int inum;
		cin >> funcnum;
		switch ( funcnum ) {
		case 1:
			cin >> inum;
			c.insert ( 0, inum );
			break;
		case 2:
			cin >> inum;
			c.del ( c.find ( inum ) );
			break;
		case 3:
			cin >> inum;
			cout << c.find ( inum ) << endl;
			break;
		case 4:
			cout << c << endl;
			break;
		case 5:
			c.reverse ();
			cout << endl;
			break;
		case 6:
			cin >> inum;
			for ( int i = 0; i < inum; i++ ) {
				int temp=0;
				cin >> temp;
				c61.insert ( i, temp );
			}
			cin >> inum;
			for ( int i = 0; i < inum; i++ ) {
				int temp = 0;
				cin >> temp;
				c62.insert ( i, temp );
			}
			merged.merge ( c61, c62 );
			cout << merged;
			c61.clear ();
			c62.clear ();
			break;

		default:
			break;
		}
	}
}