#include"chain.h"
#include<iostream>
using namespace std;
using namespace TA;
#define LGRAND(min,max) ((rand()%(max-min+(int)1))+(int)min )

chain<int>* merge( chain<int>& a,  chain<int>& b) {
	/*建立新链表*/
	chain<int>* temp = new chain<int>;
	chain<int>::chainiterator ai = a.begin();
	chain<int>::chainiterator bi = b.begin();
	while ((ai!=a.end()) && (bi != a.end())) {
		if (*ai>= *bi) {
			temp->insert(temp->listSize(),*ai);
			ai++;
		} else {
			temp->insert(temp->listSize(), *bi);
			bi++;
		}
	}

	//如果index等于listsize，说明该数组移动完毕；否则未复制完毕，继续复制剩余元素。
	//a，b线性表必只剩一个没有复制完毕，因此此处两个判断只有一个能执行
	if (ai != a.end()) {
		while (ai != a.end()) {
			temp->insert(temp->listSize(), *ai);
			ai++;
		}
	}
	if (bi != a.end()) {
		while (bi != a.end()) {
			temp->insert(temp->listSize(), *bi);
			bi++;

		}
	}

	return temp;
}

int main() {
	srand(0);

	int num = 10;

	chain<int> c;
	cout << "测试增:\n";
	for (int i = 0; i < num; i++) {
		c.insert(0, (int)LGRAND(1, 1000));
	}
	cout << c << endl
		<<"isempty: "<<c.empty()<<endl
		<<"size: "<<c.listSize() <<endl;


	cout << "\n测试改:\n";
	for (int i = 0; i < 10; i++) {
		c[i] = c[i] * 2;
	}
	cout << c << endl
		<< "isempty: " << c.empty() << endl
		<< "size: " << c.listSize() << endl;

	cout << "\n测试查:\n";
	cout << "data 78" << " in: " << c.find(78) << endl;
	cout << "data 572" << " in: " << c.find(572) << endl;
	cout<<"data 573"<<" in: "<<c.find(578)<<endl;

	cout << "\n测试 iterator 反向输出:\n";
	c.reverse ();

	cout << "\n测试删:\n";
	for (int i = 0; i < 10; i++) {
		c.del(0);
	}
	cout << c << endl
		<< "isempty: " << c.empty() << endl
		<< "size: " << c.listSize() << endl;


	cout << "\n测试merge:\n";
	chain<int> a;
	for (int i = 0; i < num; i++) {
		a.insert(i, i);
	}
	cout << a << endl;
		chain<int> temp;
	temp.merge ( a, a );
	cout << temp << endl
		<< "isempty: " << temp.empty() << endl
		<< "size: " << temp.listSize() << endl;
}