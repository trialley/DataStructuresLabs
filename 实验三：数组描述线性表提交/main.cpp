#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<cstring>		//memset£¬memcpy
#include<cstdlib>		//malloc

enum err { index_out_of_range }err;
template<typename T>
class vector {
private:
	T* head;		//the array head pointer
	int maxindex;		//the length-1 of array
	int frontindex;
	void __exlength() {
		T* newhead = new T[(maxindex + 1) * 2];
		memcpy(newhead, head, sizeof(T) * (maxindex + 1));

		maxindex = maxindex * 2 + 1;

		delete[] head;
		head = newhead;
	}
public:
	vector(int n = 50) {
		maxindex = n - 1;
		frontindex = 0;

		head = new T[n];
		memset(head, 0, sizeof(T) * n);
	}

	~vector() {
		delete[] head;
	}

	T& operator [] (int i) {
		if (i >= frontindex) {
			throw index_out_of_range;
		}

		return head[i];
	}
	void push(T in) {
		if (frontindex == maxindex) {
			__exlength();
		}

		head[frontindex++] = in;
	}
	void del(int i) {
		if (i >= frontindex) {
			//err= index_out_of_range
			throw index_out_of_range;
		}

		for (int j = i; j < frontindex; j++) {
			head[j] = head[j + 1];
		}

		frontindex--;

	}
	void insert(int i, T in) {
		if (i >= frontindex) {
			throw index_out_of_range;
		}

		//判断后移是否越界
		if (frontindex + 1 > maxindex) {
			__exlength();
		}
		//向后复制时需要总尾开始，否则第一个元素将会覆盖全部
		for (int j = frontindex; j >= i; j--) {
			head[j + 1] = head[j];
		}

		head[i] = in;

		frontindex++;
	}
	int find(T target) {
		for (int i = 0; i <= frontindex; i++) {
			if (head[i] == target) {
				return i;
			}
		}
		return -1;
	}
	int getlength() { return frontindex; }
	int getmaxlength() { return maxindex + 1; }
};

#include<iostream>
#include<stdio.h>
using namespace std;

//姓名、电话号码、班级、宿舍。由键盘输入或文件录入
typedef struct {
	char name[20];
	char phone[20];
	int classnum;
	int dom;
}student;

bool strcp(const char* a, const char* b) {
	int i = 0;
	while (a[i] != '\0' && b[i] != '\0') {
		if (a[i] != b[i]) {
			return false;
		}
		i++;
	}
	if (a[i] != b[i]) {
		return false;
	} else {
		return true;
	}
}
class contact {
private:
	vector<student> students;
public:
	contact(int n = 5) {}
	student& operator [] (int i) {
		return students[i];
	}
	int getlength() {
		return students.getlength();
	}
	int findindexbyname(char* name) {
		for (int i = 0; i < students.getlength(); i++) {
			if (strcp(students[i].name, name)) {
				return i;
			}
		}
		return -1;
	}
	void deletebyindex(int i) {
		students.del(i);
	}
	void insertbyindex(int i, char* name, int classnum, int dom, const char* phone) {
		student temp;
		strcpy(temp.name, name);
		temp.dom = dom;
		temp.classnum = classnum;
		strcpy(temp.phone, phone);
		students.insert(i, temp);
	}
	void push(char* name, int classnum, int dom, const char* phone) {
		student temp;
		strcpy(temp.name, name);
		temp.dom = dom;
		temp.classnum = classnum;
		strcpy(temp.phone, phone);
		students.push(temp);
	}
	void changenamebyindex(int i, char* iname) {
		strcpy(students[i].name, iname);
	}
	void changeclassbyid(int i, int iclassnum) {
		students[i].classnum = iclassnum;
	}
	void changedombyid(int i, int dom) {
		students[i].dom = dom;
	}
	void changephonebyid(int i, char* phone) {
		strcpy(students[i].phone, phone);
	}
	void showall() {
		cout << "\ntotal:" << students.getlength() << endl;
		for (int i = 0; i < students.getlength(); i++) {
			showbyindex(i);
		}
		cout << endl;
	}
	void showbyindex(int i) {
		cout << "index: " << i
			<< "	name: " << students[i].name
			<< "	classnum: " << students[i].classnum
			<< "	dom: " << students[i].dom
			<< "	phone: " << students[i].phone
			<< endl;
	}
	void showbyclass(int classnum) {
		for (int i = 0; i < students.getlength(); i++) {
			if (students[i].classnum == classnum) {
				showbyindex(i);
				cout << endl;
			}
		}
	}
	unsigned int getxorbyclass(int classnum) {
		unsigned int temp=0;
		for (int i = 0; i < getlength(); i++) {
			if (students[i].classnum == classnum) {
				temp = temp ^ (unsigned int)(students[i].dom);
			}
		}
		return temp;
	}
};

int main() {
	//freopen("sample.txt", "r", stdin);

	contact c(5);
	int loop;
	cin >> loop;
	for (int j = 0 ; j < loop ; j++) {
		int index;
		char temp[20];
		int i = 0;

		int func_num = 0;
		cin >> func_num;
		switch (func_num){
		case 0:
			char name[20];
			char phone[20];
			int dom;
			int classnum;

			cin>>name;
			cin>>phone;
			cin >> classnum;
			cin >> dom;
			c.push(name, classnum, dom, phone);
			break;
		case 1://delete by name
			cin >> name;
			c.deletebyindex(c.findindexbyname(name));
			break;
		case 2://changge by name
			cin >> name;
			cin >> i;
			switch (i){
			case 1:
				cin >> phone;
				c.changephonebyid(c.findindexbyname(name),phone);
				break;
			case 2:
				cin >> classnum;
				c.changeclassbyid(c.findindexbyname(name), classnum);
				break;
			case 3:
				cin >> dom;
				c.changedombyid(c.findindexbyname(name), dom);
				break;
			default:
				break;
			}
				
			break;
		case 3://find by name
			cin >> name;
			if (c.findindexbyname(name)>-1) {
				cout << 1;
			} else {
				cout << 0;
			}
			cout << endl;

			break;

		case 4://out class dom xor
			cin >> classnum;
			cout<<c.getxorbyclass(classnum);
			cout << endl;

			break;
		default:
			break;
		}
		//c.showall();
	}
}