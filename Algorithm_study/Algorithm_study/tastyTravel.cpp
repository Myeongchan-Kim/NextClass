#include <iostream>
using namespace std;

#define MIN_VAL -987654321

int taste[301][301] = { 0, };
int maxTast[301][301] = { 0, };
int N, M, K;


int MaxTasty(int cityNum, int remainCity)
{
	if (cityNum == N)
		return 0;
	if (remainCity <= 0)
		return MIN_VAL;
	if (maxTast[cityNum][remainCity] != MIN_VAL)
		return maxTast[cityNum][remainCity];

	int maxResult = MIN_VAL;
	int tasty;

	for (int i = cityNum + 1; i <= N; i++)
	{
		if (taste[cityNum][i] != 0)
		{
			tasty = taste[cityNum][i] + MaxTasty(i, remainCity - 1);
			if (maxResult < tasty)
				maxResult = tasty;
		}
	}

	maxTast[cityNum][remainCity] = maxResult;
	return maxResult;
}

int main()
{
	scanf("%d %d %d", &N, &M, &K);

	//init
	for (int i = 0; i <= N; i++)
		for (int j = 0; j <= N; j++)
			maxTast[i][j] = MIN_VAL;
	for (int i = 0; i <= N; i++)
		for (int j = 0; j <= N; j++)
			taste[i][j] = 0;
	
	for (int i = 0; i < K; i++)
	{
		int fromCity, toCity, tast;
		scanf("%d %d %d", &fromCity, &toCity, &tast);
		if (fromCity < toCity && taste[fromCity][toCity] < tast)
			taste[fromCity][toCity] = tast;
	}

	cout << MaxTasty(1, M - 1) << endl;

	return 0;
}