

/*题目描述
维护一个系统，支持查询数据库第K小元素(初始K=0)。
命令有以下三种：
令M:向数据库中插入一个数，值为x; push
令L:K++; pop
令W:输出数据库中第K小元素; head
输入描述
第一行，一个正整数n，表示命令的条数 。
接下来n行，每行一个字母M、L或W，表示执行命令M、L或W。 
对于M命令，之后有一个正整数x，表示向数据库中插入x。
输出描述
对于每条W命令，输出一个正整数。



最高频最慢到达
输入描述
一串小写字母组成的字符串，长度不超过10510^5105。
输出描述
输出这个字符串通过Huffman编码后的长度。 */
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

		/*判断是否可以直接将输入的数据放到数组（堆）的最后*/
		//currtNode/2就是该位置的父母元素的索引
		if (currentNode == 1 || arr[currentNode / 2] >= idata) {
			arr.push(idata);
			return;
		}
		/*若不能放到最后，则进行循环寻找*/
		else {
			arr.push(arr[currentNode / 2]);
			currentNode /= 2;

			//寻找到正确位置（想出这种办法来的人真TM天才
			while (currentNode != 1 && arr[currentNode / 2] < idata) {
				arr[currentNode] = arr[currentNode / 2];
				currentNode /= 2;
			}

			//插入到正确位置
			arr[currentNode] = idata;

			return;
		}
	}
	/*弹出最大元素*/
	T pop() {
		/*检查是否为空*/
		if (arr.getlength() == 0) {
			throw heap_empty;
		}

		T rdata = arr[0];

		/*没有其他元素，无需排序*/
		if (arr.getlength() == 1) {
			T temp = arr[0];
			arr.del(0);
			return temp;
		}
		/*删除头部之后，之后的元素顺次前移，无需排序*/
		if (arr.getlength()=2) {
			T temp = arr[0];
			arr.del(0);
			return temp;
		}
		
		/*有三个及以上元素，则需要排序*/
				/*递归排序每个子树*/
		int rootPosition = 1;
		int rootElement = 2;

		while (1) {
			if (arr[arr.getlength() - 1] >= arr[rootElement] || rootElement>arr.getlength()-1) {
				arr[rootPosition] = arr[arr.getlength() - 1];
				arr.del(arr.getlength - 1);
				return;
			}
			/*需要将根节点两个子中最大的那个作为新节点*/
			if (arr[rootElement] < arr[rootElement + 1]) {
				rootElement++;
			}
			/*将来的根节点变成真正的根节点*/
			arr[rootPosition] = arr[rootElement];

			/*数组中有空出位置，将该位置作为根节点继续递归排序*/
			rootPosition = rootElement;
			rootElement = rootPosition;
		}

		return rdata;
	}
	T getMax() { return arr[0]; }
	int getLength() const{return arr.getlength;}
};