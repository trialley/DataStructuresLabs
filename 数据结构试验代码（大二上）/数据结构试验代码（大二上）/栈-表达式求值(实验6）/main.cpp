#include<iostream>
#include <string.h>
#include"ջ.h"
#include"���ʽ.h"
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
	    	if(ch=='<'||ch=='>') return 0;   //������ʾѹ��ջ���'('��')' 
		} 
void infix_to_postfix(char *str)
	    {//����������׺���ʽת��׺���ʽ:(20+3)/1-1 -> 20 3 1 / + 1 -
	    //���ڻ�������������⡣����̬������ַ�������ôΪʲô������cout������� 
	       arrayStack<char> oper;
		   char *ch=new char[2*strlen(str)];
		   memset(ch,'\0',2*strlen(str)*sizeof(char));   //��ʼ������'\0'���ռ� 
		   int i=0,k=0; //i��str���α꣬k��ch���α� 
		   for(i=0;str[i]!='\0';i++)
		   {
		   	  if(IsOperator(str[i])==false)
		   	  {//������ 
		   	  	 ch[k++]=str[i]; 
			  }
			  else
			  {//�Ƿ��� 
			     ch[k++]=' ';
			  	 if(str[i]=='(') oper.push('<');
			  	 else if(str[i]==')')
			  	 {
			  	 	while(oper.top()!='<') {  ch[k++]=oper.pop();  }
				 }
				 else if(oper.empty()==true)
				 {//���ջΪ�գ�ֱ�ӰѶ����Ĳ�����ѹ��ջ
				 	oper.push(str[i]); cout<<"aaa";
				 }
				 else if(Priority(str[i])>Priority(oper.top()))
				 {//�����������������ȼ�����ջ����������ȼ�
				 	oper.push(str[i]);  cout<<"bbb";
				 }
				 else if(Priority(str[i])<=Priority(oper.top()))
				 {//�����������������ȼ�С�ڵ���ջ����������ȼ�
				 	while(oper.empty()==false&&Priority(str[i])<=Priority(oper.top()))
				 	{//�������ջ�ǿ�ʱ
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
	       ch[k++]=oper.pop();   //�������һ�������
		   cout<<ch;
		   //delete [] str;     //���Ͼʹ�.... Ϊʲô�� 
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
			int pre,post,temp;   //ǰ�������������������м��� 
			arrayStack<int> num;   //����������������intջ
			//���治�ϸ���pre��post 
			//�����str�Ѿ��Ǻ�׺���ʽ�� 
			int k=0;
			for(int i=0;str[i]!='\0';i++)
			{
				if(IsOperator(str[i])==false)
				{//�������� 
				  while(IsOperator(str[i])==false)
				  {//����λ���� ,����ѭ��˵����ʱstr[i]Ϊ�ո� 
				  	k=k*10+str[i]-'0';
				  	i++;
				  }
				  i--;  //������Ҫ��һλ������������˺þ�.. 
				  num.push(k);
				}  	
				else 
				{
					  if(str[i]==' ')
					  {//�����˿ո�,������������0,Ȼ�����һ���ַ� 
						k=0;
					  }
				      else{//������������� 
				            post=num.pop();  pre=num.pop();       //��������������ջ���ͳ�
				            if(str[i]=='+')   temp=pre+post;     //�����м�ֵ
				            if(str[i]=='-')   temp=pre-post;
				            if(str[i]=='*')   temp=pre*post;
				            if(str[i]=='/')   temp=pre/post;
				            num.push(temp);                     //���м���ѹ��ջ   
			              } 
			    }
			}
			return num.pop();
		}
	   
