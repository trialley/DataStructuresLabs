#pragma once
#include<iostream>
#include"btree.h"
#include"queue.h"


/*��Ӧ�����������͵Ĺ�ϣ�������˴�ֻдint�Ĺ�ϣ����*/
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
	//myhash<K> _myhash;//�ȴ�С��ʵ����Ҫ��ϣ������ù�ϣֵ��ֻ��Ҫ����Ӧ���������Լ�����Ƚϴ�С�Ĳ�������
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
	/*���ҶԱ�·���е����ֵ���Ҳ�������0*/
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
				}else {//key���
					return xor_result;
				}
			}
		}

		//�Ҳ�������0
		return 0;
	}
	/*���뷵�ضԱ�·���е����ֵ*/
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

		/*ɾ���������滻���̲�����*/
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

		/*Ҫɾ����Ԫ���Ǹ��ڵ��*/
		if (p == btree< mypair<K, E>>::_root) {
			btree< mypair<K, E>>::_root = c;
		}else {
			/*Ҫɾ����Ԫ���Ǹ��ڵ���ĸ��ӽڵ㣿*/
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

		/*ɾ���������滻���̲�����*/
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

		/*Ҫɾ����Ԫ���Ǹ��ڵ��*/
		if (p == btree< mypair<K, E>>::_root) {
			btree< mypair<K, E>>::_root = c;
		} else {
			/*Ҫɾ����Ԫ���Ǹ��ڵ���ĸ��ӽڵ㣿*/
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
		node* troot = btree< mypair<K, E>>::_root;//ָ��Ҫɾ���Ľڵ�
		node* troot_f = btree< mypair<K, E>>::_root;//ָ��Ҫɾ����Ԫ�صĸ��ڵ�

		//�ж������������
		if (btree< mypair<K, E>>::_root == nullptr) {
			return;
		}
		if (btree< mypair<K, E>>::_root->right == nullptr) {
			troot = btree< mypair<K, E>>::_root;
			btree< mypair<K, E>>::_root = btree< mypair<K, E>>::_root->left;
			delete troot;
			return;
		}

		//�ҵ����ҵ�������
		while (troot->right != nullptr) {
			troot_f = troot;
			troot = troot->right;
		}
		//��������ӽڵ㻹���������������������������ӽڵ�ĸ��ڵ��������
		if (troot->left != nullptr) {
			troot_f->right = troot->left;
		}
		//ɾ��������
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