#include<iostream>
#include"hashchain.h"
using namespace std;
#define LGRAND(min,max) ((rand()%(max-min+(int)1))+(int)min )


int main () {
	myhashChains<int,int> chain(961);

	/*随机获取50个不重复的数字*/
	for (int i = 0; i < 500;) {
		mypair<int, int> temp (i, LGRAND (0, 50000));
		if (chain.find (temp.data) == nullptr) {
			chain.insert (temp);
			i++;
		}
	}
	cout << "find:\n";
	for (int i = 0; i < 500;i++) {
		cout <<"find:"<<i<<" "<< *chain.find(i) << endl;
	}
	cout << "\nshow all:\n";
	cout << chain << endl << endl;

	cout << "delete:\n";
	for (int i = 0; i < 500; i++) {
		chain.erase (i) ;
		cout << "delete:"<<i<<"\n";

	}
	cout << "delete done\n";
	cout << "show all:\n";

	cout << chain << endl << endl;
	return 0;
}