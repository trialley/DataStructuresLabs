/*adjacencyWDigraph的特制堆栈模拟*/
void rDfs(int v) 
{//使用栈模拟递归 
	arrayStack<int> s(10);
	reach[v]=label;
	s.push(v);
	
	while(!s.empty()) //当栈不空时 
	{
		int w=s.top();
		s.pop();
				
		for(int j=1;j<=n;j++)  //对上一个到达的点w的所有邻接点 
		{
			if( a[w][j]!=noEdge) 
			{
				if(  reach[j]!=label ) //如果存在一个未标记的点j 
				{  reach[j]=label;  s.push(j);	} 
				else{//j已被标记且w没有其他邻接点了
					  if()  s.pop(); 
				}
			}
		}
	}
}

/*adjacencyWDigraph的迭代器堆栈模拟*/ 
void rDfs(int v) 
{//使用栈模拟递归 
	arrayStack<int> s(10);
	reach[v]=label;
	s.push(v);
	
	while(!s.empty()) //当栈不空时 
	{
		int w=s.top();
		s.pop();
		myIterator *iv=iterator(w);		
		while( ( u=iv->next() )!=0 )  //对上一个到达的点w的所有邻接点 
		{
			if(  reach[u]!=label ) //如果存在一个未标记的点j 
			{  reach[u]=label;  s.push(u);	} 
			else{//j已被标记且w没有其他邻接点了
				   if(iv->next()==0)  s.pop(); 
			    }
		}
	}
}


