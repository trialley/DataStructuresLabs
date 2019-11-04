#pragma once

using namespace std;

template <class K, class E>
struct node {
	typedef pair<const K, E> pairType;
	pairType _element;
	node<K, E>* _next;

	node ( const pairType& thePair ) :_element ( thePair ) {}
	node ( const pairType& thePair, node<K, E>* theNext ):_element ( thePair ), _next( theNext ){}
};
