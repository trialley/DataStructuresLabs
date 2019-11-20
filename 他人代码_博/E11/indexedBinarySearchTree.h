
#pragma once
#include<iostream>
#include"¶þ²æÊ÷.h"
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
		{//2¨¦?¨°¦Ì?¦Ì??a??¨º?¡Á?¦Ì???D¨°?D¦Ì?¦Ì¨²index+1¡ä¨®?a?? 
			binaryTreeNode< Pair<K,E> > *p=BT::root; 
			while(p!=NULL)
			{
				cout<<"compare "<<index<<" with pair< "<<p->element<<" >'s leftSize:"<<p->element.leftSize<<endl;
				if(index<p->element.leftSize)   
				   p=p->left;     //?¨¬D????¡Â¡Á¨®¡Á¨®¨º¡Â 
				else 
				   if(index>p->element.leftSize)
				    {
				    	index=index - (p->element.leftSize+1);  //?¨¹D?index 
						p=p->right;
					 } 
				   else
				    return &(p->element);  //?¨°¦Ì?¨¢??£¤??¦Ì??a?? 
			}
			return NULL;
		}
		Pair<K,E>* find(K &theKey,bool flag) const
		{//¡¤¦Ì???£¤??¨ºy??¦Ì?????¡ê?¨¨??T?£¤???¨°¡¤¦Ì??null 
			binaryTreeNode< Pair<K,E> > *p=BT::root; 
			while(p!=NULL)
			{
				cout<<"compare "<<theKey<<" with pair< "<<p->element<<">"<<endl;
				if(theKey<p->element.first)   
				   p=p->left;     //?¨¬D????¡Â¡Á¨®¡Á¨®¨º¡Â 
				else 
				   if(theKey>p->element.first)
				     p=p->right;
				   else
				    return &(p->element);  //?¨°¦Ì?¨¢??£¤??¦Ì??a?? 
			}
			return NULL;
		}
		void insert(Pair<K,E> &thePair)
		{//¨°a?¨¹D??¨´?¨¢2?¨¨??¨²¦Ì??¡¤??¨¦?¦Ì?leftSize?¦Ì 
			binaryTreeNode< Pair<K,E> > *p=BT::root,
		                               *pp=NULL;  //pp is the parent of p and trails p 
		   while(p!=NULL)
		   {
		   	 pp=p;
		   	 if(thePair.first<p->element.first)
		   	 {  p->element.leftSize++; p=p->left;  }  //2?¨¨??¨¹¦Ì?¡Á¨®¡Á¨®¨º¡Â¨º¡À¨°a?¨¹D?leftSize 
		   	else 
			   if(thePair.first>p->element.first)
			     p=p->right;
			   else   //?¨°¦Ì?1??¨¹¡Á??¨¤¨ª?¦Ì?¨ºy??¡ê??2??
			   {
			   	  p->element.second=thePair.second;
			   	  return;
			   }  
		   }
		   //??¨®D?¨°¦Ì?¨ºy??¡ê????¡ä?¨²2?¨¨??????¡§¨¢¡é¨°???D??¨²¦Ì?¡ê?¨¨?o¨®¨®?pp¨¢??¨®
		    binaryTreeNode< Pair<K,E> > *newNode=new binaryTreeNode< Pair<K,E> >(thePair);
		    if(BT::root!=NULL)  //¨º¡Â2??a?? 
		    {
		    	if(thePair.first < pp->element.first)  //thepair¦Ì?1??¨¹¡Á?¡À¨¨ppD?¡ê?¡¤?¡Á¨®¡Á¨®¨º¡Â 
			      pp->left=newNode;  
			    else
			      pp->right=newNode;
			}
		    else 
		      BT::root=newNode;
		   BT::treeSize++;
		}
		void erase(int index)
		{//¡ã¡ä?¡Â¨°y¨¦?3y 
			binaryTreeNode< Pair<K,E> > *p=BT::root,
		                                *pp=NULL;   
		    while(p!=NULL && p->element.leftSize != index)
			{
				pp=p;
				if(index<=p->element.leftSize)   
				   p=p->left;     //?¨¬D????¡Â¡Á¨®¡Á¨®¨º¡Â 
				else 
			    {
				    index=index - (p->element.leftSize+1);  //?¨¹D?index 
					p=p->right;
				} 
			}
		   if(p==NULL) 
		   {
		   	  cerr<<"no such index"<<endl;
		      return;  //??¨®D?£¤??¨ºy??
	       }
	       else
	       {//?¦Ì?¡Â?¨°¦Ì?¨¢???¨®|¨ºy??¡ê??¨¨?¨¹D?¨°?¡À¨¦?¨´¦Ì?p¦Ì?leftSize?¦Ì 
	       	  binaryTreeNode< Pair<K,E> > *t=BT::root;
	       	  while(t!=NULL)
	       	  {
	       	  	 if(index<=t->element.leftSize)   
				 {//?¨¬D????¡Â¡Á¨®¡Á¨®¨º¡Â   
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
	       
		   //????D¨¨¨°a??11¨º¡Â¦Ì??¨¢11¡ê?¨®??t2????¡Â¨º¡Â2¨´¡Á¡Â¨ª¨º¨¨??¨¤¨ª? 
		   //¦Ì¡Àp¨®D¨¢???o¡é¡Á¨®¨º¡À 
		   if(p->left!=NULL&&p->right!=NULL)
		   {//?¨°¦Ì?¡Á¨®¡Á¨®¨º¡Â?D¡Á?¡ä¨®?a??
		       binaryTreeNode< Pair<K,E> > *s=p->left,
		                                   *ps=p;
		       while(s->right!=NULL)
		       {//¨¬?3??-?¡¤o¨®s?¨ª???¨°¨¢?¡Á¨®¡Á¨®¨º¡Â?D¡Á?¡ä¨®?a?? 
		       	 ps=s;
		       	 s=s->right;
			   }
			   
			   //??¡Á?¡ä¨®?a??s¨°?¦Ì?p¡ê?¦Ì?2?¨º??¨°¦Ì£¤¦Ì?¨°??¡¥¡ê??-??¨º?¨°a¨ª??¨ª¨ª|o?¨¤¨ª?a¦Ì?¨¢? 
			   binaryTreeNode< Pair<K,E> > *q=new binaryTreeNode< Pair<K,E> >(s->element,p->left,p->right);
			   if(pp==NULL)
			     BT::root=q;
			   else{//¨¢??¨®pp¨®?q 
			   	if(p==pp->left)
			   	  pp->left=q;
			   	else pp->right=q;  
			   }
			   if(ps==p) pp=q; //D¨¨¨°a¦Ì£¤?¨¤¨¬???p¦Ì?¡Á¨®¡Á¨®¨º¡Â¨º?¡¤???¨®D¨°????a??¡ê?¨°¨°?a¨¨?1?ps=old p¡ê??¨¢¡À?¨¦?3y¦Ì??¡ê 
			   else  pp=ps;
			   delete p;  cout<<"p="<<p<<endl;  //?2??¨¦?3y?¨´¡À??¨ª2?3¨¦1|¡ê?
			   p=s;
		   	   
		   }//?a¨º¡Àp¨°??-???¨°¨°a¨¦?3y¦Ì?¡Á¨®¡Á¨®¨º¡Â¡Á?¡ä¨®?a?? 
		   
		   //¦Ì¡Àp??¨®D¨°???o¡é¡Á¨®?¨°??¨º?¨°??¨²¦Ì?¨º¡À
		    	 binaryTreeNode< Pair<K,E> > *c;
		         if(p->left!=NULL)    //¨¨?c???¨°p¡¤???¦Ì?o¡é¡Á¨® 
		           c=p->left;
		         else 
		           c=p->right;
		      
		         if(p==BT::root) c=BT::root;
		         else
		         {//?¨°3?p¨º?pp¦Ì?????o¡é¡Á¨®
		            if(p==pp->left) 
		              pp->left=c;
		            if(p==pp->right)
		              pp->right=c;
		         }	
				 delete p;  cout<<"p="<<p<<endl; 
			BT::treeSize--;
		}
		void erase(K theKey,bool flag)
		{//¨¦?3y1??¨¹¡Á?¨º?theKey¦Ì?¨ºy??
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
	   	   if(p==NULL) return;  //??¨®D?£¤??¨ºy??
	   	   else
	       {//?¦Ì?¡Â?¨°¦Ì?¨¢???¨®|¨ºy??¡ê??¨¨?¨¹D?¨°?¡À¨¦?¨´¦Ì?p¦Ì?leftSize?¦Ì 
		      cout<<endl<<"the p's element is:'"<<p->element<<endl<<endl;
	       	  binaryTreeNode< Pair<K,E> > *t=BT::root;
	       	  while(t!=NULL)
	       	  {
	       	  	 if(theKey<t->element.first)   
				 {//?¨¬D????¡Â¡Á¨®¡Á¨®¨º¡Â   
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
		   
		   //????D¨¨¨°a??11¨º¡Â¦Ì??¨¢11 
		   //¦Ì¡Àp¨®D¨¢???o¡é¡Á¨®¨º¡À 
		   if(p->left!=NULL&&p->right!=NULL)
		   {//?¨°¦Ì?¡Á¨®¡Á¨®¨º¡Â?D¡Á?¡ä¨®?a??
		       binaryTreeNode< Pair<K,E> > *s=p->left,
		                                   *ps=p;
		       while(s->right!=NULL)
		       {//¨¬?3??-?¡¤o¨®s?¨ª???¨°¨¢?¡Á¨®¡Á¨®¨º¡Â?D¡Á?¡ä¨®?a?? 
		       	 ps=s;
		       	 s=s->right;
			   }
		   	 
		   	 binaryTreeNode< Pair<K,E> > *q=new binaryTreeNode< Pair<K,E> >(s->element,p->left,p->right);
			   if(pp==NULL)
			     BT::root=q;
			   else{//¨¢??¨®pp¨®?q 
			   	if(p==pp->left)
			   	  pp->left=q;
			   	else pp->right=q;  
			   }
			   if(ps==p) pp=q; //D¨¨¨°a¦Ì£¤?¨¤¨¬???p¦Ì?¡Á¨®¡Á¨®¨º¡Â¨º?¡¤???¨®D¨°????a??¡ê?¨°¨°?a¨¨?1?ps=old p¡ê??¨¢¡À?¨¦?3y¦Ì??¡ê 
			   else  pp=ps;
			   delete p;  p=NULL; cout<<"p="<<p<<endl;  //?2??¨¦?3y?¨´¡À??¨ª2?3¨¦1|¡ê?
			   p=s;
		   	 
		   }
		   
		   //¦Ì¡Àp??¨®D¨°???o¡é¡Á¨®?¨°??¨º?¨°??¨²¦Ì?¨º¡À
		    binaryTreeNode< Pair<K,E> > *c;
		    if(p->left!=NULL)    //¨¨?c???¨°p¡¤???¦Ì?o¡é¡Á¨® 
		      c=p->left;
		    else 
		      c=p->right;
		      
		   if(p==BT::root) c=BT::root;
		   else
		   {//?¨°3?p¨º?pp¦Ì?????o¡é¡Á¨®
		      if(p==pp->left) 
		        pp->left=c;
		      if(p==pp->right)
		        pp->right=c;
		   }
			delete p;
			BT::treeSize--;
		}
		void ascend()
		{//¡ã??¨´¨®D1??¨¹¡Á?¨¦yD¨°¨º?3? 
			BT::inOrder();
		}
	
};
