//#include<iostream>
//#include"../实验05：矩阵/sparseMatrix.h"
//using namespace std;
//
//
//template<class T>
//class Matrix {
//private:
//	T** arr;
//	int n;
//	bool _checkIndex ( int i, int j )const {
//		cout << i << " " << j << endl;
//		if ( i < 1 || j < 1 || i > n || j>n ) {
//			throw index_err;
//		}
//	}
//
//public:
//	typedef enum err { index_err }err;
//	explicit Matrix ( int in ) {
//		n = in;
//		arr = new T*[in];
//		for ( int i = 0; i < in; i++ ) {
//			arr[i] = new T[in];
//		}
//	}
//	Matrix ( Matrix& raw ) {
//		n = raw.getN ();
//		arr = new T * [n];
//		for ( int i = 0; i < n; i++ ) {
//			arr[i] = new T[n];
//		}
//		for ( int r = 0; r < n; r++ ) {
//			for ( int c = 0; c < n; c++ ) {
//				set ( r + 1, c + 1, raw.get ( r + 1, c + 1 ) );
//			}
//		}
//	}
//	~Matrix () {
//		for ( int i = 0; i < n; i++ ) {
//			delete[] arr[i];
//		}
//		delete[] arr;
//	}
//	const T get ( int i, int j ) const{
//		_checkIndex ( i, j );
//		return arr[i-1][j-1];
//	}
//	void set ( int i, int j, T item ) {
//		_checkIndex ( i, j );
//		arr[i-1][j-1] = item;
//	}
//	int getN ()const { return n; }
//	/*输出矩阵，传入输出流的引用*/
//	void show ( ostream& out )const {
//		for ( int r = 0; r < n; r++ ) {
//			for ( int c = 0; c < n; c++ ) {
//				out << arr[r][c] << " ";
//			}
//			out << endl;
//		}
//		out << endl;
//	}
//	/*= 运算符重载，该函数与复制构造函数同功能*/
//	const Matrix<int>& operator = (const Matrix<int>& raw ) {
//
//		for ( int i = 0; i < n; i++ ) {
//			delete[] arr[i];
//		}
//		delete[] arr;
//		n = raw.getN ();
//		arr = new T * [n];
//		for ( int i = 0; i < n; i++ ) {
//			arr[i] = new T[n];
//		}
//		for ( int r = 0; r < n; r++ ) {
//			for ( int c = 0; c < n; c++ ) {
//				set ( r + 1, c + 1, raw.get ( r + 1, c + 1 ) );
//			}
//		}
//		return *this;
//	}
//};
//
//template<class T>
//class LowerTriangularMatrix {
//private:
//	T* arr;
//	int n;
//	bool _checkIndex ( int i, int j ) {
//		cout << i << " " << j << endl;
//		if ( i < 1 || j < 1 || i > n||j>n) {
//			throw index_err;
//		}
//	}
//
//public:
//	typedef enum err{ index_err }err;
//	explicit LowerTriangularMatrix (int in) {
//		n = in;
//		arr = new T[n* ( n + 1 ) / 2];
//	}
//	~LowerTriangularMatrix () {
//		delete[] arr;
//	}
//	T get ( int i, int j ) {
//		_checkIndex ( i, j );
//		if ( i < j ) {
//			return  0;
//		}
//		return arr[i *( i - 1 ) / 2 + j - 1];
//	}
//	void set ( int i, int j,T item ) {
//		_checkIndex (i,j);
//		if ( i < j ) {
//			return;
//		}
//		cout << i * ( i - 1 ) / 2 + j - 1 << endl;
//		arr[i* ( i - 1 ) / 2 + j - 1]=item;
//	}
//	int getN ()const { return n; }
//};
//template<class T>
//class UpperTriangularMatrix {
//private:
//	T* arr;
//	int n;
//	bool _checkIndex ( int i, int j ) {
//		cout << i << " " << j << endl;
//
//		if ( i < 1 || j < 1 || i > n || j>n ) {
//			throw index_err;
//		}
//	}
//
//public:
//	typedef enum err { index_err }err;
//	explicit UpperTriangularMatrix ( int in ) {
//		n = in;
//		arr = new T[n* ( n + 1 ) / 2];
//	}
//	~UpperTriangularMatrix () {
//		delete[] arr;
//	}
//	T get ( int i, int j ) {
//		_checkIndex ( i, j );
//		if ( i > j ) {
//			return 0;
//		}
//		cout << n * ( n + 1 ) / 2 - ( n - i + 2 ) * ( n - i + 1 ) / 2 + ( j - i );
//		return arr[n * ( n + 1 ) / 2 - ( n - i + 2 )*( n - i + 1 ) / 2 + ( j - i )];
//	}
//	void set ( int i, int j, T item ) {
//		_checkIndex ( i, j );
//		if ( i > j ) {
//			return;
//		}
//		cout << n * ( n + 1 ) / 2 - ( n - i + 2 ) * ( n - i + 1 ) / 2 + ( j - i ) << endl;
//
//		arr[n * ( n + 1 ) / 2 - ( n - i + 2 )*( n - i + 1 ) / 2 + ( j - i )] = item;
//	}
//
//	int getN ()const { return n; }
//};

