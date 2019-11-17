#include<iostream>
#include"hashtable.h"
using namespace std;
#define LGRAND(min,max) ((rand()%(max-min+(int)1))+(int)min )


int main () {
	myhashTable<int, int> table (961);

	/*随机获取50个不重复的数字*/
	for (int i = 0; i < 500;) {
		mypair<int, int> temp (i, LGRAND (0, 50000));
		if (table.find (temp.data) == nullptr) {
			table.insert (temp);
			i++;
		}
	}
	cout << "find:\n";
	for (int i = 0; i < 500; i++) {
		cout << "find:" << i << " " << *table.find (i) << endl;
	}
		cout << "\nshow all:\n";
	cout << table << endl << endl;

	cout << "delete:\n";
	for (int i = 0; i < 500; i++) {
		table.erase (i);
		cout << "delete:" << i << "\n";

	}
	cout << "delete done\n";
	cout << "show all:\n";

	cout << table << endl << endl;
	return 0;
}