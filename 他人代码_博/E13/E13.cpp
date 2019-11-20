#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
class queue
{
	protected:
	public:
		virtual ~queue() {}
		virtual T &top() = 0;
		virtual T &back() = 0;
		virtual bool empty() const = 0;
		virtual int size() const = 0;
		virtual void push(const T &_element) = 0;
		virtual void pop() = 0;
};

template<typename T>
class chainqueue
{
	private:
		struct chainnode
		{
			T element;
			chainnode *next;
			chainnode *prev;
			chainnode() {}
			chainnode(const T &_element)
			{
				element = _element;   //struct的默认构造函数与析构函数 (10)
			}
			chainnode(const T &_element, chainnode *_next)
			{
				element = _element;
				next = _next;
			}	//这个构造函数为什么要存在？
		};
	protected:
		chainnode *queuetop;
		chainnode *queueback;
		int queuesize;
	public:
		chainqueue()
		{
			queuetop = NULL;
			queuesize = 0;
		}
		~chainqueue()
		{
			while (queuetop != NULL)
			{
				chainnode *nextNode = queuetop->next;
				delete queuetop;
				queuetop = nextNode;
			}
		}
		T &top()
		{
			//        if (queuesize == 0)
			//            throw queueEmpty();
			return queuetop->element;
		}
		T &back()
		{
			//        if (queuesize == 0)
			//            throw queueEmpty();
			return queueback->element;
		}
		bool empty() const
		{
			return queuesize == 0;
		}
		int size() const
		{
			return queuesize;
		}
		void push(const T &_element)
		{
			chainnode *newNode = new chainnode(_element, NULL);
			if (queuesize == 0)
				queuetop = newNode;
			else
				queueback->next = newNode;
			queueback = newNode;
			queuesize++;
		}
		void pop()
		{
			//        if (queuetop == NULL)
			//            throw queueEmpty();
			chainnode *nextNode = queuetop->next;
			delete queuetop;
			queuetop = nextNode;
			queuesize--;
		}
};

template<typename T>
class arrqueue:	public queue<T>
{
	protected:
		int queuetop;
		int queueback;
		int arrlen;
		T *queue;
	public:
		arrqueue(int initial_arrlen = 10)
		{
			arrlen = initial_arrlen;
			queue = new T[arrlen];
			queuetop = 0;
			queueback = 0;
		}
		~arrqueue()
		{
			delete[] queue;
		}
		T &top()
		{
			return queue[(queuetop + 1) % arrlen];
		}
		T &back()
		{
			return queue[queueback];
		}
		bool empty() const
		{
			return queuetop == queueback;
		}
		int size() const
		{
			return (queueback - queuetop + arrlen) % arrlen;
		}
		void push(const T &_element)
		{
			if ((queueback + 1) % arrlen == queuetop)
			{
				T *newQueue = new T[2 * arrlen];
				int start = (queuetop + 1) % arrlen;
				if (start < 2)
					copy(queue + start, queue + start + arrlen - 1, newQueue);
				else
				{
					copy(queue + start, queue + arrlen, newQueue);
					copy(queue, queue + queueback + 1, newQueue + arrlen - start);
				}
				queuetop = 2 * arrlen - 1;
				queueback = arrlen - 2;
				arrlen *= 2;
				queue = newQueue;
			}
			queueback = (queueback + 1) % arrlen;
			queue[queueback] = _element;
		}
		void pop()
		{
			queuetop = (queuetop + 1) % arrlen;
			queue[queuetop].~T();
		}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class myClass
{
	public:
		int x,y,l;
} js[20199];

int Comparators(const myClass&a,const myClass&b)
{
	return a.l<b.l?1:0;
}
int f[2019];
int find(int x)
{
	if(x==f[x]) return x;
	return f[x]=find(f[x]);
}

int n;
int m;
int k;

int main()
{
	cin >> n >> m >> k;
	for(int i=1; i<=m; i++)
		cin >> js[i].x >> js[i].y >> js[i].l;
	sort(js+1,js+m+1,Comparators);
	for(int i=1; i<=n; i++)
		f[i]=i;

	int num=n,j=1,ans=0;
	while(num>k&&j<=m)
	{
		int a=js[j].x,b=js[j].y;
		if(find(a)!=find(b))
		{
			ans+=js[j].l;
			num--;
			f[find(a)]=find(b);
		}
		j++;
	}
	if(num>k)
		cout << "No Answer" << endl;
	else
		cout << ans;
	return 0;
}
