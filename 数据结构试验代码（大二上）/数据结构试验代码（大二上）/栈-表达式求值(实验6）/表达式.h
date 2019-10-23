#pragma once
#include<iostream>
#include <string.h>
#include"ջ.h"
using namespace std;
//��������Ҫ����������delete�� 
template<class T>
class expression
{//���ʽ��:������Լ�������Ӽ��˳������ţ���δʵ�֣����༶���ŵ���ѧ���ʽ��ֵ��
	public:
		expression(int n=70)
		{//��ʼ�������ַ����ĳ��� 
			T *str=new T[n];
		    memset(str,'\0',strlen(str)*sizeof(char));
		}
		expression(const char a[])  //���캯�� 
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
	    {//����������׺���ʽת��׺���ʽ:(20+3)/1-1 -> 20 3 1 / + 1 -
	    //2*(3*(4+6/3)/2) -> 2 3 4 6 3 / + * 2 *
	    //���ڻ�������������⡣����̬������ַ�������ôΪʲô������cout������� 
	       standardization();
		   arrayStack<char> oper;   //������������ַ�ջ 
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
			  	 	if(oper.top()=='<')  oper.pop();   //������������ 
				 }
				 else if(oper.empty()==true)
				 {//���ջΪ�գ�ֱ�ӰѶ����Ĳ�����ѹ��ջ
				 	oper.push(str[i]);   //cout<<"aaa";
				 }
				 else if(Priority(str[i])>Priority(oper.top()))
				 {//�����������������ȼ�����ջ����������ȼ�
				 	oper.push(str[i]);    //cout<<"bbb";
				 }
				 else if(Priority(str[i])<=Priority(oper.top()))
				 {//�����������������ȼ�С�ڵ���ջ����������ȼ�
				 	while(oper.empty()==false&&Priority(str[i])<=Priority(oper.top()))
				 	{//�������ջ�ǿ�ʱ
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
	          ch[k++]=oper.pop();   //����ʣ��������
		   }
		   //cout<<ch;
		   delete [] str;     //���Ͼʹ�.... Ϊʲô��
		   str=ch;
		   //cout<<str;
		}
		float calculate()
		{//for exmple:20 3 1 / + 1 -
			float pre,post,temp;   //ǰ�������������������м��� 
			arrayStack<float> num;   //����������������intջ
			//���治�ϸ���pre��post 
			//�����str�Ѿ��Ǻ�׺���ʽ�� 
			int k=0;
			for(int i=0;str[i]!='\0';i++)
			{
				if(IsOperator(str[i])==false)
				{//�������� 
				  while(IsOperator(str[i])==false)
				  {//����λ����,����ѭ��˵����ʱstr[i]Ϊ�ո� 
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
	    bool IsOperator(char ch)
	    {//�ж��Ƿ�Ϊ����� 
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
	    void standardization()
	    {//��-8ת��0-8 
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
        {//���ַ�������Ϊi��λ�ò����ַ�ch 
        	int size=strlen(str);
        	if(i<0||i>=size)
			{
			    cerr<<"�Ƿ������ַ�"<<endl; 
				exit(1);
		    } 
		    int temp=strlen(str);
			for(int j=strlen(str)-1;j>=i;j--)
			{//��������һ��new�������ַ���,ʵ�ʳ��ȴ���strlen 
				str[j+1]=str[j];
			} 
        	str[i]=ch;
        	str[strlen(str)]='\0';   //ɨβ���� 
        	//cout<<str<<endl;
		}
	private:
		T *str=NULL;     //�ַ����鱣����ʽ�ַ���(��׺�� 
		arrayStack<T> oper;    //����������ö�ջ 
};

