#include <iostream>
#include <vector>

using namespace std;
#define MAX_N 101
int N, M;
int memory[MAX_N] = { 0, };
int cost[MAX_N] = { 0, };
int maxMemoryRet[MAX_N][10001] = { -1, };

int MaxMemory(int curId, int remainCost)
{
	if (curId >= N || remainCost < 0)
		return 0;
	if (maxMemoryRet[curId][remainCost] != -1)
		return maxMemoryRet[curId][remainCost];

	int notSelectVal = MaxMemory(curId + 1, remainCost);
	int selectVal = 0;
	if(remainCost >= cost[curId])
		selectVal = memory[curId] + MaxMemory(curId + 1, remainCost - cost[curId]);

	int result;
	if (selectVal > notSelectVal)
		result = selectVal;
	else
		result = notSelectVal;
	maxMemoryRet[curId][remainCost] = result;
	//cout << "curId:" << curId << " remainCost:" << remainCost << " result:" << result <<endl;
	return result;
}

int main()
{
	//init
	for (int i = 0; i < MAX_N; i++)
		for (int j = 0; j < 10001; j++)
			maxMemoryRet[i][j] = -1;

	scanf("%d %d", &N, &M);

	for (int i = 0; i < N; i++)
		scanf("%d", &memory[i]);
	for (int i = 0; i < N; i++)
		scanf("%d", &cost[i]);

	int totalCost;
	for (totalCost = 1; totalCost < 10001; totalCost++)
	{
		int result = MaxMemory(0, totalCost);
		//cout << "totalcost:" << totalCost << "  mem:" << result << endl;
		if (result >= M)
			break;
	}
	cout << totalCost << endl;
	return 0;
}