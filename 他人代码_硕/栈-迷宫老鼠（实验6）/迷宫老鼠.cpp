/*ʣ�µ�bug:���ȣ���inputmaze�ж�ά����A�ǿ�������ģ�������main�������޷������Ϊʲô�� ʹ��int** &A����� 
��printpath�����У� ��ΰ�·��������Ǹ������� 
����ҵ�����·�����������������
��εõ����·���� 
*/
#include<iostream>
#include"ջ.h"
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
{//���ļ��ж���һ��m*n�Ķ�ά�����Թ� 
    m=n=10;
	A=new int* [m+2];  //Ϊ���ӱ߿�Ԥ���ռ� 
	for(int i=0;i<m+2;i++)
	{
		A[i]=new int [n+2];
	}

	cout<<"������Ҫ�򿪵��ļ�����";
    char ch[50];
	cin>>ch; 
	char *p=new char[40];
	fstream fin;  
	fin.open("maze.txt");
	  if(!fin)
	  {
	  	cerr<<"δ�ҵ����ļ���"<<endl;
	  	exit(1);
	  }
	  int j=1,r=1; 
	  while(!fin.eof())
	  {
	  	 fin.getline(p,40);  //���ļ���fin�ж�40���ֽڣ� ���Զ������ո� NO!
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
		{//����һ��ʱ,j�մ�n���n+1,�������б�Ϊ1 
			i++;  j=0;
		}*/
	  }
	fin.close();
}
static arrayStack<position> path;
bool findPath(int **A)
{//Ѱ��һ������ڣ�1,1�������ڣ�m,n)��·��
   int **maze=new int* [m+2];
	for(int i=0;i<m+2;i++)
	{
		maze[i]=new int [n+2];
	}
   for(int i=0;i<m+2;i++)
	   for(int j=0;j<n+2;j++)
	      maze[i][j]=A[i][j];
	    	
  //��ʼ��Ѱ·ƫ����
  position offset[4];
  offset[0].row=0; offset[0].col=1;  //�� 
  offset[1].row=1; offset[1].col=0;  //�� 
  offset[2].row=0; offset[2].col=-1; //�� 
  offset[3].row=-1; offset[3].col=0; //�� 
  //��ʼ���Թ����ܵ�Χǽ
   for(int i=0;i<m+2;i++)
      A[i][0]=A[i][n+1]=maze[i][0]=maze[i][n+1]=1;
   for(int i=0;i<n+2;i++)
      A[0][i]=A[m+1][i]=maze[0][i]=maze[m+1][i]=1;
  //��ʼ���������Թ���ǰλ��
  position here,next;
  here.row=1; here.col=1;
  path.push(here);
  maze[1][1]=1; //��ֹ�ص���� 
  int option=0;
  while(here.row!=m||here.col!=n)  //ֻ�е�row==m&&col==nʱ���ѳ�ѭ�� 
  {//������һ��һ��ѭ��
	   next.row=here.row+offset[option].row;
 	   next.col=here.col+offset[option].col;
 	   option++;
	 	   
 	 if(maze[next.row][next.col]==0)
 	 {//�����һ������ 	 
 	 	path.push(next);  //��һ������ջ 
 	 	here=next;        //�ߵ���һ��
		maze[here.row][here.col]=1;   //�����ϰ��� 
		option=0;         //����ѡ����
	 }
 	 else
 	 {//��һ�������ڣ�1.��ǰλ�����п���·�� 2.��ǰλ���޿���·����������һ�����������޿���·�� 
	    if(option<=3) { ; }
	    else
 	    {
		    if(path.empty()==true) 
		      return false;
	       //��Ҫ�ص���һ�� 
		   next=path.top();
		   path.pop();
		   here=next;
 	 	   option=0;   //����ѡ��������������Ϊ0�Ļ������Ч�жϣ����޸��ߵ�д���� 
	   }
    }
   } 
   //����ѭ��˵���ҵ��˳��� 
   path.push(here);
   return true;
}
void printPath(int **A)
{
	//�����ͼ 
	cout<<"Your maze is as followed:"<<endl;
	for(int i=0;i<12;i++)
	{
	   for(int j=0;j<12;j++)
	    {
		  if(A[i][j]==1) cout<<"��";
		  else cout<<"  ";
		}
		cout<<endl;
	}
    //���·��
	 cout<<endl<<"The path is:"<<endl;
	 for(int i=0;i<12;i++)
	 {
	   for(int j=0;j<12;j++)
	    {
		  if(A[i][j]==1) cout<<"��";
		  else if(path.maze_pos_search(i,j))  cout<<"��";
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












