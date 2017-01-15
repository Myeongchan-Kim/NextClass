#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
#include <memory>

#define INF 987654321

std::vector<std::vector<int>> sale;
int cache[2][301][301];
int N, M;

void clearCache() {
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 301; j++)
			for (int k = 0; k < 301; k++)
				cache[i][j][k] = -1;
}

int calculMinTotalPrice(int remain, int dayIdx)
{
	int min = (remain == N - dayIdx ? 1 : 0);
	if (remain == 0)
		return 0;
	if (cache[min][remain][dayIdx] >= 0)
		return cache[min][remain][dayIdx];

	int sum = 0;
	int minSum = INF;
	int tmpResult = 0;
	
	//calculate I have to buy today
	if(min > 0)
	{
		sum += sale[dayIdx][0];
	}
	
	tmpResult = sum + calculMinTotalPrice( remain - min, dayIdx + 1) + (min)*(min);
	minSum = tmpResult;
	//printf("tmpReulst:%d minSum:%d\n", tmpResult, minSum);

	//choose count today buy.
	for (int i = min; i < remain && i < M; i++)
	{
		sum += sale[dayIdx][i];
		tmpResult = sum + calculMinTotalPrice( remain - (i + 1), dayIdx + 1) + (i+1)*(i+1);
		//printf("tmpReulst:%d minSum:%d\n", tmpResult, minSum);

		minSum = std::min(minSum, tmpResult);
	}

	cache[min][remain][dayIdx] = minSum;
	return minSum;
}

void problem_solve(int case_num) {
	sale.clear();
	clearCache();

	scanf("%d %d", &N, &M);

	for (int i = 0; i < N; i++)
	{
		std::vector<int> dailyList;
		for (int j = 0; j < M; j++)
		{
			int P;
			scanf("%d", &P);
			dailyList.push_back(P);
		}
		std::sort(dailyList.begin(), dailyList.end());
		sale.push_back(dailyList);
	}

	int totalCost = calculMinTotalPrice(N, 0);

	printf("Case #%d: %d\n", case_num, totalCost);
}

int main() {
	int T;
	scanf("%d", &T);
	for (int i = 0; i < T; i++)
	{
		problem_solve(i+1);
	}
	return 0;
}