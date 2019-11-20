/*
	Author:  trialley
	Date:    2019-7-26
	Licence: MIT
*/

#pragma once
#include<cstring>		//memset£¬memcpy
#include<cstdlib>		//malloc

enum err{index_out_of_range }err;

template<typename T>
class vector {
private:
	T* head;		//the array head pointer
	int maxindex;		//the length-1 of array
	int frontindex;		//the last item+1
	void exlength() {
		T* newhead = new T[(maxindex + 1) * 2];
		memcpy(newhead, head, sizeof(T)*(maxindex + 1));

		maxindex = maxindex * 2 + 1;

		delete[] head;
		head = newhead;
	}
public:
	vector(vector& raw) {
		maxindex = 49;
		frontindex = -1;
		head=new  T[50];
		memset(head, 0, sizeof(T) * 50);
		for (int i = 0; i < raw.getlength(); i++) {
			push(raw[i]);
		}
	}
	vector(int n = 50) {
		maxindex = n - 1;
		frontindex = -1;

		head = new T[n];
		memset(head, 0, sizeof(T) * n);
	}

	~vector() {
		delete[] head;
	}

	T& operator [] (int i) {
		if (i > frontindex) {
			throw index_out_of_range;
		}

		return head[i];
	}
	T& operator [] (int i)const {
		if (i > frontindex) {
			throw index_out_of_range;
		}

		return head[i];
	}
	void push(T in) {
		if (frontindex == maxindex) {
			exlength();
		}

		head[++frontindex] = in;
	}
	void del(int i) {
		if (i > frontindex) {
			//err= index_out_of_range
			throw index_out_of_range;
		}

		for (int j = i; j <= frontindex; j++) {
			head[j] = head[j + 1];
		}

		frontindex--;

	}
	void insert(int i, T in) {
		if (i > frontindex) {
			throw index_out_of_range;
		}

		//判断后移是否越界
		if (frontindex + 1 > maxindex) {
			exlength();
		}
		//向后复制时需要总尾开始，否则第一个元素将会覆盖全部
		for (int j = frontindex; j >= i; j--) {
			head[j+1] = head[j];
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
	int getlength() const { return frontindex + 1; }
	int getmaxlength() const { return maxindex + 1; }
};

