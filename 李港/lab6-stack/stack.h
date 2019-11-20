#include<cstdlib>
#include<cstring>

enum stack_err{ stack_err_is_empty};
template<typename T>
class stack {
private:
	T* head;
	int buffersize;
	int frontindex;
	void checkbufferzise() {
		if ((frontindex + 1) * sizeof(T) == buffersize) {
			T* newhead= (T*)malloc(buffersize*2);
			memset(newhead, 0, buffersize*2);
			memcpy(newhead, head, buffersize);

			buffersize = buffersize * 2;
			free(head);
			head = newhead;
		}
	}
public:
	stack() {
		buffersize = sizeof(T) * 50;
		head =(T*)malloc(buffersize);
		memset(head, 0, buffersize);

		frontindex = -1;
	}
	~stack() {
		delete[] head;
	}
	stack(const stack<T>& in) {
		buffersize = in.getbuffersize();
		front = in.getfrontindex();
		head = (T*)malloc(buffersize);
		memset(head, 0, buffersize);
	}

	void push(T in) {
		checkbufferzise();
		head[++frontindex] = in;
		return;
	}
	T pop() {
		if (isempty()) {
			throw stack_err_is_empty;
		}
		else {

			return head[frontindex--];
		}
	}
	T front() const{
		if (isempty) {
			throw stack_err_is_empty;
		}
		else {
			return head[frontindex];
		}
	}
	void clear() {
		memset(head, 0, buffersize);
		frontindex = -1;
	}

	bool isempty() const{ return frontindex == -1;}
	int getbuffersize() const { return buffersize; }
	int getfrontindex() const { return front; }
};