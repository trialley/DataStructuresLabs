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

		void transpose()
{
	spareMatrix<T> p=*(this);
	int a[_cols+1];
	for(int i=1;i<=_cols;i++)
		a[i]=0;
	arriterator x=_terms.begin();
	arriterator xend=_terms.end();
	while(x!=xend)
	{
		a[(*x).col]++;
		x++;
	}
	int b[_cols+1];
	b[1]=0;
	for(int i=2;i<=_cols;i++)
		b[i]=b[i-1]+a[i-1];
	x=p._terms.begin();
	xend=p._terms.end();
	while(x!=xend)
	{
		int t=(*x).col;
		(*x).col=(*x).row;
		(*x).row=t;
		_terms.set(b[t],*x);
		b[t]++;
		x++;
	}
	int tu=_rows;
	_rows=_cols;
	_cols=tu;
}
		void add (const spareMatrix& in ) {
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
				if ( lindex > rindex ) {//右元素靠后，则插入右元素
					_terms.insert ( insert_index++, *rit++ );
				} else if ( lindex == rindex ) {//两项在同一个位置则相加并插入到临时矩阵中
					if ( ( *lit ).value + ( *rit ).value != 0 ) {//提前判断0，提高效率
						_terms.insert ( insert_index++, element(
						                    ( *lit ).row,
						                    ( *lit ).col,
						                    ( *lit ).value + ( *rit ).value
						                )
						              );
					}
					lit++;
					rit++;
				} else {//左元素靠后，则插入左元素
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
		void multi(spareMatrix<T> &b) {
			if(_cols!=b.getRows()) {
				*this=b;
				cout<<"-1"<<endl;
				return ;
			}
			spareMatrix a(_rows,b.getCols());
			element c;
			a._terms.clear();
			b.transpose();
			T sum=0;

			int rownext[_rows+1];
			int _colsize[_rows+1];
			for(int i=0; i<=_rows; i++)
				rownext[i]=0;
			for(arriterator i=_terms.begin(); i!=_terms.end(); i++)
				rownext[(*i).row]++;
			for(int i=0; i<=_rows; i++)
				_colsize[i]=0;
			for(arriterator i=b._terms.begin(); i!=b._terms.end(); i++)
				_colsize[(*i).row]++;

			arriterator it=_terms.begin();
			arriterator ib=b._terms.begin();
			T m=0,n=0;
			int csize=0;
			int x1=0,x2=0;
			for(int i=(*it).row; i<=_rows; i++) {
				ib=b._terms.begin();
				it=it+rownext[i-1];
				for(int j=(*ib).row; j<=b.getRows(); j++) {
					sum=0;
					for(int k=1; k<=_cols; k++) {
						m=0,n=0;
						if((*it).col==k&&(*it).row==i) {
							m=(*it).value;
							x1=(*it).row;
							it++;
						}
						if((*ib).col==k&&(*ib).row==j) {
							n=(*ib).value;
							x2=(*ib).row;
							ib++;
						}
						sum=sum+m*n;
					}
					it=it-rownext[i];
					c.row=x1;
					c.col=x2;
					c.value=sum;
					if(sum!=0) {
						a._terms.insert(csize,c);
						csize++;
					}
				}
			}
			*this=a;
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
					p.multi ( q );
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
