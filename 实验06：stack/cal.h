/*****************************************************************************
*  cal.h                                                                     *
*  Copyright (C) 2019.11.24 TriAlley  lg139@139.com                          *
*  @brief    �Ա��ʽ�������躯���ķ�װ                                        *
*  @license  GNU General Public License (GPL)                                *
*****************************************************************************/
#include"stack.h"
using namespace std;

/*
*��׺ת��׺����׺�ټ���
*��Щ��������ñȽϹ��������ϳ�һ�������࣬�������κ�״̬��
*ע����ʵ�����ٽ��й�����͡�
*/

/*template<class T>
class calExpression

public:
	typedef enum { wrong_char, no_such_operator }cal_err;			//�����Ĵ�����
private:
	inline bool isNumber ( char c ) ;								//�ж��ַ��Ƿ�������
	inline bool isOperator ( char c );								//�ж��ַ��Ƿ��ǲ�����
	inline T calOperator ( const char c, const T& a, const T& b );
	inline int priority ( char c );									//���ز����������ȼ������ȼ�Խ����ֵԽ��
public:
	T calPostfix ( char* postfix );									//�����׺���ʽ���ڲ�ע����ʵ
	void infixToPostfix ( char* infix, char* postfix );				//��׺ת��׺���ڲ�ע����ʵ	
*/
template<class T>
class calExpression {
public:
	typedef enum { wrong_char, no_such_operator }cal_err;
private:
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
	/*��һ�ε���a��Ϊ��ֵ���ڶ��ε���b��Ϊ��ֵ eg b/a*/
	inline T calOperator (const char c,const T& a, const T& b ) {
		switch ( c ) {
		case '*':
			return b * a;
		case '/':
			return b / a;
		case '+':
			return b + a;
		case '-':
			return b - a;
		default:
			return a;
		}
	}
	inline int priority ( char c ) {
		switch ( c ) {
		case '*':return 5; break;
		case '/':return 5; break;
		case '+':return 4; break;
		case '-':return 4; break;
		default:throw no_such_operator;
		}
	}
public:
	/*�����׺���ʽ*/
	T calPostfix ( char* postfix ) {
		stack<T> result;
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
			} else if ( isOperator ( postfix[i] ) ) {
				double a = result.top ();
				result.pop ();
				double b = result.top ();
				result.pop ();

				result.push ( calOperator ( postfix[i], a, b ) );
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
};