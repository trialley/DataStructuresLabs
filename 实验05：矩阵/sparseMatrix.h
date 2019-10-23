/*****************************************************************************
*  sparseMatrix.h                                                            *
*  Copyright (C) 2019.10.15 TriAlley  lg139@139.com                          *
*  @brief    稀疏矩阵类与加乘等的实现                                          *
*  @license  GNU General Public License (GPL)                                *
*****************************************************************************/
#pragma once
#include<iostream>
#include"../实验三：数组描述线性表/vector.h"
typedef enum { not_match, sparseMatrix_index_out_of_range }sparseMatrix_err;
template<class T>
class sparseMatrix {
public:
	struct node {
		int col;
		int row;
		T value;
	};
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
		out << endl;
	}
	/*设置某位置元素的值*/
	void set ( int r, int c, int value ) {
		/*检查下标是否越界*/
		_checkrc ( r, c );
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
				for ( int i = 0; i < _terms.getlength (); i++ ) {
					if ( _terms[i].col > temp.col ) {
						_terms.insert ( i, temp );
						return;
					}
				}
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
		if ( _rows != in._rows || _cols != in._cols ) {
			throw  not_match;
		}
		sparseMatrix temp ( _rows, _cols );

		int cSize = 0;

		typename arrayList<node>::vectoritreator it = _terms.begin ();
		typename arrayList<node>::vectoritreator ib = in._terms.begin ();
		typename arrayList<node>::vectoritreator itEnd = _terms.end ();
		typename arrayList<node>::vectoritreator ibEnd = in._terms.end ();

		while ( it != itEnd && ib != ibEnd ) {
			int tIndex = ( *it ).row * _cols + ( *it ).col;
			int bIndex = ( *ib ).row * _cols + ( *ib ).col;

			if ( tIndex < bIndex ) {
				temp._terms.insert ( cSize++, *it );
				it++;
			} else {
				if ( tIndex == bIndex ) {
					if ( ( *it ).value + ( *ib ).value != 0 ) {
						node temp_term;
						temp_term.row = ( *it ).row;
						temp_term.col = ( *it ).col;
						temp_term.value = ( *it ).value + ( *ib ).value;
						temp._terms.insert ( cSize++, temp_term );
					}

					it++;
					ib++;
				} else {
					temp._terms.insert ( cSize++, *ib );
					ib++;
				}
			}
		}

		for ( ; it != itEnd; it++ )
			temp._terms.insert ( cSize++, *it );
		for ( ; ib != ibEnd; ib++ )
			temp._terms.insert ( cSize++, *ib );
		return temp;
	}
	/*矩阵乘法*/
	const sparseMatrix operator * ( const sparseMatrix& r ) {
		/*首先判断能否相乘*/
		sparseMatrix& l = *this;
		if ( l.getCols () != r.getRows () ) {
			throw not_match;
		}
		/*建立临时数组，拥有左值的行数与右值的列数*/
		sparseMatrix<T> temp ( l.getRows (), r.getCols () );
		/*乘积第m行第n列的元素等于左矩阵的第m行元素与右矩阵的第n列对应元素乘积之和*/
		for ( int m = 1; m <= temp.getRows (); m++ ) {
			for ( int n = 1; n <= temp.getCols (); n++ ) {
				int value = 0;
				for ( int i = 1; i <= l.getCols (); i++ ) {
					value += l.get ( m, i ) * r.get ( i, n );
				}
				temp.set ( m, n, value );
			}
		}
		return temp;
	}

	/*输入运算符的重载，进行行主映射的输入*/
	template<class T> friend ostream& operator<<( ostream& out, const sparseMatrix<T>& in );
	template<class T> friend istream& operator>>( istream& in, sparseMatrix<T>& temp );
protected:
	int _rows;
	int _cols;
	arrayList<node> _terms;
	void _checkrc ( int r, int c ) {
		if ( r > _rows || c > _cols || r < 1 || c < 1 ) {
			throw sparseMatrix_index_out_of_range;
		}
	}
};

/*输出运算符的重载，直接调用show函数*/
template<class  T>
ostream& operator << ( ostream& out, const sparseMatrix<T>& in ) {
	in.show ( out );
	return out;
}
template<class T>
istream& operator>>( istream& in, sparseMatrix<T>& temp ) {

	in >> temp._rows >> temp._cols;

	temp._terms.clear ( temp._rows * temp._cols );

	typename sparseMatrix<T>::node temp_term;
	for ( int i = 0; i < temp._rows * temp._cols; i++ ) {
		in >> temp_term.row >> temp_term.col >> temp_term.value;
		if ( temp_term.value == 0 ) {
			continue;
		} else {
			temp._terms.push ( temp_term );
		}
	}

	return in;	// TODO: 在此处插入 return 语句
}