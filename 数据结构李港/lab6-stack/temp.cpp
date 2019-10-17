////表达式计算
////表达式转后缀表达式（逆波兰式）
//
//#include <cstdio>
//#include <cstring>
//#include <cctype>
//#include <algorithm>
//
////char stack-----定义堆栈，用于转换表达式 
//char stack[25]; //定义一个栈来储存各种符号 
//int top = -1; //栈为空时栈顶标记为-1 
//
//void push(char item)
//{
//	stack[++top] = item; //栈顶元素进栈（维持栈的性质） 
//}
//
//char pop()
//{
//	return stack[top--]; //栈顶元素出栈（维持栈的性质） 
//}
//
////returns precedence of operators-----运算符的优先级处理 
//int precedence(char symbol)
//{
//	switch (symbol)
//	{
//	case '+':
//	case '-':
//		return 2;
//		break;
//	case '*':
//	case '/':
//		return 3;
//		break;
//	case '^':
//		return 4;
//		break;
//	case '(':
//	case ')':
//	case '#':
//		return 1;
//		break;
//	}
//}
//
////check whether the symbol is operator?-----检测符号是否为运算符 
//int isOperator(char symbol)
//{
//
//	switch (symbol) //各种符号标记为0，数字标记为1。
//	{
//	case '+':
//	case '-':
//	case '*':
//	case '/':
//	case '^':
//	case '(':
//	case ')':
//		return 1;
//		break;
//	default:
//		return 0;
//	}
//}
//
////converts infix expression to postfix-----中缀转后缀 
//void convert(char infix[], char postfix[])
//{
//	int i, symbol, j = 0;
//	stack[++top] = '#'; //#在栈底，表示这栈里没有东西 
//
//	for (i = 0; i < strlen(infix); i++) //将整个式子全部扫一遍 
//	{
//		symbol = infix[i];
//		if (isOperator(symbol) == 0)
//		{
//			postfix[j++] = symbol;  //数字直接进入后缀表达式 ;
//		}
//		else
//		{
//			if (symbol == '(') //前括号直接入栈 
//			{
//				push(symbol);
//			}
//			else
//			{
//				if (symbol == ')') //发现后括号后开始出栈 
//				{
//					while (stack[top] != '(')  //出栈直至前括号 
//					{
//						postfix[j] = pop();
//						j++;
//					}
//					pop(); //前括号前的第一个符号也要出栈 
//				}
//				else//如果没有检测到，并且不是数字时 
//				{
//					if (precedence(symbol) > precedence(stack[top])) //如果符合计算优先级，就直接将运算符进栈 
//					{
//						push(symbol);
//					}
//					else//如果不符合运算优先级，就出栈知道符合为止，再进栈 
//					{
//						while (precedence(symbol) <= precedence(stack[top]))
//						{
//							postfix[j] = pop();
//							j++;
//						}
//						push(symbol);
//					}
//				}
//			}
//		}
//	}
//	while (stack[top] != '#')//如果栈中没有括号了，就将剩余的运算符全部出栈 
//	{
//		postfix[j] = pop();
//		j++;
//	}
//	postfix[j] = '\0'; //null terminate string.-----在字符串最后用一个“\0”来终止 
//}
//
////int stack-----定义堆栈，用来计算后缀表达式（逆波兰式） 
//int stack_int[25]; //定义栈来直接储存数字 
//int top_int = -1; //栈顶空用-1表示 
//
//void push_int(int item) //进栈 
//{
//	stack_int[++top_int] = item;
//}
//
//char pop_int() //出栈 
//{
//	return stack_int[top_int--];
//}
//
////evaluates postfix expression-----计算后缀表达式 
//int evaluate(char* postfix)
//{
//	char ch;
//	int i = 0, operand1, operand2;
//
//	while ((ch = postfix[i++]) != '\0')
//	{
//		if (isdigit(ch))
//		{
//			push_int(ch - '0'); //Push the operand-----将字符转换成数字，再入栈 
//		}
//		else //Operator,pop two operands-----取出两个数来计算 
//		{
//			operand2 = pop_int();
//			operand1 = pop_int();
//			switch (ch) //直接计算 
//			{
//			case '+':
//				push_int(operand1 + operand2);
//				break;
//			case '-':
//				push_int(operand1 - operand2);
//				break;
//			case '*':
//				push_int(operand1 * operand2);
//				break;
//			case '/':
//				push_int(operand1 / operand2);
//				break;
//			case '^':
//				push_int(operand1 ^ operand2);
//				break;
//			}
//		}
//	}
//	return stack_int[top_int]; //最后栈中只剩下一个数，即为计算结果 
//}
//
//int main()
//{
//	char infix[25] = "(-1)", postfix[25];
//	convert(infix, postfix);
//
//	printf("Infix expression is: %s\n", infix);
//	printf("Postfix expression is: %s\n", postfix);
//	printf("Evaluated expression is: %d\n", evaluate(postfix));
//
//	return 0;
//}