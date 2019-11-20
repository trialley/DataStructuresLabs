#include<iostream>
#include"稀疏矩阵.h"
#include"Arraylist.h"
using namespace std;

int main()
{
	sparseMatrix<int> A,B,C,D;
	cin>>A;
	cout<<A<<endl;	
	cin>>B;
	//cout<<B<<endl<<"加法结果："<<endl;
	//A.add(B,D);
	//cout<<"加法的结果是"<<D<<endl; 
	//D.matrix_print();
	C=A*B;
	cout<<"乘法的结果是"<<C<<endl;
	C.matrix_print();
//	Arraylist<int> K;
//	K.insert(0,1);

	return 0;
}
