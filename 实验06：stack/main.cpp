#include"stack.h"
#include"cal.h"
#include<iostream>
#pragma warning(disable:4996)
using namespace std;
/*实验六  栈
一、实验目的
1、掌握栈结构的定义与实现；
2、掌握栈结构的使用。
二、实验内容
1、创建栈类，采用数组描述；
2、计算数学表达式的值。
输入数学表达式，输出表达式的计算结果。数学表达式由单个数字和运算符“+”、“-”、“*”、“/”、“(”、“) ”构成，例如 2+3*(4+5)–6/4。假定表达式输入格式合法。
*3、以一个 m*n的长方阵表示迷宫，0和1分别表示迷宫中的通路和障碍。设计一个程序，对任意设定的迷宫，求出一条从入口到出口的通路，或得出没有通路的结论。
   迷宫根据一个迷宫数据文件建立。迷宫数据文件由一个包含0、1的矩阵组成。迷宫的通路可以使用通路上各点的坐标序列进行展示(使用图形展示最佳)。*/

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
	searchMazePath (maze, rows,cols, point(1,1),point(rows,cols), paths );

	/*----------------输出路径----------------*/
	for ( int r = 0; r < rows + 2; r++ ) {
		for ( int c = 0; c < cols + 2; c++ ) { 
				cout << maze[r][c];
		}
		cout << endl;
	}


	char str[100] = "(12*5-695+94.8/(44-(95/84+848)))-(12*5-695+94.8/(44-(95/84+848)))";
	char* postfix = new char[strlen ( str ) * 2];
	infixToPostfix ( str, postfix );
	cout << postfix << '\n';
	cout << calPostfix ( postfix );
	delete[] postfix;
	return 0;
}