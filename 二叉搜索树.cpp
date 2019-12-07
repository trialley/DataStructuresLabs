#include<iostream>
using namespace std;
//出了各种细节方面的bug
//大方向上问题没有，细节问题不断
int result = 0;

template<class T>
struct binaryTreeNode
{
	T element;
	int leftSize;
	binaryTreeNode<T>* leftChild;		//左子树
	binaryTreeNode<T>* rightChild;		//右子树

	binaryTreeNode() {
		leftChild = rightChild = NULL; leftSize = 0;
	}
	binaryTreeNode(const T& theElement) { element = theElement; leftChild = rightChild = NULL; leftSize = 0; }
	binaryTreeNode(const T& theElement, binaryTreeNode<T>* theLeftChild, binaryTreeNode<T>* theRightChild)
	{
		leftSize = 0;
		element = theElement;
		leftChild = theLeftChild;
		rightChild = theRightChild;
	}
	/*
	void operator =(binaryTreeNode<T>& a){
		leftSize = a->leftSize;
		element = a->element;
		leftChild = a->leftChild;
		rightChild = a->rightChild;
	}
	bool operator ==(binaryTreeNode<T>& a) { return this->element == a->element; }//这里相等不考虑元素值重复的情况
	*/
	
};

template<class T>
class bsTree
{
protected:
	binaryTreeNode<T>* root;
	T sumSize;
public:
	bsTree(){ root = NULL; sumSize = 0; }
	bool push(T theElement);
	binaryTreeNode<T>* search(T theElement);
	binaryTreeNode<T>* index_search(int index);//索引从零开始
	bool erase(T theElement);
	void preorder(binaryTreeNode<T>* t);
	bool index_erase(int index);
	void test()//改bug用到的函数，出现意想不到的bug要记得整个输出找问题
	{
		preorder(root);
	}

};
template<class T>
bool bsTree<T>::push(T theElement)
{
	//result = 0;
	binaryTreeNode<T>* judge = search(theElement);
	result = 0;
	if (judge != NULL && judge->element == theElement)//有这样一个节点
	{
		return false;
	}
	//没有这样的节点
	result = 0;
	binaryTreeNode<T>* p = root;
	binaryTreeNode<T>* pp = NULL;
	while (p != NULL)
	{
		pp = p;
		result = result ^ p->element;
		if (theElement < p->element)
		{
			p->leftSize++;
			p = p->leftChild;
		}
		else
		{
			p = p->rightChild;
		}	
	}
	binaryTreeNode<T>* newNode = new binaryTreeNode<T>(theElement);
	if (root != NULL)
	{
		if (theElement < pp->element) { pp->leftChild = newNode; }
		else { pp->rightChild = newNode; }
	}
	else
	{
		root = newNode;
	}
	sumSize++;
	return true;
}

template<class T>
binaryTreeNode<T>* bsTree<T>::search(T theElement)
{
	result = 0;
	binaryTreeNode<T>* p = root;
	while (p != NULL)
	{
		result = result ^ p->element;
		// examine p->element
		if (theElement < p->element)//这里记得if else的结构，连用if的时候记得退出
		{
			p = p->leftChild;
		}
		else
		{
			if (theElement > p->element)
			{
				p = p->rightChild;
			}
			else // found matching pair
				return p;
		}
	}
	// no matching pair
	return NULL;
}
template<class T>
binaryTreeNode<T>* bsTree<T>::index_search(int index)
{
	//result = 0;
	if (index < 0 || index >= sumSize)//索引越界
	{
		return NULL;
	}
	result = 0;
	binaryTreeNode<T>* p = root;
	//binaryTreeNode<T>* pp = NULL;
	while (p != NULL)
	{
		result = result ^ p->element;
		if (p->leftSize == index)
		{
			//cout << result << endl;
			return p;
		}
		else
		{
			if (p->leftSize > index)//这里是倒数第二个错误，脑子不清楚。。。
			{
				p = p->leftChild;
			}
			else
			{
				index = index - p->leftSize - 1;
				p = p->rightChild;
			}
		}
	}
	return NULL;
}
template<class T>
void bsTree<T>::preorder(binaryTreeNode<T>* t)//前序遍历 
{
	if (t == NULL)
		return;
	cout << t->element << " " << t->leftSize << endl;
	preorder(t->leftChild);
	preorder(t->rightChild);
}

