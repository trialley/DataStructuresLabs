#include"../ʵ��4������/chain.h"
#include"../ʵ�����������������Ա�/vector.h"
#include<iostream>
using namespace std;
using namespace TA;

/*
* brief��������ת��Ϊ�������Ա�
* in:
*     chain<T>& raw    ������������
* out:
*     arrayList<T>*    ���ظ��ƺ��������Ա��ָ��
*/
template<class T>
arrayList<T>* chainToListGet ( chain<T>& raw ) {
	/*�����б�*/
	arrayList<T>* temp = new arrayList<T>;

	/*����ѭ������*/
	int size = raw.listSize ();
	for ( int i = 0; i < size; i++ ) {
		temp->insert ( i, raw.get ( i ) );
	}

	/*�����б�ָ��*/
	return temp;
}


/*
* brief��������ת��Ϊ�������Ա�
* in:
*     chain<T>& raw    ������������
* out:
*     arrayList<T>*    ���ظ��ƺ��������Ա��ָ��
*/
template<class T>
arrayList<T>* chainToListIterator ( chain<T>& raw ) {
	/*�����б�*/
	arrayList<T>* temp = new arrayList<T>;

	/*����ѭ������*/
	int size = raw.listSize ();

	//Ҫ���� size ��ֵ��������Ҫ���� size-1 ��������ȶԵ�һ��Ԫ�ؽ��и���
	chain<int>::iterator it = raw.begin ();
	temp->insert ( 0, *it );

	//�ٶ�ʣ��Ԫ�ؽ��и���
	for ( int i = 1; i < size; i++ ) {
		it++;
		temp->insert ( i, *it );
	}

	/*�����б�ָ��*/
	return temp;
}

/*
* brief�������µķ�ת����ʹָ��ָ��������
* in:
*     chain<int>& a    �������������
*     chain<int>& b    
* out: 
*     chain<int>*      Ϊ���ٸ��Ƶ���Դ���ģ��˴�����ָ��
*/
chain<int>* merge ( chain<int>& chain1, chain<int>& chain2) {
	/*����׼������*/
	//
	chain<int>* temp = new chain<int>;
	chain<int>::iterator it1 = chain1.begin ();
	chain<int>::iterator it2 = chain2.begin ();

	/*�������岿��*/
	//��������δ֪�������һ��������ϼ��������渴��
	//��֮�󣬵����жϲ�����δ�����������
	while ( ( it1 != chain1.end () ) && ( it2 != chain1.end () ) ) {
		if ( *it1 <= *it2 ) {
			temp->insert ( temp->listSize (), *it1 );
			it1++;
		} else {
			temp->insert ( temp->listSize (), *it2 );
			it2++;
		}
	}

	/*����ɨβ����*/
	//���index����listsize��˵�������鸴����ϣ�����δ������ϣ���������ʣ��Ԫ�ء�
	//chain1��chain2���Ա��ֻʣһ��û�и�����ϣ���˴˴������ж�ֻ��һ����ִ��
	if ( it1 != chain1.end () ) {
		while ( it1 != chain1.end () ) {
			temp->insert ( temp->listSize (), *it1 );
			it1++;
		}
	}
	if ( it2 != chain1.end () ) {
		while ( it2 != chain1.end () ) {
			temp->insert ( temp->listSize (), *it2 );
			it2++;

		}
	}

	return temp;
}


/*
* brief�������µķ�ת����ʹָ��ָ��������
* in:  chain<T>** in
* out: void 
*/
template<class T>
void reverse ( chain<T>** in ) {       //��Ҫ����ָ���ָ�룬ͨ��ָ���ָ���ָ����в�����
	chain<T>* temp = new chain<T>;

	/*��ת���Ƶ����岿��*/
	int size = ( *in )->listSize ();
	chain<int>::iterator it = ( *in )->begin ();
	temp->insert ( 0, *it );           //ʹ�õ����������� size ��Ԫ����Ҫ���� size-1 ��
	                                   //�����ǰ����һ�Σ������������븴�Ʋ���ѭ�� size-1 �μ���

	for ( int i = 1; i < size; i++ ) { //�����븴�Ʋ���ѭ�� size-1 ��
		it++;
		temp->insert ( 0, *it );
	}

	/*��ת���Ƶ�ɨβ����*/
	delete ( *in );                    //ɾ��ָ��ָ��ľ�����������ָ��������
	*in = temp;
	return;
}
int main () {
	chain<int>* raw = ( new chain<int> );
	for ( int i = 0; i < 10; i++ ) {
		raw->insert ( 0, i );
	}
	cout <<"ԭʼ����"<< *raw << endl;


	//raw->reverse ();
	//cout << "��Ա������ת��" << *raw << endl;
	//reverse ( &raw );
	//cout << "�ⲿ�����ٴη�ת��" << *raw << endl;
	chain<int> a;
	//cout << "��Ա�����ϲ���" << a.merge ( *raw, *raw )<<endl;
	cout << "�ⲿ�����ϲ���" << *merge ( *raw, *raw );
	//arrayList<int>* temp = chainToListIterator<int>(*raw);
	//cout << "���������Ա�";
	//for (int i = 0; i < 10; i++) {
	//	cout << (*temp)[i] << " ";
	//}
	//raw->clear ();
	//cout << endl << raw->listSize ();
	delete raw;
	//delete temp;
	return 0;
}





