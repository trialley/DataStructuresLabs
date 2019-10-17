/*****************************************************************************
*  @brief    vector的测试程序                                                 *
*  @author   TriAlley                                                        *
*  @email    lg139@139.com                                                   *
*  @license  GNU General Public License (GPL)                                *
*                                                                            *
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*  2019/09/26 | 1.0       | TriAlley       | Create file                     *
*****************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>
using namespace std;
#include "vector.h"

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
	vector<student> studets;
public:
	contact(int n = 5) {
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
	student& operator [] (int i) {
		return studets[i];
	}
	int getlength() {
		return studets.getlength();
	}
	int findindexbyname(char* name) {
		for (int i = 0; i < studets.getlength(); i++) {
			if (strcp(studets[i].name, name)) {
				return i;
			}
		}
		return -1;
	}
	void deletebyindex(int i) {
		studets.del(i);
	}

	void insertbyindex(int i, char* name, int classnum, int dom, const char* phone) {
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
	void changenamebyindex(int i, char* iname) {
		strcpy(studets[i].name, iname);
	}
	void changeclassbyid(int i, int iclassnum) {
		studets[i].classnum=iclassnum;
	}
	void changedombyid(int i, int dom) {
		studets[i].dom = dom;
	}
	void changephonebyid(int i, char* phone) {
		strcpy(studets[i].phone, phone);
	}

	void showall() {
		cout << "\ntotal:" << studets.getlength()<<endl;
		for (int i = 0; i < studets.getlength(); i++) {
			showbyindex(i);
		}
		cout << endl;
	}
	void showbyindex(int i) {
		cout << "index: " << i
			<< "	name: " << studets[i].name
			<< "	classnum: " << studets[i].classnum
			<< "	dom: " << studets[i].dom
			<< "	phone: " << studets[i].phone
			<< endl;
	}
	void showbyclass(int classnum) {
		for (int i = 0; i < studets.getlength(); i++) {
			if (studets[i].classnum == classnum) {
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
		for (;;) {
			int index;
			char temp[20];
			int i = 0;
			cout
				<< "\n1: name" << endl
				<< "2: classnum" << endl
				<< "3: dom" << endl
				<< "4: phone" << endl
				<< "5: show all" << endl
				<< "6: find by class" << endl
				<< "7: show by index" << endl
				<< "8: insert by index" << endl
				<< "9: delete by index" << endl
				<< "Please input function number:";
			int func_num = 0;
			cin >> func_num;
			switch (func_num){
			case 1:
				cout << "Please input the item you want to change:";
				cin >> index;
				i = 0;
				cout << "Please input new name:";
				getchar();
				gets_s(temp);
				c.changenamebyindex(index, temp);
				break;
			case 2:
				cout << "Please input the item you want to change:";
				cin >> index;
				cout << "Please input new class number:";
				cin >> i;
				c.changeclassbyid(index, i);
				break;
			case 3:
				cout << "Please input the item you want to change:";
				cin >> index;
				cout << "Please input new dom number:";
				cin >> i;
				c.changedombyid(index, i);
				break;
			case 4:
				cout << "Please input the item you want to change:";
				cin >> index;
				i = 0;
				cout << "Please input new phone:";
				getchar();
				gets_s(temp);
				c.changephonebyid(index, temp);
				break;
			case 5:
				c.showall();
				break;
			case 6:
				cout << "Please input the class you want to show:";
				cin >> index;
				c.showbyclass(index);
				break;
			case 7:
				cout << "Please input the index you want to show:";
				cin >> index;
				c.showbyindex(index);
				break;
			case 8:
				char name[20];
				char phone[20];
				int index;
				int dom;
				int classnum;
				cout << "Please input new index:";
				cin >> index;
				cout << "Please input new name:";
				getchar();
				gets_s(name);
				cout << "Please input new class number:";
				cin >> classnum;
				cout << "Please input new dom number:";
				cin >> dom;
				cout << "Please input new phone:";
				getchar();
				gets_s(phone);
				c.insertbyindex(index, name, classnum, dom, phone);
				break;
			case 9:
				//int index;
				cout << "Please input new index:";
				cin >> index;
				c.deletebyindex(index);
			default:
				cout << "No such function!";
				break;
			}

		}
	} catch (enum err err) {
		switch (err) {
		case index_out_of_range:
			cout << endl << "index_out_of_range" << endl;
			break;
		default:
			cout << endl << "unknown err" << endl;
		}
	}
}