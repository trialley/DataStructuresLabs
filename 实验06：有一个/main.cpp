#include<iostream>
#include<cstring>
#include<algorithm> 
#include<stack>
using namespace std;

stack<char> op;		//�����ջ 
stack<char> temp;		//�м���ջ 

int f ( const char str ) {
	int yxj;		//���ȼ� 
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
	//��ȡ�ַ��� 
	for ( int i = 0; i < lenc; i++ ) {
		if ( c[i] >= '0' && c[i] <= '9' ) {		//��������֣�ֱ��ѹ��temp 
			temp.push ( c[i] );
		} else if ( c[i] == '+' || c[i] == '-' || c[i] == '*' || c[i] == '/' ) {	//���������� 
			while ( true ) {
				if ( op.empty () || op.top () == '(' ) {		//opΪ�� ������ջ��Ϊ( 
					op.push ( c[i] );
					break;
				} else if ( f ( c[i] ) > f ( op.top () ) ) {		//��ǰ��������ȼ�����opջ����������ȼ� 
					op.push ( c[i] );
					break;
				} else {								//С�ڵ��� 
					char cc = op.top ();
					op.pop ();
					temp.push ( cc );
				}
			}
		} else {
			if ( c[i] == '(' ) {			//ֱ�Ӷ��� 
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

	//while(!temp.empty()){	//���������� 
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