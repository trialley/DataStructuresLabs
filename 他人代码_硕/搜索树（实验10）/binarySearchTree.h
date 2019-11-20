#pragma once
#include<iostream>
#include"二叉树.h"
#include"pair.h"

using namespace std;

template<class K,class E>
class binarySearchTree :public linkedBinaryTree<Pair<K, E> >
{//二叉搜索树，元素由小到大，左，根，右 
	public:
	typedef linkedBinaryTree< Pair<K, E> > BT;
		binarySearchTree()
		{
			
		}
		Pair<K,E>* find(K &theKey) const
		{//返回匹配数对的指针，若无匹配则返回null 
			binaryTreeNode< Pair<K,E> > *p=BT::root; 
			while(p!=NULL)
			{
				if(theKey<p->element.first)   
				   p=p->left;     //继续搜索左子树 
				else 
				   if(theKey>p->element.first)
				     p=p->right;
				   else
				    return &(p->element);  //找到了匹配的元素 
			}
			return NULL;
		}
		void insert(Pair<K,E> &thePair)
		{//插入thePair，如果存在与其关键字相同的数对，则覆盖 
		  //寻找插入位置
		   binaryTreeNode< Pair<K,E> > *p=BT::root,
		                               *pp=NULL;  //pp is the parent of p and trails p 
		   while(p!=NULL)
		   {
		   	 pp=p;
		   	 if(thePair.first<p->element.first)
		   	   p=p->left;
		   	else 
			   if(thePair.first>p->element.first)
			     p=p->right;
			   else   //找到关键字相同的数对，覆盖 
			   {
			   	  p->element.second=thePair.second;
			   	  return;
			   }  
		   }
		   //没有找到数对，那么在插入位置建立一个新节点，然后与pp连接
		    binaryTreeNode< Pair<K,E> > *newNode=new binaryTreeNode< Pair<K,E> >(thePair);
		    if(BT::root!=NULL)  //树不为空 
		    {
		    	if(thePair.first<pp->element.first)  //thepair的关键字比pp小，放左子树 
			      pp->left=newNode;
			    else
			      pp->right=newNode;
			}
		    else 
		      BT::root=newNode;
		   BT::treeSize++;
		}
		void erase(K theKey)
		{//删除关键字是theKey的数对
		   binaryTreeNode< Pair<K,E> > *p=BT::root,
		                               *pp=NULL;   
		   while(p!=NULL)
		   {
		   	 binaryTreeNode< Pair<K,E> > *t=p;
		   	 if(theKey<p->element.first)
		   	   p=p->left;
		   	 else 
			 {
				 if(theKey>p->element.first)
			       p=p->right;
			     else   //找到关键字相同的数对
			       break;
		     }
			 pp=t;
		   }
/*		   while (p != NULL && p->element.first != theKey)
   {// move to a child of p
      pp = p;
      if (theKey < p->element.first)
         p = p->left;
      else
         p = p->right;
   }*/
	   
	   
	   if(p==NULL) return;  //没有匹配数对
	   cout<<endl<<"the p's element is:'"<<p->element<<endl<<endl;
		   //下面需要重构树的结构 
		   //当p有两个孩子时 
		   if(p->left!=NULL&&p->right!=NULL)
		   {//找到左子树中最大元素
		       binaryTreeNode< Pair<K,E> > *s=p->left,
		                                   *ps=p;
		       while(s->right!=NULL)
		       {//跳出循环后s就指向了左子树中最大元素 
		       	 ps=s;
		       	 s=s->right;
			   }
		   	 
		   	 binaryTreeNode< Pair<K,E> > *q=new binaryTreeNode< Pair<K,E> >(s->element,p->left,p->right);
			   if(pp==NULL)
			     BT::root=q;
			   else{//连接pp与q 
			   	if(p==pp->left)
			   	  pp->left=q;
			   	else pp->right=q;  
			   }
			   if(ps==p) pp=q; //需要单独讨论p的左子树是否只有一个元素，因为如果ps=old p，会被删除的。 
			   else  pp=ps;
			   delete p;  p=NULL; cout<<"p="<<p<<endl;  //貌似删除根本就不成功？
			   p=s;
		   	 
		   }
		   
		   //当p只有一个孩子或者是叶节点时
		    binaryTreeNode< Pair<K,E> > *c;
		    if(p->left!=NULL)    //让c指向p非空的孩子 
		      c=p->left;
		    else 
		      c=p->right;
		      
		   if(p==BT::root) c=BT::root;
		   else
		   {//找出p是pp的哪个孩子
		      if(p==pp->left) 
		        pp->left=c;
		      if(p==pp->right)
		        pp->right=c;
		   }
			delete p;
			BT::treeSize--;
		}
		void ascend()
		{//按升序输出所有数对，有搜索二叉树的定义知中序遍历即可 
			BT::inOrder();
		}
	private:
		//binaryTreeNode< Pair<K,E> > *root;  //指向根节点的指针 ,不需要这么写了，因为继承了二叉树 
		//int treeSize;     //树中的元素个数 
};
