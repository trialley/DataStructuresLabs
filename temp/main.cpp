#include<stdio.h>
#include<stdlib.h>
#include<ctype.h> 
#include<assert.h>
#include<stack>
#include<iostream>
using namespace std;

/*��׺ת��׺����*/
void infixToPostfix ( char str[], char* postfix );
double calPostfix ( char* postfix ) {
	stack<double> result;
	//��Ҫ����׺���ʽ�����������ջ��ֱ���������ţ���ǰջ������Ԫ������Ż�ջ�����ɡ�
	for (int i=0 ;;) {
		if ( isdigit ( postfix[i] ) || postfix[i] == '.' ) {
			double temp = 0;
			double ch = 10;
			while ( isdigit ( postfix[i] ) || postfix[i] == '.' ) {/*���������ַ���ֱ�������ֱ����һλ���������ַ���ӡ�ո�����ѭ�� */
				if ( postfix[i] == '.' ) {
					ch = 0.1;
				}
				temp = ( postfix[i++] - '0' ) + temp * ch;
			}
			result.push ( temp );

			//�������ţ���ǰջ������Ԫ������Ż�ջ������
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
			printf ( "\n����Ƿ��ַ���\n" );
			return 0;
		}
		i++;
	}

}


void infixToPostfix ( char str[],char* postfix ) {
/*
a.����ֱ�����
b.�����
���һ������������ֱ����ջ�����������Ž�ջ��������֮����ջ�������ȫ����ջ�����ͬʱ�����ų�ջ���ǲ������
������������˺źͳ���ֱ����ջ��ֱ���������ȼ��������͵�����������ε�ջ��
������������Ӻźͼ��ţ������ʱջ�գ���ֱ����ջ�����򣬽�ջ�����ȼ��ߵ���������ε�ջ��ע�⣺�Ӻźͼ�����
		��ͬһ�����ȼ�������Ҳ���ε�ջ��ֱ��ջ�ջ�������������Ϊֹ��ֹͣ��ջ������Ϊ������Ҫƥ��������ʱ�ŵ�������
����ģ���ȡ��󣬽�ջ��ʣ�������������ε�ջ���
*/

	int j = 0;
	int i = 0;
	char e;
	stack<char> s;
	//while ( str[i] != '\0' )
	for ( ;;) {
		while ( isdigit ( str[i] ) || str[i] == '.' ) {/*���������ַ���ֱ�������ֱ����һλ���������ַ���ӡ�ո�����ѭ�� */
			postfix[j++] = str[i++];
			if ( !isdigit ( str[i] ) && str[i]!='.' ) {
				postfix[j++] = ' ';
			}
		}

		/*�����Ӻźͼ��ţ������ʱջ�գ���ֱ����ջ
		���򣬽�ջ�����ȼ��ߵ���������ε�ջ��ע�⣺�Ӻźͼ�������ͬһ�����ȼ�������Ҳ���ε�ջ��ֱ��ջ�ջ�������������Ϊֹ*/
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
			/*���������Ž�ջ��������֮����ջ�������ȫ����ջ�����ͬʱ�����ų�ջ���ǲ����*/
			e = s.top ();
			s.pop ();
			while ( e != '(' ) {
				postfix[j++] = e;
				postfix[j++] = ' ';
				e = s.top ();
				s.pop ();
			}
		} else if ( str[i] == '*' || str[i] == '/' || str[i] == '(' ) {
			/*�ˡ����������Ŷ������ȼ��ߵģ�ֱ��ѹջ*/
			s.push ( str[i] );
		} else if ( str[i] == '\0' ) {
			//��ȡ��󣬽�ջ��ʣ�������������ε�ջ���
				/*����ջ��ʣ�����������ε�ջ��ӡ*/
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
			printf ( "\n����Ƿ��ַ���\n" );
			return;
		}
		i++;
	}

}