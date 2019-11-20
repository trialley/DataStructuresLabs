#include "matrix.h"
#include <iostream>
#include <algorithm>
using namespace std;

template<class T>
matrix<T>::matrix(int row,int col)
{//构造函数,只给空间不赋值 
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
{//复制构造函数、深复制 
	*this.Row=A.row;
	*this.Column=A.col;
	element=new T[Row*Column];
	
	copy(A.element,A.element+Row*Column,element);
	//复制m的每一个元素 
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
{//矩阵乘法. 返回矩阵C=(*this)*A 
		if(Column!=A.Row) cerr<<"The column of left matrix and row of right matrix must be same."<<endl;

		matrix<T> w(Row,A.Column);
		int ct=0,cw=0,ca=0;  //三个矩阵的游标初始化并以（1，1）元素定位 
		for(int i=1;i<Row;i++)
		{//第i行 
			for(int j=1;j<A.Column;j++)
			{//第j列 
				T sum=element[i]*element[j];  //计算w(i,j)第一项 
				for(int k=2;k<Column;k++)
				{//计算剩余项 
				    ct=ct+1;
				    ca=ca+A.Column;
					sum+=element[ct]*A.element[ca];
				}
				w.element[cw++]=sum;  //存储在w(i,j) 
				//转到该行开头，该列的下一列 
				ct=ct-(Column-1);
				ca=j;
			}
			//转到该行的下一行开头，转到第一列
			ct=ct+Column;
			ca=0;
		}
	return w; 
}



