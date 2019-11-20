/*剩下的bug:首先，在inputmaze中二维数组A是可以输出的，但是在main函数中无法输出，为什么？ 使用int** &A解决？ 
在printpath函数中， 如何把路径输出，是个大问题 
如何找到所有路径？广度优先搜索。
如何得到最短路径？ 
*/
#include<iostream>
#include"栈.h"
#include<fstream>
#include<string.h>
using namespace std;
static int m,n;

class position
{
	public:
		int row;
		int col;
};
void inputMaze(int **&A)
{//从文件中读入一个m*n的二维数组迷宫 
    m=n=10;
	A=new int* [m+2];  //为增加边框预留空间 
	for(int i=0;i<m+2;i++)
	{
		A[i]=new int [n+2];
	}

	cout<<"请输入要打开的文件名：";
    char ch[50];
	cin>>ch; 
	char *p=new char[40];
	fstream fin;  
	fin.open("maze.txt");
	  if(!fin)
	  {
	  	cerr<<"未找到此文件！"<<endl;
	  	exit(1);
	  }
	  int j=1,r=1; 
	  while(!fin.eof())
	  {
	  	 fin.getline(p,40);  //从文件流fin中读40个字节？ 会自动跳过空格？ NO!
	  	 cout<<endl<<p<<endl;
	  	 sscanf(p,"%d %d %d %d %d %d %d %d %d %d",&A[r][1],&A[r][2],&A[r][3],&A[r][4],&A[r][5],&A[r][6],&A[r][7],&A[r][8],&A[r][9],&A[r][10]);
/*	  	 cout<<"A["<<r<<","<<1<<"]="<<A[r][1]<<" ";
	  	 cout<<"A["<<r<<","<<2<<"]="<<A[r][2]<<" ";
	  	 cout<<"A["<<r<<","<<3<<"]="<<A[r][3]<<" ";
	  	 cout<<"A["<<r<<","<<4<<"]="<<A[r][4]<<" ";
	  	 cout<<"A["<<r<<","<<5<<"]="<<A[r][5]<<" ";
	  	 cout<<"A["<<r<<","<<6<<"]="<<A[r][6]<<" ";
	  	 cout<<"A["<<r<<","<<7<<"]="<<A[r][7]<<" ";
	  	 cout<<"A["<<r<<","<<8<<"]="<<A[r][8]<<" ";
	  	 cout<<"A["<<r<<","<<9<<"]="<<A[r][9]<<" ";
	  	 cout<<"A["<<r<<","<<10<<"]="<<A[r][10]<<" ";*/
		   r++;
		  
/*		fin>>A[i][j++];
        if(j==n+1)
		{//读完一行时,j刚从n变成n+1,并更新列标为1 
			i++;  j=0;
		}*/
	  }
	fin.close();
}
static arrayStack<position> path;
bool findPath(int **A)
{//寻找一条从入口（1,1）到出口（m,n)的路径
   int **maze=new int* [m+2];
	for(int i=0;i<m+2;i++)
	{
		maze[i]=new int [n+2];
	}
   for(int i=0;i<m+2;i++)
	   for(int j=0;j<n+2;j++)
	      maze[i][j]=A[i][j];
	    	
  //初始化寻路偏移量
  position offset[4];
  offset[0].row=0; offset[0].col=1;  //右 
  offset[1].row=1; offset[1].col=0;  //下 
  offset[2].row=0; offset[2].col=-1; //左 
  offset[3].row=-1; offset[3].col=0; //上 
  //初始化迷宫四周的围墙
   for(int i=0;i<m+2;i++)
      A[i][0]=A[i][n+1]=maze[i][0]=maze[i][n+1]=1;
   for(int i=0;i<n+2;i++)
      A[0][i]=A[m+1][i]=maze[0][i]=maze[m+1][i]=1;
  //初始化老鼠在迷宫当前位置
  position here,next;
  here.row=1; here.col=1;
  path.push(here);
  maze[1][1]=1; //防止回到入口 
  int option=0;
  while(here.row!=m||here.col!=n)  //只有当row==m&&col==n时才脱出循环 
  {//这里是一步一个循环
	   next.row=here.row+offset[option].row;
 	   next.col=here.col+offset[option].col;
 	   option++;
	 	   
 	 if(maze[next.row][next.col]==0)
 	 {//如果下一步存在 	 
 	 	path.push(next);  //下一步存入栈 
 	 	here=next;        //走到下一步
		maze[here.row][here.col]=1;   //加上障碍物 
		option=0;         //重置选择数
	 }
 	 else
 	 {//下一步不存在：1.当前位置仍有可走路径 2.当前位置无可走路径，返回上一步继续看有无可走路径 
	    if(option<=3) { ; }
	    else
 	    {
		    if(path.empty()==true) 
		      return false;
	       //需要回到上一步 
		   next=path.top();
		   path.pop();
		   here=next;
 	 	   option=0;   //重置选择数，但是重置为0的会进行无效判断，有无更高的写法？ 
	   }
    }
   } 
   //跳出循环说明找到了出口 
   path.push(here);
   return true;
}
void printPath(int **A)
{
	//输出地图 
	cout<<"Your maze is as followed:"<<endl;
	for(int i=0;i<12;i++)
	{
	   for(int j=0;j<12;j++)
	    {
		  if(A[i][j]==1) cout<<"█";
		  else cout<<"  ";
		}
		cout<<endl;
	}
    //输出路径
	 cout<<endl<<"The path is:"<<endl;
	 for(int i=0;i<12;i++)
	 {
	   for(int j=0;j<12;j++)
	    {
		  if(A[i][j]==1) cout<<"█";
		  else if(path.maze_pos_search(i,j))  cout<<"·";
		  else cout<<"  ";
		}
		cout<<endl;
	 }
	 
}

int main()
{
	int **A;
	inputMaze(A);
	findPath(A);
	printPath(A);
	return 0;
}












