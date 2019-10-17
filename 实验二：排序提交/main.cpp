#include<cstdlib>
#include<ctime>
#include<iostream>
using std::cout;
using std::cin;
using std::endl;

#define LGRAND(min,max) ((rand()%(max-min+(int)1))+(int)min )

template<typename T>
class LgSorts {
private:
	T* _arr;
	int _len;
	void _Lg_swap(T* A, T* B) {
		T temp = *A;
		*A = *B;
		*B = temp;
	}

	/**
	* @brief 取随机数 返回min-max中间的数值
	*/
	int _LgRand(int min, int max) {
		return  ((rand() % (max - min + 1)) + min);
	}

	/**
	* @brief 将数组中所有值展示一次
	* int times 循环轮次
	*/
	void _Show(int times) {
		cout << "第 " << times << " 轮循环：";
		for (int times = 0; times < _len; times++) {
			cout << _arr[times] << " ";
		}
		cout << endl;
	}
	void _swap(T& a, T& b) {
		T temp = a;
		a = b;
		b = temp;
	}
public:
	LgSorts(int in, T* iarr) :_len(in), _arr(iarr) {}

	/**
	* @brief 每次排序后进行打乱，以便再次排序
	*/
	void ReArrange() {
		for (int i = 0; i < _len; i++) {
			_Lg_swap(_arr + i, _arr + LGRAND(0, _len - 1));
		}
		return;
	}

	/**
	* @brief 冒泡排序
	*/
	void BubbleSort() {
		int cmp_times = 0;	//记录比较次数 
		int move_times = 0;	//记录交换次数 
		int loop = 0;

		/*冒泡排序核心代码，每次扫描都将所有元素扫描一遍，根据其大小进行互换*/
		for (int j = 0; j < _len - 1; j++) {
			loop++;

			/*单次扫描*/
			bool no__swap = 1;	//记录该次扫描是否有交换行为 
			for (int i = 0; i < _len - j - 1; i++) {

				cmp_times++;
				if (_arr[i] > _arr[i + 1]) {
					no__swap = 0;
					move_times++;
					_Lg_swap(_arr + i, _arr + i + 1);
				} else { //严格if-else配对
					continue;
				}
			}

			_Show(j + 1);

			/*判断该次扫描是否有过交换行为，若无，则说明以排好序，提前终止*/
			if (no__swap) {
				cout << "无可交换数据，提前停止。" << endl;
				break;
			}
		}

		cout << "扫描次数：" << loop << " 比较次数：" << cmp_times << " 移动次数：" << move_times << endl;
	}

	/**
	* @brief 选择排序
	*/
	void SelectSort() {
		int cmp_times = 0;
		int move_times = 0;
		int loop = 0;


		/*选择排序核心代码，从大到小，左测为排序区，右测未排序区*/
		for (int i = 0; i < _len; i++) {
			loop++;


			int maxindex = _len - 1;//该下标有讲究，从目标最低处开始，如果他一直变化，说明未排序区也排好序了 
			bool sorted = true;
			for (int j = _len - 1; j > i - 1; j--) {
				cmp_times++;
				if (_arr[j] >= _arr[maxindex]) {
					maxindex = j;
				} else {//如果maxindex有一次未变化，说明未排序区还没有完全排序
					sorted = false;
				}
			}
			_Show(i + 1);

			if (sorted) {
				cout << "排序完成，提前终止！" << endl;
				break;
			}

			_Lg_swap(_arr + maxindex, _arr + i);
			move_times++;
		}

		cout << "扫描次数：" << loop << " 比较次数：" << cmp_times << " 移动次数：" << move_times << endl;
	}


	/**
	* @brief 插入排序
	*/
	void InsertSort() {
		int cmp_times = 0;
		int move_times = 0;
		int loop = 0;

		for (int i = 1; i < _len; i++) { // i到_len-1是未排序区域，0到i-1是已排序区域 
			T temp = _arr[i];
			for (int j = i; 0 < j; j--) {
				cmp_times++;
				//把_arr【i】插入到a【0：1-1】
				/*以排序区域右侧为最大值，若它小于temp，则temp就是最新的最大值*/
				if (_arr[j - 1] <= temp) {
					break;
				} else {
					move_times++;
					_arr[j] = _arr[j - 1];
					_arr[j - 1] = temp;
				}

			}
			_Show(i);
			loop++;
		}

		cout << "扫描次数：" << loop << " 比较次数：" << cmp_times << " 移动次数：" << move_times << endl;
	}

	/**
	* @brief 为oj准备的函数
	*/
	void PureOutputInsertSort() {
		int cmp_times = 0;
		int move_times = 0;
		int loop = 0;

		for (int i = 1; i < _len; i++) { // i到_len-1是未排序区域，0到i-1是已排序区域 
			T temp = _arr[i];
			for (int j = i; 0 < j; j--) {
				cmp_times++;
				//把_arr【i】插入到a【0：1-1】
				/*以排序区域右侧为最大值，若它小于temp，则temp就是最新的最大值*/
				if (_arr[j - 1] <= temp) {
					break;
				} else {
					move_times++;
					_arr[j] = _arr[j - 1];
					_arr[j - 1] = temp;
				}

			}
			loop++;
		}
		for (int i = 0; i < _len; i++) {
			cout<< _arr[i]<<" ";
		}
	}

	/**
	* @brief 排名次
	*/
	void Rank() {
		int* r = new int[_len];
		for (int i = 0; i < _len; i++) {
			r[i] = 0;
		}

		//oj编译器使用memset会报错
		//memset((void*)r, 0, sizeof(int) * _len);

		/*Rank核心代码*/
		//目的是让所有元素都与其他元素比较一次
		//左侧为已主动比较的，右侧为未主动比较的
		for (int i = 1; i < _len; i++) {
			for (int j = 0; j < i; j++) {
				if (_arr[j] <= _arr[i]) {//名次等于比他小的元素的数量加上左侧同大小元素的数量 
					r[i]++;
				} else {
					r[j]++;
				}
			}
		}

		cout << "排名结果：";
		for (int i = 0; i < _len; i++) {
			cout << r[i] << " ";
		}
		cout << endl;
	}
};




int main() {
	srand(0);

	/*初始化待排序数组*/
	int num = 0;
	cin >> num;
	int* iarr = new int[num];

	for (int i = 0; i < num; i++) {
		cin>>iarr[i];
	}



	/*进行排序*/
	LgSorts<int> s(num, iarr);
	s.PureOutputInsertSort();
	/*释放资源*/
	delete[] iarr;
	return 0;
}
