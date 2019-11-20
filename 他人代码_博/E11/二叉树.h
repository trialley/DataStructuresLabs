
#pragma once
#include<iostream>
#include"arrayQueue.h"
#include<string.h>
using namespace std;

template<class T>
class binaryTreeNode
{
	public:
		T element;  //?¨²¦Ì??D¦Ì??a?? 
		binaryTreeNode<T> *left,*right;  //¡Á¨®¨®¨°¡Á¨®¨º¡Â 
	
	    binaryTreeNode()  //?T2?¨ºy 
	    {	left=right=NULL;   }
		binaryTreeNode(const T& ele)
		{//??¨®D¨ºy?Y2?¨ºy 
			element=ele;
			left=right=NULL;
		}
		binaryTreeNode(const T& ele,binaryTreeNode* theLeft,binaryTreeNode* theRight)
		{//¨ºy?Y?¨®???? 
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
		    preOrder(root);  //?a¨¤?¦Ì¡Â¨®?¦Ì?¨º??2¨¬?3¨¦?¡Ào¡¥¨ºy 
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
		{//??left,righto¨ªelemento?2¡é3¨¦¨°???D?¨º¡Â 
		 //left¡ê?righto¨ªthis¡À?D?2?¨ª?¡ê?¡ê?
		 
		   root=new binaryTreeNode<T>(element,left.root,right.root);
		   treeSize=left.treeSize+right.treeSize+1;
		 
		 //¡Á¨¨?1¡¤??¨ºlefto¨ªright
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
		{//¡¤¦Ì???¨´?a*t¦Ì?¨º¡Â¦Ì??¨²¦Ì?¨ºy?¡ê???3?¨´¦Ì??¨®?¨¹¡Á¨®¨®¨°¡Á¨®¨º¡Â¦Ì??a??¨ºy¡ê??¨¤?¨®?¨´?¨®¨¦??¨¹¡À?¨¦¨ª?¡ä?a¡Á¨¹?¨²¦Ì?¨ºy?¡ê 
		   if(t==NULL)  return 0;
		   else
		   {
		   	  int ls=size(t->left);  //¡Á¨®¡Á¨®¨º¡Â?a??¨ºy 
		   	  int rs=size(t->right);  //¨®¨°¡Á¨®¨º¡Â?a??¨ºy 
			  return ls+rs+1;         //?¨®¨¦??¨´?¨²¦Ì? 
		   }
		   //?¡ä?¨®?¨¨O(n) 	
		}
		void levelOrder()
		{
			Sub_levelOrder(root);
		}
		int max_width(binaryTreeNode<T> *t)
		{//?¨®?t2?¨º¡Â¦Ì???2?¡Á?¡ä¨®?¨²¦Ì?¨ºy 
			arrayQueue< binaryTreeNode<T>* > q;
			binaryTreeNode<T> *last=root;   //last???¨°??2?¡Á?¨®¨°??¦Ì??a??
			int level=1;   //2?¨ºy 
			int width[20];   //¡À¡ê¡ä???2??¨²¦Ì?¨ºy 
			while(t!=NULL)
			{
				if(t->left!=NULL)
			       q.push(t->left.element);
			    if(t->right!=NULL)
			       q.push(t->right.element);
			    
			    //??¨°???t
			    if(q.empty()==true)  break;  //?¨®¨¢D?a??¡ê??¨¢¨º??-?¡¤ 
				t=q.front();
				q.pop(); 
				if(t==last) 
				{//¨°??-¨¦¡§¨ª¨º¦Ì¡À?¡ã2?,¡ä?¨º¡À?¨®¨¢D¨¤?¨¨?¨º???¨°?2?¦Ì??¨²¦Ì? 
					width[++level]=q.size();
					last=q.back();   //?¨¹D?last 
				}
			}
			//¡ä¨®2?¨ºy¡Á¨¦?D?¨°3?¡Á?¡ä¨®?¨²¦Ì?¨ºy 
			int max=0;
			for(int i=1;i<level;i++)
			{
				if(width[i]>max) 
				   max=width[i];
			}
			
			return max;
		}
		static bool compare(binaryTreeNode<T> *root1,binaryTreeNode<T> *root2)
		{//?¨¨?D??¨¢???¨º¡Â?¨´?¨²¦Ì?¨º?¡¤?¨®D??¡ê?¨¨??¨´2??a???¨ª¡À¨¨?????¨²¦Ì??a???¦Ì 
		 //?¨´?D??¡Á¨®¨®¨°¡Á¨®¨º¡Â    ------O(N)	 
		    if( (root1==NULL&&root2!=NULL) || (root1!=NULL&&root2==NULL) )
			   return false;  //¨º¡Â¦Ì??¨¢112?¨°??¨´ 
			else
			{
				if(root1==NULL && root2==NULL) return true;   //?¨´?¨²¦Ì??¨´?a??¡ê?¦ÌY1¨¦¦Ì???¦Ì? 
				if( *(root1) != *(root2) )    return false;  //?¨´?¨²¦Ì??¨´2??a???¨°?¦Ì2?¨ª? 
				else
				{//?¨´?¨²¦Ì?2??a???¨°?¦Ì?¨¤¨ª?¡ê?¡À¨¨??¡Á¨®¨®¨°¡Á¨®¨º¡Â 
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
	        int mid;  //mid¨º?root?¨²in?D¦Ì??¡Â¨°y
			
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
		binaryTreeNode<T> *root;   //???¨°?¨´?¨²¦Ì?¦Ì?????
		int treeSize;              //¨º¡Â¦Ì??¨²¦Ì?¨ºy 
		static void visit(binaryTreeNode<T> *X)
		{//¡¤??¨ºo¡¥¨ºy 
			cout<< X->element<<endl;
		}
		static void preOrder(binaryTreeNode<T> *t)
		{//?¡ãD¨°¡À¨¦¨¤¨² 
			if(t!=NULL)
			{
				visit(t);
				preOrder(t->left);
				preOrder(t->right);
			}
		}
		static void inOrder(binaryTreeNode<T> *t)
		{//?DD¨°¡À¨¦¨¤¨² 
			if(t!=NULL)
			{
			    inOrder(t->left);
				visit(t);
				inOrder(t->right);
			}
		}
		static void postOrder(binaryTreeNode<T> *t)
		{//o¨®D¨°¡À¨¦¨¤¨² 
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
		{//¡¤¦Ì???¨´?a*t¦Ì?¨º¡Â¦Ì????¨¨?¡ê???¨´?¨²¦Ì??¨®?¨¹¦Ì?¡Á¨®¨®¨°¡Á¨®¨º¡Â¦Ì????¨¨¡ê?¨¨?¡ä¨®??¡Á¡Â?a¡Á¨¹¨º¡Â¦Ì????¨¨ 
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
			//?¡ä?¨®?¨¨O(n)¡ê???¨°????a????¡À¨¨??¨¢?¨°?¡À¨¦ 
		}
		binaryTreeNode<T> *Sub_makeTree(char *pre,char *in,const int n)
		{//¨®¨¦?¡ãD¨°o¨ª?DD¨°D¨°¨¢D11?¨¬¨°????t2?¨º¡Â¡ê?n¨º??t2?¨º¡Â¦Ì??¨²¦Ì?¡Á¨¹¨ºy 
			if(n<1)  return NULL;
			char Root=pre[0];  cout<<"Root="<<Root<<"\t";
			binaryTreeNode<T> *b=new binaryTreeNode<T>(Root);
			treeSize++;
			
			char *p;  int mid=0;  //?¨´?¨²¦Ì??¨²in?D¦Ì??¡Â¨°y 
			for(p=in;p<in+n;p++)
			{//?¨²?DD¨°D¨°¨¢D?D?¨°¦Ì??¨´?¨²¦Ì? 
				if( (*p)==Root )
				   break;
				mid++;
			}
			cout<<"mid="<<mid<<endl;
			b->left=Sub_makeTree(pre+1,in,mid);               //??¡Á¨®¡Á¨®¨º¡Â¦ÌY1¨¦ 
			b->right=Sub_makeTree(pre+1+mid,in+mid+1,n-mid-1);   //??¨®¨°¡Á¨®¨º¡Â¦ÌY1¨¦ 
			
			return b;
		}
		void Sub_levelOrder(binaryTreeNode<T> *t)
		{//2?¡ä?¡À¨¦¨¤¨²?t2?¨º¡Â*t 
		     arrayQueue< binaryTreeNode<T>* > q;  //?a¨¤??¨¨???¨¨3??¨´¨°?¨®??¨®¨¢D 
		     while(t!=NULL)
		     {
			    visit(t);   //¡¤??¨º t
				
				//??t¦Ì?o¡é¡Á¨®2?¨¨??¨®¨¢D¡ê??¨¨¡Á¨®o¨®¨®¨° 
			    if(t->left!=NULL)
			       q.push(t->left);
			    if(t->right!=NULL)
			       q.push(t->right);
				
				//¡¤??¨º??¨°????¨²¦Ì? 
				if(q.empty()==true) return;  //¨°?¡¤??¨º¨ª¨º?¨´¨®D?a?? 
			    t=q.front();
			    q.pop();
			 }    	
		}
		
};
