#include"queue.h"
#include<iostream>

using namespace std;

int main () {
	queue<int> q(50);
	for ( int i = 0; i < 100; i++ ) {
		q.push ( i );
	}
	cout << q.size () << endl<<endl;
	for ( int i = 0; i < 50; i++ ) {
	//	cout << q.front () << endl;
		q.pop ();
	}
	cout <<"size:"<< q.size () << endl << endl;

	for ( int i = 0; i < 100; i++ ) {
		q.push ( i );
	}
	cout << "size:" << q.size () << endl << endl;

	for ( int i = 0; i < 150; i++ ) {
	//	cout << q.front () << endl;
		q.pop ();
	}
	q.pop ();

	cout << "size:" << q.size () << endl << endl;

	//for ( int i = 0; i < 50; i++ ) {
	//	cout << q.front ();
	//	q.pop ();
	//}
}