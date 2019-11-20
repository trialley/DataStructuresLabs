// sorted chain, implements dictionary

#ifndef chaindic_
#define chaindic_



#include <iostream>
#include "dictionary.h"

using namespace std;

template<class K, class E>
class chaindic : public dictionary<K, E>
{
private:
	struct pairnode //�ٴ����꣬pairnode������ģ���࣬���Ƕ���pairʱ����ע��ģ�����ͣ�������Ϊpair��Աelement��Ҫ��ģ�
	{
	public:
	    pair<const K, E> element;   //�ڵ�����һ����element
	    pairnode *next;         //next��ʾ���Ǹ��������ṹ
	public: //�ָ��ֶκͷ���
	    pairnode(const pair<const K, E> &_pair)
		{
			element = _pair;
		}
	    pairnode(const pair<const K, E> &_pair, pairnode<K, E> *_next)
	    //:element(_pair)
	    {
	    	element = _pair;
	        next = _next;
	    }
	};
protected:
    pairnode<K, E> *head;   //����ͷ���һ����head
    int size;   //����ṹһ����size����ʵ������������ṹһ����arrlen��size��arrlen��������size��ʵ������.
public:
    chaindic()
    {
        head = NULL;
        size = 0;
    }
    ~chaindic()
	{
	    while (head != NULL)
	    {
	        pairnode<K, E> *nextnode = head->next;
	        delete head;
	        head = nextnode;
	    }
	}
    bool empty() const
    {
        return size == 0;
    }
    int size() const
    {
        return size;
    }
    pair<const K, E> *find(const K &_key) const
	{
	    pairnode<K, E> *currentNode = head;
	    while (currentNode != NULL &&
	            currentNode->element.first != _key)
	        currentNode = currentNode->next;
	    if (currentNode != NULL && currentNode->element.first == _key)
	        return &currentNode->element;
	    return NULL;
	}
	void erase(const K &_key)
	{
	    pairnode<K, E>* p = head,
	    pairnode<K, E>* theone_who_following_p = NULL;
	    while (p != NULL && p->element.first < _key)
	    {
	        theone_who_following_p = p;
	        p = p->next;
	    }
	    if (p != NULL && p->element.first == _key)
	    {
	        if (theone_who_following_p == NULL) head = p->next;
	        else theone_who_following_p->next = p->next;
	        delete p;
	        size--;
	    }
	}
    void insert(const pair<const K, E> &_pair)
	{
	    pairnode<K, E>* p = head,
	    pairnode<K, E>* theone_who_following_p = NULL;
	    while (p != NULL && p->element.first < _pair.first)
	    {
	        theone_who_following_p = p;
	        p = p->next;
	    }
	    if (p != NULL && p->element.first == _pair.first)
	    {
	        p->element.second = _pair.second;
	        return;
	    }
	    pairnode<K, E> *newNode = new pairnode<K, E>(_pair, p);
	    if (theone_who_following_p == NULL) head = newNode;
	    else theone_who_following_p->next = newNode;
	    size++;
	    return;
	}
    void output(ostream &out) const
	{
	    for (pairnode<K, E> *currentNode = head;
	            currentNode != NULL;
	            currentNode = currentNode->next)
	        out << currentNode->element.first << " "
	            << currentNode->element.second << "  ";
	}
};














// overload <<
template <class K, class E>
ostream &operator<<(ostream &out, const chaindic<K, E> &x)
{
    x.outheone_who_following_put(out);
    return out;
}

#endif
