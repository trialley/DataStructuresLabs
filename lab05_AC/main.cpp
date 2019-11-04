#include <iostream>
#include<cstring>
using namespace std;

/*class arrayList {
public:
	enum err;									//��������
	class iterator;								//���������
protected:
	inline void _checkIndex ( int index )const ;//����±��Ƿ�Խ��
	void _exLength ();							��չ���鳤��
	T* _head;									//����ͷָ��
	int _maxLength;								//������󳤶�
	int _size;									//����Ԫ�ظ���
public:
	arrayList ( int ilength=10 );				//ָ�����ȵĹ��캯��
	~arrayList ();								//��������
	arrayList ( const arrayList& ilist );		//�������캯��
	T& get ( int index ) const;					//��ȡĳԪ�ص�ֵ
	void insert (const int index, T in );		//����Ԫ��
	void clear ();								//�������
	const arrayList& operator = ( const arrayList& in );//�Ⱥ����������
	void set ( int index, const T& in );		//����ĳԪ��ֵ
	int size () const;							//��ȡ���鳤Ԫ�ظ���
	iterator begin () const;					//����ͷ��������
	iterator end () const; 						//����β��������
*/
template<class T>
class arrayList {
public:
	typedef enum {
		index_out_of_range
	} err;
	class iterator {
	public:
		typedef bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

		iterator ( T* ipos ) {
			datap = ipos;
		}

		T& operator*()const {
			return *datap;
		}
		T* operator&()const {
			return datap;
		}
		bool operator!=( const iterator in ) const {
			return datap != in.datap;
		}
		bool operator==( const iterator in )const {
			return datap == in.datap;
		}
		iterator& operator++() {
			++datap;
			return *this;
		}
		iterator operator++( int ) {
			iterator old = *this;
			++datap;
			return old;
		}
		iterator operator+( int n ) {
			datap += n;
			return *this;
		}
		iterator& operator--() {
			--datap;
			return *this;
		}
		iterator operator--( int ) {
			iterator old = *this;
			--datap;
			return old;
		}
		iterator operator-( int n ) {
			datap -= n;
			return *this;
		}
	protected:
		T* datap;
	};
protected:
	inline void _checkIndex ( int index )const {
		if ( index<0 || index>_size ) {
			throw index_out_of_range;
		}
	}
	void _exLength () {
		T* newhead = new T[_maxLength * 2];
		memcpy ( newhead, _head, sizeof ( T ) * ( _maxLength ) );

		_maxLength = _maxLength * 2;

		delete[] _head;
		_head = newhead;
	}
	T* _head;
	int _maxLength;
	int _size;
public:
	~arrayList () {
		delete[] _head;
	}
	arrayList ( int ilength = 10 ) :_maxLength ( ilength ), _size ( 0 ) {
		_head = new T[_maxLength];
	}

	arrayList ( const arrayList& ilist ) {
		_maxLength = ilist._maxLength;
		_size = ilist._size;
		_head = new T[_maxLength];
		for ( int i = 0; i < _size; i++ ) {
			_head[i] = ilist._head[i];
		}
	}

	T& get ( int index ) const {
		_checkIndex ( index );
		return _head[index];
	}

	void insert ( const int index, T in ) {
		_checkIndex ( index );
		if ( _size == _maxLength ) {
			_exLength ();
		}
		if ( _size - 1 == index ) {
			copy_backward ( _head + index, _head + _size, _head + _size + 1 );
		}
		_head[index] = in;
		_size++;
	}

	void clear () {
		delete[]_head;
		_head = new T[_maxLength];
		_size = 0;
	}

	const arrayList& operator =  ( const arrayList& in ) {
		delete[]_head;
		_maxLength = in._maxLength;
		_size = in._size;
		T* x = in._head;
		_head = new T[_maxLength];
		for ( int i = 0; i < in.size (); i++ ) {
			_head[i] = x[i];
		}
	}
	void set ( int index, const T& in ) {
		_head[index] = in;
	}

	int size () const {
		return _size;
	}
	iterator begin () const {
		return iterator ( _head );
	}
	iterator end () const {
		return iterator ( _head + _size );
	}
};


