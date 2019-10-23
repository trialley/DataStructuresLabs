#include<iostream>
#include<cstring>
#include<algorithm> 
#include<stack>
using namespace std;

stack<char> op;		//运算符栈 
stack<char> temp;		//中间结果栈 

int f ( const char str ) {
	int yxj;		//优先级 
	switch ( str ) {
	case '*':yxj = 5; break;
	case '/':yxj = 5; break;
	case '+':yxj = 4; break;
	case '-':yxj = 4; break;
	}
	return yxj;

}
int main () {
	char c[100] = "1/3*2/9";
	//char c[100]="1+((2+3)*4)-5";
	int lenc = strlen ( c );
	//读取字符串 
	for ( int i = 0; i < lenc; i++ ) {
		if ( c[i] >= '0' && c[i] <= '9' ) {		//如果是数字，直接压入temp 
			temp.push ( c[i] );
		} else if ( c[i] == '+' || c[i] == '-' || c[i] == '*' || c[i] == '/' ) {	//如果是运算符 
			while ( true ) {
				if ( op.empty () || op.top () == '(' ) {		//op为空 ，或者栈顶为( 
					op.push ( c[i] );
					break;
				} else if ( f ( c[i] ) > f ( op.top () ) ) {		//当前运算符优先级大于op栈顶运算符优先级 
					op.push ( c[i] );
					break;
				} else {								//小于等于 
					char cc = op.top ();
					op.pop ();
					temp.push ( cc );
				}
			}
		} else {
			if ( c[i] == '(' ) {			//直接读入 
				op.push ( c[i] );
			} else {
				while ( op.top () != '(' ) {
					char ccc = op.top ();
					op.pop ();
					temp.push ( ccc );
				}
				op.pop ();
			}
		}
	}
	while ( !op.empty () ) {
		char cccc = op.top ();
		temp.push ( cccc );
		op.pop ();
	}

	//while(!temp.empty()){	//结果是逆序的 
	//	cout<<temp.top();
	//	temp.pop();
	//}
	while ( !temp.empty () ) {
		char c = temp.top ();
		op.push ( c );
		temp.pop ();
	}
	while ( !op.empty () ) {
		cout << op.top ();
		op.pop ();
	}

	return 0;
}