#pragma once
#include<iostream>
#include"arrayQueue.h"
#include<string.h>
using namespace std;

template<class T>
class binaryTreeNode
{
	public:
		T element;  //节点中的元素 
		binaryTreeNode<T> *left,*right;  //左右子树 
	
	    binaryTreeNode()  //无参数 
	    {	left=right=NULL;   }
		binaryTreeNode(const T& ele)
		{//只有数据参数 
			element=ele;
			left=right=NULL;
		}
		binaryTreeNode(const T& ele,binaryTreeNode* theLeft,binaryTreeNode* theRight)
		{//数据加指针 
			element=ele;
			left=theLeft;
			right=theRight;
		}
};

template<class T>
class linkedBinaryTree
{
	public:
		linkedBinaryTree() 
		{   
		    root=NULL;  
		    treeSize=0;	
		}
		~linkedBinaryTree() 
		{  
		    //erase();	 
		}
		bool empty() const
		{
			return treeSize;
		}
		void preOutput()
		{
			preOrder(&linkedBinaryTree<T>::output);  cout<<endl;
		}
		void inOutput()
		{
			inOrder(&linkedBinaryTree<T>::output);  cout<<endl;
		}
		void postOutput()
		{
			postOrder(&linkedBinaryTree<T>::output);  cout<<endl;
		}
		void preOrder(void (*theVisit) (binaryTreeNode<T>*) )
		{
		    visit=theVisit;	  
			preOrder(root);  //这里调用的是静态成员函数 
		}
		void inOrder(void (*theVisit) (binaryTreeNode<T>*))
		{
		   inOrder(root);
		}
		void postOrder(void (*theVisit) (binaryTreeNode<T>*))
		{
		   postOrder(root);
		}
		void makeTree(const T& element,linkedBinaryTree<T>& left,linkedBinaryTree<T> &right)
		{//将left,right和element合并成一颗新树 
		 //left，right和this必须不同！！
		 
		   root=new binaryTreeNode<T>(element,left.root,right.root);
		   treeSize=left.treeSize+right.treeSize+1;
		 
		 //阻止访问left和right
		    left.root=right.root=NULL;
		    left.treeSize=right.treeSize=0;
		} 
		void makeTree(const char *pre,const char *in,const int n)
		{
			root=Sub_makeTree(pre,in,n);
		//	cout<<"this is "<<root<<endl;
		}
		int height()
		{
			return Sub_height(root);
		}
		int size()
		{
			//return treeSize;
			return size(root);
		}
		int size(binaryTreeNode<T> *t)
		{//返回根为*t的树的节点数。对某根点求它左右子树的元素数，相加再加上它本身即为总节点数。 
		   if(t==NULL)  return 0;
		   else
		   {
		   	  int ls=size(t->left);  //左子树元素数 
		   	  int rs=size(t->right);  //右子树元素数 
			  return ls+rs+1;         //加上根节点 
		   }
		   //复杂度O(n) 	
		}
		void levelOrder()
		{
			Sub_levelOrder(root);
		}
		int max_width(binaryTreeNode<T> *t)
		{//求二叉树的每层最大节点数 
			arrayQueue< binaryTreeNode<T>* > q;
			binaryTreeNode<T> *last=root;   //last指向每层最右端的元素
			int level=1;   //层数 
			int width[20];   //保存每层节点数 
			while(t!=NULL)
			{
				if(t->left!=NULL)
			       q.push(t->left.element);
			    if(t->right!=NULL)
			       q.push(t->right.element);
			    
			    //下一个t
			    if(q.empty()==true)  break;  //队列为空，结束循环 
				t=q.front();
				q.pop(); 
				if(t==last) 
				{//已经扫完当前层,此时队列里全是下一层的节点 
					width[++level]=q.size();
					last=q.back();   //更新last 
				}
			}
			//从层数组中找出最大节点数 
			int max=0;
			for(int i=1;i<level;i++)
			{
				if(width[i]>max) 
				   max=width[i];
			}
			
			return max;
		}
		static bool compare(binaryTreeNode<T> *root1,binaryTreeNode<T> *root2)
		{//先判断两棵树根节点是否有空，若均不为空就比较其内的元素值 
		 //再判断左右子树    ------O(N)	 
		    if( (root1==NULL&&root2!=NULL) || (root1!=NULL&&root2==NULL) )
			   return false;  //树的结构不一样 
			else
			{
				if(root1==NULL && root2==NULL) return true;   //根节点均为空，递归到终点 
				if( *(root1) != *(root2) )    return false;  //根节点均不为空且值不同 
				else
				{//根节点不为空且值相同，比较左右子树 
					bool lt=compare(root1->left,root2->left);
				    bool rt=compare(root1->right,root2->right);
				    return lt&&rt;
			    }   
			} 
		}
		static void changeIntoPost(const T *pre,const T *in,T *post,const int n)
		{
			if(n<1)  return;
			T root=pre[0];
			post[n-1]=root;
	        int mid;  //mid是root在in中的索引
			
			for(mid=0;mid<n;mid++)
			{//在中序序列中找到根节点 
				if(in[mid]==root )
				   break;
			}
			changeIntoPost(pre+1,in,post,mid);
			changeIntoPost(pre+mid+1,in+mid+1,post+mid,n-1-mid);
		}
		
