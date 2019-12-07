#pragma once
#include<iostream>
#include"btree.h"
#include"queue.h"


/*对应各种数据类型的哈希函数，此处只写int的哈希函数*/
template <class K> class myhash;
template<>
class myhash<int> {
public:
	size_t operator()(const int keyin) const {
		return size_t (keyin);
	}
};

//template <class K>
//bool operator < (K& inl, K& inr) {
//	return myhash<K>(inl) < myhash<K> (inr);
//}
//template <class K>
//bool operator > (K& inl, K& inr) {
//	return myhash<K> (inl) > myhash<K> (inr);
//}
//template <class K>
//bool operator == (K& inl, K& inr) {
//	return myhash<K> (inl) == myhash<K> (inr);
//}
//template <class K>
//bool operator <= (K& inl, K& inr) {
//	return myhash<K> (inl) <= myhash<K> (inr);
//}
//template <class K>
//bool operator >= (K& inl, K& inr) {
//	return myhash<K> (inl) >= myhash<K> (inr);
//}

template<class K, class E>
struct  mypair {
	const K key;
	E data;
	mypair (const K& keyi, E& datai) :key (keyi), data (datai) {};
	mypair () {};
};


template<class K, class E>
class bstree : public btree< mypair<K, E>> {
public:
	using node = btree< mypair<K, E> >::node;
	//myhash<K> _myhash;//比大小其实不需要哈希函数获得哈希值，只需要让相应数据类型自己定义比较大小的操作即可
public:
	bool empty () const { return btree< mypair<K, E> >::_size == 0; }
	int size () const { return btree< mypair<K, E> >::_size; }
	mypair<K, E>* find (const K& theKey) const {
		node* p = btree< mypair<K, E> >::_root;
		while (p != nullptr) {
			if (theKey < p->data.key) {
				p = p->left;
			} else {
				if (theKey > p->data.key)
					p = p->right;
				else
					return &p->data;
			}
		}

		return nullptr;
	}
	void insertKE (const K& keyi, E& datai) {
		mypair<K, E> temp (keyi, datai);
		insert (temp);
	}
	/*查找对比路径中的异或值，找不到返回0*/
	int findGetXor (const  K& keyin) {
		int xor_result=0;
		node* p = btree< mypair<K, E> >::_root;
		node* pp = nullptr;
		while (p != nullptr) {
			pp = p;
			if (keyin < p->data.key) {
				xor_result ^= p->data.key;
				p = p->left;
			}else {
				if (keyin > p->data.key) {
					xor_result ^= p->data.key;
					p = p->right;
				}else {//key相等
					return xor_result;
				}
			}
		}

		//找不到返回0
		return 0;
	}
	/*插入返回对比路径中的异或值*/
	int insertGetXor (const  mypair<K, E>& thePair) {
		int xor_result = 0;
		node* p = btree< mypair<K, E> >::_root;
		node* pp = nullptr;
		while (p != nullptr) {
			pp = p;
			if (thePair.key < p->data.key) {
				xor_result ^= p->data.key;
				p = p->left;

			} else {
				if (thePair.key > p->data.key) {
					xor_result ^= p->data.key;
					p = p->right;

				} else {
					p->data.data = thePair.data;
					return 0;
				}
			}

		}

		node* newNode = new node (thePair);
		if (btree< mypair<K, E>>::_root != nullptr) {
			if (thePair.key < pp->data.key) {
				xor_result ^= pp->data.key;

				pp->left = newNode;
			} else {
				pp->right = newNode;
			}
		} else {
			btree< mypair<K, E>>::_root = newNode;
		}
		btree< mypair<K, E>>::_size++;
		return xor_result;
	}
	void eraseGetXor (const K& theKey) {
		int xor_result = 0;
		node* p = btree< mypair<K, E>>::_root;
		node* pp = nullptr;
		while (p != nullptr && p->data.key != theKey) {
			xor_result ^= pp->data.key;
			pp = p;
			if (theKey < p->data.key) {
				xor_result ^= pp->data.key;
				p = p->left;
			}else {
				p = p->right;
			}
		}
		if (p == nullptr) {
			return 0;
		}

		/*删除操作的替换过程不计算*/
		if (p->left != nullptr && p->right != nullptr) {

			node* s = p->left,
				* ps = p;
			while (s->right != nullptr) {
				ps = s;
				s = s->right;
			}

			node* q = new node (s->data, p->left, p->right);
			if (pp == nullptr)
				btree< mypair<K, E>>::_root = q;
			else if (p == pp->left)
				pp->left = q;
			else
				pp->right = q;
			if (ps == p) pp = q;
			else pp = ps;
			delete p;
			p = s;


		}

		node* c;
		if (p->left != nullptr) {
			c = p->left;
		}else {
			c = p->right;
		}

		/*要删除的元素是根节点否？*/
		if (p == btree< mypair<K, E>>::_root) {
			btree< mypair<K, E>>::_root = c;
		}else {
			/*要删除的元素是父节点的哪个子节点？*/
			if (p == pp->left)
				pp->left = c;
			else pp->right = c;
		}
		
		btree< mypair<K, E>>::_size--;
		delete p;

		return xor_result;
	}
	void eraseByThGetXor (const K& theKey) {
		int xor_result = 0;
		node* p = btree< mypair<K, E>>::_root;
		node* pp = nullptr;
		while (p != nullptr && p->data.key != theKey) {
			xor_result ^= pp->data.key;
			pp = p;
			if (theKey < p->data.key) {
				xor_result ^= pp->data.key;
				p = p->left;
			} else {
				p = p->right;
			}
		}
		if (p == nullptr) {
			return 0;
		}

		/*删除操作的替换过程不计算*/
		if (p->left != nullptr && p->right != nullptr) {

			node* s = p->left,
				* ps = p;
			while (s->right != nullptr) {
				ps = s;
				s = s->right;
			}

			node* q = new node (s->data, p->left, p->right);
			if (pp == nullptr)
				btree< mypair<K, E>>::_root = q;
			else if (p == pp->left)
				pp->left = q;
			else
				pp->right = q;
			if (ps == p) pp = q;
			else pp = ps;
			delete p;
			p = s;


		}

		node* c;
		if (p->left != nullptr) {
			c = p->left;
		} else {
			c = p->right;
		}

		/*要删除的元素是根节点否？*/
		if (p == btree< mypair<K, E>>::_root) {
			btree< mypair<K, E>>::_root = c;
		} else {
			/*要删除的元素是父节点的哪个子节点？*/
			if (p == pp->left)
				pp->left = c;
			else pp->right = c;
		}

		btree< mypair<K, E>>::_size--;
		delete p;

		return xor_result;
	}

