/*****************************************************************************
*  main.cpp                                                                  *
*  Copyright (C) 2019.10.25 TriAlley  lg139@139.com                          *
*  @brief    栈测试                                                           *
*  @license  GNU General Public License (GPL)                                *
*****************************************************************************/
#include"stack.h"
#include"cal.h"
#include<iostream>
#pragma warning(disable:4996)
using namespace std;

struct point{
	int _row;
	int _col;
	point ( int row, int col ) :_row ( row ), _col ( col ) {}
	point ():_row ( 0 ), _col ( 0 ) {}
};


template<class T>
bool searchMazePathBFS ( char** maze, int m, int n, point entry, point finish, stack<T>& paths ) {

	paths.push ( entry );
	while ( !paths.empty () ) {
		point current = paths.top ();
		paths.pop ();
		maze[current._row][current._col] = '*';

		//如果到了终点则返回真
		if ( current._row == finish._row && current._col == finish._col ) {
			return true;
		}

		//上
		if ( maze[current._row - 1][current._col] == '0' ) {paths.push ( point ( current._row - 1, current._col ) );}
		//下
		if ( maze[current._row + 1][current._col] == '0' ) {paths.push ( point ( current._row + 1, current._col ) );}
		//左
		if ( maze[current._row][current._col - 1] == '0' ) {paths.push ( point ( current._row, current._col - 1 ) );}
		//右
		if ( maze[current._row][current._col + 1] == '0' ) {paths.push ( point ( current._row, current._col + 1 ) );}
	}

	return false;
}
template<class T>
bool searchMazePath ( char** maze,int m, int n, point entry, point finish, stack<T>& paths ){

	paths.push ( entry );
	while ( !paths.empty () ) {
		point current = paths.top ();
		maze[current._row][current._col] = '*';

		//如果到了终点则返回真
		if ( current._row == finish._row && current._col == finish._col ) {
			return true;
		}

		//上
		if ( maze[ current._row - 1][current._col] == '0' ) {//如果能通过，则入栈
			paths.push ( point( current._row-1, current._col) );
			continue;
		}

		//下
		if ( maze[current._row +1][current._col] == '0' ) {
			paths.push ( point ( current._row + 1, current._col ) );
			continue;
		}

		//左
		if ( maze[current._row][current._col-1] == '0') {
			paths.push ( point ( current._row, current._col-1 ) );
			continue;
		}

		//右
		if ( maze[current._row][current._col + 1] == '0' ) {
			paths.push ( point ( current._row, current._col + 1 ) );
			continue;
		}

		paths.pop ();    //若上下左右都不通，则回溯。
		maze[current._row][current._col] = '+';
	}

	return false;
}

int main () {
	freopen ( "input.txt", "r", stdin );

	int rows, cols;
	cin >> rows >> cols;
	/*------构建迷宫矩阵开始----------*/
	char** maze = new char*[rows+2];
	for ( int r = 0; r < rows+2; r++ ) {
		maze[r] = new char[cols + 2];
	}

	for ( int r = 0; r < rows; r++ ) {
		for ( int c = 0; c < cols; c++ ) {cin >> maze[r + 1][c + 1];}
	}
	for ( int c = 0; c < cols + 2; c++ ) {maze[0][c] = '1';}
	for ( int c = 0; c < cols + 2; c++ ) {maze[rows + 1][c] = '1';}
	for ( int r = 0; r < rows + 2; r++ ) {maze[r][0] = '1';}
	for ( int r = 0; r < rows + 2; r++ ) {maze[r][cols + 1] = '1';}
	for ( int r = 0; r < rows + 2; r++ ) {
		for ( int c = 0; c < cols + 2; c++ ) {cout << maze[r][c];}
		cout << endl;
	}
	/*------构建迷宫矩阵结束----------*/


	/*使用栈计算路径*/
	//(1,1)是入口，(rows,cols)是出口，矩阵外围封闭
	stack<point> paths;
	if ( searchMazePath ( maze, rows, cols, point ( 1, 1 ), point ( rows, cols ), paths ) ) {
		printf ( "寻找成功：\n" );
	} else {
		printf ( "寻找失败！\n" );
	}

	/*----------------输出路径----------------*/
	printf ( "\n已经行走的一条道路：\n" );
	for ( int r = 0; r < rows + 2; r++ ) {
		for ( int c = 0; c < cols + 2; c++ ) { 
				cout << maze[r][c];
		}
		cout << endl;
	}
	calExpression<double> cal;

	char str[100] = "12*5-695+94.8/(44-(95/84+848))";
	char* postfix = new char[strlen ( str ) * 2];
	cal.infixToPostfix ( str, postfix );
	
	cout << "中缀表达式：" << str << '\n';
	cout <<"后缀表达式：" <<postfix << '\n';
	cout <<"计算结果："<< cal.calPostfix ( postfix );
	delete[] postfix;
	return 0;
}