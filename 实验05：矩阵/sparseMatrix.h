/*****************************************************************************
*  sparseMatrix.h                                                            *
*  Copyright (C) 2019.10.15 TriAlley  lg139@139.com                          *
*  @brief    ϡ���������ӳ˵ȵ�ʵ��                                          *
*  @license  GNU General Public License (GPL)                                *
*****************************************************************************/
#pragma once
#include<iostream>
#include"../ʵ�����������������Ա�/vector.h"
typedef enum { not_match, sparseMatrix_index_out_of_range }sparseMatrix_err;
template<class T>
class sparseMatrix {
public:
	struct node {
		int col;
		int row;
		T value;
	};
	/*Ĭ�Ϲ��캯��*/
	sparseMatrix ( int i_rows = 5, int i_cols = 5 ) {
		_rows = i_rows;
		_cols = i_cols;
	}
	/*���ƹ��캯��*/
	sparseMatrix ( sparseMatrix& raw ) {
		_rows = raw.getRows ();
		_cols = raw.getCols ();
		_terms = *( new vector<node> );
		for ( int r = 0; r < _rows; r++ ) {
			for ( int c = 0; c < _cols; c++ ) {
				set ( r + 1, c + 1, raw.get ( r + 1, c + 1 ) );
			}
		}
		//Ĭ������Ԫ�ض���0
	}
	/*= ��������أ��ú����븴�ƹ��캯��ͬ����*/
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
	/*������󣬴��������������*/
	void show ( ostream& out )const {
		for ( int r = 0; r < _rows; r++ ) {
			for ( int c = 0; c < _cols; c++ ) {
				out << get ( r + 1, c + 1 ) << " ";
			}
			out << endl;
		}
		out << endl;
	}
	/*����ĳλ��Ԫ�ص�ֵ*/
	void set ( int r, int c, int value ) {
		/*����±��Ƿ�Խ��*/
		_checkrc ( r, c );
		if ( _terms.getlength () == 0 ) {//�������û�з�0Ԫ��
			if ( value == 0 ) {//���Ҫ��ֵ0���򲻽��в�����ֱ�ӷ���
				return;
			} else {//���������ֵ��Ϊ0�������½�㲢���뵽_terms��
				node temp;
				temp.col = c;
				temp.row = r;
				temp.value = value;
				_terms.push ( temp );
				return;
			}
			/*��������Ѿ��з�0Ԫ�أ�����_terms���ҵ���Ӧ�С��е�Ԫ�ز��޸�*/
		} else {
			for ( int i = 0; i < _terms.getlength (); i++ ) {
				if ( _terms[i].col == c && _terms[i].row == r ) {
					/*���Ԫ��Ҫ����ֵΪ0�����vector��ɾ����Ԫ��*/
					if ( value == 0 ) {
						_terms.del ( i );
						/*���Ԫ��Ҫ����ֵ��Ϊ0����ֵ*/
					} else {
						_terms[i].value = value;
					}
					return;
				}
			}
			/*����������Ҳ�����Ԫ��*/
			if ( value == 0 ) {//���Ԫ��Ҫ����ֵΪ0����ֱ�ӷ���
				return;
			} else {//���Ԫ��Ҫ����ֵ��Ϊ0����ֱ�Ӽ������Ԫ��
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
	/*��ȡֵ*/
	T get ( int r, int c )const {
		/*�������û�з�0Ԫ�أ���ֱ�ӷ���0*/
		if ( _terms.getlength () == 0 ) {
			return 0;
		}
		/*Ѱ��Ԫ�ز�����ֵ*/
		for ( int i = 0; i < _terms.getlength (); i++ ) {
			if ( _terms.get ( i ).col == c && _terms.get ( i ).row == r ) {
				return _terms.get ( i ).value;
			}
		}
		/*����Ҳ���Ԫ�أ���ֱ�ӷ���0*/
		return 0;
	}
	/*��������*/
	int getRows () const { return _rows; }
	/*��������*/
	int getCols ()const { return _cols; }

	/*����ӷ�*/
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
	/*����˷�*/
	const sparseMatrix operator * ( const sparseMatrix& r ) {
		/*�����ж��ܷ����*/
		sparseMatrix& l = *this;
		if ( l.getCols () != r.getRows () ) {
			throw not_match;
		}
		/*������ʱ���飬ӵ����ֵ����������ֵ������*/
		sparseMatrix<T> temp ( l.getRows (), r.getCols () );
		/*�˻���m�е�n�е�Ԫ�ص��������ĵ�m��Ԫ�����Ҿ���ĵ�n�ж�ӦԪ�س˻�֮��*/
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

	/*��������������أ���������ӳ�������*/
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

/*�������������أ�ֱ�ӵ���show����*/
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

	return in;	// TODO: �ڴ˴����� return ���
}