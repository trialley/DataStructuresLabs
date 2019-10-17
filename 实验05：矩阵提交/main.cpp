#include<iostream>
#include<cstring>		//memset£¬memcpy
#include<cstdlib>		//malloc
using namespace std;

enum err { index_out_of_range }err;
template<typename T>
class vector {
private:
	T* head;		//the array head pointer
	int maxindex;		//the length-1 of array
	int frontindex;		//the last item+1
	void exlength () {
		T* newhead = new T[( maxindex + 1 ) * 2];
		memcpy ( newhead, head, sizeof ( T ) * ( maxindex + 1 ) );

		maxindex = maxindex * 2 + 1;

		delete[] head;
		head = newhead;
	}
public:
	vector ( vector& raw ) {
		maxindex = 49;
		frontindex = -1;
		head = new  T[50];
		memset ( head, 0, sizeof ( T ) * 50 );
		for ( int i = 0; i < raw.getlength (); i++ ) {
			push ( raw[i] );
		}
	}
	vector ( int n = 50 ) {
		maxindex = n - 1;
		frontindex = -1;

		head = new T[n];
		memset ( head, 0, sizeof ( T ) * n );
	}

	~vector () {
		delete[] head;
	}
	void reset ( int n = 50 ) {
		delete[] head;

		maxindex = n - 1;
		frontindex = -1;

		head = new T[n];
		memset ( head, 0, sizeof ( T ) * n );
	}
	T& operator [] ( int i ) {
		if ( i > frontindex ) {
			throw index_out_of_range;
		}

		return head[i];
	}
	T& operator [] ( int i )const {
		if ( i > frontindex ) {
			throw index_out_of_range;
		}

		return head[i];
	}
	void push ( T in ) {
		if ( frontindex == maxindex ) {
			exlength ();
		}

		head[++frontindex] = in;
	}
	void del ( int i ) {
		if ( i > frontindex ) {
			//err= index_out_of_range
			throw index_out_of_range;
		}

		for ( int j = i; j <= frontindex; j++ ) {
			head[j] = head[j + 1];
		}

		frontindex--;

	}
	void insert ( int i, T in ) {
		if ( i > frontindex ) {
			throw index_out_of_range;
		}

		//判断后移是否越界
		if ( frontindex + 1 > maxindex ) {
			exlength ();
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
	int getlength () const { return frontindex + 1; }
	int getmaxlength () const { return maxindex + 1; }
};

enum sparseMatrix_err { not_match, sparseMatrix_index_out_of_range };
class sparseMatrix {
private:
	struct node {
		int col;
		int row;
		int num;
	};
	int rows;
	int cols;
	vector<node> arr;
	void checkrc ( int r, int c ) {
		if ( r > rows || c > cols || r < 1 || c < 1 ) {
			throw sparseMatrix_index_out_of_range;
		}
	}
public:
	/*手动构造矩阵，所有元素默认为0*/
	sparseMatrix ( int irows, int icols ) {
		rows = irows;
		cols = icols;
		//默认所有元素都是0
	}
	/*自动构造矩阵,5*5,全为0*/
	sparseMatrix () {
		rows = 5;
		cols = 5;
	}
	/*复制构造函数*/
	sparseMatrix ( sparseMatrix& raw ) {
		rows = raw.getRows ();
		cols = raw.getCols ();
		arr = *( new vector<node> );
		for ( int r = 0; r < rows; r++ ) {
			for ( int c = 0; c < cols; c++ ) {
				set ( r + 1, c + 1, raw.get ( r + 1, c + 1 ) );
			}
		}
		//默认所有元素都是0
	}
	const sparseMatrix& operator = ( const sparseMatrix& raw ) {

		rows = raw.getRows ();
		cols = raw.getCols ();
		arr = *( new vector<node> );
		for ( int r = 0; r < rows; r++ ) {
			for ( int c = 0; c < cols; c++ ) {
				set ( r + 1, c + 1, raw.get ( r + 1, c + 1 ) );
			}
		}
		return *this;
	}


	/*设置某位置元素的值*/
	void set ( int r, int c, int value ) {
		/*检查下标是否越界*/
		checkrc ( r, c );

		/*如果在数组中找到该元素*/
		if ( arr.getlength () == 0 ) {
			if ( value == 0 ) {
				return;
			} else {
				node temp;

				temp.col = c;
				temp.row = r;
				temp.num = value;
				arr.push ( temp );
				return;
			}
		} else {
			for ( int i = 0; i < arr.getlength (); i++ ) {
				if ( arr[i].col == c && arr[i].row == r ) {
					/*如果元素赋的值为0*/
					if ( value == 0 ) {
						arr.del ( i );
					} else {
						arr[i].num = value;
					}
					return;
				}
			}

			/*如果数组中找不到该元素*/
			/*如果元素赋的值为0*/
			if ( value == 0 ) {
				return;
			} else {
				node temp;

				temp.col = c;
				temp.row = r;
				temp.num = value;
				arr.push ( temp );
				return;
			}
		}

	}
	/*显示内容*/
	void show ( ostream& out )const {
		for ( int r = 0; r < rows; r++ ) {
			for ( int c = 0; c < cols; c++ ) {
				out << get ( r + 1, c + 1 ) << " ";
			}
			out << endl;
		}
		out << endl;
	}
	/*获取值*/
	int get ( int r, int c )const {
		if ( arr.getlength () == -1 ) {
			return 0;
		}
		for ( int i = 0; i < arr.getlength (); i++ ) {
			if ( arr[i].col == c && arr[i].row == r ) {
				return arr[i].num;
			}
		}
		return 0;
	}
	/*返回行数*/
	int getRows () const {
		return rows;
	}
	/*返回列数*/
	int getCols ()const {
		return cols;
	}



};
/*矩阵加法*/
const sparseMatrix operator + ( const sparseMatrix& l, const sparseMatrix& r ) {
	if ( l.getCols () != r.getCols () && l.getRows () != r.getRows () ) {
		throw not_match;
	}
	sparseMatrix temp ( l.getRows (), l.getCols () );
	for ( int tr = 0; tr < l.getRows (); tr++ ) {
		for ( int tc = 0; tc < l.getCols (); tc++ ) {
			temp.set ( tr + 1, tc + 1, ( l.get ( tr + 1, tc + 1 ) + r.get ( tr + 1, tc + 1 ) ) );
		}
	}
	return temp;
}
/*矩阵减法*/
const sparseMatrix operator * ( const sparseMatrix& l, const sparseMatrix& r ) {
	if ( l.getCols () != r.getRows () ) {
		throw not_match;
	}
	sparseMatrix temp ( l.getRows (), r.getCols () );

	/*乘积C的第m行第n列的元素等于矩阵A的第m行的元素与矩阵B的第n列对应元素乘积之和*/
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

ostream& operator << ( ostream& out, sparseMatrix& in ) {
	in.show ( out );
	return out;
}
int main () {
#pragma warning(disable:4996)//用于禁止vs的多余报错
	freopen ( "input.txt", "r", stdin );
	int funcnums = 0;
	cin >> funcnums;
	for ( int i = 0; i < funcnums; i++ ) {
		int funcnum = 0;
		cin >> funcnum;
		switch ( funcnum ) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		default:
			break;
		}

	}
	return 0;
}