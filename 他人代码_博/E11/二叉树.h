
#pragma once
#include<iostream>
#include"arrayQueue.h"
#include<string.h>
using namespace std;

template<class T>
class binaryTreeNode
{
	public:
		T element;  //?����??D��??a?? 
		binaryTreeNode<T> *left,*right;  //���������������� 
	
	    binaryTreeNode()  //?T2?��y 
	    {	left=right=NULL;   }
		binaryTreeNode(const T& ele)
		{//??��D��y?Y2?��y 
			element=ele;
			left=right=NULL;
		}
		binaryTreeNode(const T& ele,binaryTreeNode* theLeft,binaryTreeNode* theRight)
		{//��y?Y?��???? 
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
		void preOrder()
		{
		    preOrder(root);  //?a��?�̡¨�?��?��??2��?3��?��o����y 
		}
		void inOrder()
		{
		   inOrder(root);
		}
		void postOrder()
		{
		   postOrder(root);
		}
		void makeTree(const T& element,linkedBinaryTree<T>& left,linkedBinaryTree<T> &right)
		{//??left,righto��elemento?2��3����???D?���� 
		 //left��?righto��this��?D?2?��?��?��?
		 
		   root=new binaryTreeNode<T>(element,left.root,right.root);
		   treeSize=left.treeSize+right.treeSize+1;
		 
		 //����?1��??��lefto��right
		    left.root=right.root=NULL;
		    left.treeSize=right.treeSize=0;
		} 
		binaryTreeNode<T> *makeTree(char *pre,char *in,const int n)
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
		{//����???��?a*t��?���¦�??����?��y?��???3?����??��?�����������������¦�??a??��y��??��?��?��?����??����?����?��?a����?����?��y?�� 
		   if(t==NULL)  return 0;
		   else
		   {
		   	  int ls=size(t->left);  //������������?a??��y 
		   	  int rs=size(t->right);  //������������?a??��y 
			  return ls+rs+1;         //?����??��?����? 
		   }
		   //?��?��?��O(n) 	
		}
		void levelOrder()
		{
			Sub_levelOrder(root);
		}
		int max_width(binaryTreeNode<T> *t)
		{//?��?t2?���¦�???2?��?�䨮?����?��y 
			arrayQueue< binaryTreeNode<T>* > q;
			binaryTreeNode<T> *last=root;   //last???��??2?��?����??��??a??
			int level=1;   //2?��y 
			int width[20];   //�����???2??����?��y 
			while(t!=NULL)
			{
				if(t->left!=NULL)
			       q.push(t->left.element);
			    if(t->right!=NULL)
			       q.push(t->right.element);
			    
			    //??��???t
			    if(q.empty()==true)  break;  //?����D?a??��??����??-?�� 
				t=q.front();
				q.pop(); 
				if(t==last) 
				{//��??-���������̡�?��2?,��?����?����D��?��?��???��?2?��??����? 
					width[++level]=q.size();
					last=q.back();   //?��D?last 
				}
			}
			//�䨮2?��y����?D?��3?��?�䨮?����?��y 
			int max=0;
			for(int i=1;i<level;i++)
			{
				if(width[i]>max) 
				   max=width[i];
			}
			
			return max;
		}
		static bool compare(binaryTreeNode<T> *root1,binaryTreeNode<T> *root2)
		{//?��?D??��???����?��?����?��?��?��D??��?��??��2??a???������?????����??a???�� 
		 //?��?D??����������������    ------O(N)	 
		    if( (root1==NULL&&root2!=NULL) || (root1!=NULL&&root2==NULL) )
			   return false;  //���¦�??��112?��??�� 
			else
			{
				if(root1==NULL && root2==NULL) return true;   //?��?����??��?a??��?��Y1����???��? 
				if( *(root1) != *(root2) )    return false;  //?��?����??��2??a???��?��2?��? 
				else
				{//?��?����?2??a???��?��?����?��?����??���������������� 
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
	        int mid;  //mid��?root?��in?D��??�¨�y
			
			for(p=in;p<in+n;p++)
			{
				if( *(p)==root )
				  break;
			}
			mid=p-in;
			changeIntoPost(pre+1,in,post,mid);
			changeIntoPost(pre+mid+1,p+1,post+mid,n-1-mid);
		}
		
	protected:
		binaryTreeNode<T> *root;   //???��?��?����?��?????
		int treeSize;              //���¦�??����?��y 
		static void visit(binaryTreeNode<T> *X)
		{//��??��o����y 
			cout<< X->element<<endl;
		}
		static void preOrder(binaryTreeNode<T> *t)
		{//?��D���������� 
			if(t!=NULL)
			{
				visit(t);
				preOrder(t->left);
				preOrder(t->right);
			}
		}
		static void inOrder(binaryTreeNode<T> *t)
		{//?DD���������� 
			if(t!=NULL)
			{
			    inOrder(t->left);
				visit(t);
				inOrder(t->right);
			}
		}
		static void postOrder(binaryTreeNode<T> *t)
		{//o��D���������� 
			if(t!=NULL)
			{
			    postOrder(t->left);
				postOrder(t->right);
				visit(t);
			}
		} 
		static void dispose(binaryTreeNode<T> *t)
		{
			delete t;
		}
		int Sub_height(binaryTreeNode<T> *t)
		{//����???��?a*t��?���¦�????��?��???��?����??��?����?���������������¦�????����?��?�䨮??����?a�������¦�????�� 
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
			//?��?��?��O(n)��???��????a????����??��?��?���� 
		}
		binaryTreeNode<T> *Sub_makeTree(char *pre,char *in,const int n)
		{//����?��D��o��?DD��D����D11?����????t2?���¡�?n��??t2?���¦�??����?������y 
			if(n<1)  return NULL;
			char Root=pre[0];  cout<<"Root="<<Root<<"\t";
			binaryTreeNode<T> *b=new binaryTreeNode<T>(Root);
			treeSize++;
			
			char *p;  int mid=0;  //?��?����??��in?D��??�¨�y 
			for(p=in;p<in+n;p++)
			{//?��?DD��D����D?D?����??��?����? 
				if( (*p)==Root )
				   break;
				mid++;
			}
			cout<<"mid="<<mid<<endl;
			b->left=Sub_makeTree(pre+1,in,mid);               //??�����������¦�Y1�� 
			b->right=Sub_makeTree(pre+1+mid,in+mid+1,n-mid-1);   //??�����������¦�Y1�� 
			
			return b;
		}
		void Sub_levelOrder(binaryTreeNode<T> *t)
		{//2?��?��������?t2?����*t 
		     arrayQueue< binaryTreeNode<T>* > q;  //?a��??��???��3??����?��??����D 
		     while(t!=NULL)
		     {
			    visit(t);   //��??�� t
				
				//??t��?o�����2?��??����D��??������o������ 
			    if(t->left!=NULL)
			       q.push(t->left);
			    if(t->right!=NULL)
			       q.push(t->right);
				
				//��??��??��????����? 
				if(q.empty()==true) return;  //��?��??������?����D?a?? 
			    t=q.front();
			    q.pop();
			 }    	
		}
		
};
