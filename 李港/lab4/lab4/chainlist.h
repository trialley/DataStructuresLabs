#pragma once

template<typename T>
struct node {
	T data;
	node* next;
};

template<typename T>
class chainlist {
private:
	node<T>* head;
	node<T>* end;
public:
	chainlist() {
		head =NULL;
		end = head;
	}
	void push(T data) {
		if (!head) {
			head = new node<T>;
			head->data = data;
			end = head;
		}
		else {
		node<T>* pend = end;
		
		end = new node<T>;
		end->data = data;
		end->next = NULL;

		pend->next = end;
		}

	}
	void del(int i) {
		node<T>* before = head;
		for (int j = 0; j < i-1; j++) {
			node<T>* before = before->next;
		}
		node<T>* temp = before->next;
		before->next = temp->next;
		delete temp;
	}
	void insert(int i, T data) {
		node<T>* before = head;
		for (int j = 0; j < i - 1; j++) {
			node<T>* before = before->next;
		}
		node<T>* after = before->next;
		node<T>* temp = new node<T>;
		temp->data = data;
		temp->next = after;
		before->next = temp;
	}
	void show() {
		node<T>* current = head;
		 while(current) {
			cout << current->data<<" -> ";
			current = current->next;
		}
	}
	int find(T data) {
		int i = 0;
		node<T>* current = head;
		while (current) {
			if (current->data == data) {
				return i;
			}
			node<T>* current = current->next;
			i++;
		}
		return -1;
	}

};