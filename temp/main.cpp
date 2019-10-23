#include<stdio.h>
#include<stdlib.h>
#include<ctype.h> 
#include<assert.h>
#include<stack>
#include<iostream>
using namespace std;

/*中缀转后缀函数*/
void infixToPostfix ( char str[], char* postfix );
double calPostfix ( char* postfix ) {
	stack<double> result;
	//需要将后缀表达式的数字逐个入栈，直到遇到符号，将前栈顶两个元素运算放回栈顶即可。
	for (int i=0 ;;) {
		if ( isdigit ( postfix[i] ) || postfix[i] == '.' ) {
			double temp = 0;
			double ch = 10;
			while ( isdigit ( postfix[i] ) || postfix[i] == '.' ) {/*过滤数字字符，直接输出，直到下一位不是数字字符打印空格跳出循环 */
				if ( postfix[i] == '.' ) {
					ch = 0.1;
				}
				temp = ( postfix[i++] - '0' ) + temp * ch;
			}
			result.push ( temp );

			//遇到符号，将前栈顶两个元素运算放回栈顶即可
		}
		if ( postfix[i] == ' ') {

		} else if ( postfix[i] == '+' ) {
			double a = result.top ();
			result.pop ();
			double b = result.top ();
			result.pop ();

			result.push ( a + b );
		} else if ( postfix[i] == '*' ) {
			double a = result.top ();
			result.pop ();
			double b = result.top ();
			result.pop ();

			result.push ( a * b );
		} else if ( postfix[i] == '/' ) {
			double a = result.top ();
			result.pop ();
			double b = result.top ();
			result.pop ();

			result.push ( a / b );
		} else if ( postfix[i] == '-' ) {
			double a = result.top ();
			result.pop ();
			double b = result.top ();
			result.pop ();

			result.push ( a - b );
		} else if( postfix[i] == '\0' ){
			return result.top ();
		} else {
			printf ( "\n输入非法字符！\n" );
			return 0;
		}
		i++;
	}

}


void infixToPostfix ( char str[],char* postfix ) {
/*
a.数字直接输出
b.运算符
情况一：遇到左括号直接入栈，遇到右括号将栈中左括号之后入栈的运算符全部弹栈输出，同时左括号出栈但是不输出。
情况二：遇到乘号和除号直接入栈，直到遇到优先级比它更低的运算符，依次弹栈。
情况三：遇到加号和减号，如果此时栈空，则直接入栈，否则，将栈中优先级高的运算符依次弹栈（注意：加号和减号属
		于同一个优先级，所以也依次弹栈）直到栈空或则遇到左括号为止，停止弹栈。（因为左括号要匹配右括号时才弹出）。
情况四：获取完后，将栈中剩余的运算符号依次弹栈输出
*/

	int j = 0;
	int i = 0;
	char e;
	stack<char> s;
	//while ( str[i] != '\0' )
	for ( ;;) {
		while ( isdigit ( str[i] ) || str[i] == '.' ) {/*过滤数字字符，直接输出，直到下一位不是数字字符打印空格跳出循环 */
			postfix[j++] = str[i++];
			if ( !isdigit ( str[i] ) && str[i]!='.' ) {
				postfix[j++] = ' ';
			}
		}

		/*遇到加号和减号，如果此时栈空，则直接入栈
		否则，将栈中优先级高的运算符依次弹栈（注意：加号和减号属于同一个优先级，所以也依次弹栈）直到栈空或则遇到左括号为止*/
		if ( str[i] == '+' || str[i] == '-' ) {
			if ( !s.size () ) {
				s.push ( str[i] );
			} else {
				do {
					e = s.top ();
					s.pop ();
					if ( e == '(' ) {
						s.push ( e );
					} else {
						postfix[j++] = e;
						postfix[j++] = ' ';
					}
				} while ( s.size () && e != '(' );

				s.push ( str[i] );
			}
		}else if ( str[i] == ')' ) {
			/*遇到右括号将栈中左括号之后入栈的运算符全部弹栈输出，同时左括号出栈但是不输出*/
			e = s.top ();
			s.pop ();
			while ( e != '(' ) {
				postfix[j++] = e;
				postfix[j++] = ' ';
				e = s.top ();
				s.pop ();
			}
		} else if ( str[i] == '*' || str[i] == '/' || str[i] == '(' ) {
			/*乘、除、左括号都是优先级高的，直接压栈*/
			s.push ( str[i] );
		} else if ( str[i] == '\0' ) {
			//获取完后，将栈中剩余的运算符号依次弹栈输出
				/*最后把栈中剩余的运算符依次弹栈打印*/
			while ( s.size () ) {
				e = s.top ();
				s.pop ();
				postfix[j++] = e;
				postfix[j++] = ' ';
			}
			postfix[j++] = '\0';
			return;
			break;
		} else {
			printf ( "\n输入非法字符！\n" );
			return;
		}
		i++;
	}

}