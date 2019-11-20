#include <iostream>
using namespace std;
template<class T>
struct node
{
	T element;
	node<T> *left;
	node<T> *right;
	node<T>()
	{
		left = NULL;
		right = NULL;
	}
	node<T>(const T &_element)
		:element(_element)
	{
		left = NULL;
		right = NULL;
	}
	node<T>(const T &_element, node<T> *_left, node<T> *_right)
		:element(_element)
	{
		left = _left;
		right = _right;
	}
};

void output(char* inorder, char* preorder, int length)
{
	if(length == 0)
	{
		return;
	}
	node<char>* _node = new node<char>;
	_node->element = *preorder;
	int rootIndex = 0;
	for(; rootIndex < length; rootIndex++)
	{
		if(inorder[rootIndex] == *preorder)
			break;
	}
	output(inorder, preorder +1, rootIndex);
	output(inorder + rootIndex + 1, preorder + rootIndex + 1, length - (rootIndex + 1));
	cout<<_node->element << ' ';
	return;
}


int main()
{
	int n;
	cin >> n;
	int*pr = new int[n];
	int*in = new int[n];
	for(int i=0;i<n;i++)
		cin >> pr[i];
	for(int i=0;i<n;i++)
		cin >> in[i];
	
	char* cpr = new char[n];
	char* cin = new char[n];
	
	for(int i=0;i<n;i++)
	{
		cpr[i] = pr[i]+48;
		cin[i] = in[i]+48;
	}

	output(cin, cpr, n);

	return 0;
}
