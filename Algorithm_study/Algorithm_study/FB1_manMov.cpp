#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
#include <memory>

#define INF 987654321

int weight[102][102];
std::vector<std::pair<int, int>> orders;

int N, M, K;

int cache[2][5001][5001];

void clearCache()
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 5001; j++)
			for (int k = 0; k < 5001; k++)
				cache[i][j][k] = -1;
}

void clearWeight()
{
	for (int i = 0; i < 102; i++)
		for (int j = 0; j < 102; j++)
		{
			if (i == j)
				weight[i][j] = 0;
			else 
				weight[i][j] = INF;
		}
}

int calculMinGas(int loadId, int deliverId, int isDelivered)
{
	int curCityId = 0;
	if (isDelivered == 1)
	{
		if (deliverId == 0)
			curCityId = 1;
		else
			curCityId = orders[deliverId - 1].second;
	}
	else {
		curCityId = orders[loadId - 1].first;
	}

	if (cache[isDelivered][loadId][deliverId] >= 0)
		return cache[isDelivered][loadId][deliverId];

	//loadeId means orderId to loded, 
	//deliverId means orderId to deliver,
	//deliverId == -1, means empty truck.

	int result = INF;

	if (loadId == orders.size() && deliverId == loadId)
		return 0;
	else if (loadId < orders.size() && deliverId == loadId) // You have to load.
	{
		auto order = orders[loadId];
		int s = order.first;
		
		if (weight[curCityId][s] >= INF) return INF;
		result = weight[curCityId][s] + calculMinGas(loadId + 1, loadId, 0);
	}
	else if (loadId < orders.size() && deliverId == loadId - 1) // have 1 empty space.
	{
		// first case. load 1more.
		int s, d;
		auto loadOrder = orders[loadId];
		s = loadOrder.first;
		
		int tmpResult_l = weight[curCityId][s] + calculMinGas(loadId + 1, deliverId, 0);
		
		// second case. deliver now.
		auto deliverOrder = orders[deliverId];
		d = deliverOrder.second;
		
		int tmpResult_d = weight[curCityId][d] + calculMinGas(loadId, deliverId + 1, 1);
		
		int min_val = std::min(tmpResult_l, tmpResult_d);
		min_val = min_val >= INF ? INF : min_val;
		result = min_val;
	}
	else // You must deliver. 
	{
		auto order = orders[deliverId];
		int d = order.second;

		if (weight[curCityId][d] >= INF) return INF;
		result = weight[curCityId][d] + calculMinGas(loadId, deliverId + 1, 1);
	}
	
	cache[isDelivered][loadId][deliverId] = result;
	return result;
}

void problem_solve(int case_num) 
{
	orders.clear();
	clearWeight();
	clearCache();
	
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i < M; i++)
	{
		int gas;
		int s, d;
		scanf("%d %d %d", &s, &d, &gas);
		weight[s][d] = std::min(weight[s][d], gas);
		weight[d][s] = std::min(weight[d][s], gas);
	}

	for (int i = 0; i < K; i++)
	{
		int s, d;
		scanf("%d %d", &s, &d);
		orders.push_back({ s, d });
	}

	//make min weight of each city; // Floyed-warshal
	//for(int q = 1; q<= N; q++)
	for (int i = 1; i <= N; i++)
	{
		//for each edge, relaxation
		for(int j = 1; j <= N; j++)
			for (int k = 1; k <= N; k++)
			{
				//relaxation
				if (weight[j][i] >= INF || weight[i][k] >= INF)
					continue;
				
				weight[j][k] = std::min(weight[j][k], weight[j][i] + weight[i][k]);
				weight[k][j] = weight[j][k];
			}
	}

	int totalCost = calculMinGas(0, 0, 1);
	totalCost = totalCost >= INF ? -1 : totalCost;
	printf("Case #%d: %d\n", case_num, totalCost);
}

int main() {
	int T;
	scanf("%d", &T);
	for (int i = 0; i < T; i++)
	{
		problem_solve(i + 1);
	}
	return 0;
}