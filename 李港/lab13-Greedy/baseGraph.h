template<typename D>
class graphInterface {
public:
	//virtual GraphInterface(int nodeNum) {}
	virtual  void SetLinkValue(const int from, const int to, const int value) = 0;
	virtual  int  GetLinkValue(const int from, const int to)const = 0;
	virtual void SetNodeDate(const int i, const D data) = 0;
	virtual D GetNodeDate(const int i)const = 0;
	virtual int GetNodeNum()const = 0;
	//virtual ~GraphInterface(){}
};

template<typename D>
class arrGraph : public graphInterface<D> {
private:
	int nodeNum;
	int** weights;
	D* nodes;
public:
	arrGraph(int inodeNum) {
		nodeNum = inodeNum;
		weights = new int*[inodeNum];
		for (int i = 0; i < inodeNum; i++) {
			weights[i] = new int[inodeNum];
			for (int j = 0; j < inodeNum;j++) {
				weights[i][j] = 0;
			}
		}

		nodes = new D[inodeNum];
	}
	~arrGraph() {
		for (int i = 0; i < nodeNum; i++) {
			delete[] weights[i];
		}

		delete[] weights;
		delete[] nodes;
	}

	void SetLinkValue(const int from, const int to,const int value) {weights[from][to] = value;}
	int  GetLinkValue(const int from, const int to)const {return weights[from][to];}
	void SetNodeDate(const int i, const D data) {nodes[i] = data;}
	D GetNodeDate(const int i)const { return nodes[i]; }
	int GetNodeNum()const { return nodeNum; }
};

//template<typename D>
//class linkGraph : public graphInterface {
//private:
//
//};


/*对外统一接口*/
//typedef enum  { uniGraph_type_arr, uniGraph_type_link } graphType;
template<typename G,typename D>
class uniGraph : public graphInterface<D> {
private:
	G graph;
public:
	uniGraph(int inodeNum, int type = 0) :graph(inodeNum) {}
	~uniGraph(){}

	void SetLinkValue(const int from, const int to, const int value) {
		graph.SetLinkValue(from, to, value);
	}
	int  GetLinkValue(const int from, const int to)const {
		return graph.GetLinkValue(from, to);
	}
	void SetNodeDate(const int i, const D data) {
		graph.SetNodeDate(i, data);
	}
	D GetNodeDate(const int i)const {
		return graph.GetNodeDate(i);
	}
	int GetNodeNum()const {
		return graph.GetNodeNum();
	}
		//virtual ~GraphInterface(){}
};