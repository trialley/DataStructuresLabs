#pragma once

enum queue_err{ queue_empty };

template<typename T>
class queue {
private:
	typedef struct node {
		T data;
		node* next;
	}node;
	node* head;
	node* end;
	int length;
public:
	queue() {
		head = new node;
		end = head;
	}
	~queue() {
		while (head->next != NULL) {
			node* temp = head;
			head = head->next;
			delete temp;
		}
		delete head;
	}

	void push(T in) {
		length++;
		node* nend = new node;
		nend->data = in;
		nend->next = NULL;
		
		end->next = nend;
		end = nend;
	}
	T get() {
		if (isempty()) {
			throw queue_empty;
		}
		node* nhead = head->next;
		T data = head->next->data;
		delete head;
		head = nhead;

		length--;
		return data;
	}

	T readhead()const {return head->data;}
	bool isempty()const {return head == end;}
	int getlength()const { return length; }
};