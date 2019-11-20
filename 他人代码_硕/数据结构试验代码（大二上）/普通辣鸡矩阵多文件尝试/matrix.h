#pragma once
#include<iostream>
using namespace std;
template<class T>
class matrix
{
	friend ostream& operator<<(ostream &out, const matrix<T> &A)
	{
	   for(int i=0;i<A.Row*A.Column;i++)
	   {
		   out<<A.element[i]<<" ";
	   }
	   out<<endl;
	   return out;
    }
	public:
		matrix(int row=0,int col=0);
		matrix(const matrix<T>&);
		~matrix();
		int rows() const {return Row;}
		int columns() const {return Column;}
		T& operator()(int i,int j) const;
		matrix<T>& operator=(const matrix<T>& );
		matrix<T> operator+(const matrix<T>& );
		matrix<T> operator-(const matrix<T>& );
		matrix<T> operator*(const matrix<T>& );
		
	//protected:
		int Row,Column;  //行数、列数(从1开始） 
		T *element;     //下标从0开始 
		
};

/*
	matrix<T> w(Row,A.Column);
	int ct=0,cw=0,ca=0; 
	for(int i=1;i<Row;i++)
	{
	  for(int j=1;j<Column;j++)
	  {
	     T sum=element[ct]*A.element[ca];
	     for(int k=2;k<Row;k++)
	     {
	        ct++;
	        ca=ca+A.Column;
	        sum+=element[ct]*element[ca];
	     }
	     ct=ct-(Column-1);
	     ca=j;
	  }
	  ct=ct+Column;
	  ca=0;
    }
*/
