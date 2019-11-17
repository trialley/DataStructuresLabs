/*****************************************************************************
*  main.cpp                                                                  *
*  Copyright (C) 2019.10.30 TriAlley  lg139@139.com                          *
*  @brief    ������еĲ���                                                   *
*  @license  GNU General Public License (GPL)                                *
*****************************************************************************/
#include<iostream>
#include"queue.h"
using namespace std;
#define DEBUG
#ifdef DEBUG
#define dprintf printf
#else
#define dprintf /\
/ printf
#endif

int main () {
	try {
		queue<int> q;
		int n;
		cin >> n;

		for ( int i = 1; i <= n; i++ ) {
			q.push ( i );
		}
		while ( q.size () >= 2 ) {
		dprintf ( "�ӵ���");
			dprintf ( "%d\n", q.front () );
			q.pop ();
			if (q.size () == 1) {
				break;
			}
			dprintf ("�ƶ���%d\n", q.front ());

			q.push ( q.front () );
			q.pop ();

		}
		dprintf ( "ʣ�ࣺ\n" );
		//while ( !q.isempty () ) {
			cout << q.front () << endl;
			//q.pop ();
		//}
	} catch ( queue<int>::queue_err e ) {
		cout << endl << e << endl;
	}
}