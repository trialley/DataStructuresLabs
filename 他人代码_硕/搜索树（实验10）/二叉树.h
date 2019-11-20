#pragma once
#include<iostream>
#include"arrayQueue.h"
#include<string.h>
using namespace std;

template<class T>
class binaryTreeNode
{
	public:
		T element;  //�ڵ��е�Ԫ�� 
		binaryTreeNode<T> *left,*right;  //�������� 
		int leftSize;  //���������������õ���������Ԫ���� 
	
	    binaryTreeNode()  //�޲��� 
	    {	left=right=NULL;  leftSize=0;  }
		binaryTreeNode(const T& ele)
		{//ֻ�����ݲ��� 
			element=ele;
			left=right=NULL;
			leftSize=0;
		}
		binaryTreeNode(const T& ele,binaryTreeNode* theLeft,binaryTreeNode* theRight)
		{//���ݼ�ָ�� 
			element=ele;
			left=theLeft;
			right=theRight;
			leftSize=0;
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
		    erase(root);	 
		}
		void erase(binaryTreeNode<T> *t)
		{//�������ɾ����� 
			if(t->left)   erase(t->left);
			if(t->right)  erase(t->right);
			dispose(t);
		}
		bool empty() const
		{
			return treeSize;
		}
		void preOrder()
		{
		    preOrder(root);  //������õ��Ǿ�̬��Ա���� 
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
		{//��left,right��element�ϲ���һ������ 
		 //left��right��this���벻ͬ����
		 
		   root=new binaryTreeNode<T>(element,left.root,right.root);
		   treeSize=left.treeSize+right.treeSize+1;
		 
		 //��ֹ����left��right
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
		{//���ظ�Ϊ*t�����Ľڵ�������ĳ������������������Ԫ����������ټ���������Ϊ�ܽڵ����� 
		   if(t==NULL)  return 0;
		   else
		   {
		   	  int ls=size(t->left);  //������Ԫ���� 
		   	  int rs=size(t->right);  //������Ԫ���� 
			  return ls+rs+1;         //���ϸ��ڵ� 
		   }
		   //���Ӷ�O(n) 	
		}
		void levelOrder()
		{
			Sub_levelOrder(root);
		}
		int max_width(binaryTreeNode<T> *t)
		{//���������ÿ�����ڵ��� 
			arrayQueue< binaryTreeNode<T>* > q;
			binaryTreeNode<T> *last=root;   //lastָ��ÿ�����Ҷ˵�Ԫ��
			int level=1;   //���� 
			int width[20];   //����ÿ��ڵ��� 
			while(t!=NULL)
			{
				if(t->left!=NULL)
			       q.push(t->left.element);
			    if(t->right!=NULL)
			       q.push(t->right.element);
			    
			    //��һ��t
			    if(q.empty()==true)  break;  //����Ϊ�գ�����ѭ�� 
				t=q.front();
				q.pop(); 
				if(t==last) 
				{//�Ѿ�ɨ�굱ǰ��,��ʱ������ȫ����һ��Ľڵ� 
					width[++level]=q.size();
					last=q.back();   //����last 
				}
			}
			//�Ӳ��������ҳ����ڵ��� 
			int max=0;
			for(int i=1;i<level;i++)
			{
				if(width[i]>max) 
				   max=width[i];
			}
			
			return max;
		}
		static bool compare(binaryTreeNode<T> *root1,binaryTreeNode<T> *root2)
		{//���ж����������ڵ��Ƿ��пգ�������Ϊ�վͱȽ����ڵ�Ԫ��ֵ 
		 //���ж���������    ------O(N)	 
		    if( (root1==NULL&&root2!=NULL) || (root1!=NULL&&root2==NULL) )
			   return false;  //���Ľṹ��һ�� 
			else
			{
				if(root1==NULL && root2==NULL) return true;   //���ڵ��Ϊ�գ��ݹ鵽�յ� 
				if( *(root1) != *(root2) )    return false;  //���ڵ����Ϊ����ֵ��ͬ 
				else
				{//���ڵ㲻Ϊ����ֵ��ͬ���Ƚ��������� 
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
	        int mid;  //mid��root��in�е�����
			
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
		binaryTreeNode<T> *root;   //ָ����ڵ��ָ��
		int treeSize;              //���Ľڵ��� 
		static void visit(binaryTreeNode<T> *X)
		{//���ʺ��� 
			cout<< X->element<<endl;
		}
		static void preOrder(binaryTreeNode<T> *t)
		{//ǰ����� 
			if(t!=NULL)
			{
				visit(t);
				preOrder(t->left);
				preOrder(t->right);
			}
		}
		static void inOrder(binaryTreeNode<T> *t)
		{//������� 
			if(t!=NULL)
			{
			    inOrder(t->left);
				visit(t);
				inOrder(t->right);
			}
		}
		static void postOrder(binaryTreeNode<T> *t)
		{//������� 
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
		{//���ظ�Ϊ*t�����ĸ߶ȡ��Ը��ڵ����������������ĸ߶ȣ�ȡ������Ϊ�����ĸ߶� 
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
			//���Ӷ�O(n)��ÿһ��Ԫ�ض��Ƚ���һ�� 
		}
		binaryTreeNode<T> *Sub_makeTree(char *pre,char *in,const int n)
		{//��ǰ����������й���һ�Ŷ�������n�Ƕ������Ľڵ����� 
			if(n<1)  return NULL;
			char Root=pre[0];  cout<<"Root="<<Root<<"\t";
			binaryTreeNode<T> *b=new binaryTreeNode<T>(Root);
			treeSize++;
			
			char *p;  int mid=0;  //���ڵ���in�е����� 
			for(p=in;p<in+n;p++)
			{//�������������ҵ����ڵ� 
				if( (*p)==Root )
				   break;
				mid++;
			}
			cout<<"mid="<<mid<<endl;
			b->left=Sub_makeTree(pre+1,in,mid);               //���������ݹ� 
			b->right=Sub_makeTree(pre+1+mid,in+mid+1,n-mid-1);   //���������ݹ� 
			
			return b;
		}
		void Sub_levelOrder(binaryTreeNode<T> *t)
		{//��α���������*t 
		     arrayQueue< binaryTreeNode<T>* > q;  //�����Ƚ��ȳ������ö��� 
		     while(t!=NULL)
		     {
			    visit(t);   //���� t
				
				//��t�ĺ��Ӳ�����У�������� 
			    if(t->left!=NULL)
			       q.push(t->left);
			    if(t->right!=NULL)
			       q.push(t->right);
				
				//������һ���ڵ� 
				if(q.empty()==true) return;  //�ѷ���������Ԫ�� 
			    t=q.front();
			    q.pop();
			 }    	
		}
		
};










