#include<iostream>
#include"queue.h"

using namespace std;


int main() {
	try{
		queue<int> q;
		int n;
		cin >> n;

		for (int i = 1; i <= n; i++) {
			q.push(i);
		}
		cout << "ÈÓµô£º" << endl;
		while (q.getlength()>=2) {
			cout<<q.get()<<endl;
			q.push(q.get());
		}
		cout << "Ê£Óà£º" << endl;
		while (!q.isempty()) {
			cout << q.get() << endl;
		}
	}
	catch(queue_err e){
		cout << endl << e << endl;
	}






}