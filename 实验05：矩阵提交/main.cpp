#include<iostream>
#include<cstring>		//memset£¬memcpy
#include<cstdlib>		//malloc
using namespace std;

/*vector常见错误的枚举*/
enum err { index_out_of_range }err;

/**
 * @brief vector类
 * private:
 *    T* head;           //内容数组头指针
 *    int maxindex;		 //指示index的最大值
 *    int frontindex;    //指向第一个空闲位置
 *    void __exlength()；//私有函数，提供将数组长度成两倍的功能
 *
 * public:
 *    vector();                                   //构造函数，参数为初始长度，默认为50
 *    ~vector();                                  //析构函数，释放构造函数申请的内存资源
 *    T& operator [] (int i);                     //重载方括号[]
 *    void push(T in);                            //push
 *    void clear(int n=50);                       //重置vector
 *    void del(int i);                            //根据下标删除元素
 *    void insert(int i, T in);                   //将元素插入到下标位置，其余元素后移
 *    int find(T target);                         //查找元素，返回下标，查找失败返回-1
 *    int getlength() { return frontindex; }      //返回数组元素数量
 *    int getmaxlength() { return maxindex + 1; } //返回数组最大长度
 */
template<typename T>
class vector {
protected:
	T* head;		//the array head pointer
	int maxindex;		//the length-1 of array
	int frontindex;
	void __exlength () {
		T* newhead = new T[( maxindex + 1 ) * 2];
		memcpy ( newhead, head, sizeof ( T ) * ( maxindex + 1 ) );

		maxindex = maxindex * 2 + 1;

		delete[] head;
		head = newhead;
	}
public:
	friend class vectoritreator;
	class vectoritreator {
	public:
		vectoritreator ( vector* ivec, int thePosition = 0 ) {
			index = thePosition;
			vec = ivec;
		}

		T& operator*() const {
			return ( vec->head )[index];
		}
		/*加法操作*/
		vectoritreator& operator++() {
			++index;
			return *this;
		}
		vectoritreator operator++( int ) {
			vectoritreator old = *this;
			++index;
			return old;
		}
		vectoritreator operator+( int n ) {
			index += n;
			return *this;
		}

		/*减法操作*/
		vectoritreator& operator--() { --index; return *this; }
		vectoritreator operator--( int ) {
			vectoritreator old = *this;
			--index;
			return old;
		}
		vectoritreator operator-( int n ) {
			index -= n;
			return *this;
		}
		void clear () {
			frontindex = -1;
		}
		/*逻辑判断*/
		bool operator!=( const vectoritreator right ) const { return index != right.index; }
		bool operator==( const vectoritreator right ) const { return index == right.index; }
	protected:
		int index;
		vector* vec;
	};

	vector ( int n = 50 ) {
		maxindex = n - 1;
		frontindex = 0;

		head = new T[n];
		memset ( head, 0, sizeof ( T ) * n );
	}

	~vector () {
		delete[] head;
	}

	/*清空vector*/
	void clear ( int n = 50 ) {
		delete[] head;

		maxindex = n - 1;
		frontindex = 0;

		head = new T[n];
		memset ( head, 0, sizeof ( T ) * n );
	}

	/*取得元素的引用*/
	T& operator [] ( int i ) {
		//if ( i >= frontindex ) {
		//	throw index_out_of_range;
		//}

		return head[i];
	}

	/*取得元素的值*/
	T get ( int i ) const {
		//if ( i >= frontindex ) {
		//	throw index_out_of_range;
		//}

		return head[i];
	}

	/*增加新元素*/
	void push ( T in ) {
		if ( frontindex == maxindex ) {
			__exlength ();
		}

		head[frontindex++] = in;
	}

	/*删除元素*/
	void del ( int i ) {
		//if ( i >= frontindex ) {
		//	//err= index_out_of_range
		//	throw index_out_of_range;
		//}

		for ( int j = i; j < frontindex; j++ ) {
			head[j] = head[j + 1];
		}

		frontindex--;

	}

	/*插入函数*/
	void insert ( int i, T in ) {
		//if ( i > frontindex ) {
		//	throw index_out_of_range;
		//}

		//判断后移是否越界
		if ( frontindex + 1 > maxindex ) {
			__exlength ();
		}
		//向后复制时需要总尾开始，否则第一个元素将会覆盖全部
		for ( int j = frontindex; j >= i; j-- ) {
			head[j + 1] = head[j];
		}

		head[i] = in;
		frontindex++;
	}
	int find ( T target ) {
		for ( int i = 0; i <= frontindex; i++ ) {
			if ( head[i] == target ) {
				return i;
			}
		}
		return -1;
	}
	int getlength ()const { return frontindex; }
	int getmaxlength () const { return maxindex + 1; }

