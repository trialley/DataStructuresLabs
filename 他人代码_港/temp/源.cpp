#include <iostream>
#include <queue>
#include <deque>
#include <stack>
using namespace std;

///树节点
struct Node
{
	char   data;
	Node* right;
	Node* left;
	Node(char data)
	{
		this->data = data;
		right = left = NULL;
	}
};


class Tree
{
private:
	Node* Root;

	///清空树的所有节点的函数
	void Clear()
	{
		deque<Node*> d;
		stack<Node*> s;
		if (Root == NULL) return;
		d.push_front(Root);
		Root = NULL;
		while (!d.empty())
		{
			Node* now = d.front();
			s.push(now);
			d.pop_front();
			if (now->right != NULL) d.push_front(now->right);
			if (now->left != NULL) d.push_front(now->left);
		}
		while (!s.empty())
		{
			Node* now = s.top();
			s.pop();
			delete now;
		}
	}

	///根据前序遍历与中序遍历构造树的递归方法
	Node* CreatByPreAndIn(char* pre, char* in, int n)
	{
		Node* newNode = new Node(pre[0]);
		if (n == 0) return NULL;
		if (n == 1) return newNode;
		char  tmp[2] = { pre[0],'\0' };
		char* FindIn = strstr(in, tmp);
		if (FindIn == NULL) throw;
		int len = (FindIn - in);
		newNode->left = CreatByPreAndIn(pre + 1, in, len);
		newNode->right = CreatByPreAndIn(pre + len + 1, in + len + 1, n - len - 1);
		return newNode;
	}
public:
	///构造函数 构造的时候调用初始化函数
	Tree()
	{
		Root = NULL;
		Init();
	}

	///析构函数
	~Tree()
	{
		Clear();
	}

	///初始化函数
	void Init()
	{
		Clear();
		char tmp;
		cout << "Input Root char:";
		cin >> tmp;
		if (tmp == '#') return;
		Root = new Node(tmp);
		queue<Node*> q;
		q.push(Root);
		while (!q.empty())
		{
			Node* tmpNode = NULL, * now = q.front();
			q.pop();
			cout << "Input " << now->data << "'s Left char:";
			cin >> tmp;
			if (tmp != '#') {
				tmpNode = new Node(tmp);
				q.push(tmpNode);
				now->left = tmpNode;
			}
			else now->left = NULL;
			cout << "Input " << now->data << "'s Right char:";
			cin >> tmp;
			if (tmp != '#') {
				tmpNode = new Node(tmp);
				q.push(tmpNode);
				now->right = tmpNode;
			}
			else now->right = NULL;
		}
	}

	///前序遍历函数
	void Pre_Order()
	{
		deque<Node*> d;
		if (Root == NULL) return;
		d.push_front(Root);
		while (!d.empty())
		{
			Node* now = d.front();
			d.pop_front();
			if (now->right != NULL) d.push_front(now->right);
			if (now->left != NULL) d.push_front(now->left);
			cout << now->data << ' ';
		}
		cout << endl;
	}

	///中序遍历函数
	void In_Order()
	{
		stack<Node*> s;
		Node* p = Root;
		while (!s.empty() || p != NULL)
		{
			while (p != NULL)
			{
				s.push(p);
				p = p->left;
			}
			if (!s.empty())
			{
				p = s.top();
				s.pop();
				cout << p->data << ' ';
				p = p->right;
			}
		}
		cout << endl;
	}

	///后序遍历函数
	void Post_Order()
	{
		stack<char>  MyStack;
		deque<Node*> MyDeque;
		MyDeque.push_front(Root);
		while (!MyDeque.empty())
		{
			Node* now = MyDeque.front();
			MyDeque.pop_front();
			MyStack.push(now->data);
			if (now->left != NULL) MyDeque.push_front(now->left);
			if (now->right != NULL) MyDeque.push_front(now->right);
		}
		while (!MyStack.empty())
		{
			cout << MyStack.top() << ' ';
			MyStack.pop();
		}
		cout << endl;
	}

	void InitByPreAndIn(char* Pre, char* In, int n)
	{
		Clear();
		Root = CreatByPreAndIn(Pre, In, n);
	}
};
int main()
{
	Tree* tree = new Tree();
	char* str1 = "1245367";
	char* str2 = "4251637";
	tree->InitByPreAndIn(str1, str2, 7);
	tree->Pre_Order();
	tree->In_Order();
	tree->Post_Order();
	return 0;
}