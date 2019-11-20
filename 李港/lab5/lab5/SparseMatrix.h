/*一、实验目的
掌握稀疏矩阵结构的描述及操作的实现。
二、实验内容
1、 创建稀疏矩阵类，采用行主顺序把稀疏矩阵非 0 元素映射到一维数组中，
提供操作： 两个稀疏矩阵相加、 两个稀疏矩阵相乘、输出矩阵（以通常的
阵列形式输出）。
2、 键盘输入矩阵的行数、列数；按行输入矩阵的各元素值，建立矩阵；
3、 对建立的矩阵执行相加、相乘的操作，输出操作的结果矩阵。

加 乘 构造 输出

*/


#include<iostream>
#include"vector.h"
using namespace std;

enum SparseMatrix_err { not_match, SparseMatrix_index_out_of_range };

class SparseMatrix {
private:
	struct node {
		int col;
		int row;
		int num;
	};
	int rows;
	int cols;
	vector<node> arr;
	void checkrc(int r, int c) {
		if (r > rows || c > cols ||r<1||c<1) {
			throw SparseMatrix_index_out_of_range;
		}
	}
public:
	/*手动构造矩阵，所有元素默认为0*/
	SparseMatrix(int irows, int icols) {
		rows = irows;
		cols = icols;
		//析构自动清除，无需再手动删除
		arr = *(new vector<node>);
		//默认所有元素都是0
	}

	/*复制构造函数*/
	SparseMatrix(SparseMatrix& raw) {
		rows = raw.getrows();
		cols = raw.getcols();
		arr = *(new vector<node>);
		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < cols; c++) {
				setvalue(r + 1, c + 1, raw.getvalue(r + 1, c + 1));
			}
		}
		//默认所有元素都是0
	}

	/*设置某位置元素的值*/
	void setvalue(int r, int c, int value) {
		/*检查下标是否越界*/
		checkrc(r, c);

		/*如果在数组中找到该元素*/
		if (arr.getlength() == 0) {
			if (value == 0) {
				return;
			}
			else {
				node temp;

				temp.col = c;
				temp.row = r;
				temp.num = value;
				arr.push(temp);
				return;
			}
		}
		else {
			for (int i = 0; i < arr.getlength(); i++) {
				if (arr[i].col == c && arr[i].row == r) {
					/*如果元素赋的值为0*/
					if (value == 0) {
						arr.del(i);
					}
					else {
						arr[i].num = value;
					}
					return;
				}
			}

			/*如果数组中找不到该元素*/
/*如果元素赋的值为0*/
			if (value == 0) {
				return;
			}
			else {
				node temp;

				temp.col = c;
				temp.row = r;
				temp.num = value;
				arr.push(temp);
				return;
			}
		}

	}
	void show()const {
		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < cols; c++) {
				cout << getvalue(r+1, c+1) << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

	/*获取值*/
	int getvalue(int r, int c)const {
		if (arr.getlength() == -1) {
			return 0;
		}
		for (int i = 0; i < arr.getlength(); i++) {
			if (arr[i].col == c && arr[i].row == r) {
				return arr[i].num;
			}
		}
		return 0;
	}
	/*返回行数*/
	int getrows() const{
		return rows;
	}
	/*返回列数*/
	int getcols()const {
		return cols;
	}
	/*重载加法运算*/

	/*自动构造矩阵,5*5,全为0*/
	SparseMatrix() {
		rows = 5;
		cols = 5;
	}
	const SparseMatrix& operator = (const SparseMatrix& r) {
		if (getcols() != r.getrows() && getrows() != r.getcols()) {
			throw not_match;
		}
		for (int tr = 0; tr < r.getrows(); tr++) {
			for (int tc = 0; tc < r.getcols(); tc++) {
				setvalue(tr + 1, tc + 1, r.getvalue(tr + 1, tc + 1) );
			}
		}
		return *this;
	}

};

const SparseMatrix operator + (const SparseMatrix l, const SparseMatrix r) {
	if (l.getcols() != r.getrows() && l.getrows()!= r.getcols()) {
		throw not_match;
	}
	SparseMatrix temp(l.getrows(), r.getcols());
	for (int tr = 0; tr < r.getrows(); tr++) {
		for (int tc = 0; tc < r.getcols(); tc++) {
			temp.setvalue(tr + 1, tc + 1, (l.getvalue(tr + 1, tc + 1) + r.getvalue(tr + 1, tc + 1)));
		}
	}
	return temp;
}
