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
	* @brief ȡ����� ����min-max�м����ֵ
	*/
	int _LgRand(int min, int max) {
		return  ((rand() % (max - min + 1)) + min);
	}

	/**
	* @brief ������������ֵչʾһ��
	* int times ѭ���ִ�
	*/
	void _Show(int times) {
		cout << "�� " << times << " ��ѭ����";
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
	* @brief ÿ���������д��ң��Ա��ٴ�����
	*/
	void ReArrange() {
		for (int i = 0; i < _len; i++) {
			_Lg_swap(_arr + i, _arr + LGRAND(0, _len - 1));
		}
		return;
	}

	/**
	* @brief ð������
	*/
	void BubbleSort() {
		int cmp_times = 0;	//��¼�Ƚϴ��� 
		int move_times = 0;	//��¼�������� 
		int loop = 0;

		/*ð��������Ĵ��룬ÿ��ɨ�趼������Ԫ��ɨ��һ�飬�������С���л���*/
		for (int j = 0; j < _len - 1; j++) {
			loop++;

			/*����ɨ��*/
			bool no__swap = 1;	//��¼�ô�ɨ���Ƿ��н�����Ϊ 
			for (int i = 0; i < _len - j - 1; i++) {

				cmp_times++;
				if (_arr[i] > _arr[i + 1]) {
					no__swap = 0;
					move_times++;
					_Lg_swap(_arr + i, _arr + i + 1);
				} else { //�ϸ�if-else���
					continue;
				}
			}

			_Show(j + 1);

			/*�жϸô�ɨ���Ƿ��й�������Ϊ�����ޣ���˵�����ź�����ǰ��ֹ*/
			if (no__swap) {
				cout << "�޿ɽ������ݣ���ǰֹͣ��" << endl;
				break;
			}
		}

		cout << "ɨ�������" << loop << " �Ƚϴ�����" << cmp_times << " �ƶ�������" << move_times << endl;
	}

	/**
	* @brief ѡ������
	*/
	void SelectSort() {
		int cmp_times = 0;
		int move_times = 0;
		int loop = 0;


		/*ѡ��������Ĵ��룬�Ӵ�С�����Ϊ���������Ҳ�δ������*/
		for (int i = 0; i < _len; i++) {
			loop++;


			int maxindex = _len - 1;//���±��н�������Ŀ����ʹ���ʼ�������һֱ�仯��˵��δ������Ҳ�ź����� 
			bool sorted = true;
			for (int j = _len - 1; j > i - 1; j--) {
				cmp_times++;
				if (_arr[j] >= _arr[maxindex]) {
					maxindex = j;
				} else {//���maxindex��һ��δ�仯��˵��δ��������û����ȫ����
					sorted = false;
				}
			}
			_Show(i + 1);

			if (sorted) {
				cout << "������ɣ���ǰ��ֹ��" << endl;
				break;
			}

			_Lg_swap(_arr + maxindex, _arr + i);
			move_times++;
		}

		cout << "ɨ�������" << loop << " �Ƚϴ�����" << cmp_times << " �ƶ�������" << move_times << endl;
	}


	/**
	* @brief ��������
	*/
	void InsertSort() {
		int cmp_times = 0;
		int move_times = 0;
		int loop = 0;

		for (int i = 1; i < _len; i++) { // i��_len-1��δ��������0��i-1������������ 
			T temp = _arr[i];
			for (int j = i; 0 < j; j--) {
				cmp_times++;
				//��_arr��i�����뵽a��0��1-1��
				/*�����������Ҳ�Ϊ���ֵ������С��temp����temp�������µ����ֵ*/
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

		cout << "ɨ�������" << loop << " �Ƚϴ�����" << cmp_times << " �ƶ�������" << move_times << endl;
	}

	/**
	* @brief Ϊoj׼���ĺ���
	*/
	void PureOutputInsertSort() {
		int cmp_times = 0;
		int move_times = 0;
		int loop = 0;

		for (int i = 1; i < _len; i++) { // i��_len-1��δ��������0��i-1������������ 
			T temp = _arr[i];
			for (int j = i; 0 < j; j--) {
				cmp_times++;
				//��_arr��i�����뵽a��0��1-1��
				/*�����������Ҳ�Ϊ���ֵ������С��temp����temp�������µ����ֵ*/
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
	* @brief ������
	*/
	void Rank() {
		int* r = new int[_len];
		for (int i = 0; i < _len; i++) {
			r[i] = 0;
		}

		//oj������ʹ��memset�ᱨ��
		//memset((void*)r, 0, sizeof(int) * _len);

		/*Rank���Ĵ���*/
		//Ŀ����������Ԫ�ض�������Ԫ�رȽ�һ��
		//���Ϊ�������Ƚϵģ��Ҳ�Ϊδ�����Ƚϵ�
		for (int i = 1; i < _len; i++) {
			for (int j = 0; j < i; j++) {
				if (_arr[j] <= _arr[i]) {//���ε��ڱ���С��Ԫ�ص������������ͬ��СԪ�ص����� 
					r[i]++;
				} else {
					r[j]++;
				}
			}
		}

		cout << "���������";
		for (int i = 0; i < _len; i++) {
			cout << r[i] << " ";
		}
		cout << endl;
	}
};




int main() {
	srand(0);

	/*��ʼ������������*/
	int num = 0;
	cin >> num;
	int* iarr = new int[num];

	for (int i = 0; i < num; i++) {
		cin>>iarr[i];
	}



	/*��������*/
	LgSorts<int> s(num, iarr);
	s.PureOutputInsertSort();
	/*�ͷ���Դ*/
	delete[] iarr;
	return 0;
}
