
#pragma once
#include<iostream>
#include"������.h"
#include"pair.h"
using namespace std;

template<class K,class E>
class indexedBinarySearchTree:public linkedBinaryTree<Pair<K, E> >
{
	public:
		typedef linkedBinaryTree< Pair<K, E> > BT;
		indexedBinarySearchTree() 
		{ 
		   
		}
		Pair<K,E>* find(int index) const
		{//2��?����?��??a??��?��?��???D��?D��?�̨�index+1�䨮?a?? 
			binaryTreeNode< Pair<K,E> > *p=BT::root; 
			while(p!=NULL)
			{
				cout<<"compare "<<index<<" with pair< "<<p->element<<" >'s leftSize:"<<p->element.leftSize<<endl;
				if(index<p->element.leftSize)   
				   p=p->left;     //?��D????�¡����������� 
				else 
				   if(index>p->element.leftSize)
				    {
				    	index=index - (p->element.leftSize+1);  //?��D?index 
						p=p->right;
					 } 
				   else
				    return &(p->element);  //?����?��??��??��??a?? 
			}
			return NULL;
		}
		Pair<K,E>* find(K &theKey,bool flag) const
		{//����???��??��y??��?????��?��??T?��???������??null 
			binaryTreeNode< Pair<K,E> > *p=BT::root; 
			while(p!=NULL)
			{
				cout<<"compare "<<theKey<<" with pair< "<<p->element<<">"<<endl;
				if(theKey<p->element.first)   
				   p=p->left;     //?��D????�¡����������� 
				else 
				   if(theKey>p->element.first)
				     p=p->right;
				   else
				    return &(p->element);  //?����?��??��??��??a?? 
			}
			return NULL;
		}
		void insert(Pair<K,E> &thePair)
		{//��a?��D??��?��2?��??����??��??��?��?leftSize?�� 
			binaryTreeNode< Pair<K,E> > *p=BT::root,
		                               *pp=NULL;  //pp is the parent of p and trails p 
		   while(p!=NULL)
		   {
		   	 pp=p;
		   	 if(thePair.first<p->element.first)
		   	 {  p->element.leftSize++; p=p->left;  }  //2?��??����?�����������¨�����a?��D?leftSize 
		   	else 
			   if(thePair.first>p->element.first)
			     p=p->right;
			   else   //?����?1??����??����?��?��y??��??2??
			   {
			   	  p->element.second=thePair.second;
			   	  return;
			   }  
		   }
		   //??��D?����?��y??��????��?��2?��??????�����騰???D??����?��?��?o����?pp��??��
		    binaryTreeNode< Pair<K,E> > *newNode=new binaryTreeNode< Pair<K,E> >(thePair);
		    if(BT::root!=NULL)  //����2??a?? 
		    {
		    	if(thePair.first < pp->element.first)  //thepair��?1??����?����ppD?��?��?������������ 
			      pp->left=newNode;  
			    else
			      pp->right=newNode;
			}
		    else 
		      BT::root=newNode;
		   BT::treeSize++;
		}
		void erase(int index)
		{//���?�¨�y��?3y 
			binaryTreeNode< Pair<K,E> > *p=BT::root,
		                                *pp=NULL;   
		    while(p!=NULL && p->element.leftSize != index)
			{
				pp=p;
				if(index<=p->element.leftSize)   
				   p=p->left;     //?��D????�¡����������� 
				else 
			    {
				    index=index - (p->element.leftSize+1);  //?��D?index 
					p=p->right;
				} 
			}
		   if(p==NULL) 
		   {
		   	  cerr<<"no such index"<<endl;
		      return;  //??��D?��??��y??
	       }
	       else
	       {//?��?��?����?��???��|��y??��??��?��D?��?����?����?p��?leftSize?�� 
	       	  binaryTreeNode< Pair<K,E> > *t=BT::root;
	       	  while(t!=NULL)
	       	  {
	       	  	 if(index<=t->element.leftSize)   
				 {//?��D????�¡�����������   
				     t->element.leftSize--;
				     t=t->left;
				 }
				else 
				   if(index>t->element.leftSize)
                   t=t->right;
				   else
				        break;
			  }
		   }
	       
		   //????D����a??11���¦�??��11��?��??t2????�¨���2�����¨�����??����? 
		   //�̡�p��D��???o��������� 
		   if(p->left!=NULL&&p->right!=NULL)
		   {//?����?������������?D��?�䨮?a??
		       binaryTreeNode< Pair<K,E> > *s=p->left,
		                                   *ps=p;
		       while(s->right!=NULL)
		       {//��?3??-?��o��s?��???����?������������?D��?�䨮?a?? 
		       	 ps=s;
		       	 s=s->right;
			   }
			   
			   //??��?�䨮?a??s��?��?p��?��?2?��??���̣���?��??����??-??��?��a��??����|o?����?a��?��? 
			   binaryTreeNode< Pair<K,E> > *q=new binaryTreeNode< Pair<K,E> >(s->element,p->left,p->right);
			   if(pp==NULL)
			     BT::root=q;
			   else{//��??��pp��?q 
			   	if(p==pp->left)
			   	  pp->left=q;
			   	else pp->right=q;  
			   }
			   if(ps==p) pp=q; //D����a�̣�?����???p��?�����������¨�?��???��D��????a??��?����?a��?1?ps=old p��??����?��?3y��??�� 
			   else  pp=ps;
			   delete p;  cout<<"p="<<p<<endl;  //?2??��?3y?����??��2?3��1|��?
			   p=s;
		   	   
		   }//?a����p��??-???����a��?3y��?�����������¡�?�䨮?a?? 
		   
		   //�̡�p??��D��???o�����?��??��?��??����?����
		    	 binaryTreeNode< Pair<K,E> > *c;
		         if(p->left!=NULL)    //��?c???��p��???��?o����� 
		           c=p->left;
		         else 
		           c=p->right;
		      
		         if(p==BT::root) c=BT::root;
		         else
		         {//?��3?p��?pp��?????o�����
		            if(p==pp->left) 
		              pp->left=c;
		            if(p==pp->right)
		              pp->right=c;
		         }	
				 delete p;  cout<<"p="<<p<<endl; 
			BT::treeSize--;
		}
		void erase(K theKey,bool flag)
		{//��?3y1??����?��?theKey��?��y??
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
	   	   if(p==NULL) return;  //??��D?��??��y??
	   	   else
	       {//?��?��?����?��???��|��y??��??��?��D?��?����?����?p��?leftSize?�� 
		      cout<<endl<<"the p's element is:'"<<p->element<<endl<<endl;
	       	  binaryTreeNode< Pair<K,E> > *t=BT::root;
	       	  while(t!=NULL)
	       	  {
	       	  	 if(theKey<t->element.first)   
				 {//?��D????�¡�����������   
				     t->element.leftSize--;
				     t=t->left;
				 }
				else 
				   if(theKey>t->element.first)
                   t=t->right;
				   else
				        break;
			  } 
		   }
		   
		   //????D����a??11���¦�??��11 
		   //�̡�p��D��???o��������� 
		   if(p->left!=NULL&&p->right!=NULL)
		   {//?����?������������?D��?�䨮?a??
		       binaryTreeNode< Pair<K,E> > *s=p->left,
		                                   *ps=p;
		       while(s->right!=NULL)
		       {//��?3??-?��o��s?��???����?������������?D��?�䨮?a?? 
		       	 ps=s;
		       	 s=s->right;
			   }
		   	 
		   	 binaryTreeNode< Pair<K,E> > *q=new binaryTreeNode< Pair<K,E> >(s->element,p->left,p->right);
			   if(pp==NULL)
			     BT::root=q;
			   else{//��??��pp��?q 
			   	if(p==pp->left)
			   	  pp->left=q;
			   	else pp->right=q;  
			   }
			   if(ps==p) pp=q; //D����a�̣�?����???p��?�����������¨�?��???��D��????a??��?����?a��?1?ps=old p��??����?��?3y��??�� 
			   else  pp=ps;
			   delete p;  p=NULL; cout<<"p="<<p<<endl;  //?2??��?3y?����??��2?3��1|��?
			   p=s;
		   	 
		   }
		   
		   //�̡�p??��D��???o�����?��??��?��??����?����
		    binaryTreeNode< Pair<K,E> > *c;
		    if(p->left!=NULL)    //��?c???��p��???��?o����� 
		      c=p->left;
		    else 
		      c=p->right;
		      
		   if(p==BT::root) c=BT::root;
		   else
		   {//?��3?p��?pp��?????o�����
		      if(p==pp->left) 
		        pp->left=c;
		      if(p==pp->right)
		        pp->right=c;
		   }
			delete p;
			BT::treeSize--;
		}
		void ascend()
		{//��??����D1??����?��yD����?3? 
			BT::inOrder();
		}
	
};