template<class T>
bool bsTree<T>::erase(T theElement)//交oj不过的原因为改代码时只改了后边main函数里的代码cout,没有改这里的cout
{
	
	binaryTreeNode<T>* judge = search(theElement);
	//result = 0;
	if (judge == NULL)//不存在这样的节点
	{
		//cout << "0" << endl;
		return false;
	}
	result = 0;
	binaryTreeNode<T>* p = root;
	binaryTreeNode<T>* pp = NULL;
	while (p->element != theElement && p != NULL)
	{
		result = result ^ p->element;
		pp = p;
		if (theElement < p->element)
		{
			p->leftSize--;
			p = p->leftChild;
		}
		else
		{
			p = p->rightChild;
		}

	}
	result = result ^ theElement;
	if (p == NULL)
	{
		return false;             //不存在与关键字匹配的数对
	}
	/*if (p->leftChild != NULL && p->rightChild != NULL)
	{
		binaryTreeNode<T>* s = p->rightChild;
		binaryTreeNode<T>* ps = p;
		while (s->leftChild != NULL)//找到右子树的最小孩子
		{
			s->leftSize--;
			ps = s;
			s = s->leftChild;
		}
		binaryTreeNode<T>* q = new binaryTreeNode<T>(s->element, p->leftChild, p->rightChild);
		if (p == pp->leftChild)
		{
			pp->leftChild = q;
		}
		else
		{
			pp->rightChild = q;
		}
		ps->leftChild = s->rightChild;
		delete p;
	}*/
	if (p->leftChild != NULL && p->rightChild != NULL)
	{
		binaryTreeNode<T>* s = p->rightChild,
			* ps = p;  // parent of s
		while (s->leftChild != NULL)
		{// move to larger element
			
			ps = s;
			s->leftSize--;
			s = s->leftChild;
		}
		binaryTreeNode<T>* q = new binaryTreeNode<T>(s->element, p->leftChild, p->rightChild);
		q->leftSize = p->leftSize;//将s元素的值赋给p，后将s元素删除 
		if (pp == NULL)
			root = q;
		else if (p == pp->leftChild)
				pp->leftChild = q;
			else
				pp->rightChild = q;
		if (ps == p) pp = q;
		else pp = ps;
		delete p;
		p = s;
	}
	//p最多一个孩子
	binaryTreeNode<T>* c=NULL;
	if (p->leftChild != NULL) { c = p->leftChild;}
	else { c = p->rightChild; }
	//删除p
	if (p == root) { root = c; }
	else
	{
		if (p == pp->leftChild)
		{
			pp->leftChild = c;
		}
		else
		{
			pp->rightChild = c;
		}
	}
	sumSize--;
	delete p;
	return true;
	//cout << result << endl;
}

template<class T>
bool bsTree<T>::index_erase(int index)
{
	//result = 0;
	if (index < 0 || index >= sumSize)//索引越界
	{
		//cout << "0" << endl;
		return false;
	}
	result = 0;
	binaryTreeNode<T>* judge = index_search(index);
	if (judge==NULL)
	{
		return false;
	}
	erase(judge->element);
	return true;
}


/*
template<class T>
bool bsTree<T>::index_erase(int index)
{
	result = 0;
	if (index < 0 || index >= sumSize)//索引越界
	{
		cout << "0" << endl;
		return false;
	}

	binaryTreeNode<T>* p = root;
	binaryTreeNode<T>* pp = NULL;
	while (p != NULL)
	{
		pp = p;
		result = result ^ p->element;
		if (p->leftSize == index)
		{
			break;
		}
		else
			if (p->leftSize > index)
			{
				p = p->leftChild;
			}
			else
			{
				index = index - p->leftSize - 1;
				p = p->rightChild;
			}
	}
	T theElement = p->element;
	//需要重新组织树型结构
	//p有两个孩子的时候处理
	if (p->leftChild != NULL && p->rightChild != NULL)
	{
		binaryTreeNode<T>* s = p->rightChild,
			* ps = p;  // parent of s
		while (s->leftChild != NULL)
		{// move to larger element
			s->leftSize--;
			ps = s;
			s = s->leftChild;
		}
		binaryTreeNode<T>* q = new binaryTreeNode<T>(s->element, p->leftChild, p->rightChild);
		q->leftSize = p->leftSize;
		if (pp == NULL)
			root = q;
		else if (p == pp->leftChild)
			pp->leftChild = q;
		else
			pp->rightChild = q;
		if (ps == p) pp = q;
		else pp = ps;
		delete p;
		p = s;
	}
	//p最多一个孩子
	binaryTreeNode<T>* c;
	if (p->leftChild != NULL) { c = p->leftChild; }
	else { c = p->rightChild; }
	//删除p
	if (p == root) { root = c; }
	else
	{
		if (p == pp->leftChild)
		{
			pp->leftChild = c;
		}
		else
		{
			pp->rightChild = c;
		}
	}
	sumSize--;
	delete p;
	return true;
}
*/




int main()
{
	int n;
	cin >> n;
	int choice;
	bsTree<int> m;
	binaryTreeNode<int>* x;
	int temp;
	for (int i = 0; i < n; i++)
	{
		cin >> choice;
		if (choice == 0)
		{
			cin >> temp;
			if (m.push(temp))
				cout << result << endl;
			else
				cout << "0" << endl;
			//cout<<endl;
			//m.test();
			//cout<<endl;
		}
		if (choice == 1)
		{
			cin >> temp;
			x=m.search(temp);
			if (x != NULL)//确实存在
				cout << result << endl;
			else
				cout << "0" << endl;
			//cout<<endl;
			//m.test();
			//cout<<endl;
		}
		if (choice == 2)
		{
			cin >> temp;
			if (m.erase(temp))
			{
				cout << result << endl;
			}
			else
			{
				cout << "0" << endl;
			}
			//cout<<endl;
			//m.test();
			//cout<<endl;
		}
		if (choice == 3)
		{
			cin >> temp;
			temp--;
			x=m.index_search(temp);
			if (x != NULL)
				cout << result << endl;
			else
				cout << "0" << endl;
			//cout<<endl;
			//m.test();
			//cout<<endl;
		}
		if (choice == 4)
		{
			cin >> temp;
			temp--;
			if (m.index_erase(temp))
			{
				cout << result << endl;
			}
			else
				cout << "0" << endl;
			//cout<<endl;
			//m.test();
			//cout<<endl;
		}
	}
}
