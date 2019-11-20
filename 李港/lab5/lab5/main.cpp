#include<iostream>
using namespace std;
#include"SparseMatrix.h"

class hhh{
public:
	~hhh(){
		cout << "hhh" << endl;
	}
};
int main() {

	SparseMatrix a;
	SparseMatrix b;
	a.setvalue(1, 1, 2);
	b.setvalue(1, 1, 2);
	{
		SparseMatrix c;
	}


	int i;

	SparseMatrix c;

	c = a + b;
	c = a;

	c.show();


	return 0;
}