#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include "vector.h"

//姓名、电话号码、班级、宿舍。由键盘输入或文件录入
typedef struct {
	char name[20];
	char phone[20];
	int classnum;
	int dom;
}student;

bool strcp(const char* a,const char* b) {
	int i = 0;
	while (a[i] != '\0' && b[i] != '\0') {
		if (a[i] != b[i]) {
			return false;
		}
		i++;
	}
	if (a[i] != b[i]) {
		return false;
	}
	else {
		return true;
	}
}

class contact {
private:
	vector<student> studets;
public:
	contact(int n=5) {
		/*构建初始线性表*/
		//strcpy属于c标准库
		
		for (int i = 0; i < n; i++) {
			student temp;
			strcpy(temp.name, "name");
			strcpy(temp.phone, "1575332828");
			temp.classnum = i % 2;
			temp.dom = i;
			studets.push(temp);
		}
	}
	int getlength() {
		return studets.getlength();
	}
	int findindexbyname(char* name) {
		for (int i = 0; i < studets.getlength();i++) {
			if (strcp(studets[i].name, name)){
				return i;
			}
		}
		return -1;
	}
	void deletebyindex(int i) {
		studets.del(i);
	}
	void insertbyindex(int i,char* name,int classnum,int dom,const char* phone) {
		student temp;
		strcpy(temp.name, name);
		temp.dom = dom;
		temp.classnum = classnum;
		strcpy(temp.phone, phone);
		studets.insert(i, temp);
	}
	void push(char* name, int classnum, int dom, const char* phone) {
		student temp;
		strcpy(temp.name, name);
		temp.dom = dom;
		temp.classnum = classnum;
		strcpy(temp.phone, phone);
		studets.push(temp);
	}
	void changenamebyindex(int i,char* name) {
		
	}
	void changeclassbyid(int i,int classnum) {

	}
	void changedombyid(int i,int dom) {

	}
	void changephonebyid(int i,int phone) {

	}
	void showall() {
		for (int i=0; i < studets.getlength(); i++) {
			showbyindex(i);
			cout << endl;
		}
	}
	void showbyindex(int i) {
		cout << "index: " << i
			<< "\nname: " << studets[i].name
			<< "\nclassnum: " << studets[i].classnum
			<< "\ndom: " << studets[i].dom
			<< "\nphone: " << studets[i].phone
			<<endl;
	}
	void showbyclass(int classnum) {
		for (int i = 0; i < studets.getlength(); i++) {
			if (studets[i].classnum==classnum) {
				showbyindex(i);
				cout << endl;
			}
		}
	}

};

int main() {
	try {
		contact c;
		c.showall();
	}
	catch (enum err err) {
		switch (err) {
		case index_out_of_range:
			cout <<endl<< "index_out_of_range"<<endl;
			break;
		default:
			cout << endl << "unknown" << endl;
		}
	}



}