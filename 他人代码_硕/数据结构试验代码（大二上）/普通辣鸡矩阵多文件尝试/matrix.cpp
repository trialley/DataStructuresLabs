#include "matrix.h"
#include <iostream>
#include <algorithm>
using namespace std;

template<class T>
matrix<T>::matrix(int row,int col)
{//���캯��,ֻ���ռ䲻��ֵ 
	if(row<=0||col<=0)
	{
		cerr<<"Rows and columns must be >0"<<endl;
		return;
	}
	else{
		this->Row=row;
		this->Column=col;
		element=new T[Row*Column];
	}
}
template<class T>
matrix<T>::matrix(const matrix<T> &A)
{//���ƹ��캯������� 
	*this.Row=A.row;
	*this.Column=A.col;
	element=new T[Row*Column];
	
	copy(A.element,A.element+Row*Column,element);
	//����m��ÿһ��Ԫ�� 
}
template<class T>
matrix<T>::~matrix()
{
	delete [] element;
}
template<class T>
matrix<T>& matrix<T>::operator=(const matrix<T> &A)
{
	if(this!=&A)
	{
	*this.Row=A.row;
	*this.Column=A.col;
	element=new T[Row*Column];
	
	copy(A.element,A.element+Row*Column,element);
    }
    return *this;
}
template<class T>
T& matrix<T>::operator()(int i,int j) const
{
	if(i>Row||j>Column||i<1||j<1) cerr<<"matrix index out of bounds."<<endl;
	else return element[(i-1)*Row+j-1];
}
template<class T>
matrix<T> matrix<T>::operator+(const matrix<T> &A)
{
	if(Row!=A.Row||Column!=A.Column) cerr<<"The row and column number of two matrixs must be same."<<endl;
	else{
		matrix<T> C(Row,Column);
		for(int i=0;i<Row*Column;i++)
		{
			C.element[i]=element[i]+A.element[i];
		}
		return C;
	}
}
template<class T>
matrix<T> matrix<T>::operator-(const matrix<T> &A)
{
	if(Row!=A.Row||Column!=A.Column) cerr<<"The row and column number of two matrixs must be same."<<endl;
	else{
		matrix<T> C(Row,Column);
		for(int i=0;i<Row*Column;i++)
		{
			C.element[i]=element[i]-A.element[i];
		}
		return C;
	}
}
template<class T>
matrix<T> matrix<T>::operator*(const matrix<T> &A)
{//����˷�. ���ؾ���C=(*this)*A 
		if(Column!=A.Row) cerr<<"The column of left matrix and row of right matrix must be same."<<endl;

		matrix<T> w(Row,A.Column);
		int ct=0,cw=0,ca=0;  //����������α��ʼ�����ԣ�1��1��Ԫ�ض�λ 
		for(int i=1;i<Row;i++)
		{//��i�� 
			for(int j=1;j<A.Column;j++)
			{//��j�� 
				T sum=element[i]*element[j];  //����w(i,j)��һ�� 
				for(int k=2;k<Column;k++)
				{//����ʣ���� 
				    ct=ct+1;
				    ca=ca+A.Column;
					sum+=element[ct]*A.element[ca];
				}
				w.element[cw++]=sum;  //�洢��w(i,j) 
				//ת�����п�ͷ�����е���һ�� 
				ct=ct-(Column-1);
				ca=j;
			}
			//ת�����е���һ�п�ͷ��ת����һ��
			ct=ct+Column;
			ca=0;
		}
	return w; 
}