/*class spareMatrix
public:
	enum  err;								//���������ö��
	struct element;							//��Ԫ��
private:
	int _rows;								//��������
	int _cols;								//��������
	arrayList<element > _terms;				//������Ԫ������
	typedef  typename arrayList<element >::iterator arriterator;//����������
	bool _checkIndex(int irow, int icol );	//����±��Ƿ�Խ��
	void _swap ( T& _Left, T& _Right )		//����Ԫ��
public:
	spareMatrix() {}												//���캯��
	spareMatrix ( int irow, int icol );								//ָ����С�Ĺ��캯��
	void set ( int irow, int icol, T ivalue );						//����ĳԪ�ص�ֵ
	T get ( int irow, int icol )const;								//���ĳԪ�ص�ֵ
	void transpose ();												//ת��
	void add (const spareMatrix& in );								//�ӷ�
	void multi(spareMatrix<T> &in);									//����˷�
	void input (istream& icin);										//�ӱ�׼�����ȡ
	friend istream& operator >> (istream& icin, spareMatrix& in);	//����
	void out (ostream& icout)const;									//�������׼���
	friend ostream& operator << (ostream& icout,const spareMatrix& in);//����
	const spareMatrix& operator =  ( const spareMatrix& in );		//���صȺ��������ʹ����һ���������³�ʼ���˾���
*/
template<class T>
class spareMatrix {
public:
	typedef enum {
		not_match,
		index_out_of_range
	} err;
	typedef struct element {
		int row;
		int col;
		T value;
		element () {}//���ʹ���˴��ι��캯��������Ҫ��ʽ�������޲ι��캯�������ι��캯���е�T�����޷�ȷ�����ͣ�����ָ��Ĭ���β�
		element ( int irow, int icol, T ivalue ) :row ( irow ), col ( icol ), value ( ivalue ) {}
	} element;
private:
	int _rows;
	int _cols;
	arrayList<element > _terms;
	typedef  typename arrayList<element >::iterator arriterator;
	bool _checkIndex ( int irow, int icol ) {
		if ( irow > _rows || irow<0 || icol>_cols || icol < 0 ) {
			throw index_out_of_range;
		}
		return true;
	}
	void _swap ( T& _Left, T& _Right ) {
		T _Tmp = _Left;
		_Left = _Right;
		_Right = _Tmp;
	}
public:
	spareMatrix () {}
	spareMatrix ( int irow, int icol ) :_rows ( irow ), _cols ( icol ) {}
	~spareMatrix () {}

	int getRows () const {return _rows;}
	int getCols ()const {return _cols;}
	void set ( int irow, int icol, T ivalue ) {
		_checkIndex ( irow, icol );
		arriterator it = _terms.begin ();
		arriterator itend = _terms.end ();

		//��ȡ����ֵӦ�������λ�� ,�п�����ǰ��ֹ
		int insert_index = 0;
		int target_index = irow * _cols + icol;//��ʵ�ʾ����е�Ŀ��λ��
		while ( it != itend ) {
			int cur_element_index = ( *it ).row * _cols + ( *it ).col;//��ǰԪ���ھ����еĵ�ʵ��λ��

			//��ǰԪ��λ����Ŀ��Ԫ��λ��ǰ�棬Ŀ��Ԫ��λ��Ӧ�ü�һ
			if ( cur_element_index < target_index ) {
				insert_index++;
			} else if ( cur_element_index > target_index ) {
				//��ǰԪ��λ����Ŀ��λ�ú�ߣ���Ŀ��Ԫ��Ӧ���뵽��Ԫ��ǰ��
				_terms.insert ( insert_index, element ( icol, irow, ivalue ) );
				return;
			} else if ( cur_element_index == target_index ) {
				//��ǰԪ��λ�õ���Ŀ��Ԫ��λ�ã�Ŀ��Ԫ�ؾ��ڴ˴�
				( *it ).value = ivalue;
				return;
			}
			it++;
		}


	}
	T get ( int irow, int icol )const {
		_checkIndex ( irow, icol );
		arriterator it = _terms.begin ();
		arriterator itend = _terms.end ();

		//����ѭ���Ա�
		while ( it != itend ) {
			if ( ( *it ).row == irow && ( *it ).col == icol ) {
				return ( *it ).value;
			}
			it++;
		}
		return 0;
	}

