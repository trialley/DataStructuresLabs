#pragma once
#include <iostream>
#include "hash.h" 
#include "myExceptions.h"
using namespace std;

template<class K, class E>
class hashTable{
public:
    hashTable(int theDivisor = 11);
    ~hashTable(){delete [] table;}
    bool empty() const {return dSize==0;}
    int size() const {return dSize;}
    pair<const K, E>* find(const K&) const;
    void insert(const pair<const K, E>&);
    void output(ostream& out) const;
    bool erase(const K& theKey); 
protected:
    int search(const K&) const;
    pair<const K, E>** table;  
    hash hashed;       // 将K类型转化成一个非负整数 
    int dSize;                 
    int divisor;              
};

template<class K, class E>
hashTable<K,E>::hashTable(int theDivisor){
    divisor = theDivisor;
    dSize = 0;
    table = new pair<const K, E>* [divisor];
    for(int i = 0; i < divisor; i++)table[i] = NULL;
}

template<class K, class E>
int hashTable<K,E>::search(const K& theKey) const{
    int i = hashed(theKey) % divisor, j = i;   // 转化 
    do{
        if (table[j] == NULL || table[j]->first == theKey)return j;
        j = (j + 1) % divisor; 
    } while (j != i);          
    return j;  
}

template<class K, class E>
pair<const K,E>* hashTable<K,E>::find(const K& theKey) const{
    int b = search(theKey);
    if (table[b] == NULL || table[b]->first != theKey)return NULL;          
    return table[b];  
}

template<class K, class E>
void hashTable<K,E>::insert(const pair<const K, E>& thePair){
    int b = search(thePair.first);
    if(table[b] == NULL){
        table[b] = new pair<const K,E> (thePair);
        dSize++;
    }
    else{
        if(table[b]->first == thePair.first) table[b]->second = thePair.second;
        else throw hashTableFull();
    }
}

template<class K, class E>
void hashTable<K,E>::output(ostream& out) const{
    for(int i = 0; i < divisor; i++)
        if (table[i] == NULL)cout << "NULL"<< endl;
        else cout << table[i]->first << " "<< table[i]->second << endl;
}
template<class K,class E>
bool hashTable<K,E>::erase(const K& theKey){
	int b=search(theKey);
	if(table[b]==NULL||table[b]->first!=theKey){
		cout<<"Key is not found."<<endl;
		return false;
	}
	delete table[b];
	table[b]=NULL;
	dSize--;
	while(true){
		int gap=b;
		while(true){
			b=(++b)%divisor;
			if(table[b]==NULL)return true;
			int home_bucket=hashed(table[b]->first)%divisor;
			if((gap<home_bucket&&home_bucket<=b)
			    ||(gap>b&&gap<home_bucket)
			    ||(gap>b&&home_bucket<=b))continue;
			break;
		}
		table[gap]=table[b];
		table[b]=NULL;
	}
}

template <class K, class E>
ostream& operator<<(ostream& out, const hashTable<K,E>& x)
   {x.output(out); return out;}

