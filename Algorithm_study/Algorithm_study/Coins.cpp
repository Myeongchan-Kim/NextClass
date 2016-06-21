#include <iostream>
#include <vector>
using namespace std;

int valueTable[101][10001];
int coinValue[101];
int coinCount[101];

int main()
{
	int total = 0;
	cin >> total;

	int coinKind = 0;
	cin >> coinKind;

	//테이블 초기화
	for (int i = 0; i < 101; i++)
		for (int j = 0; j < 10001; j++)
			valueTable[i][j] = 0;
	for (int i = 0; i < 101; i++)
	{
		valueTable[i][0] = 1;
		coinValue[i] = 0;
		coinCount[i] = 0;
	}

	//값 입력
	for (int i = 1; i <= coinKind; i++)
	{
		scanf("%d", &coinValue[i]);
		scanf("%d", &coinCount[i]);
	}

	for (int i = 1; i <= coinKind; i++)
	{
		for (int money = total; money > 0; money--)
		{
			valueTable[i][money] = valueTable[i - 1][money];
		}

		for (int money = total; money > 0; money--)
		{
			for (int coinNum = 1; coinNum <= coinCount[i]; coinNum++)
			{
				int curMoney = money - coinValue[i] * coinNum;
				if (curMoney >= 0)
					valueTable[i][money] += valueTable[i][curMoney];
			}
		}
	}

	printf("%d\n", valueTable[coinKind][total]);
	return 0;
}