	vectoritreator begin () { return vectoritreator ( this, 0 ); }
	vectoritreator end () { return vectoritreator ( this, maxindex ); }
};

template <class T>
using arrayList = vector<T>;

/*稀疏矩阵常见异常*/
typedef enum { not_match, sparseMatrix_index_out_of_range }sparseMatrix_err;

template<class T>
class sparseMatrix {
public:
	struct node {
		int col;
		int row;
		T value;
	};
protected:
	int _rows;
	int _cols;
	arrayList<node> _terms;
	void _checkrc ( int r, int c ) {
		//if ( r > _rows || c > _cols || r < 1 || c < 1 ) {
		//	throw sparseMatrix_index_out_of_range;
		//}
	}
public:
	/*默认构造函数*/
	sparseMatrix ( int i_rows = 5, int i_cols = 5 ) {
		_rows = i_rows;
		_cols = i_cols;
	}
	/*复制构造函数*/
	sparseMatrix ( sparseMatrix& raw ) {
		_rows = raw.getRows ();
		_cols = raw.getCols ();
		_terms = *( new vector<node> );
		for ( int r = 0; r < _rows; r++ ) {
			for ( int c = 0; c < _cols; c++ ) {
				set ( r + 1, c + 1, raw.get ( r + 1, c + 1 ) );
			}
		}
		//默认所有元素都是0
	}
	/*= 运算符重载，该函数与复制构造函数同功能*/
	const sparseMatrix& operator = ( const sparseMatrix& raw ) {

		_rows = raw.getRows ();
		_cols = raw.getCols ();
		_terms.clear ();
		for ( int r = 0; r < _rows; r++ ) {
			for ( int c = 0; c < _cols; c++ ) {
				set ( r + 1, c + 1, raw.get ( r + 1, c + 1 ) );
			}
		}
		return *this;
	}

	/*重构矩阵，清空元素*/
	void reShape ( int n, int m ) {
		_terms.clear ();
		_rows = n;
		_cols = m;
	}

	/*输出矩阵，传入输出流的引用*/
	void show ( ostream& out )const {
		for ( int r = 0; r < _rows; r++ ) {
			for ( int c = 0; c < _cols; c++ ) {
				out << get ( r + 1, c + 1 ) << " ";
			}
			out << endl;
		}
	}

	/*设置某位置元素的值*/
	void set ( int r, int c, int value ) {
		/*检查下标是否越界*/
		//_checkrc ( r, c );
		if ( _terms.getlength () == 0 ) {//如果矩阵还没有非0元素
			if ( value == 0 ) {//如果要赋值0，则不进行操作，直接返回
				return;
			} else {//如果赋的数值不为0，则建立新结点并加入到_terms中
				node temp;
				temp.col = c;
				temp.row = r;
				temp.value = value;
				_terms.push ( temp );
				return;
			}
			/*如果矩阵已经有非0元素，则在_terms中找到相应行、列的元素并修改*/
		} else {
			for ( int i = 0; i < _terms.getlength (); i++ ) {
				if ( _terms[i].col == c && _terms[i].row == r ) {
					/*如果元素要赋的值为0，则从vector中删除该元素*/
					if ( value == 0 ) {
						_terms.del ( i );
						/*如果元素要赋的值不为0，则赋值*/
					} else {
						_terms[i].value = value;
					}
					return;
				}
			}
			/*如果数组中找不到该元素*/
			if ( value == 0 ) {//如果元素要赋的值为0，则直接返回
				return;
			} else {//如果元素要赋的值不为0，则直接加入该新元素
				node temp;
				temp.col = c;
				temp.row = r;
				temp.value = value;
				//for ( int i = 0; i < _terms.getlength (); i++ ) {
				//	if ( _terms[i].col > temp.col ) {
				//		_terms.insert ( i, temp );
				//		return;
				//	}
				//}
				_terms.push ( temp );
				return;
			}
		}
	}

	/*获取值*/
	T get ( int r, int c )const {
		/*如果矩阵没有非0元素，则直接返回0*/
		if ( _terms.getlength () == 0 ) {
			return 0;
		}
		/*寻找元素并返回值*/
		for ( int i = 0; i < _terms.getlength (); i++ ) {
			if ( _terms.get ( i ).col == c && _terms.get ( i ).row == r ) {
				return _terms.get ( i ).value;
			}
		}
		/*如果找不到元素，则直接返回0*/
		return 0;
	}
	/*返回行数*/
	int getRows () const { return _rows; }
	/*返回列数*/
	int getCols ()const { return _cols; }