///*矩阵乘法*/
//const Matrix<int> operator * (  LowerTriangularMatrix<int>& l,  UpperTriangularMatrix<int>& r ) {
//	/*首先判断能否相乘*/
//	if ( l.getN () != r.getN () ) {
//		throw not_match;
//	}
//	int size = l.getN ();
//	/*建立临时数组，拥有左值的行数与右值的列数*/
//	Matrix<int> temp ( size );
//	/*乘积第m行第n列的元素等于左矩阵的第m行元素与右矩阵的第n列对应元素乘积之和*/
//	for ( int m = 1; m <= size; m++ ) {
//		for ( int n = 1; n <= size; n++ ) {
//			int value = 0;
//			for ( int i = 1; i <= size; i++ ) {
//				value += l.get ( m, i ) * r.get ( i, n );
//			}
//			temp.set ( m, n, value );
//		}
//	}
//	return temp;
//}
///*上下三角矩阵矩阵乘法*/
//const int** operator * ( LowerTriangularMatrix <int> & l, LowerTriangularMatrix<int> & r ) {
//	/*首先判断能否相乘*/
//	if ( l.getN () != r.getN () ) {
//		throw not_match;
//	}
//	int size = l.getN ();
//
//	/*建立结果数组*/
//	int** result = new int* [size];
//	for ( int i = 0; i < size; i++ ) {
//		result[i] = new int[size];
//	}
//
//	/*乘积第m行第n列的元素等于左矩阵的第m行元素与右矩阵的第n列对应元素乘积之和*/
//	for ( int m = 1; m <= size; m++ ) {
//		for ( int n = 1; n <= size; n++ ) {
//			int value = 0;
//			for ( int i = 1; i <= size; i++ ) {
//				value += l.get ( m, i ) * r.get ( i, n );
//			}
//			result[m][n] = value;
//		}
//	}
//	return result;
//}
//int main () {
//	Matrix<int>  a ( 5 );
//
//	{
//		LowerTriangularMatrix<int> b ( 5 );
//		UpperTriangularMatrix<int> c ( 5 );
//		int d = 1;
//		for ( int i = 1; i <= b.getN (); i++ ) {
//			for ( int j = i; j <= b.getN (); j++ ) {
//				c.set ( i, j, d );
//			}
//		}
//		cout << "done"<<endl;
//		for ( int i = 1; i <= b.getN (); i++ ) {
//			for ( int j = 1; j <= i; j++ ) {
//				b.set ( i, j, 1 );
//			}
//		}
//		a = (b * c);
//	}
//	a.show ( cout );
//
//	return 0;
//}
//
//#include<iostream>
//#include"../实验05：矩阵/sparseMatrix.h"
//using namespace std;
//
//
//template<class T>
//class Matrix {
//private:
//	T** arr;
//	int n;
//	bool _checkIndex ( int i, int j )const {
//		cout << i << " " << j << endl;
//		if ( i < 1 || j < 1 || i > n || j>n ) {
//			throw index_err;
//		}
//	}
//
//public:
//	typedef enum err { index_err }err;
//	explicit Matrix ( int in ) {
//		n = in;
//		arr = new T * [in];
//		for ( int i = 0; i < in; i++ ) {
//			arr[i] = new T[in];
//		}
//	}
//	Matrix ( Matrix& raw ) {
//		n = raw.getN ();
//		arr = new T * [n];
//		for ( int i = 0; i < n; i++ ) {
//			arr[i] = new T[n];
//		}
//		for ( int r = 0; r < n; r++ ) {
//			for ( int c = 0; c < n; c++ ) {
//				set ( r + 1, c + 1, raw.get ( r + 1, c + 1 ) );
//			}
//		}
//	}
//	~Matrix () {
//		for ( int i = 0; i < n; i++ ) {
//			delete[] arr[i];
//		}
//		delete[] arr;
//	}
//	const T get ( int i, int j ) const {
//		_checkIndex ( i, j );
//		return arr[i - 1][j - 1];
//	}
//	void set ( int i, int j, T item ) {
//		_checkIndex ( i, j );
//		arr[i - 1][j - 1] = item;
//	}
//	int getN ()const { return n; }
//	/*输出矩阵，传入输出流的引用*/
//	void show ( ostream& out )const {
//		for ( int r = 0; r < n; r++ ) {
//			for ( int c = 0; c < n; c++ ) {
//				out << arr[r][c] << " ";
//			}
//			out << endl;
//		}
//		out << endl;
//	}
//	/*= 运算符重载，该函数与复制构造函数同功能*/
//	const Matrix<int>& operator = ( const Matrix<int>& raw ) {
//
//		for ( int i = 0; i < n; i++ ) {
//			delete[] arr[i];
//		}
//		delete[] arr;
//		n = raw.getN ();
//		arr = new T * [n];
//		for ( int i = 0; i < n; i++ ) {
//			arr[i] = new T[n];
//		}
//		for ( int r = 0; r < n; r++ ) {
//			for ( int c = 0; c < n; c++ ) {
//				set ( r + 1, c + 1, raw.get ( r + 1, c + 1 ) );
//			}
//		}
//		return *this;
//	}
//};
//
//template<class T>
//class EquidiagonalMatrix {
//private:
//	T* arr;
//	int n;
//	bool _checkIndex ( int i, int j ) {
//		cout << i << " " << j << endl;
//		if ( i < 1 || j < 1 || i > n || j>n ) {
//			throw index_err;
//		}
//	}
//
//public:
//	typedef enum err { index_err }err;
//	explicit EquidiagonalMatrix ( int in ) {
//		n = in;
//		arr = new T[2 * n - 1];
//	}
//	~EquidiagonalMatrix () {
//		delete[] arr;
//	}
//	T get ( int i, int j ) {
//		_checkIndex ( i, j );
//		if ( i <= j ) {
//			return arr[j - i];
//		}
//		if ( i > j ) {
//			return arr[n + i - j - 1];
//		}
//	}
//	void set ( int i, int j, T item ) {
//		_checkIndex ( i, j );
//		if ( i <= j ) {
//			arr[j - i] = item;
//		}
//		if ( i > j ) {
//			arr[n + i - j - 1] = item;
//		}
//	}
//
//	int getN ()const { return n; }
//};

