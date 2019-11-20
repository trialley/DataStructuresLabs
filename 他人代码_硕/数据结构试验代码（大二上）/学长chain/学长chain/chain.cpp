#include "chain.h"

template<class T>
chainNode<T>* chain<T>::preMerge(chainNode<T>* pa, chainNode<T>* pb)
{
	if (pa == nullptr)
		return pb;
	if (pb == nullptr)
		return pa;
	chainNode<T> *p = nullptr;
	if (pa->element < pb->element) {
		p = pa;
		p->next = preMerge(pa->next, pb);
	}
	else {
		p = pb;
		p->next = preMerge(pa, pb->next);
	}
	return p;
}

template<class T>
chain<T>::chain()
{
	firstNode = nullptr;
	listSize = 0;
}

template<class T>
chain<T>::chain(const chain<T>& c)
{
	listSize = c.listSize;
	chainNode<T>* srcNode = c.firstNode;
	firstNode = new chainNode<T>(srcNode->element);
	chainNode<T>* currNode = firstNode;
	srcNode = srcNode->next;
	while (srcNode != nullptr) {
		currNode->next = new chainNode<T>(srcNode->next);
		currNode = currNode->next;
		srcNode = srcNode->next;
	}
	currNode->next = nullptr;
}

template<class T>
chain<T>::~chain()
{
	chainNode<T>* currNode = firstNode;
	chainNode<T>* nextNode = nullptr;
	while (currNode != nullptr) {
		nextNode = currNode->next;
		delete currNode;
		currNode = nextNode;
	}
}

template<class T>
T & chain<T>::get(int index) const
{
	chainNode<T>* currNode = firstNode;
	for (int i = 0;i < index;i++) {
		currNode = currNode->next;
	}
	return currNode->element;
}

template<class T>
int chain<T>::indexOf(T & element)
{
	chainNode<T>* currNode = firstNode;
	int index = 0;
	while (currNode != nullptr) {
		if (currNode->element == element)
			return index;
		else
			currNode = currNode->next;
		index++;
	}
	return -1;
}

template<class T>
void chain<T>::erase(int index)
{
	chainNode<T>* deleteNode = nullptr;
	if (index == 0) {
		deleteNode = firstNode;
		firstNode = firstNode->next;
	}
	else {
		chainNode<T>* p = firstNode;
		for (int i = 0;i < index-1;i++) {
			p = p->next;
		}
		deleteNode = p->next;
		p->next = p->next->next;
	}
	delete deleteNode;
	listSize--;
}

template<class T>
void chain<T>::insert(int index, const T & element)
{
	if (index == 0) {
		firstNode = new chainNode<T>(element, firstNode);
	}
	else {
		chainNode<T>* p = firstNode;
		for (int i = 0;i < index;i++) {
			p = p->next;
		}
		p = new chainNode<T>(element, p);
	}
	listSize++;
}

template<class T>
void chain<T>::clear()
{
	chainNode<T>* currNode = firstNode;
	chainNode<T>* nextNode = nullptr;
	while (currNode != nullptr) {
		nextNode = currNode->next;
		delete currNode;
		currNode = nextNode;
	}
}

//���Ӷ�O(1)
template<class T>
void chain<T>::push_front(const T & element)
{
	firstNode = new chainNode<T>(element, firstNode);
	//insert(0, element);
}

template<class T>
void chain<T>::push_back(const T & element)
{
	insert(listSize, element);
}

//����ϲ�������ԭ�ڵ�ռ�
template<class T>
void chain<T>::merge(chain<T>& a, chain<T>& b)
{
	clear();
	listSize = a.listSize + b.listSize;

	chainNode<T> *pa = a.firstNode,
		*pb = b.firstNode,
		*p = nullptr;
	if (pa->element <= pb->element) {
		p = pa;
		pa = pa->next;
	}
	else {
		p = pb;
		pb = pb->next;
	}
	firstNode = p;

	while (pa&&pb) {
		if (pa->element <= pb->element) {
			p->next = pa;
			pa = pa->next;
		}
		else {
			p->next = pb;
			pb = pb->next;
		}
		p = p->next;
	}
	if (pa)
		p->next = pa;
	if (pb)
		p->next = pb;

	p = nullptr;
	a.firstNode = nullptr;
	b.firstNode = nullptr;
	a.listSize = 0;
	b.listSize = 0;
}

template<class T>
void chain<T>::mergeWithRecursion(chain<T>& a, chain<T>& b)
{
	clear();
	listSize = a.listSize + b.listSize;
	chainNode<T> *pa = a.firstNode,
		*pb = b.firstNode;

	firstNode = preMerge(pa, pb);

	a.firstNode = nullptr;
	b.firstNode = nullptr;
	a.listSize = 0;
	b.listSize = 0;
}

//ʹ�õ������������µĽڵ�ռ�
template<class T>
void chain<T>::mergeWithIterator(chain<T>& a, chain<T>& b)
{
	clear();
	auto ita = a.begin();
	auto itb = b.begin();
	listSize = a.listSize + b.listSize;
	chainNode<T>* p = nullptr;
	if (*ita <= *itb) {
		p = new chainNode<T>(*ita, nullptr);
		ita++;
	}
	else {
		p = new chainNode<T>(*itb, nullptr);
		itb++;
	}
	firstNode = p;
	while (ita != a.end() && itb != b.end()) {
		if (*ita <= *itb) {
			p->next = new chainNode<T>(*ita, nullptr);
			ita++;
		}
		else {
			p->next = new chainNode<T>(*itb, nullptr);
			itb++;
		}
		p = p->next;
	}
	while (ita != a.end()) {
		p->next = new chainNode<T>(*ita, nullptr);
		ita++;
	}
	while (itb != b.end()) {
		p->next = new chainNode<T>(*itb, nullptr);
		itb++;
	}
}

template<class T>
void chain<T>::initFromArray(const T * arr, int size)
{
	listSize = size;
	firstNode = new chainNode<T>(arr[0], nullptr);
	chainNode<T>* currNode = firstNode;
	for (int i = 1;i < size;i++) {
		currNode->next=new chainNode<T>(arr[i], nullptr);
		currNode = currNode->next;
	}
	currNode->next = nullptr;
}

template<class T>
void chain<T>::reverse()
{
	chainNode<T> *p = firstNode->next, *pr = nullptr;//p������ԭ������б��������α���ԭͷ����next��pr�����������ͷ���
	while (p != nullptr) {
		firstNode->next = pr;//��ԭ�����ͷ������������ĵ�һ��
		pr = firstNode;//��ʱfirstNode����ָ����ͷ��㣬����λ�ñ�����pr��
		firstNode = p;//ԭͷ����next��Ϊ��һ�ε�ͷ���
		p = p->next;//p�����Ųһλ
	}
	firstNode->next = pr;
}

