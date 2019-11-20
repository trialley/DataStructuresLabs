#include<iostream>
#include"matrix.cpp"
#include"matrix.h"
using namespace std;

int main()
{
	matrix <int> A(2,2);
	A.element[0]=1;
	A.element[1]=1;
	A.element[2]=1;
	A.element[3]=1;
	cout<<A;
	return 0;
}
