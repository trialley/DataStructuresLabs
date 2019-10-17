#include <queue>
#include <iostream>
using namespace std;
int main()
{
	queue<int> card;//¿¨Æ¬ÄÚÖ½ÅÆ
	int n;//¿¨Æ¬µÄ×ÜÊý 
	cin >> n;
	if (n <= 0) return 1;
	for (int i = 1; i <= n; i++)
	{    //Ñ¹ÈëÖ½ÅÆ 
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
