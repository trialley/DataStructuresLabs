#include<iostream>
#include"ϡ�����.h"
#include"Arraylist.h"
using namespace std;

int main()
{
	sparseMatrix<int> A,B,C,D;
	cin>>A;
	cout<<A<<endl;	
	cin>>B;
	//cout<<B<<endl<<"�ӷ������"<<endl;
	//A.add(B,D);
	//cout<<"�ӷ��Ľ����"<<D<<endl; 
	//D.matrix_print();
	C=A*B;
	cout<<"�˷��Ľ����"<<C<<endl;
	C.matrix_print();
//	Arraylist<int> K;
//	K.insert(0,1);

	return 0;
}
