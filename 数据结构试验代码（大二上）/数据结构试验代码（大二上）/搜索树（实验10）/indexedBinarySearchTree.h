#pragma once
#include<iostream>
#include"������.h"
#include"pair.h"
using namespace std;
//Ҫע�����в��롢ɾ��������Ҫ��������Ӧ�ڵ�����ͷ��һ�����leftSize��ֵ����Ϊ���ܴ���ɾ�����ɹ��Ͳ����Ǹ�����ͬ�ؼ��ֽڵ����� 
//����д����ʵ�������ã�leftSizeӦ���Ƿ���treeNode���棬������treeNode��element���� 
template<class K,class E>
class indexedBinarySearchTree:public linkedBinaryTree<Pair<K, E> >
{
	public:
		typedef linkedBinaryTree< Pair<K, E> > BT;
		indexedBinarySearchTree() 
		{ 
		   
		}
		Pair<K,E>* find(int index) const
		{//���ҵ���Ԫ�����ֵ������еĵ�index+1��Ԫ�� 
			binaryTreeNode< Pair<K,E> > *p=BT::root; 
			while(p!=NULL)
			{
				cout<<"compare "<<index<<" with pair< "<<p->element<<" >'s leftSize:"<<p->leftSize<<endl;
				if(index<p->leftSize)   
				   p=p->left;     //�������������� 
				else 
				   if(index>p->leftSize)
				    {
				    	index=index - (p->leftSize+1);  //����index 
						p=p->right;
					 } 
				   else
				    return &(p->element);  //�ҵ���ƥ���Ԫ�� 
			}
			return NULL;
		}
		Pair<K,E>* find(K &theKey,bool flag) const
		{//����ƥ�����Ե�ָ�룬����ƥ���򷵻�null 
			binaryTreeNode< Pair<K,E> > *p=BT::root; 
			while(p!=NULL)
			{
				cout<<"compare "<<theKey<<" with pair< "<<p->element<<">"<<endl;
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
		{//Ҫ���¸�������ڵ�·���ϵ�leftSizeֵ 
			binaryTreeNode< Pair<K,E> > *p=BT::root,
		                               *pp=NULL;  //pp is the parent of p and trails p 
		   while(p!=NULL)
		   {
		   	 pp=p;
		   	 if(thePair.first<p->element.first)
		   	     p=p->left;                     //��һ��������ʱ����Ҫ�޸�leftSize��ֵ 
		   	else 
			   if(thePair.first>p->element.first)
			     p=p->right;
			   else   //�ҵ��ؼ�����ͬ�����ԣ�����
			   {
			   	  p->element.second=thePair.second;
			   	  return;
			   }  
		   }
		   //û���ҵ����ԣ��ȸ���һ��leftSize��ֵ 
		   binaryTreeNode< Pair<K,E> > *t=BT::root
		   while(t!=NULL)
	       	  {
	       	  	 if(thePair.first<t->element.first)   
				 {//��������������   
				     t->leftSize++;  //��������������ʱҪ����leftSize 
				     t=t->left;
				 }
				else 
				   if(thePair.first>t->element.first)
                   t=t->right;
				   else
				        break;
			  }
		   }
		   
		   //��ô�ڲ���λ�ý���һ���½ڵ㣬Ȼ����pp����
		    binaryTreeNode< Pair<K,E> > *newNode=new binaryTreeNode< Pair<K,E> >(thePair);
		    if(BT::root!=NULL)  //����Ϊ�� 
		    {
		    	if(thePair.first < pp->element.first)  //thepair�Ĺؼ��ֱ�ppС���������� 
			      pp->left=newNode;  
			    else
			      pp->right=newNode;
			}
		    else 
		      BT::root=newNode;
		   BT::treeSize++;
		}
		void erase(int index)
		{//������ɾ�� 
			binaryTreeNode< Pair<K,E> > *p=BT::root,
		                                *pp=NULL;   
		    while(p!=NULL && p->leftSize != index)
			{
				pp=p;
				if(index<p->leftSize)   
				   p=p->left;     //�������������� 
				else 
			    {
				    index=index - (p->leftSize+1);  //����index 
					p=p->right;
				} 
			}
		   if(p==NULL) 
		   {
		   	  cerr<<"δ�ҵ�ƥ�����ԣ�"<<endl;
		      return;  //û��ƥ������
	       }
	       else
	       {//˵���ҵ��˶�Ӧ���ԣ��ȸ���һ�����p��leftSizeֵ 
	       	  binaryTreeNode< Pair<K,E> > *t=BT::root;
	       	  while(t!=NULL)
	       	  {
	       	  	 if(p->element.first<t->element.first)  
				 {//��������������   
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
	       
		   //������Ҫ�ع����Ľṹ�������������������ȫ��ͬ 
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
			   
			   //�����Ԫ��s�Ƶ�p�������Ǽ򵥵��ƶ�������ʾ��ͼ��ͦ�������� 
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
			   delete p;  cout<<"p="<<p<<endl;  //ò��ɾ�������Ͳ��ɹ���
			   p=s;
		   	   
		   }//��ʱp�Ѿ�ָ��Ҫɾ�������������Ԫ�� 
		   
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
				 delete p;  cout<<"p="<<p<<endl; 
			BT::treeSize--;
		}
		void erase(K theKey,bool flag)
		{//ɾ���ؼ�����theKey������
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
	   	   if(p==NULL) return;  //û��ƥ������
	   	   else
	       {//˵���ҵ��˶�Ӧ���ԣ��ȸ���һ�����p��leftSizeֵ 
		      cout<<endl<<"the p's element is:'"<<p->element<<endl<<endl;
	       	  binaryTreeNode< Pair<K,E> > *t=BT::root;
	       	  while(t!=NULL)
	       	  {
	       	  	 if(theKey<t->element.first)   
				 {//��������������   
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
		{//�����йؼ���������� 
			BT::inOrder();
		}
	
};
