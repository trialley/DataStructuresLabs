/*
ʵ���  ����������
һ��ʵ��Ŀ��
���ն������Ļ��������������������������������ʵ�֡�
����ʵ������
1�������������ࡣ�������Ĵ洢�ṹʹ�������ṩ����:ǰ���������������������������α�������������������Ŀ������������߶ȡ�
2���Խ����õĶ�������ִ������������������������Ľ����
3�����ռ���¼��Ķ�����ǰ�����к���������(��Ԫ�ظ�����ͬ)������ö������ĺ������С�


*/

#pragma once

template<class T>
class btree {
public:
	typedef enum {}err;
	typedef struct node {
		T data;
		node* left;
		node* right;
	}node;
protected:
	node* _root;
	int _size;

	void deleteLeft (node* _root) {

	}
	void deleteRight (node* _root) {

	}
public:
	btree () {

	}
	~btree () {
		deleteLeft (_root);
		deleteRight (_root);
		delete _root;
	}
};