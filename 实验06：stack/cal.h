#include<stdio.h>
#include<stdlib.h>
#include<ctype.h> 
#include<assert.h>
#include<iostream>
#include"stack.h"
using namespace std;

/*
*��׺ת��׺����׺�ټ���
*��Щ��������ñȽϹ�������������д��һ���ࡣ
*ע����ʵ�����ٽ��й�����͡�

infixToPostfix����׺���ʽת��׺���ʽ
	in:
		char* infix		�������׺���ʽ��������С���������пո��� '\0' ��β��
		char* postfix	����ĺ�׺���ʽ��ÿ��Ԫ���Կո�ָ����� '\0' ��β

calPostfix����׺���ʽ����
	in��
		char* postfix	����ĺ�׺���ʽ��ÿ��Ԫ���Կո�ָ����� '\0' ��β��
	out:
		double			����Ľ����

isNumber		����һ���ַ��������ǲ���0-9�������ַ�
isOperator		����һ���ַ��������ǲ��ǲ�����
priority		����һ���ַ������ظò����������ȼ�
enum cal_err	���ܳ��ֵĴ���
*/
typedef enum { wrong_char, no_such_operator }cal_err;
inline bool isNumber ( char c ) {
	if ( c >= '0' && c <= '9' ) {
		return true;
	} else {
		return false;
	}
}
inline bool isOperator ( char c ) {
	switch ( c ) {
	case '*':
	case '/':
	case '+':
	case '-':
		return true;
	default:
		return false;
	}
}

int priority ( char c ) {
	switch ( c ) {
	case '*':return 5; break;
	case '/':return 5; break;
	case '+':return 4; break;
	case '-':return 4; break;
	default:throw no_such_operator;
	}
}

/*�����׺���ʽ*/
double calPostfix ( char* postfix ) {
	stack<double> result;

	/*
	�����׺���ʽ����׺ת��׺��
	����׼��һ����׺���ʽ��һ������ջ

	���ں�׺���ʽ������ÿ��Ԫ��
	��������֣���ѹ������ջ
	����ǲ��������򵯳�����ջ�е��������Ե�һ�ε�����Ϊ��ֵ���ڶ��ε�����Ϊ��ֵ��������Ӧ���㲢������ջ����Ϊ/��-������˳����أ�
	ֱ����׺���ʽ����������ջ������
	*/
	for ( int i = 0;;) {
		if ( isNumber ( postfix[i] ) || postfix[i] == '.' ) {

			/*���ｫ�����ַ���ת��Ϊ����������ʱ����Գ���ɵ����ĺ���*/
			double temp = 0;
			bool is_int = true;
			while ( isNumber ( postfix[i] ) || postfix[i] == '.' ) {
				if ( postfix[i] == '.' ) {
					is_int = false;
				} else {
					if ( is_int ) {
						temp = ( postfix[i] - '0' ) + temp * 10;
					} else {
						temp = ( postfix[i] - '0' ) * 0.1 + temp;
					}
				}
				i++;
			}
			i--;
			result.push ( temp );
		} else if ( postfix[i] == ' ' ) {
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

			result.push ( b / a );
		} else if ( postfix[i] == '+' ) {
			double a = result.top ();
			result.pop ();
			double b = result.top ();
			result.pop ();

			result.push ( a + b );
		} else if ( postfix[i] == '-' ) {
			double a = result.top ();
			result.pop ();
			double b = result.top ();
			result.pop ();

			result.push ( b - a );
		} else if ( postfix[i] == '\0' ) {
			return result.top ();
		} else {
			throw wrong_char;
			return 0;
		}
		i++;
	}

}

/*��׺ת��׺��ע����ʵ*/
void infixToPostfix ( char* infix, char* postfix ) {
	int j = 0;//Ŀ���±�
	int i = 0;//Դ�±�
	stack<char> op_stack;

	/*
	��׺ת��׺��Ҫһ����׺���ʽ��һ����ź�׺���ʽ�Ļ�������һ������ջ

	������׺���ʽ������ÿ��Ԫ��
	1.��������֣�ֱ�ӽ����׺���ʽ
	2.����ǲ�����
		->ѭ���жϿ�ʼ
		1.��� ����ջΪ�� �� ջ��Ϊ�����ţ���ֱ����ջ
		2.��� ��ǰ��������ջ���������ȼ��ߣ�Ҳֱ����ջ
		3.��� ��ǰ��������ջ���������ȼ��ͻ���ȣ���ջ��Ԫ�ص�������׺���ʽ�������½��д��ж�
		��ǿ�������½��д˵��жϡ���Ϊ���Ż�����ṹ������������ֻ��Ҫдһ��whileѭ����
		<-ѭ���жϽ���
	3.�������������
		1.����������ţ�����ջ
		2.����������ţ���ջ��������׺���ʽ��ֱ�������ţ�������������
	*/

	/*ÿ��ѭ����i��ָ��ǰѭ����Ҫ���жϵ�λ��*/
	for ( ;;) {
		if ( isNumber ( infix[i] ) || infix[i] == '.' ) {
			/*�����ַ�ֱ���������׺���ʽ��ֱ����һλ���������ַ�����ո񵽺�׺���ʽ������ѭ�� */
			while ( isNumber ( infix[i] ) || infix[i] == '.' ) {
				postfix[j++] = infix[i++];
			}
			postfix[j++] = ' ';
			i--;
		} else if ( isOperator ( infix[i] ) ) {
			while ( true ) {
				if ( op_stack.empty () || op_stack.top () == '(' ) {
					op_stack.push ( infix[i] );
					break;
				} else if ( priority ( infix[i] ) > priority ( op_stack.top () ) ) {
					op_stack.push ( infix[i] );
					break;
				} else {
					postfix[j++] = op_stack.top ();
					postfix[j++] = ' ';
					op_stack.pop ();
				}
			}
		} else if ( infix[i] == ')' ) {
			while ( op_stack.top () != '(' ) {
				postfix[j++] = op_stack.top ();
				postfix[j++] = ' ';
				op_stack.pop ();
			}
			op_stack.pop ();
		} else if ( infix[i] == '(' ) {
			op_stack.push ( infix[i] );
		} else if ( infix[i] == '\0' ) {
			break;
		} else {
			throw wrong_char;
			return;
		}

		i++;//ѭ��ĩ��i���ڱ���ѭ���жϴ�����Ҫ����ָ���´�ѭ���жϴ���
	}
	while ( !op_stack.empty () ) {
		postfix[j++] = op_stack.top ();
		postfix[j++] = ' ';
		op_stack.pop ();
	}
	postfix[j++] = '\0';
	return;

}