#pragma once
#include<iostream>
#include"������.h"
#include"pair.h"

using namespace std;

template<class K,class E>
class binarySearchTree :public linkedBinaryTree<Pair<K, E> >
{//������������Ԫ����С�����󣬸����� 
	public:
	typedef linkedBinaryTree< Pair<K, E> > BT;
		binarySearchTree()
		{
			
		}
		Pair<K,E>* find(K &theKey) const
		{//����ƥ�����Ե�ָ�룬����ƥ���򷵻�null 
			binaryTreeNode< Pair<K,E> > *p=BT::root; 
			while(p!=NULL)
			{
				if(theKey<p->element.first)   
				   p=p->left;     //�������������� 
				else 
				   if(theKey>p->element.first)
				     p=p->right;
				   else
				    return &(p->element);  //�ҵ���ƥ���Ԫ�� 
			}
			return NULL;
		}
		void insert(Pair<K,E> &thePair)
		{//����thePair�������������ؼ�����ͬ�����ԣ��򸲸� 
		  //Ѱ�Ҳ���λ��
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
			   else   //�ҵ��ؼ�����ͬ�����ԣ����� 
			   {
			   	  p->element.second=thePair.second;
			   	  return;
			   }  
		   }
		   //û���ҵ����ԣ���ô�ڲ���λ�ý���һ���½ڵ㣬Ȼ����pp����
		    binaryTreeNode< Pair<K,E> > *newNode=new binaryTreeNode< Pair<K,E> >(thePair);
		    if(BT::root!=NULL)  //����Ϊ�� 
		    {
		    	if(thePair.first<pp->element.first)  //thepair�Ĺؼ��ֱ�ppС���������� 
			      pp->left=newNode;
			    else
			      pp->right=newNode;
			}
		    else 
		      BT::root=newNode;
		   BT::treeSize++;
		}
		void erase(K theKey)
		{//ɾ���ؼ�����theKey������
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
			     else   //�ҵ��ؼ�����ͬ������
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
	   
	   
	   if(p==NULL) return;  //û��ƥ������
	   cout<<endl<<"the p's element is:'"<<p->element<<endl<<endl;
		   //������Ҫ�ع����Ľṹ 
		   //��p����������ʱ 
		   if(p->left!=NULL&&p->right!=NULL)
		   {//�ҵ������������Ԫ��
		       binaryTreeNode< Pair<K,E> > *s=p->left,
		                                   *ps=p;
		       while(s->right!=NULL)
		       {//����ѭ����s��ָ���������������Ԫ�� 
		       	 ps=s;
		       	 s=s->right;
			   }
		   	 
		   	 binaryTreeNode< Pair<K,E> > *q=new binaryTreeNode< Pair<K,E> >(s->element,p->left,p->right);
			   if(pp==NULL)
			     BT::root=q;
			   else{//����pp��q 
			   	if(p==pp->left)
			   	  pp->left=q;
			   	else pp->right=q;  
			   }
			   if(ps==p) pp=q; //��Ҫ��������p���������Ƿ�ֻ��һ��Ԫ�أ���Ϊ���ps=old p���ᱻɾ���ġ� 
			   else  pp=ps;
			   delete p;  p=NULL; cout<<"p="<<p<<endl;  //ò��ɾ�������Ͳ��ɹ���
			   p=s;
		   	 
		   }
		   
		   //��pֻ��һ�����ӻ�����Ҷ�ڵ�ʱ
		    binaryTreeNode< Pair<K,E> > *c;
		    if(p->left!=NULL)    //��cָ��p�ǿյĺ��� 
		      c=p->left;
		    else 
		      c=p->right;
		      
		   if(p==BT::root) c=BT::root;
		   else
		   {//�ҳ�p��pp���ĸ�����
		      if(p==pp->left) 
		        pp->left=c;
		      if(p==pp->right)
		        pp->right=c;
		   }
			delete p;
			BT::treeSize--;
		}
		void ascend()
		{//����������������ԣ��������������Ķ���֪����������� 
			BT::inOrder();
		}
	private:
		//binaryTreeNode< Pair<K,E> > *root;  //ָ����ڵ��ָ�� ,����Ҫ��ôд�ˣ���Ϊ�̳��˶����� 
		//int treeSize;     //���е�Ԫ�ظ��� 
};
