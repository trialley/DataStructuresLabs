#pragma once
#include <iostream>
#include "dictionary.h"
#include "node.h"

using namespace std;

template<class K, class E>
class sortedChain{
protected:
	node<K, E>* _first_node;  // pointer to first node in chain
	int _size;                 // number of elements in dictionary
   public:
      sortedChain() {_first_node = nullptr; _size = 0;}
      ~sortedChain() {
		  // Destructor.  Delete all nodes.
		  while ( _first_node != nullptr ) {// delete _first_node
			  node<K, E>* nextNode = _first_node->next;
			  delete _first_node;
			  _first_node = nextNode;
		  }
	  }
      bool empty() const {return _size == 0;}
      int size() const {return _size;}
      pair<const K, E>* find(const K&) const {
		  // Return pointer to matching pair.
           // Return nullptr if no matching pair.
		  node<K, E>* currentNode = _first_node;

		  // search for match with theKey
		  while ( currentNode != nullptr && currentNode->element.first != theKey ) {
			  currentNode = currentNode->next;
		  }

		  // verify match
		  if ( currentNode != nullptr && currentNode->element.first == theKey )
			  // yes, found match
			  return &currentNode->element;

		  // no match
		  return nullptr;
	  }
      void erase(const K&) {
		  // Delete the pair, if any, whose key equals theKey.
		  node<K, E>* p = _first_node,
			  * tp = nullptr; // tp trails p

 // search for match with theKey
		  while ( p != nullptr && p->element.first < theKey ) {
			  tp = p;
			  p = p->next;
		  }

		  // verify match
		  if ( p != nullptr && p->element.first == theKey ) {// found a match
			 // remove p from the chain
			  if ( tp == nullptr ) _first_node = p->next;  // p is first node
			  else tp->next = p->next;

			  delete p;
			  _size--;
		  }
	  }
      void insert(const pair<const K, E>&) {
		  // Insert thePair into the dictionary. Overwrite existing
          // pair, if any, with same key.
		  node<K, E>* p = _first_node;
			  node<K, E>* tp = nullptr; // tp trails p

          // move tp so that thePair can be inserted after tp
		  while ( p != nullptr && p->element.first < thePair.first ) {
			  tp = p;
			  p = p->next;
		  }

		  // check if there is a matching pair
		  if ( p != nullptr && p->element.first == thePair.first ) {// replace old value
			  p->element.second = thePair.second;
			  return;
		  }

		  // no match, set up node for thePair
		  node<K, E>* newNode = new node<K, E> ( thePair, p );

		  // insert newNode just after tp
		  if ( tp == nullptr ) _first_node = newNode;
		  else tp->next = newNode;

		  _size++;
		  return;
	  }
      void output(ostream& out) const {// Insert the chain elements into the stream out.
		  for ( node<K, E>* currentNode = _first_node;
			  currentNode != nullptr;
			  currentNode = currentNode->next )
			  out << currentNode->element.first << " "
			  << currentNode->element.second << "  ";
	  }
};

template <class K, class E>
ostream& operator<<(ostream& out, const sortedChain<K,E>& x){
	x.output(out);
	return out;
}

