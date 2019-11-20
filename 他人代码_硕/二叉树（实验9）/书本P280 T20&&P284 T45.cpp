//��һ�����������Ķ���������дǰ�����������֪���������һ��Ԫ�ص�λ����last��
//Ԫ������������pair<bool,T>������a[i].first=true <=> ��λ��i��һ��Ԫ��

void visit(pair<bool,T> *a,int pos)
{
	if(a[pos].first==true)
	   cout<<a[pos].second<<" ";
}

void preOrder(pair<bool,T> *a,int pos=1)
{
	if(pos>=last) return;
    visit(a,pos);	
    preOrder(a,pos*2);
    preOrder(a,pos*2+1);
} 

void levelOrder(binaryTreeNode<T> *t)
{//��α���������*t 
	Queue q;
	while(t!=NULL)
	{
		visit(t);
		
		if(t->left!=NULL)
		   q.push(t->left);
		if(t->right!=NULL)
		   q.push(t->right);
		   
		if(q.empty()==true)  return;
		t=q.front();
		q.pop();
		
		
	}	  	
}

void linkedBinaryTree<T>:: visit(BinaryTreeNode<T>*t,string str)
{
	int size=str.size();
	str.insert(size,t->element);
}

string linkedBinaryTree<T>:: preOrder()
{
	static string str;
	t=root;
	if(t!=NULL)
	{
		visit(t,str);
		preOrder(t->left);
		preOrder(t->right);
	}
	if(*this.treeSize==str.size())
	{//���Ѿ�����this��������Ԫ�� 
		string temp_str=str;
	    str="";   //���str
	    return temp_str;
	}
	else return str;
}

bool compare(linkedBinaryTree<T> x)
{
	if(	x.preOrder()==*this.preOrder() && x.inOrder()==*this.inOrder() )
		 return true;
	else return false;
}

