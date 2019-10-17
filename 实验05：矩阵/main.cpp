/*****************************************************************************
*  main.cpp                                                                  *
*  Copyright (C) 2019.10.11 TriAlley  lg139@139.com                          *
*  @brief    ����ӳ˵Ĳ���                                                  *
*  @license  GNU General Public License (GPL)                                *
*****************************************************************************/
#include<iostream>
using namespace std;
#include"./sparseMatrix.h"

#pragma warning(disable:4996)//���ڽ�ֹvs�Ķ��౨��
int main () {
	
	FILE* fileh =  freopen ( "input.txt", "r", stdin );

	/*������ͬ�͵�ab������˸�ֵ��c*/
	int rows, cols,nums,inum;
	cin >> rows>> cols>> nums;
	sparseMatrix<int> a( rows, cols );
	for ( int i = 0; i < nums; i++ ) {
		cin >> rows >> cols >> inum;
		a.set ( rows, cols , inum );
	}

	cin >> rows >> cols >> nums;
	sparseMatrix<int> b ( rows, cols );
	for ( int i = 0; i < nums; i++ ) {
		cin >> rows >> cols >> inum;
		b.set ( rows, cols , inum );
	}
	sparseMatrix<int>  c;
	c = a * b;

	cout << "����˷����ԣ�" << endl;
	cout << a << endl;
	cout << b << endl;
	cout << "��˽��" << endl;
	cout << c << endl;


	/*������ͬ�͵�de������˸�ֵ��f*/
	cin >> rows >> cols >> nums;
	sparseMatrix<int> d ( rows, cols );
	for ( int i = 0; i < nums; i++ ) {
		cin >> rows >> cols >> inum;
		d.set ( rows, cols , inum );
	}

	cin >> rows >> cols >> nums;
	sparseMatrix<int> e ( rows, cols );
	for ( int i = 0; i < nums; i++ ) {
		cin >> rows >> cols >> inum;
		e.set ( rows, cols , inum );
	}
	sparseMatrix<int>  f;
	f = e + d;

	cout << "����ӷ����ԣ�" << endl;
	cout << d << endl;
	cout << e << endl;
	cout << "��ӽ��" << endl;
	cout << f << endl;

	return 0;
}