	void transpose () {
		spareMatrix temp = *( this );
		arriterator it = temp._terms.begin ();
		arriterator end = temp._terms.end ();
		//ͳ�Ƹ��з���Ԫ����
		int colindex[_cols + 1];
		memset ( colindex, 0, sizeof ( colindex ) );
		while ( it != end ) {
			colindex[( *it++ ).col]++;
		}

		//����ת�ú����Ԫ����ʼλ��
		int new_raw_index[_cols + 1];
		new_raw_index[1] = 0;
		for ( int i = 2; i <= _cols; i++ ) {
			new_raw_index[i] = new_raw_index[i - 1] + colindex[i - 1];
		}

		//����ת��
		it = temp._terms.begin ();//���õ�����
		end = temp._terms.end ();
		while ( it != end ) {
			_swap ( ( *it ).col, ( *it ).row );
			_terms.set ( new_raw_index[( *it ).row]++, *it );
			it++;
		}
		_swap ( _rows, _cols );
	}
	void add ( const spareMatrix& in ) {
		if ( _rows != in.getRows () || _cols != in.getCols () ) {
			throw not_match;
		}
		spareMatrix<T> temp = *( this );
		int insert_index = 0;
		_terms.clear ();

		arriterator lit = temp._terms.begin ();
		arriterator rit = in._terms.begin ();
		arriterator litend = temp._terms.end ();
		arriterator ritend = in._terms.end ();

		while ( lit != litend && rit != ritend ) {
			int lindex = ( *lit ).row * _cols + ( *lit ).col;
			int rindex = ( *rit ).row * _cols + ( *rit ).col;
			if ( lindex > rindex ) {
			//��Ԫ�ؿ����������Ԫ��
				_terms.insert ( insert_index++, *rit++ );
			} else if ( lindex == rindex ) {
			//������ͬһ��λ������Ӳ����뵽��ʱ������
				if ( ( *lit ).value + ( *rit ).value != 0 ) {//��ǰ�ж�0�����Ч��
					_terms.insert ( insert_index++, element (
						( *lit ).row,
						( *lit ).col,
						( *lit ).value + ( *rit ).value
					)
					);
				}
				lit++;
				rit++;
			} else {
			//��Ԫ�ؿ����������Ԫ��
				_terms.insert ( insert_index++, *lit++ );
			}
		}

		//ʣ�µģ�δ������ɵ��Ǹ������������ ��ֻ��һ�������ִ�����´���
		while ( rit != ritend ) {
			_terms.insert ( insert_index++, *rit++ );
		}
		while ( lit != litend ) {
			_terms.insert ( insert_index++, *lit++ );
		}
	}
	void multi ( spareMatrix<T>& in ) {
		if ( _cols != in.getRows () ) {
			throw not_match;
		}

		//���ȹ������Ҿ��󣬲����*this��׼�����������*this
		spareMatrix lm = *this;
		_rows = _rows;
		_cols = in.getCols ();
		_terms.clear ();
		spareMatrix rm = in;
		rm.transpose ();

		//����û��/�и��ж���Ԫ�أ�����������ʼ��ʹ��
		int each_row_num[_rows + 1] = { 0 };
		int each_col_num[_rows + 1] = { 0 };
		for ( arriterator i = lm._terms.begin (); i != lm._terms.end (); i++ ) {
			each_row_num[( *i ).row]++;
		}
		for ( arriterator i = rm._terms.begin (); i != rm._terms.end (); i++ ) {
			each_col_num[( *i ).row]++;
		}
		arriterator lit = lm._terms.begin ();
		arriterator rit = rm._terms.begin ();

		int insert_index = 0;

		//����ÿ��
		for ( int insert_row = ( *lit ).row; insert_row <= lm._rows; insert_row++ ) {
			//��ʼ��������
			rit = rm._terms.begin ();
			lit = lit + each_row_num[insert_row - 1];
			//����ÿ��
			for ( int insert_col = ( *rit ).row; insert_col <= rm.getRows (); insert_col++ ) {
				int sum = 0;

				//��������еĽ��������*this
				for ( int current_col = 1; current_col <= lm._cols; current_col++ ) {
					int lvalue = 0;
					int rvalue = 0;
					if ( ( *lit ).col == current_col && ( *lit ).row == insert_row ) {
						lvalue = ( *lit++ ).value;
					}
					if ( ( *rit ).col == current_col && ( *rit ).row == insert_col ) {
						rvalue = ( *rit++ ).value;
					}
					sum = sum + lvalue * rvalue;
				}
				lit = lit - each_row_num[insert_row];
				if ( sum != 0 ) {
					_terms.insert ( insert_index++, element ( insert_row, insert_col, sum ) );
				}
			}
		}
	}
	void input ( istream& icin ) {
		_terms.clear ();
		icin >> _rows >> _cols;
		int tindex = 0;
		element temp;
		for ( int i = 1; i <= _rows; i++ )
			for ( int j = 1; j <= _cols; j++ ) {
				temp.row = i;
				temp.col = j;
				icin >> temp.value;
				if ( temp.value != 0 ) {
					_terms.insert ( tindex++, temp );
				}
			}
	}
	friend istream& operator >> ( istream& icin, spareMatrix& in ) {
		in.input ( icin );
		return icin;
	}
	void out ( ostream& icout )const {
		icout << _rows << " " << _cols << endl;
		arriterator it = _terms.begin ();
		for ( int row = 1; row <= _rows; row++ ) {
			for ( int col = 1; col <= _cols; col++ ) {
				if ( ( *it ).row == row && ( *it ).col == col ) {
					icout << ( *it++ ).value << " ";
				} else {
					icout << "0" << " ";
				}
			}
			icout << endl;
		}
	}
	friend ostream& operator << ( ostream& icout, const spareMatrix& in ) {
		in.out ( icout );
		return icout;
	}
	const spareMatrix& operator =  ( const spareMatrix& in ) {
		_rows = in._rows;
		_cols = in._cols;
		_terms = in._terms;
	}

};

int main () {
	//FILE* fileh = freopen ( "input.txt", "r", stdin );
	int num = 0;
	int func = 0;
	spareMatrix<int> p, q;
	cin >> num;
	for ( int i = 0; i < num; i++ ) {
		cin >> func;
		switch ( func ) {
		case 1:
			cin >> p;
			break;
		case 2:
			cin >> q;
			if ( p.getCols () != q.getRows () ) {
				p = q;
				cout << "-1" << endl;
			} else {
				p.multi ( q );
			}
			break;
		case 3:
			cin >> q;
			if ( p.getRows () != q.getRows () || p.getCols () != q.getCols () ) {
				p = q;
				cout << "-1" << endl;
			} else {
				p.add ( q );
			}
			break;
		case 4:
			cout << p;
			break;
		}
	}
	return 0;
}