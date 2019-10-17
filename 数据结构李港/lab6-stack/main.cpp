/*一、实验目的


2、计算数学表达式的值。
输入数学表达式，输出表达式的计算结果。数学表达式由单个数字和运
算符“+”、“-”、“*”、“/”、“(”、“) ”构成， 例如 2+3*(4+5)–6/4。 假定表达式
输入格式合法。

*3、 以一个 m*n 的长方阵表示迷宫， 0 和 1 分别表示迷宫中的通路和障碍。
设计一个程序，对任意设定的迷宫，求出一条从入口到出口的通路， 或得出
没有通路的结论。
迷宫根据一个迷宫数据文件建立。迷宫数据文件由一个包含 0、 1 的矩阵
组成。迷宫的通路可以使用通路上各点的坐标序列进行展示(使用图形展示最
佳)*/
#include<iostream>
#include<fstream>
using namespace std;

#include"stack.h"

void cal() {
	char str[] = "1+(2-3)*4/5";

}
void maze() {
	/*------构建迷宫矩阵开始----------*/
	//(1,1)是入口，(rows,cols)是出口，矩阵外围封闭
	int maze[100][100];
	ifstream infile;
	infile.open("./maze.txt");

	int rows, cols;
	infile >> rows >> cols;

	/*载入迷宫*/
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			infile >> maze[r+1][c+1];
		}
	}


	/*封闭迷宫顶部*/
	for (int c = 0; c < cols+2; c++) {
		maze[0][c] = 1;
	}
	/*封闭迷宫底部*/
	for (int c = 0; c < cols + 2; c++) {
		maze[rows+1][c] = 1;
	}
	/*封闭迷宫左侧*/
	for (int r = 0; r < rows + 2; r++) {
		maze[r][0] = 1;
	}
	/*封闭迷宫右侧*/
	for (int r = 0; r < rows + 2; r++) {
		maze[r][cols+1] = 1;
	}

	/*------构建迷宫矩阵结束----------*/

	/*------输出迷宫矩阵开始----------*/
	for (int r = 0; r < rows+2; r++) {
		for (int c = 0; c < cols+2; c++) {
			cout << maze[r][c];
		}
		cout << endl;
	}
	/*------输出迷宫矩阵结束----------*/


	/*使用栈计算路径*/
}
int main() {
	cal();
	maze();
}