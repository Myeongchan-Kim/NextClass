#include <iostream>
#include <vector>

using namespace std;

#define MAX_INDENT 987654321

int N;
int deltaIndet[1001];
int total;

int GetMinPositiveId()
{
	int minId = -1;
	int minVal = MAX_INDENT;
	for (int i = 0; i < N; i++)
	{
		if (deltaIndet[i] > 0 && minVal > deltaIndet[i])
		{
			minId = i;
			minVal = deltaIndet[i];
		}
	}
	return minId;
}

int GetMaxNegativeId()
{
	int maxId = -1;
	int maxVal = -MAX_INDENT;
	for (int i = 0; i < N; i++)
	{
		if (deltaIndet[i] < 0 && maxVal < deltaIndet[i])
		{
			maxId = i;
			maxVal = deltaIndet[i];
		}
	}
	return maxId;
}

void priblem_solve()
{
	int startPos = 0;

	//positive
	while ((startPos = GetMinPositiveId()) != -1)
	{
		int val = deltaIndet[startPos];
		for (int i = startPos; i < N && deltaIndet[i] >= val; i++)
		{
			deltaIndet[i] -= val;
		}
		for (int i = startPos - 1; i >= 0 && deltaIndet[i] >= val; i--)
		{
			deltaIndet[i] -= val;
		}
		total += val;
	}

	startPos = 0;
	//negative
	while ((startPos = GetMaxNegativeId()) != -1)
	{
		int val = deltaIndet[startPos];
		for (int i = startPos; i < N && deltaIndet[i] <= val; i++)
		{
			deltaIndet[i] -= val;
		}
		for (int i = startPos - 1; i >= 0 && deltaIndet[i] <= val; i--)
		{
			deltaIndet[i] -= val;
		}
		total -= val;
	}
}

int main()
{
	//reset
	N = 0;
	total = 0;
	for (int i = 0; i < 1001; i++)
		deltaIndet[i] = 0;

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &deltaIndet[i]);
	}
	for (int i = 0; i < N; i++)
	{
		int val;
		scanf("%d", &val);
		deltaIndet[i] -= val;
	}

	priblem_solve();

	printf("%d\n", total);
	return 0;
}