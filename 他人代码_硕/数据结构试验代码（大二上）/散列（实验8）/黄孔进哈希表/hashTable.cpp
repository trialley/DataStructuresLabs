#include <iostream>
#include "hashTable.h"
using namespace std;

int main(){
   hashTable<int, int> z(11);
   pair<int, int> p;
   p.first = 2; p.second = 4;
   z.insert(p);
   p.first = 10; p.second = 20;
   z.insert(p);
   p.first = 13; p.second = 26;
   z.insert(p);
   p.first = 32; p.second = 64;
   z.insert(p);
   p.first = 3; p.second = 6;
   z.insert(p);
   p.first = 12; p.second = 24;
   z.insert(p);
   p.first = 8; p.second = 16;
   z.insert(p);
   
   cout << z << endl;
   cout << "first is 2 and its second is " << z.find(2)->second << endl;
   return 0; 
}