	/*矩阵加法*/
	const sparseMatrix operator + ( sparseMatrix& in ) {
		//if ( _rows != in._rows || _cols != in._cols ) {
		//	throw  not_match;
		//}
		sparseMatrix temp ( _rows, _cols );

		for ( int r = 1; r <= temp.getRows (); r++ ) {
			for ( int c = 1; c<= temp.getCols (); c++ ) {
				temp.set ( r, c, get ( r, c ) + in.get ( r, c ) );
			}
		}
		return temp;
	}
	void add( sparseMatrix& in ) {
		//if ( _rows != in._rows || _cols != in._cols ) {
		//	throw  not_match;
		//}
		for ( int r = 1; r <= in.getRows (); r++ ) {
			for ( int c = 1; c <= in.getCols (); c++ ) {
				set ( r, c, get ( r, c ) + in.get ( r, c ) );
			}
		}
	}
	/*矩阵乘法*/
	const sparseMatrix operator * ( const sparseMatrix& r ) {
		/*首先判断能否相乘*/
		sparseMatrix& l = *this;
		//if ( l.getCols () != r.getRows () ) {
		//	throw not_match;
		//}
		/*建立临时数组，拥有左值的行数与右值的列数*/
		sparseMatrix<T> temp ( l.getRows (), r.getCols () );
		/*乘积第m行第n列的元素等于左矩阵的第m行元素与右矩阵的第n列对应元素乘积之和*/
		int rows = temp.getRows ();
		int cols = temp.getCols ();
		for ( int m = 1; m <= rows; m++ ) {
			for ( int n = 1; n <= cols; n++ ) {
				int value = 0;
				for ( int i = 1; i <= cols; i++ ) {
					value += l.get ( m, i ) * r.get ( i, n );
				}
				temp.set ( m, n, value );
			}
		}
		return temp;
	}

	template <class U>
	friend istream& operator>> ( istream& in, sparseMatrix<U>& temp );

	template <class U>
	friend ostream& operator<< ( ostream& out, const sparseMatrix<U>& temp );

};

/*输出运算符的重载，直接调用show函数*/
template<class  T>
ostream& operator << ( ostream& out, const sparseMatrix<T>& temp ) {
	temp.show ( out );
	return out;
}
template<class T>
istream& operator>>( istream& in, sparseMatrix<T>& temp ) {
	/*临时矩阵*/
	temp._terms.clear ( temp._rows * temp._cols );

	/*循环输入内容，跳过0元素*/
	typename sparseMatrix<T>::node temp_term;
	for ( int i = 1; i <= temp._rows; i++ ) {
		for ( int j = 1; j <= temp._cols ; j++ ){
			temp_term.row = i;
			temp_term.col = j;
			in >> temp_term.value;
			if ( temp_term.value == 0 ) {
				continue;
			} else {
				temp._terms.push ( temp_term );
			}
		}
	}
	return in;
}
//#pragma warning(disable:4996)//用于禁止vs的多余报错

int main () {
	//freopen ( "input.txt", "r", stdin );
	int funcnums = 0;
	cin >> funcnums;
	sparseMatrix<int> p, q;
	for ( int i = 0; i < funcnums; i++ ) {
		int funcnum = 0;
		cin >> funcnum;

		int rows=0, cols = 0;
		int n = 0, m = 0;

		switch ( funcnum ) {
		case 1:
			cin >> n >> m;
			p.reShape ( n, m );
			cin >> p;
			break;
		case 2:
			cin >> n >> m;
			q.reShape ( n, m );
			cin >> q;
			if (p.getCols()==q.getRows() ) {
				p = p * q;
			} else {
				p = q;
				cout << "-1"<<endl;
			}
			break;
		case 3:
			cin >> n >> m;
			q.reShape ( n, m );
			cin >> q;
			if ( p.getCols () == q.getCols ()&& p.getRows () == q.getRows () ) {
				p.add( q);
			} else {
				p = q;
				cout << "-1" << endl;
			}
			
			break;
		case 4:
			rows = p.getRows ();
			cols = p.getCols ();
			cout << rows << " " << cols<<endl;
			cout << p;
			break;
		default:
			break;
		}

	}
	return 0;
}