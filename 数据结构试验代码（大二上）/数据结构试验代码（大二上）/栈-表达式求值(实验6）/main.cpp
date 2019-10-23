#include<iostream>
#include <string.h>
#include"栈.h"
#include"表达式.h"
using namespace std;

bool IsOperator(char ch)
	    { 
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
void infix_to_postfix(char *str)
	    {//本函数将中缀表达式转后缀表达式:(20+3)/1-1 -> 20 3 1 / + 1 -
	    //现在还差最后的输出问题。。动态分配的字符数组怎么为什么不能用cout输出啊？ 
	       arrayStack<char> oper;
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
				 }
				 else if(oper.empty()==true)
				 {//如果栈为空，直接把读到的操作符压入栈
				 	oper.push(str[i]); cout<<"aaa";
				 }
				 else if(Priority(str[i])>Priority(oper.top()))
				 {//如果读到的运算符优先级大于栈顶运算符优先级
				 	oper.push(str[i]);  cout<<"bbb";
				 }
				 else if(Priority(str[i])<=Priority(oper.top()))
				 {//如果读到的运算符优先级小于等于栈顶运算符优先级
				 	while(oper.empty()==false&&Priority(str[i])<=Priority(oper.top()))
				 	{//在运算符栈非空时
				 	   char temp=oper.pop();  cout<<temp<<" ";
				 	   if(temp!='('||temp!=')')
					   { ch[k++]=temp;  ch[k++]=' '; }
					}
				 	oper.push(str[i]);  cout<<"ccc";
				 }
			  cout<<"ddd"<<endl;
			  }
		   }
		   ch[k++]=' ';
	       ch[k++]=oper.pop();   //读入最后一个运算符
		   cout<<ch;
		   //delete [] str;     //加上就错.... 为什么？ 
		   str=ch;
		   cout<<str;
		}
int main()
{//2*(-3*(4+6/3)/2)+(-8-6)/(3-10)
//2*(-3*(4+6/3)/2)+(-8-6)/(3-10)
	expression<char> A("((-1)+(7)*((5*6))-(0-3)/(9/3))-(5+(9+4*3))+(-2+3*8/6*3-(2+3*4/6-(-2)*4))");
	cout<<A<<endl;
	A.standardization();
    A.infix_to_postfix(); cout<<endl;
	cout<<"The answer is:"<<A.calculate();
//	char *p="(20+3)/1-1";
//	cout<<p<<endl;
//	infix_to_postfix(p);
/*	char *ch=new char[10];
	memset(ch,'\0',10*sizeof(char));
	ch[0]='a'; ch[1]='b';
	cout<<strlen(ch)<<endl;
	cout<<sizeof(ch)<<endl;

	cout<<ch;*/
	
	return 0;
}


int calculate(char *str)
		{//for exmple:20 3 1 / + 1 -
			int pre,post,temp;   //前运算数、后运算数、中间结果 
			arrayStack<int> num;   //用来保存运算数的int栈
			//下面不断更新pre和post 
			//这里的str已经是后缀表达式了 
			int k=0;
			for(int i=0;str[i]!='\0';i++)
			{
				if(IsOperator(str[i])==false)
				{//读到数字 
				  while(IsOperator(str[i])==false)
				  {//读多位数字 ,跳出循环说明此时str[i]为空格 
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
	   