///*矩阵乘法*/
////const Matrix<int> operator * ( EquidiagonalMatrix <int>& l, EquidiagonalMatrix<int>& r ) {
////	/*首先判断能否相乘*/
////	if ( l.getN () != r.getN () ) {
////		throw not_match;
////	}
////	int size = l.getN ();
////
////	/*建立临时数组*/
////	Matrix<int> temp ( size );
////
////	/*乘积第m行第n列的元素等于左矩阵的第m行元素与右矩阵的第n列对应元素乘积之和*/
////	for ( int m = 1; m <= size; m++ ) {
////		for ( int n = 1; n <= size; n++ ) {
////			int value = 0;
////			for ( int i = 1; i <= size; i++ ) {
////				value += l.get ( m, i ) * r.get ( i, n );
////			}
////			temp.set ( m, n, value );
////		}
////	}
////	return temp;
////}
///*矩阵乘法*/
//const int** operator * ( EquidiagonalMatrix <int>& l, EquidiagonalMatrix<int>& r ) {
//	/*首先判断能否相乘*/
//	if ( l.getN () != r.getN () ) {
//		throw not_match;
//	}
//	int size = l.getN ();
//
//	/*建立结果数组*/
//	int** result= new int * [size];
//	for ( int i = 0; i < size; i++ ) {
//		result[i] = new int[size];
//	}
//
//	/*乘积第m行第n列的元素等于左矩阵的第m行元素与右矩阵的第n列对应元素乘积之和*/
//	for ( int m = 1; m <= size; m++ ) {
//		for ( int n = 1; n <= size; n++ ) {
//			int value = 0;
//			for ( int i = 1; i <= size; i++ ) {
//				value += l.get ( m, i ) * r.get ( i, n );
//			}
//			result[m][n]=value;
//		}
//	}
//	return result;
//}
//int main () {
//	Matrix<int>  a ( 5 );
//
//	{
//		EquidiagonalMatrix<int> b ( 5 );
//		EquidiagonalMatrix<int> c ( 5 );
//		int d = 1;
//		for ( int i = 1; i <= b.getN (); i++ ) {
//			for ( int j = 1; j <= b.getN (); j++ ) {
//				c.set ( i, j, 1 );
//			}
//		}
//		cout << "done" << endl;
//		for ( int i = 1; i <= b.getN (); i++ ) {
//			for ( int j = 1; j <= b.getN (); j++ ) {
//				b.set ( i, j, 1 );
//			}
//		}
//		a = ( b * c );
//	}
//	a.show ( cout );
//
//	return 0;
//}