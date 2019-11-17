#include<iostream>
#include"btree.h"
using namespace std;
int main () {
	int  pre[100];
	int  in[100];

	btree<int> b;

	int length = 0;
	cin >> length;
	for (int i = 0; i < length; i++) {
		cin >> pre[i];
	}
	for (int i = 0; i < length; i++) {
		cin >> in[i];
	}


	b.buildFromPreIn (pre, in, length);
	b.preOut (cout);
	return 0;
}
