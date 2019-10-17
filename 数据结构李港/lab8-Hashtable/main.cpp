#include"hashtable.h"
#include<iostream>
using namespace std;
unsigned int lghash(const char* key, int length) {
	register unsigned int nr = 1, nr2 = 4;
	while (length--) {
		nr ^= (((nr & 63) + nr2) * ((unsigned int)(unsigned char)* key++)) + (nr << 8);
		nr2 += 3;
	}
	return((unsigned int)nr);
}
int main() {

	hashtable<int,int> h;
	h.insert(hashtable<int,int>::makepair(1, 1));
	int i = 1;
	cout << h.find(i);






}