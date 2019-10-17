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
	/*迭代器的实现*/
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

		/*复制的准备部分*/
		node* source_node = in_list.head;
		head = new node ( source_node->data );
		source_node = source_node->next;
		node* target_node = head;

		/*复制的主体部分*/
		while ( source_node != nullptr ) {
			target_node->next = new node ( source_node->data );
			target_node = target_node->next;
			source_node = source_node->next;
		}

		/*复制的收尾部分*/
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

	/*增删改查部分*/
	void insert ( int index, const T& target ) {
		/*插入下标允许与size相同，故此处不使用统一的下标检查函数*/
		if ( index < 0 || index > size ) {
			throw index_out_of_range;
		}else if ( index == 0 ) {//若插入到0位置，则直接建立新的结点，将原head设置为新head的next
			head = new node ( target, head );
		}else {//若插入到其他位置，则循环到所需位置再建立新结点
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
		node* delete_node;//待删除结点的指针
		if ( index == 0 ) {//若删除0位。则建立新head并直接删除旧head
			delete_node = head;
			head = head->next;
		} else {//若删除其它位置，则循环找到所需元素并删除
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
	/*重载中括号，达到“改”的目的*/
	T& operator []( int index ) const {
		_checkIndex ( index );

		node* current_node = head;
		for ( int i = 0; i < index; i++ )
			current_node = current_node->next;

		return current_node->data;
	}
	/*返回目的元素的下标，找不到则返回-1*/
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

	/*返回链表是否为空*/
	bool empty () const { return size == 0; }
	/*返回链表长度*/
	int listSize () const { return size; }
	/*返回指向链表头的迭代器*/
	chainiterator begin () { return chainiterator ( head ); }
	/*返回指向链表尾的迭代器（此处为nullptr）*/
	chainiterator end () { return chainiterator ( nullptr ); }

	/*将链表翻转-使用迭代器*/
	/*父函数，向子函数提供参数*/
	void reverse () {
		_reverse ( begin (), end () );
	}

	/*
	* brief：将两个输入的链表合并
	* in:
	*     chain<int>& a：输入的链表之一
	*     chain<int>& b：输入的链表之一
	* out:
	*     chain<int>&  ：返回函数调用者的引用
	*/
	chain<int>& merge ( chain<int>& a, chain<int>& b ) {

		clear ();

		/*合并的主体部分*/
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

		//如果index等于listsize，说明该数组移动完毕；否则未复制完毕，继续复制剩余元素。
		//a，b线性表必只剩一个没有复制完毕，因此此处两个判断只有一个能执行
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
	* brief：将链表内容输出到流
	* in:
	*     ostream& out   ：需要输出到的流的引用
	*     const chain& c ：需要被输出的链表的引用
	* out:
	*     ostream&    流的引用
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
	/*检查下标是否越界，越界则 throw index_out_of_range*/
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

	node* head;     //链表头指针
	int size;       //链表长度
};
#pragma warning(disable:4996)//用于禁止vs的多余报错
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