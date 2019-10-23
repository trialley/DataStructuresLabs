#include<iostream>
using namespace std;
//���̲�p428-430 
bool topologicalOrder(int *theOrder)
{//����false�����ҽ�������ͼû����������
 //������һ���������У����������theOrder[0:n-1]
 
   int *inDegree = new int [n+1];  //n��ͼ�Ķ�����
   for(int i=0;i<=n;i++)
     inDegree[i]=0;
   for(int i=1;i<=n;i++)        //������е����� 
   {
   	  vertexIterator<T> *ii= iterator(i);
   	  int u;
   	  while( (u=i->next()) !=0)
   	  inDegree[i]++;
   }
    
    //�����Ϊ0�ĵ����ջ��
	arrayStack<int> stack;   //��ʵ����Ҳ�����ö��� 
	for(int i=1;i<=n;i++)
	{
		if(inDegree[i]==0)
		  stack.push(i);
	}
	
	//������������
	int j=0;   //����theOrder������
	while( !stack.empty() )  
	{
		int nextVertex=stack.top();
		stack.pop();
		theOrder[j++]=nextVertex;
		//����ʣ������ȣ��������Ϊ0�Ķ���ѹջ׼�������������� 
		 vertexIterator<T> *iNextVertex = iterator(nextVertex);
		 int u;
		 while( (u=iNextVertex->next()) !=0 )
		 {
		 	inDegree[u]--;
		 	if(inDegree[u]==0)
		 	  stack.push(u);
		 }
	 } 
	return (j==n);
}
