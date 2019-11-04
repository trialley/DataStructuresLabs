#include <iostream>
#include<cstring>
using namespace std;

/*class arrayList {
public:
	enum err;									//常见错误
	class iterator;								//数组迭代器
protected:
	inline void _checkIndex ( int index )const ;//检查下标是否越界
	void _exLength ();							扩展数组长度
	T* _head;									//数组头指针
	int _maxLength;								//数组最大长度
	int _size;									//数组元素个数
public:
	arrayList ( int ilength=10 );				//指定长度的构造函数
	~arrayList ();								//析构函数
	arrayList ( const arrayList& ilist );		//拷贝构造函数
	T& get ( int index ) const;					//获取某元素的值
	void insert (const int index, T in );		//插入元素
	void clear ();								//清空内容
	const arrayList& operator = ( const arrayList& in );//等号运算符重载
	void set ( int index, const T& in );		//设置某元素值
	int size () const;							//获取数组长元素个数
	iterator begin () const;					//返回头部迭代器
	iterator end () const; 						//返回尾部迭代器
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
	enum  err;								//常见错误的枚举
	struct element;							//三元组
private:
	int _rows;								//矩阵行数
	int _cols;								//矩阵列数
	arrayList<element > _terms;				//矩阵三元组数组
	typedef  typename arrayList<element >::iterator arriterator;//迭代器类型
	bool _checkIndex(int irow, int icol );	//检查下标是否越界
	void _swap ( T& _Left, T& _Right )		//交换元素
public:
	spareMatrix() {}												//构造函数
	spareMatrix ( int irow, int icol );								//指定大小的构造函数
	void set ( int irow, int icol, T ivalue );						//设置某元素的值
	T get ( int irow, int icol )const;								//获得某元素的值
	void transpose ();												//转置
	void add (const spareMatrix& in );								//加法
	void multi(spareMatrix<T> &in);									//矩阵乘法
	void input (istream& icin);										//从标准输入读取
	friend istream& operator >> (istream& icin, spareMatrix& in);	//重载
	void out (ostream& icout)const;									//输出到标准输出
	friend ostream& operator << (ostream& icout,const spareMatrix& in);//重载
	const spareMatrix& operator =  ( const spareMatrix& in );		//重载等号运算符，使用另一个矩阵重新初始化此矩阵
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
		element () {}//如果使用了带参构造函数，则需要显式声明此无参构造函数；带参构造函数中的T类型无法确定类型，不能指定默认形参
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

		//获取插入值应当插入的位置 ,有可能提前终止
		int insert_index = 0;
		int target_index = irow * _cols + icol;//在实际矩阵中的目标位置
		while ( it != itend ) {
			int cur_element_index = ( *it ).row * _cols + ( *it ).col;//当前元素在矩阵中的的实际位置

			//当前元素位置在目标元素位置前面，目标元素位置应该加一
			if ( cur_element_index < target_index ) {
				insert_index++;
			} else if ( cur_element_index > target_index ) {
				//当前元素位置在目标位置后边，则目标元素应插入到该元素前面
				_terms.insert ( insert_index, element ( icol, irow, ivalue ) );
				return;
			} else if ( cur_element_index == target_index ) {
				//当前元素位置等于目标元素位置，目标元素就在此处
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

		//依次循环对比
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
		//统计各列非零元素数
		int colindex[_cols + 1];
		memset ( colindex, 0, sizeof ( colindex ) );
		while ( it != end ) {
			colindex[( *it++ ).col]++;
		}

		//计算转置后各行元素起始位置
		int new_raw_index[_cols + 1];
		new_raw_index[1] = 0;
		for ( int i = 2; i <= _cols; i++ ) {
			new_raw_index[i] = new_raw_index[i - 1] + colindex[i - 1];
		}

		//进行转置
		it = temp._terms.begin ();//重置迭代器
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
			//右元素靠后，则插入右元素
				_terms.insert ( insert_index++, *rit++ );
			} else if ( lindex == rindex ) {
			//两项在同一个位置则相加并插入到临时矩阵中
				if ( ( *lit ).value + ( *rit ).value != 0 ) {//提前判断0，提高效率
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
			//左元素靠后，则插入左元素
				_terms.insert ( insert_index++, *lit++ );
			}
		}

		//剩下的，未复制完成的那个矩阵继续复制 ，只有一个矩阵会执行如下代码
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

		//首先构造左右矩阵，并清空*this，准备将结果赋给*this
		spareMatrix lm = *this;
		_rows = _rows;
		_cols = in.getCols ();
		_terms.clear ();
		spareMatrix rm = in;
		rm.transpose ();

		//描述没行/列各有多少元素，供迭代器初始化使用
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

		//对于每行
		for ( int insert_row = ( *lit ).row; insert_row <= lm._rows; insert_row++ ) {
			//初始化迭代器
			rit = rm._terms.begin ();
			lit = lit + each_row_num[insert_row - 1];
			//对于每列
			for ( int insert_col = ( *rit ).row; insert_col <= rm.getRows (); insert_col++ ) {
				int sum = 0;

				//计算该行列的结果并赋给*this
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