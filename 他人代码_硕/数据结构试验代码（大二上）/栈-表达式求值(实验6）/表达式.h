#pragma once
#include<iostream>
#include <string.h>
#include"栈.h"
using namespace std;
//析构函数要命啊，不能delete？ 
template<class T>
class expression
{//表达式类:本类可以计算包含加减乘除、负号（尚未实现）、多级括号的数学表达式的值，
	public:
		expression(int n=70)
		{//初始化设置字符串的长度 
			T *str=new T[n];
		    memset(str,'\0',strlen(str)*sizeof(char));
		}
		expression(const char a[])  //构造函数 
		{
			int i;
			int size=strlen(a);
			str=new char[size+1];

			   for(i=0;i<size;i++)  { str[i]=a[i]; }
			   str[i]='\0';

		} 
		~expression()
		{
			delete []str;
		}
		friend istream& operator>>(istream &in,expression &A)
		{
			in>>A.str;
			return in;
		}
		friend ostream& operator<<(ostream &out,expression &A)
		{
			out<<A.str;
			return out;
		}    
		void infix_to_postfix()
	    {//本函数将中缀表达式转后缀表达式:(20+3)/1-1 -> 20 3 1 / + 1 -
	    //2*(3*(4+6/3)/2) -> 2 3 4 6 3 / + * 2 *
	    //现在还差最后的输出问题。。动态分配的字符数组怎么为什么不能用cout输出啊？ 
	       standardization();
		   arrayStack<char> oper;   //保存运算符的字符栈 
		   char *ch=new char[2*strlen(str)];
		   memset(ch,'\0',2*strlen(str)*sizeof(char));   //初始化，用'\0'填充空间 
		   int i=0,k=0; //i是str的游标，k是ch的游标 
		   for(i=0;str[i]!='\0';i++)
		   {
		   	  if(IsOperator(str[i])==false)
		   	  {//是数字 
		   	  	 ch[k++]=str[i]; 
			  }
			  else
			  {//是符号 
			     ch[k++]=' ';
			  	 if(str[i]=='(') oper.push('<');
			  	 else if(str[i]==')')
			  	 {
			  	 	while(oper.top()!='<') {  ch[k++]=oper.pop();  }
			  	 	if(oper.top()=='<')  oper.pop();   //弹出但不保存 
				 }
				 else if(oper.empty()==true)
				 {//如果栈为空，直接把读到的操作符压入栈
				 	oper.push(str[i]);   //cout<<"aaa";
				 }
				 else if(Priority(str[i])>Priority(oper.top()))
				 {//如果读到的运算符优先级大于栈顶运算符优先级
				 	oper.push(str[i]);    //cout<<"bbb";
				 }
				 else if(Priority(str[i])<=Priority(oper.top()))
				 {//如果读到的运算符优先级小于等于栈顶运算符优先级
				 	while(oper.empty()==false&&Priority(str[i])<=Priority(oper.top()))
				 	{//在运算符栈非空时
				 	   char temp=oper.pop();  //cout<<temp<<" ";
				 	   if(temp!='('||temp!=')')
					   { ch[k++]=temp;  ch[k++]=' '; }
					}
				 	oper.push(str[i]);  //cout<<"ccc";
				 }
			  //cout<<"ddd"<<endl;
			  }
		   }
		   while(oper.empty()==false)
		   {
		   	  ch[k++]=' ';
	          ch[k++]=oper.pop();   //读入剩余的运算符
		   }
		   //cout<<ch;
		   delete [] str;     //加上就错.... 为什么？
		   str=ch;
		   //cout<<str;
		}
		float calculate()
		{//for exmple:20 3 1 / + 1 -
			float pre,post,temp;   //前运算数、后运算数、中间结果 
			arrayStack<float> num;   //用来保存运算数的int栈
			//下面不断更新pre和post 
			//这里的str已经是后缀表达式了 
			int k=0;
			for(int i=0;str[i]!='\0';i++)
			{
				if(IsOperator(str[i])==false)
				{//读到数字 
				  while(IsOperator(str[i])==false)
				  {//读多位数字,跳出循环说明此时str[i]为空格 
				  	k=k*10+str[i]-'0';
				  	i++;
				  }
				  i--;  //这里需要回一位，否则出错，看了好久.. 
				  num.push(k);
				}  	
				else 
				{
					  if(str[i]==' ')
					  {//读到了空格,将新运算数置0,然后等下一个字符 
						k=0;
					  }
				      else{//读到了运算符号 
				            post=num.pop();  pre=num.pop();       //把两个运算数从栈中掏出
				            if(str[i]=='+')   temp=pre+post;     //计算中间值
				            if(str[i]=='-')   temp=pre-post;
				            if(str[i]=='*')   temp=pre*post;
				            if(str[i]=='/')   temp=pre/post;
				            num.push(temp);                     //把中间结果压入栈   
			              } 
			    }  
			}
			return num.pop();
		}
	    bool IsOperator(char ch)
	    {//判断是否为运算符 
          switch (ch) 
          { 
          case '+':return true; break; 
          case '-':return true; break; 
          case '*':return true; break; 
          case '/':return true; break; 
          case ' ':return true; break;
		  case '(':return true; break;
          case ')':return true; break; 
          default: return false;
          }  
        } 
	    int Priority(char ch)
	    {
	    	if(ch=='+'||ch=='-') return 1;
	    	if(ch=='*'||ch=='/') return 2;
	    	if(ch=='('||ch==')') return 10;
	    	if(ch=='<'||ch=='>') return 0;   //用来表示压入栈后的'('和')' 
		}
	    void standardization()
	    {//把-8转成0-8 
	       // cout<<strlen(str)<<endl;
	     	for (int i = 0; i < strlen(str); i++)
		    {
			    if (str[i] == '-')
			    {
				    if (i == 0)
				    insert(str,0,'0');
			        else if (str[i - 1] == '(')
				    insert(str, i, '0');
			   }
		    }
		    //cout<<str<<endl;
       }
        void insert(char *str,int i,char ch)
        {//在字符串索引为i的位置插入字符ch 
        	int size=strlen(str);
        	if(i<0||i>=size)
			{
			    cerr<<"非法插入字符"<<endl; 
				exit(1);
		    } 
		    int temp=strlen(str);
			for(int j=strlen(str)-1;j>=i;j--)
			{//我这里是一个new出来的字符串,实际长度大于strlen 
				str[j+1]=str[j];
			} 
        	str[i]=ch;
        	str[strlen(str)]='\0';   //扫尾工作 
        	//cout<<str<<endl;
		}
	private:
		T *str=NULL;     //字符数组保存表达式字符串(中缀） 
		arrayStack<T> oper;    //保存运算符用堆栈 
};

