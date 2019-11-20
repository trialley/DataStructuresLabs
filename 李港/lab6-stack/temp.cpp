////���ʽ����
////���ʽת��׺���ʽ���沨��ʽ��
//
//#include <cstdio>
//#include <cstring>
//#include <cctype>
//#include <algorithm>
//
////char stack-----�����ջ������ת�����ʽ 
//char stack[25]; //����һ��ջ��������ַ��� 
//int top = -1; //ջΪ��ʱջ�����Ϊ-1 
//
//void push(char item)
//{
//	stack[++top] = item; //ջ��Ԫ�ؽ�ջ��ά��ջ�����ʣ� 
//}
//
//char pop()
//{
//	return stack[top--]; //ջ��Ԫ�س�ջ��ά��ջ�����ʣ� 
//}
//
////returns precedence of operators-----����������ȼ����� 
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
////check whether the symbol is operator?-----�������Ƿ�Ϊ����� 
//int isOperator(char symbol)
//{
//
//	switch (symbol) //���ַ��ű��Ϊ0�����ֱ��Ϊ1��
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
////converts infix expression to postfix-----��׺ת��׺ 
//void convert(char infix[], char postfix[])
//{
//	int i, symbol, j = 0;
//	stack[++top] = '#'; //#��ջ�ף���ʾ��ջ��û�ж��� 
//
//	for (i = 0; i < strlen(infix); i++) //������ʽ��ȫ��ɨһ�� 
//	{
//		symbol = infix[i];
//		if (isOperator(symbol) == 0)
//		{
//			postfix[j++] = symbol;  //����ֱ�ӽ����׺���ʽ ;
//		}
//		else
//		{
//			if (symbol == '(') //ǰ����ֱ����ջ 
//			{
//				push(symbol);
//			}
//			else
//			{
//				if (symbol == ')') //���ֺ����ź�ʼ��ջ 
//				{
//					while (stack[top] != '(')  //��ջֱ��ǰ���� 
//					{
//						postfix[j] = pop();
//						j++;
//					}
//					pop(); //ǰ����ǰ�ĵ�һ������ҲҪ��ջ 
//				}
//				else//���û�м�⵽�����Ҳ�������ʱ 
//				{
//					if (precedence(symbol) > precedence(stack[top])) //������ϼ������ȼ�����ֱ�ӽ��������ջ 
//					{
//						push(symbol);
//					}
//					else//����������������ȼ����ͳ�ջ֪������Ϊֹ���ٽ�ջ 
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
//	while (stack[top] != '#')//���ջ��û�������ˣ��ͽ�ʣ��������ȫ����ջ 
//	{
//		postfix[j] = pop();
//		j++;
//	}
//	postfix[j] = '\0'; //null terminate string.-----���ַ��������һ����\0������ֹ 
//}
//
////int stack-----�����ջ�����������׺���ʽ���沨��ʽ�� 
//int stack_int[25]; //����ջ��ֱ�Ӵ������� 
//int top_int = -1; //ջ������-1��ʾ 
//
//void push_int(int item) //��ջ 
//{
//	stack_int[++top_int] = item;
//}
//
//char pop_int() //��ջ 
//{
//	return stack_int[top_int--];
//}
//
////evaluates postfix expression-----�����׺���ʽ 
//int evaluate(char* postfix)
//{
//	char ch;
//	int i = 0, operand1, operand2;
//
//	while ((ch = postfix[i++]) != '\0')
//	{
//		if (isdigit(ch))
//		{
//			push_int(ch - '0'); //Push the operand-----���ַ�ת�������֣�����ջ 
//		}
//		else //Operator,pop two operands-----ȡ�������������� 
//		{
//			operand2 = pop_int();
//			operand1 = pop_int();
//			switch (ch) //ֱ�Ӽ��� 
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
//	return stack_int[top_int]; //���ջ��ֻʣ��һ��������Ϊ������ 
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