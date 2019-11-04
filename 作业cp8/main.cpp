#include"twoStacks.h"
#include<iostream>

using namespace std;


int main () {
	twoStacks<int> s;
	for ( int i = 0; i < 100;i++ ) {
		s.push1 ( i );
		s.push2 ( i );
	}
	for ( int i = 0; i < 1001; i++ ) {
		cout << s.top1 ()<<"  ";
		cout<<s.top2 ();
		cout << endl;
		s.pop1 ();
		s.pop2 ();
	}
}