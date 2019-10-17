/*****************************************************************************
*  main.cpp                                                                  *
*  Copyright (C) 2019.10.11 TriAlley  lg139@139.com                          *
*  @brief    矩阵加乘的测试                                                  *
*  @license  GNU General Public License (GPL)                                *
*****************************************************************************/
#include<iostream>
using namespace std;
#include"./sparseMatrix.h"

#pragma warning(disable:4996)//用于禁止vs的多余报错
int main () {
	
	FILE* fileh =  freopen ( "input.txt", "r", stdin );

	/*构建不同型的ab矩阵，相乘赋值给c*/
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

	cout << "矩阵乘法测试：" << endl;
	cout << a << endl;
	cout << b << endl;
	cout << "相乘结果" << endl;
	cout << c << endl;


	/*构建不同型的de矩阵，相乘赋值给f*/
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

	cout << "矩阵加法测试：" << endl;
	cout << d << endl;
	cout << e << endl;
	cout << "相加结果" << endl;
	cout << f << endl;

	return 0;
}