#include <iostream>
#include<cstring>
using namespace std;

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

				iterator ( T* ipos) {
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
					datap+=n;
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
					datap-=n;
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

			_maxLength = _maxLength * 2 ;

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
		arrayList ( int ilength=10 ):_maxLength(ilength),_size(0) {
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

		void insert (const int index, T in ) {
			_checkIndex ( index );
			if ( _size == _maxLength ) {
				_exLength ();
			}
			if(_size-1==index) {
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
			_head[index]=in;
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
			element() {}
			element(int irow,int icol,T ivalue):row(irow),col(icol),value(ivalue) {}
		} element;
	private:
		int _rows;
		int _cols;
		arrayList<element > _terms;
		typedef  typename arrayList<element >::iterator arriterator;
		bool _checkIndex(int irow, int icol ) {
			if(irow>_rows||irow<0||icol>_cols||icol<0) {
				throw index_out_of_range;
			}
			return true;
		}
	public:
		spareMatrix() {}
		spareMatrix ( int irow, int icol ):_rows( irow ),_cols( icol ) {}
		~spareMatrix () {}

		int getRows () const {
			return _rows;
		}
		int getCols ()const {
			return _cols;
		}

		void set ( int irow, int icol, T ivalue ) {
			_checkIndex(irow,icol);
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
					_terms.insert ( insert_index, element(icol,irow,ivalue) );
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
			_checkIndex(irow,icol);
			arriterator it = _terms.begin ();
			arriterator itend = _terms.end ();
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
			memset(colindex, 0, sizeof(colindex));
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
				swap(( *it ).col,( *it ).row);
				_terms.set ( new_raw_index[( *it ).row]++, *it );
				it++;
			}
			swap(_rows,_cols);
		}
		void add(spareMatrix &b) {
			if(_rows!=b.getRows()||_cols!=b.getCols()) {
				*this=b;
				cout<<"-1"<<endl;
				return;
			}
			spareMatrix<T> c=*(this);
			int csize=0;
			_terms.clear();

			arriterator it = c._terms.begin();
			arriterator ib = b._terms.begin();
			arriterator itEnd=c._terms.end();
			arriterator ibEnd=b._terms.end();

			while(it !=itEnd&&ib !=ibEnd) {
				int theIndex1=(*it).row * _cols +(*it).col;
				int theIndex2=(*ib).row * _cols +(*ib).col;
				element mterm;

				if(theIndex1<theIndex2) {
					_terms.insert(csize++,*it);
					it++;
				}

				else {
					if(theIndex1==theIndex2) {
						//????????
						if((*it).value+(*ib).value!=0) {
							mterm.row=(*it).row;
							mterm.col=(*it).col;
							mterm.value=(*it).value+(*ib).value;
							_terms.insert(csize++,mterm);
						}
						it++;
						ib++;
					}


					else {
						_terms.insert(csize++,*ib);
						ib++;
					}
				}

			}
			while(it!=itEnd) {
				_terms.insert(csize,*it);
				csize++;
				it++;
			}
			while(ib!=ibEnd) {
				_terms.insert(csize,*ib);
				csize++;
				ib++;
			}
		}

		void mult(spareMatrix<T> &in) {
			if(_cols!=in.getRows()) {
				throw not_match;
			}
			spareMatrix rMatrix=in;
			rMatrix.transpose();//转置之后    相乘变为行行相乘
			spareMatrix lMatrix=*this;

			this->_terms.clear();
			this->_cols=rMatrix._cols;
			this->_rows=lMatrix._rows;

			int each_row_num[_rows+1]= {0};
			for(arriterator i=lMatrix._terms.begin(); i!=lMatrix._terms.end(); i++) {
				each_row_num[(*i).row]++;
			}

			int each_col_num[_rows+1]= {0};
			for(arriterator i=rMatrix._terms.begin(); i!=rMatrix._terms.end(); i++) {
				each_col_num[(*i).row]++;
			}

			arriterator lit = lMatrix._terms.begin ();
			arriterator rit = rMatrix._terms.begin ();
			int insert_index=0;
			for(int insert_row=(*lit).row; insert_row<=_rows; insert_row++) {
				rit=rMatrix._terms.begin();
				lit=lit+each_row_num[insert_row-1];
				for(int insert_col=(*rit).row; insert_col<=rMatrix.getRows(); insert_col++) {
					int sum=0;
					for(int k=1; k<=_cols; k++) {
						int rvalue=0;
						int lvalue=0;
						if((*lit).col==k&&(*lit).row==insert_row) {
							lvalue=(*lit++).value;
						}
						if((*rit).col==k&&(*rit).row==insert_col) {
							rvalue=(*rit++).value;
						}
						sum=sum+lvalue*rvalue;
					}
					lit=lit-each_row_num[insert_row];
					if(sum!=0) {
						_terms.insert(insert_index++,element(insert_row,insert_col,sum));
					}
				}
			}
		}

		void input (istream& icin) {
			_terms.clear ();
			icin >> _rows>>_cols;
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
		friend istream& operator >> (istream& icin, spareMatrix& in) {
			in.input(icin);
			return icin;
		}
		void out (ostream& icout)const {
			icout << _rows << " " << _cols << endl;
			arriterator it = _terms.begin ();
			for ( int row = 1; row <= _rows; row++ ) {
				for ( int col = 1; col <= _cols; col++ ) {
					if (( *it ).row == row  && (*it).col == col) {
						icout << ( *it++ ).value << " ";
					} else {
						icout << "0" << " ";
					}
				}
				icout << endl;
			}
		}
		friend ostream& operator << (ostream& icout,const spareMatrix& in) {
			in.out(icout);
			return icout;
		}
		const spareMatrix& operator =  ( const spareMatrix& in ) {
			_rows = in._rows;
			_cols = in._cols;
			_terms = in._terms;
		}

};

int main () {
	FILE* fileh =  freopen ( "input.txt", "r", stdin );
	int num = 0;
	int func = 0;
	spareMatrix<int> p,q;
	cin >> num;
	for(int i=0; i<num; i++) {
		cin >> func;
		switch ( func ) {
			case 1:
				cin>>p;
				break;
			case 2:
				cin>>q;
				if ( p.getCols() != q.getRows () ) {
					p=q;
					cout << "-1" << endl;
				} else {
					p.mult ( q );
				}
				break;
			case 3:
				cin>>q;
				if ( p.getRows() != q.getRows () || p.getCols() != q.getCols () ) {
					p=q;
					cout << "-1" << endl;
				} else {
					p.add ( q );
				}
				break;
			case 4:
				cout<<p;
				break;
		}
	}
	return 0;
}