	private:
		binaryTreeNode<T> *root;   //指向根节点的指针
		int treeSize;              //树的节点数 
		static void output(binaryTreeNode<T> *X)
		{//访问函数 
			cout<< X->element<<' ';
		}
		static void (*visit) (binaryTreeNode<T> *);    //函数指针 
		static void preOrder(binaryTreeNode<T> *t)
		{//前序遍历 
			if(t!=NULL)
			{
				linkedBinaryTree<T>::visit(t);
				preOrder(t->left);
				preOrder(t->right);
			}
		}
		static void inOrder(binaryTreeNode<T> *t)
		{//中序遍历 
			if(t!=NULL)
			{
			    linkedBinaryTree<T>::inOrder(t->left);
				visit(t);
				inOrder(t->right);
			}
		}
		static void postOrder(binaryTreeNode<T> *t)
		{//后序遍历 
			if(t!=NULL)
			{
			    postOrder(t->left);
				postOrder(t->right);
				linkedBinaryTree<T>::visit(t);
			}
		} 
		static void dispose(binaryTreeNode<T> *t)
		{
			delete t;
		}
		int Sub_height(binaryTreeNode<T> *t)
		{//返回根为*t的树的高度。对根节点求它的左右子树的高度，取大者作为总树的高度 
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
			 //复杂度O(n)，每一个元素都比较了一遍 
		}
		binaryTreeNode<T> *Sub_makeTree(const char *pre,const char *in,const int n)
		{//由前序和中序序列构造一颗二叉树，n是二叉树的节点总数 
			if(n<1)  return NULL;
			char Root=pre[0];  cout<<"Root="<<Root<<"\t";
			binaryTreeNode<T> *b=new binaryTreeNode<T>(Root);
			treeSize++;
			
			int mid=0;  //根节点在in中的索引 
			for(mid=0;mid<n;mid++)
			{//在中序序列中找到根节点 
				if(in[mid]==Root )
				   break;
			}
			cout<<"mid="<<mid<<endl;
			b->left=Sub_makeTree(pre+1,in,mid);               //对左子树递归 
			b->right=Sub_makeTree(pre+1+mid,in+mid+1,n-mid-1);   //对右子树递归 
			
			return b;
		}
		void Sub_levelOrder(binaryTreeNode<T> *t)
		{//层次遍历二叉树*t 
		     arrayQueue< binaryTreeNode<T>* > q;  //这里先进先出所以用队列 
		     while(t!=NULL)
		     {
			    output(t);   //访问 t
				
				//将t的孩子插入队列，先左后右 
			    if(t->left!=NULL)
			       q.push(t->left);
			    if(t->right!=NULL)
			       q.push(t->right);
				
				//访问下一个节点 
				if(q.empty()==true) return;  //已访问完所有元素 
			    t=q.front();
			    q.pop();
			 }    	
		}
		
};
template<> void(*(linkedBinaryTree<char> ::visit))(binaryTreeNode<char>*);


