template<typename T>
class edge{
	public:
		int from = -1;
		int to = -1;
		T weight = 0; 

		edge(){
			from = -1;
			to = -1;
			weight = 0;
		}
		edge(int _from,int _to,T _weight){
			from = _from;
			to = _to;
			weight = _weight;
		} 
};

template<typename T>
class arrGraph{
	private:
		T** graph = NULL;
		int numOfVertices = 0;
		int numOfEdges = 0;
	public:
		int numOfVertic(){
			return numOfVertices;
		}
		int numOfEdge(){
			return numOfEdges;
		}
		bool haveEdge(int i,int j){
			if(graph[i][j]!=0)return true;
			else return false;
		}
		void insertEdge(edge<T> _edge){
			graph[_edge.from][_edge.to] = _edge.weight;
		}
		
};

template<typename T>
class chainGraph{
	
};

