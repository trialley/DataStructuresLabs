/*****************************************************************************
*  cal.h                                                                     *
*  Copyright (C) 2019.11.24 TriAlley  lg139@139.com                          *
*  @brief    对表达式计算所需函数的封装                                        *
*  @license  GNU General Public License (GPL)                                *
*****************************************************************************/
#include"stack.h"
using namespace std;

/*
*中缀转后缀，后缀再计算
*这些函数整理得比较规整，集合成一个工具类，不保存任何状态。
*注释详实，不再进行过多解释。
*/

/*template<class T>
class calExpression

public:
	typedef enum { wrong_char, no_such_operator }cal_err;			//常见的错误项
private:
	inline bool isNumber ( char c ) ;								//判断字符是否是数字
	inline bool isOperator ( char c );								//判断字符是否是操作符
	inline T calOperator ( const char c, const T& a, const T& b );
	inline int priority ( char c );									//返回操作符的优先级，优先级越高数值越大
public:
	T calPostfix ( char* postfix );									//计算后缀表达式，内部注释详实
	void infixToPostfix ( char* infix, char* postfix );				//中缀转后缀，内部注释详实	
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
	/*第一次弹出a作为右值，第二次弹出b作为左值 eg b/a*/
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
	/*计算后缀表达式*/
	T calPostfix ( char* postfix ) {
		stack<T> result;
		/*
		计算后缀表达式比中缀转后缀简单
		首先准备一个后缀表达式与一个数字栈

		对于后缀表达式从左到右每个元素
		如果是数字，则压入数字栈
		如果是操作符，则弹出数字栈中的两个，以第一次弹出作为右值，第二次弹出作为左值，进行相应计算并入数字栈（因为/与-与数字顺序相关）
		直到后缀表达式结束，返回栈顶数字
		*/
		for ( int i = 0;;) {
			if ( isNumber ( postfix[i] ) || postfix[i] == '.' ) {

				/*这里将浮点字符串转化为浮点数，有时间可以抽离成单独的函数*/
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
	/*中缀转后缀，注释详实*/
	void infixToPostfix ( char* infix, char* postfix ) {
		int j = 0;//目的下标
		int i = 0;//源下标
		stack<char> op_stack;

		/*
		中缀转后缀需要一个中缀表达式，一个存放后缀表达式的缓冲区，一个符号栈

		对于中缀表达式从左到右每个元素
		1.如果是数字，直接进入后缀表达式
		2.如果是操作符
			->循环判断开始
			1.如果 符号栈为空 或 栈顶为左括号，则直接入栈
			2.如果 当前操作符比栈顶符号优先级高，也直接入栈
			3.如果 当前操作符比栈顶符号优先级低或相等，则栈顶元素弹出到后缀表达式，并重新进行此判断
			（强调“重新进行此的判断”是为了优化程序结构，这样表述就只需要写一个while循环）
			<-循环判断结束
		3.如果是左右括号
			1.如果是左括号，则入栈
			2.如果是右括号，则栈弹出到后缀表达式，直到左括号，并抛弃左括号
		*/

		/*每次循环，i均指向当前循环需要被判断的位置*/
		for ( ;;) {
			if ( isNumber ( infix[i] ) || infix[i] == '.' ) {
				/*数字字符直接输出到后缀表达式，直到下一位不是数字字符输出空格到后缀表达式并跳出循环 */
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

			i++;//循环末，i处于本次循环判断处，需要让其指向下次循环判断处。
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