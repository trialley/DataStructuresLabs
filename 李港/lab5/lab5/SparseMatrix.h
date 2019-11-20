/*һ��ʵ��Ŀ��
����ϡ�����ṹ��������������ʵ�֡�
����ʵ������
1�� ����ϡ������࣬��������˳���ϡ������ 0 Ԫ��ӳ�䵽һά�����У�
�ṩ������ ����ϡ�������ӡ� ����ϡ�������ˡ����������ͨ����
������ʽ�������
2�� �����������������������������������ĸ�Ԫ��ֵ����������
3�� �Խ����ľ���ִ����ӡ���˵Ĳ�������������Ľ������

�� �� ���� ���

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
	/*�ֶ������������Ԫ��Ĭ��Ϊ0*/
	SparseMatrix(int irows, int icols) {
		rows = irows;
		cols = icols;
		//�����Զ�������������ֶ�ɾ��
		arr = *(new vector<node>);
		//Ĭ������Ԫ�ض���0
	}

	/*���ƹ��캯��*/
	SparseMatrix(SparseMatrix& raw) {
		rows = raw.getrows();
		cols = raw.getcols();
		arr = *(new vector<node>);
		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < cols; c++) {
				setvalue(r + 1, c + 1, raw.getvalue(r + 1, c + 1));
			}
		}
		//Ĭ������Ԫ�ض���0
	}

	/*����ĳλ��Ԫ�ص�ֵ*/
	void setvalue(int r, int c, int value) {
		/*����±��Ƿ�Խ��*/
		checkrc(r, c);

		/*������������ҵ���Ԫ��*/
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
					/*���Ԫ�ظ���ֵΪ0*/
					if (value == 0) {
						arr.del(i);
					}
					else {
						arr[i].num = value;
					}
					return;
				}
			}

			/*����������Ҳ�����Ԫ��*/
/*���Ԫ�ظ���ֵΪ0*/
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

	/*��ȡֵ*/
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
	/*��������*/
	int getrows() const{
		return rows;
	}
	/*��������*/
	int getcols()const {
		return cols;
	}
	/*���ؼӷ�����*/

	/*�Զ��������,5*5,ȫΪ0*/
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
