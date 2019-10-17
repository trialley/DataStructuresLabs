#include"chain.h"
#include<iostream>
using namespace std;
using namespace TA;
#define LGRAND(min,max) ((rand()%(max-min+(int)1))+(int)min )

chain<int>* merge( chain<int>& a,  chain<int>& b) {
	/*����������*/
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

	//���index����listsize��˵���������ƶ���ϣ�����δ������ϣ���������ʣ��Ԫ�ء�
	//a��b���Ա��ֻʣһ��û�и�����ϣ���˴˴������ж�ֻ��һ����ִ��
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
	cout << "������:\n";
	for (int i = 0; i < num; i++) {
		c.insert(0, (int)LGRAND(1, 1000));
	}
	cout << c << endl
		<<"isempty: "<<c.empty()<<endl
		<<"size: "<<c.listSize() <<endl;


	cout << "\n���Ը�:\n";
	for (int i = 0; i < 10; i++) {
		c[i] = c[i] * 2;
	}
	cout << c << endl
		<< "isempty: " << c.empty() << endl
		<< "size: " << c.listSize() << endl;

	cout << "\n���Բ�:\n";
	cout << "data 78" << " in: " << c.find(78) << endl;
	cout << "data 572" << " in: " << c.find(572) << endl;
	cout<<"data 573"<<" in: "<<c.find(578)<<endl;

	cout << "\n���� iterator �������:\n";
	c.reverse ();

	cout << "\n����ɾ:\n";
	for (int i = 0; i < 10; i++) {
		c.del(0);
	}
	cout << c << endl
		<< "isempty: " << c.empty() << endl
		<< "size: " << c.listSize() << endl;


	cout << "\n����merge:\n";
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