	void ascend () { btree< mypair<K, E>>::inOrderOutput (); }

	void deleteMax () {
		node* troot = btree< mypair<K, E>>::_root;//指向要删除的节点
		node* troot_f = btree< mypair<K, E>>::_root;//指向要删除的元素的父节点

		//判断两种特殊情况
		if (btree< mypair<K, E>>::_root == nullptr) {
			return;
		}
		if (btree< mypair<K, E>>::_root->right == nullptr) {
			troot = btree< mypair<K, E>>::_root;
			btree< mypair<K, E>>::_root = btree< mypair<K, E>>::_root->left;
			delete troot;
			return;
		}

		//找到最右的右子树
		while (troot->right != nullptr) {
			troot_f = troot;
			troot = troot->right;
		}
		//如果最右子节点还有左子树，则该左子树变成最右子节点的父节点的右子树
		if (troot->left != nullptr) {
			troot_f->right = troot->left;
		}
		//删除右子树
		delete troot;
		return;
	}

	void insertArray (E* arri, int len) {
		btree< mypair<K, E>>::_root = new node;

		for (int i = 0; i < len; i++) {
			node* p = btree< mypair<K, E>>::_root;
			node* pp = nullptr;
			while (p != nullptr) {
				pp = p;
				if (i < p->data.key)
					p = p->left;
				else
					p = p->right;
			}

			node* newNode = new node (i, arri[i]);
			if (btree< mypair<K, E>>::_root != nullptr) {
				if (i < pp->data.key)pp->left = newNode;
				else pp->right = newNode;
			} else {
				btree< mypair<K, E>>::_root = newNode;
			}

			btree< mypair<K, E>>::_size++;
		}
	}

	void inOrderToArr (node* t, E* position) {
		if (t != nullptr) {
			inOrderToArr (t->left, position);
			position[0] = t->key;
			position++;
			inOrderToArr (t->left, position);
			return;
		} else {
			return;
		}
	}

	int getHight () {



	}
};
template<class K, class E>
ostream& operator << (ostream& out, bstree<K, E>& in) {
	in.btree< mypair<K, E>>::levelOut (out);
	return out;
}
template<class K, class E>
ostream& operator<<(ostream& out, mypair<K, E>& in) {
	out << in.key << ':' << in.data;
	return out;
}