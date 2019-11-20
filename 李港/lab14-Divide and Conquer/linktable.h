#include<iostream>

template<typename D>
class chain {
private:
	typedef struct node {
		D data;
		node* next;
	};
	node* head;
	int length;
public:
	chain() {
		head = NULL;
	}
	~chain() {
		if (head == NULL) {
			return;
		}
		if (head->next == NULL) {
			delete head;
			head = NULL;
			return;
		}
		node* temp = head;
		while (temp!=NULL) {
			node* d;
			d = temp;
			temp = temp->next;
			delete d;
		}
	}
	void push(D idata) {
		if (head==NULL) {
			head = new node;
			head->data = idata;
			head->next = NULL;
		}
		else {
			node* nhead = new node;
			nhead->data = idata;
			nhead->next = head;
			head =nhead;
		}
	}
	static void show(node* ihead) {
		node* temp = ihead;

		while (temp != NULL) {
			std::cout << temp->data<<" ";
			temp = temp->next;
		}
		cout << endl;
	}
	void ShowChain() {
		show(head);
	}
	/*头上最小*/
	static node* merge(node* head1, node* head2) {
		node rhead;
		node* temp=&rhead;

		while (head1 && head2) {
			if (head1->data < head2->data) {
				temp->next = head1;
				head1 = head1->next;
			}
			else {
				temp->next = head2;
				head2 = head2->next;
			}
			temp = temp->next;
		}

		if (head1) {
			temp->next = head1;
		}
		if (head2) {
			temp->next = head2;
		}


		return rhead.next;
	}

	static node* mergeSort(node* head) {
		if (head == NULL || head->next == NULL) {
			return head;
		}

		/*将一个链表切割成两部分*/
		node* end = head;
		node* half = head;
		while (end->next && end->next->next){
			half = half->next;
			end = end->next->next;
		}
		node* head2 = half->next;
		half->next = NULL;
		node* head1 = head;

		/*对向部分分别进行排序*/
		head1 = mergeSort(head1);
		show(head1);
		std::cout << "  ";
		head2 = mergeSort(head2);
		show(head2);


		return merge(head1, head2);
	}

	void callMergeSort() {
		mergeSort(head);
	}
};
