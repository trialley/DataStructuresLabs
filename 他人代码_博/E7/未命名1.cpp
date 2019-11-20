#include<iostream>
using namespace std;
template<typename T>
class chainqueue{
private:
	struct chainnode{
		T element;
		chainnode* next;
		chainnode* prev;
		chainnode(){}
		chainnode(const T& _element){element = _element;}
		chainnode(const T& _element, chainnode* _next){
			element = _element;
			next = _next;
		}
	};
protected:
	chainnode *queuetop;
    chainnode *queueback = NULL;
    int queuesize;
public:
	chainqueue() {
        queuetop = NULL;
        queuesize = 0;
    }
    ~chainqueue() {
        while (queuetop != NULL) {
            chainnode *nextNode = queuetop->next;
            delete queuetop;
            queuetop = nextNode;
        }
    }
    T &top() {
        return queuetop->element;
    }
    T &back() {
        return queueback->element;
    }
    bool empty() const {
        return queuesize == 0;
    }
    int size() const {
        return queuesize;
    }
    void push(const T &_element) {
        chainnode *newNode = new chainnode(_element, NULL);
        if (queuesize == 0)
            queuetop = newNode;
        else
            queueback->next = newNode;
        queueback = newNode;
        queuesize++;
    }
    void pop() {
        chainnode *nextNode = queuetop->next;
        delete queuetop;
        queuetop = nextNode;
        queuesize--;
    }
};

int main(){
 	int m = 0;
	cin >> m;
	chainqueue<int> chainpoker;
	int x=1;
	for(;x<=m;x++)
		chainpoker.push(x);
	x = 1;
	while(chainpoker.size()>1){
		printf("%d ",chainpoker.top());
		x++;
		chainpoker.pop();
		int save = chainpoker.top();
		chainpoker.pop();
		chainpoker.push(save);
	}
	printf("%d",chainpoker.top());
	return 0;
}

