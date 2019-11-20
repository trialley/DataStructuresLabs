#include "chain.h"
#include "chain.cpp"

//template<class T>
//extern class chain::iterator;

bool getEnd = false;

//template<class T>
//void output(chain<T> *c, chain<T>::iterator it)
//{
//	if (it==c->end()) {
//		getEnd = true;
//		return;
//	}
//	if (getEnd) {
//		cout << *it << " ";
//		return;
//	}
//	//it++;
//	output(c,it++);
//}

template<class T>
void merge(chain<T> &a, chain<T> &b, chain<T> &c)
{
	c.clear();

	iterator<T> p(nullptr);
	auto ita = a.begin();
	auto itb = b.begin();
	auto itc = c.begin();
	if (*ita <= *itb) {
		p = ita;
		ita++;
	}
	else {
		p = itb;
		itb++;
	}
	itc = p;
	p++;
	while (ita != a.end() && itb != b.end()) {
		if (*ita <= *itb) {
			p = ita;
			ita++;
		}
		else {
			p = itb;
			itb++;
		}
		p++;
	}
	if (ita != a.end())
		p = ita;
	if (itb != b.end())
		p = itb;
}

int main()
{
	//chain<int> *c = new chain<int>();
	//chain<int> c;
	//cin >> &c;
	//cout << "Now chain is: " << c << endl;
	////c->erase(1);
	////cout << "Now chain is: " << c << endl;
	////c->insert(0, 5);
	////cout << "Now chain is: " << c << endl;
	//c.push_back(10);
	//c.reverse();
	//cout << "Now chain is: " << &c << endl;
	//int ele = 5;
	//int index = c->indexOf(ele);
	//cout << "index:" << index << endl;

	////µü´úÆ÷²âÊÔ
	//cout << "Iterator test:" << endl;
	//auto it = c->begin();
	//cout << "->(): " << it.operator->() << endl;
	//for (;it != c->end();it++)
	//	cout << *it << " ";
	//delete c;

	cout << "merge:" << endl;
	chain<int> a, b, d;
	int aa[] = { 2, 3, 5, 6 };
	int bb[] = { 1,3,4,7,8,9 };
	a.initFromArray(aa, 4);
	b.initFromArray(bb, 6);
	cout << "a: " << &a << endl;
	cout << "b: " << &b << endl;
	d.mergeWithIterator(a, b);
	//merge(a, b, d);
	cout << "d: " << &d << endl;


	system("pause");
	return 0;
}