#include <queue>
#include <iostream>
using namespace std;
int main()
{
	queue<int> card;//��Ƭ��ֽ��
	int n;//��Ƭ������ 
	cin >> n;
	if (n <= 0) return 1;
	for (int i = 1; i <= n; i++)
	{    //ѹ��ֽ�� 
		card.push(i);
	}
	while (card.size() != 1)
	{
		cout << card.front() << " ";
		card.pop();
		int i = card.front();
		card.pop();
		card.push(i);
	}
	cout << card.front();
}
