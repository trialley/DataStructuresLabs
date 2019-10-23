#include<iostream>
using namespace std;
//见教材p428-430 
bool topologicalOrder(int *theOrder)
{//返回false，当且仅当有向图没有拓扑序列
 //若存在一个拓扑序列，则把它赋给theOrder[0:n-1]
 
   int *inDegree = new int [n+1];  //n是图的顶点数
   for(int i=0;i<=n;i++)
     inDegree[i]=0;
   for(int i=1;i<=n;i++)        //求出所有点的入度 
   {
   	  vertexIterator<T> *ii= iterator(i);
   	  int u;
   	  while( (u=i->next()) !=0)
   	  inDegree[i]++;
   }
    
    //把入度为0的点加入栈中
	arrayStack<int> stack;   //其实这里也可以用队列 
	for(int i=1;i<=n;i++)
	{
		if(inDegree[i]==0)
		  stack.push(i);
	}
	
	//生成拓扑序列
	int j=0;   //数组theOrder的索引
	while( !stack.empty() )  
	{
		int nextVertex=stack.top();
		stack.pop();
		theOrder[j++]=nextVertex;
		//更新剩余点的入度，并把入度为0的顶点压栈准备加入拓扑序列 
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
