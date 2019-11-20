//Author ZhangJunshuo
//Using zjslib.h
//zjslib.h for details please contact me.
#include<iostream>
using namespace std;
#include<cstddef>
#include<string.h>

template<class K, class E>
class dic
{
public:
    virtual ~dic() {}
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual pair<const K, E> *find(const K &) const = 0;
    virtual int erase(const K &) = 0;
    virtual int insert(const pair<const K, E> &) = 0;
};

template<class K, class E>
class hasharrdic: public dic<K,E>
{
private:
	class zjshash
	{
	public:
	    size_t operator()(const int _key) const
	    {
	        return size_t(_key);
	    }
	};
	struct arrnode
	{
	public:
		bool deleted = false;   //添加一个是否被删除的标记.
		pair<const K, E>* element;
	};
protected:
    int search(const K &_key) const
	{
	    int i = (int) _hash(_key) % divisor;
	    int j = i;
	    int num_cycle;
	    if(table[j].element==NULL) return -1;
	    if(table[j].element->first==_key && table[j].deleted == true) return -1;
	    if(table[j].element->first==_key && table[j].deleted == false) return j;
	    while(1)
		{
			j++;
			if(table[j].element == NULL || table[j].deleted == true) return -1; //遇到空了还没找到，返回-1！
	    	if(table[j].element->first == _key && table[j].deleted == false) return j;
			if(j==divisor) j = 0;   //找到最右边了，返回最左边，实现循环查找.
			if(num_cycle>num_elements) return -2;   //表已经满了，但是还是没找到，返回-2！
			num_cycle++;
	    }
	}
protected:
    //pair<const K, E> **table;
    arrnode *table;
    zjshash _hash;
    int num_elements;
    int divisor;
public:
    hasharrdic(int _divisor)
	{
	    divisor = _divisor;
	    num_elements = 0;
	    table = new arrnode[divisor];
	    for (int i = 0;i<divisor;i++)
			table[i].element = NULL;
	}
    ~hasharrdic()
    {
        delete[] table;
    }
    bool empty() const
    {
        return num_elements == 0;
    }
    int size() const
    {
        return num_elements;
    }
    pair<const K, E> *find(const K &_key) const
	{
	    int b = search(_key);
	    if(b==-1)return NULL;
	    return table[b].element;
	}
    int insert(const pair<const K, E> &_pair)
	{
		if(num_elements == divisor) return -2;  //表满再插就溢出了，返回-2.
		int num_bucket = (int) _hash(_pair.first) % divisor;
		if(table[num_bucket].element==NULL)
		{
			table[num_bucket].element = new pair<const K, E> (_pair);
			num_elements++;
			return num_bucket;
		}
		if(table[num_bucket].element->first==_pair.first && table[num_bucket].deleted == true)
		{
			table[num_bucket].element = new pair<const K, E> (_pair);
			num_elements++;
			table[num_bucket].deleted = false;
			return num_bucket;
		}
		if(table[num_bucket].element->first==_pair.first && table[num_bucket].deleted == false)   return -1;  //已存在，返回-1;
		int j = num_bucket;
		while(1)
		{
			j++;
			if(j==divisor) j = 0;   //找到最右边了，返回最左边.
			if(table[j].element == NULL)
			{
				table[j].element = new pair<const K, E> (_pair);
				num_elements++;
				return j;
			}
			if(table[j].element != NULL && table[j].deleted == true)
			{
				table[j].element = new pair<const K, E> (_pair);
				table[j].deleted = false;
				num_elements++;
				return j;
			}
			if(table[j].element->first==_pair.first && table[num_bucket].deleted == false)   return -1;
		}
	}
	int erase(const K &_key)
	{
		int b = search(_key);
		if(b==-1||b==-2) return -1;
		table[b].deleted = true;
		num_elements--;
		return 0;
	}
	int locate(const K &_key)
	{
		return search(_key);
	}
    void output(ostream &out) const
	{
	    for (int i = 0; i < divisor; i++)
	        if (table[i] == NULL)
	            cout << "NULL" << endl;
	        else
	            cout << table[i]->first << " "
	                 << table[i]->second << endl;
	}
};

int main()
{
	int D = 0;
	int m = 0;
	cin >> D >> m;
	hasharrdic<int,int> test(D);
	for(int i=0;i<m;i++)
	{
		int opt = 0;
		int x = 0;
		cin >> opt >> x;
		pair<int,int> tempx(x,0);
		switch(opt)
		{
			case 0:
			{
				int num_bucket = test.insert(tempx);
				if(num_bucket==-1) cout << "Existed" << endl;
				else cout << num_bucket << endl;
				break;
			}
			case 1:
			{
				int num_bucket = test.locate(x);
				if(num_bucket==-1) cout << -1 << endl;
				else cout << num_bucket << endl;

				break;
			}
			case 2:
			{
				int num_bucket = test.erase(x);
				if(num_bucket!=0) cout << "Not Found" << endl;
				else cout << num_bucket << endl;
				break;
			}
		}
	}
	return 0;
}





