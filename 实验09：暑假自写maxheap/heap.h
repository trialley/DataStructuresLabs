

/*��Ŀ����
ά��һ��ϵͳ��֧�ֲ�ѯ���ݿ��KСԪ��(��ʼK=0)��
�������������֣�
��M:�����ݿ��в���һ������ֵΪx; push
��L:K++; pop
��W:������ݿ��е�KСԪ��; head
��������
��һ�У�һ��������n����ʾ��������� ��
������n�У�ÿ��һ����ĸM��L��W����ʾִ������M��L��W�� 
����M���֮����һ��������x����ʾ�����ݿ��в���x��
�������
����ÿ��W������һ����������



���Ƶ��������
��������
һ��Сд��ĸ��ɵ��ַ��������Ȳ�����10510^5105��
�������
�������ַ���ͨ��Huffman�����ĳ��ȡ� */
#pragma once
#include"vector.h"
enum heapErr{ heap_empty };
template<typename T>
class minHeap {
private:
	vector<T> arr;
	int k;
public:
	heap() {
		k = 0;

	}
	push(const T& idata) {
		int currentNode = arr.getlength + 1;

		/*�ж��Ƿ����ֱ�ӽ���������ݷŵ����飨�ѣ������*/
		//currtNode/2���Ǹ�λ�õĸ�ĸԪ�ص�����
		if (currentNode == 1 || arr[currentNode / 2] >= idata) {
			arr.push(idata);
			return;
		}
		/*�����ܷŵ���������ѭ��Ѱ��*/
		else {
			arr.push(arr[currentNode / 2]);
			currentNode /= 2;

			//Ѱ�ҵ���ȷλ�ã�������ְ취��������TM���
			while (currentNode != 1 && arr[currentNode / 2] < idata) {
				arr[currentNode] = arr[currentNode / 2];
				currentNode /= 2;
			}

			//���뵽��ȷλ��
			arr[currentNode] = idata;

			return;
		}
	}
	/*�������Ԫ��*/
	T pop() {
		/*����Ƿ�Ϊ��*/
		if (arr.getlength() == 0) {
			throw heap_empty;
		}

		T rdata = arr[0];

		/*û������Ԫ�أ���������*/
		if (arr.getlength() == 1) {
			T temp = arr[0];
			arr.del(0);
			return temp;
		}
		/*ɾ��ͷ��֮��֮���Ԫ��˳��ǰ�ƣ���������*/
		if (arr.getlength()=2) {
			T temp = arr[0];
			arr.del(0);
			return temp;
		}
		
		/*������������Ԫ�أ�����Ҫ����*/
				/*�ݹ�����ÿ������*/
		int rootPosition = 1;
		int rootElement = 2;

		while (1) {
			if (arr[arr.getlength() - 1] >= arr[rootElement] || rootElement>arr.getlength()-1) {
				arr[rootPosition] = arr[arr.getlength() - 1];
				arr.del(arr.getlength - 1);
				return;
			}
			/*��Ҫ�����ڵ��������������Ǹ���Ϊ�½ڵ�*/
			if (arr[rootElement] < arr[rootElement + 1]) {
				rootElement++;
			}
			/*�����ĸ��ڵ��������ĸ��ڵ�*/
			arr[rootPosition] = arr[rootElement];

			/*�������пճ�λ�ã�����λ����Ϊ���ڵ�����ݹ�����*/
			rootPosition = rootElement;
			rootElement = rootPosition;
		}

		return rdata;
	}
	T getMax() { return arr[0]; }
	int getLength() const{return arr.getlength;}
};