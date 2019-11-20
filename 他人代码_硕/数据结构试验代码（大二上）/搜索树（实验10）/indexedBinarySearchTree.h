#pragma once
#include<iostream>
#include"二叉树.h"
#include"pair.h"
using namespace std;
//要注意所有插入、删除操作都要先搜索对应节点再重头走一遍更新leftSize的值，因为可能存在删除不成功和插入是覆盖相同关键字节点的情况 
//这里写的其实还不够好，leftSize应该是放在treeNode里面，而不是treeNode的element里面 
template<class K,class E>
class indexedBinarySearchTree:public linkedBinaryTree<Pair<K, E> >
{
	public:
		typedef linkedBinaryTree< Pair<K, E> > BT;
		indexedBinarySearchTree() 
		{ 
		   
		}
		Pair<K,E>* find(int index) const
		{//查找到的元素是字典排序中的第index+1大元素 
			binaryTreeNode< Pair<K,E> > *p=BT::root; 
			while(p!=NULL)
			{
				cout<<"compare "<<index<<" with pair< "<<p->element<<" >'s leftSize:"<<p->leftSize<<endl;
				if(index<p->leftSize)   
				   p=p->left;     //继续搜索左子树 
				else 
				   if(index>p->leftSize)
				    {
				    	index=index - (p->leftSize+1);  //更新index 
						p=p->right;
					 } 
				   else
				    return &(p->element);  //找到了匹配的元素 
			}
			return NULL;
		}
		Pair<K,E>* find(K &theKey,bool flag) const
		{//返回匹配数对的指针，若无匹配则返回null 
			binaryTreeNode< Pair<K,E> > *p=BT::root; 
			while(p!=NULL)
			{
				cout<<"compare "<<theKey<<" with pair< "<<p->element<<">"<<endl;
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
		{//要更新根至插入节点路径上的leftSize值 
			binaryTreeNode< Pair<K,E> > *p=BT::root,
		                               *pp=NULL;  //pp is the parent of p and trails p 
		   while(p!=NULL)
		   {
		   	 pp=p;
		   	 if(thePair.first<p->element.first)
		   	     p=p->left;                     //第一步搜索的时候不需要修改leftSize的值 
		   	else 
			   if(thePair.first>p->element.first)
			     p=p->right;
			   else   //找到关键字相同的数对，覆盖
			   {
			   	  p->element.second=thePair.second;
			   	  return;
			   }  
		   }
		   //没有找到数对，先更新一遍leftSize的值 
		   binaryTreeNode< Pair<K,E> > *t=BT::root
		   while(t!=NULL)
	       	  {
	       	  	 if(thePair.first<t->element.first)   
				 {//继续搜索左子树   
				     t->leftSize++;  //插入它的左子树时要更新leftSize 
				     t=t->left;
				 }
				else 
				   if(thePair.first>t->element.first)
                   t=t->right;
				   else
				        break;
			  }
		   }
		   
		   //那么在插入位置建立一个新节点，然后与pp连接
		    binaryTreeNode< Pair<K,E> > *newNode=new binaryTreeNode< Pair<K,E> >(thePair);
		    if(BT::root!=NULL)  //树不为空 
		    {
		    	if(thePair.first < pp->element.first)  //thepair的关键字比pp小，放左子树 
			      pp->left=newNode;  
			    else
			      pp->right=newNode;
			}
		    else 
		      BT::root=newNode;
		   BT::treeSize++;
		}
		void erase(int index)
		{//按索引删除 
			binaryTreeNode< Pair<K,E> > *p=BT::root,
		                                *pp=NULL;   
		    while(p!=NULL && p->leftSize != index)
			{
				pp=p;
				if(index<p->leftSize)   
				   p=p->left;     //继续搜索左子树 
				else 
			    {
				    index=index - (p->leftSize+1);  //更新index 
					p=p->right;
				} 
			}
		   if(p==NULL) 
		   {
		   	  cerr<<"未找到匹配数对！"<<endl;
		      return;  //没有匹配数对
	       }
	       else
	       {//说明找到了对应数对，先更新一遍根到p的leftSize值 
	       	  binaryTreeNode< Pair<K,E> > *t=BT::root;
	       	  while(t!=NULL)
	       	  {
	       	  	 if(p->element.first<t->element.first)  
				 {//继续搜索左子树   
				     t->leftSize--;
				     t=t->left;
				 }
				else 
				   if(p->element.first>t->element.first)
                   t=t->right;
				   else
				        break;
			  } 
		   }
	       
		   //下面需要重构树的结构，与二叉搜索树操作完全相同 
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
			   
			   //将最大元素s移到p，但不是简单的移动，画个示意图就挺好理解的了 
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
			   delete p;  cout<<"p="<<p<<endl;  //貌似删除根本就不成功？
			   p=s;
		   	   
		   }//这时p已经指向要删除的左子树最大元素 
		   
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
				 delete p;  cout<<"p="<<p<<endl; 
			BT::treeSize--;
		}
		void erase(K theKey,bool flag)
		{//删除关键字是theKey的数对
		   binaryTreeNode< Pair<K,E> > *p=BT::root,
		                               *pp=NULL;   

		   while (p != NULL && p->element.first != theKey)
           {// move to a child of p
               pp = p;
               if (theKey < p->element.first)
                  p = p->left;
               else
                  p = p->right;
           }
	   	   if(p==NULL) return;  //没有匹配数对
	   	   else
	       {//说明找到了对应数对，先更新一遍根到p的leftSize值 
		      cout<<endl<<"the p's element is:'"<<p->element<<endl<<endl;
	       	  binaryTreeNode< Pair<K,E> > *t=BT::root;
	       	  while(t!=NULL)
	       	  {
	       	  	 if(theKey<t->element.first)   
				 {//继续搜索左子树   
				     t->leftSize--;
				     t=t->left;
				 }
				else 
				   if(theKey>t->element.first)
                   t=t->right;
				   else
				        break;
			  } 
		   }
		   
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
		{//把所有关键字升序输出 
			BT::inOrder();
		}
	
};
