#include<iostream>
//#include"二叉树.h"
#include"二叉树(函数指针版).h"
using namespace std;

int main()
{
    char *pre="ABHFDECKG";
    char *in="HBDFAEKCG";
	linkedBinaryTree<char> BT;
	BT.makeTree(pre,in,9);
	
	cout<<"preOrder is:";  BT.preOutput();    cout<<endl;
/*	cout<<"inOrder is:";  BT.inOrder();    cout<<endl;
	cout<<"postOrder is:";  BT.postOrder();    cout<<endl;
	cout<<"levelOrder is:"; BT.levelOrder(); cout<<endl;
	cout<<"tree size is:"<<BT.size();        cout<<endl;
	cout<<"tree height is:"<<BT.height();    cout<<endl;
	
	char *post=new char[10];
	linkedBinaryTree<char>::changeIntoPost(pre,in,post,9);
	post[9]='\0';
	cout<<"由前后序转来的后序序列为："<<post<<endl;*/
	return 0;
}
