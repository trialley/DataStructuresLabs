#pragma once
#include<iostream>
#include"arrqueue.h"
#include<string.h>
using namespace std;

template<class T>
class node
{
	public:
		T element;
		node<T> *left,*right;
		node()
		{
			left=right=NULL;
		}
		node(const T& ele)
		{
			element=ele;
			left=right=NULL;
		}
		node(const T& ele,node* theLeft,node* theRight)
		{
			element=ele;
			left=theLeft;
			right=theRight;
		}
};

template<class T>
class bintree
{
	public:
		bintree()
		{
			root=NULL;
			treeSize=0;
		}
		~bintree()
		{
			//erase();
		}
		bool empty() const
		{
			return treeSize;
		}
		void preOrder()
		{
			preOrder(root);
		}
		void inOrder()
		{
			inOrder(root);
		}
		void postOrder()
		{
			postOrder(root);
		}
		void makeTree(const T& element,bintree<T>& left,bintree<T> &right)
		{
			root=new node<T>(element,left.root,right.root);
			treeSize=left.treeSize+right.treeSize+1;
			left.root=right.root=NULL;
			left.treeSize=right.treeSize=0;
		}
		node<T> *makeTree(char *pre,char *in,const int n)
		{
			root=Sub_makeTree(pre,in,n);
		}
		int height()
		{
			return Sub_height(root);
		}
		int size()
		{
			return size(root);
		}
		int size(node<T> *t)
		{
			if(t==NULL)  return 0;
			else
			{
				int ls=size(t->left);
				int rs=size(t->right);
				return ls+rs+1;
			}
		}
		void levelOrder()
		{
			Sub_levelOrder(root);
		}
		int max_width(node<T> *t)
		{
			arrayQueue< node<T>* > q;
			node<T> *last=root;
			int level=1;
			int width[20];
			while(t!=NULL)
			{
				if(t->left!=NULL)
					q.push(t->left.element);
				if(t->right!=NULL)
					q.push(t->right.element);
				if(q.empty()==true)  break;
				t=q.front();
				q.pop();
				if(t==last)
				{
					width[++level]=q.size();
					last=q.back();
				}
			}
			int max=0;
			for(int i=1; i<level; i++)
			{
				if(width[i]>max)
					max=width[i];
			}

			return max;
		}
		static bool compare(node<T> *root1,node<T> *root2)
		{
			if( (root1==NULL&&root2!=NULL) || (root1!=NULL&&root2==NULL) )
				return false;
			else
			{
				if(root1==NULL && root2==NULL) return true;
				if( *(root1) != *(root2) )    return false;
				else
				{
					bool lt=compare(root1->left,root2->left);
					bool rt=compare(root1->right,root2->right);
					return lt&&rt;
				}
			}
		}
		static void changeIntoPost(T *pre,T *in,T *post,const int n)
		{
			if(n<1)  return;
			T root=pre[0];
			post[n-1]=root;
			T *p;
			int mid;

			for(p=in; p<in+n; p++)
			{
				if( *(p)==root )
					break;
			}
			mid=p-in;
			changeIntoPost(pre+1,in,post,mid);
			changeIntoPost(pre+mid+1,p+1,post+mid,n-1-mid);
		}

	protected:
		node<T> *root;
		int treeSize;
		static void visit(node<T> *X)
		{
			cout<< X->element<<endl;
		}
		static void preOrder(node<T> *t)
		{
			if(t!=NULL)
			{
				visit(t);
				preOrder(t->left);
				preOrder(t->right);
			}
		}
		static void inOrder(node<T> *t)
		{
			if(t!=NULL)
			{
				inOrder(t->left);
				visit(t);
				inOrder(t->right);
			}
		}
		static void postOrder(node<T> *t)
		{
			if(t!=NULL)
			{
				postOrder(t->left);
				postOrder(t->right);
				visit(t);
			}
		}
		static void dispose(node<T> *t)
		{
			delete t;
		}
		int Sub_height(node<T> *t)
		{
			if(t==NULL)
				return 0;
			else
			{
				int hl=Sub_height(t->left);
				int hr=Sub_height(t->right);
				if(hl>hr)
					return ++hl;
				else
					return ++hr;
			}
		}
		node<T> *Sub_makeTree(char *pre,char *in,const int n)
		{
			if(n<1)  return NULL;
			char Root=pre[0];
			cout<<"Root="<<Root<<"\t";
			node<T> *b=new node<T>(Root);
			treeSize++;
			char *p;
			int mid=0;
			for(p=in; p<in+n; p++)
			{
				if( (*p)==Root )
					break;
				mid++;
			}
			cout<<"mid="<<mid<<endl;
			b->left=Sub_makeTree(pre+1,in,mid);
			b->right=Sub_makeTree(pre+1+mid,in+mid+1,n-mid-1);
			return b;
		}
		void Sub_levelOrder(node<T> *t)
		{
			arrayQueue< node<T>* > q;
			while(t!=NULL)
			{
				visit(t);
				if(t->left!=NULL)
					q.push(t->left);
				if(t->right!=NULL)
					q.push(t->right);
				if(q.empty()==true) return;
				t=q.front();
				q.pop();
			}
		}
};

template<class K,class E>
class myPair
{
	public:
		K first;
		E second;
		int leftSize;
		myPair()
		{
			first=0;
			second=0;
			leftSize=0;
		}
		myPair(K fir,E sec)
		{
			first=fir;
			second=sec;
			leftSize=0;
		}
		myPair(const myPair<K,E> &x)
		{
			first=x.first;
			second=x.second;
			leftSize=x.leftSize;
		}
		void operator=(const myPair<K,E> &x)
		{
			first=x.first;
			second=x.second;
			leftSize=x.leftSize;
		}
		friend ostream& operator << (ostream& out,myPair<K,E> myPair)
		{
			out<<"Key="<<myPair.first<<" value="<<myPair.second<<" leftSize="<<myPair.leftSize;
			return out;
		}
};
