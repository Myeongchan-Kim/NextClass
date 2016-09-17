#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>
#include <limits>

#define INF 987654321
#define MAX_N 21

struct CityInfo {
	int cityId;
	std::vector<std::pair<int, double>> dist;
};

double dist_map[MAX_N][MAX_N];
double minDistFromCity[MAX_N];
double min_dist = INF;
CityInfo* cityInfoList[MAX_N] = {nullptr,};

double MyHuristic1(std::vector<bool>& visited) {
	double result = 0;
	int N = visited.size();

	for (int i = 0; i < N; i++)
		if (visited[i] == false)
			result += minDistFromCity[i];

	return result;
}

double GetMemoResult(std::vector<bool>& visited)
{ 
	return -1;
}

void CalcMinDist(std::vector<bool>& visited,int lastVistedId, double beforeSum, int remainCity)
{
	if (remainCity == 0)
	{
		min_dist = std::min(min_dist, beforeSum);
		return;
	}
	if (beforeSum >= min_dist)
		return;
	
	if ((beforeSum + MyHuristic1(visited) >= min_dist))
		return;

	for (auto& cityInfo : cityInfoList[lastVistedId]->dist)
	{
		if (visited[cityInfo.first] == false)
		{
			visited[cityInfo.first] = true;
			CalcMinDist(visited, cityInfo.first, beforeSum + dist_map[lastVistedId][cityInfo.first], remainCity - 1);
			visited[cityInfo.first] = false;
		}
	}
}

void problem_solve()
{
	int N;
	scanf("%d", &N);

	//map clear
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			dist_map[i][j] = INF;
	min_dist = INF;

	//input distance
	for (int i = 0; i < N; i++)
	{
		CityInfo* cInfo = new CityInfo();
		cInfo->cityId = i;
		for (int j = 0; j < N; j++)
		{
			scanf("%lf", &dist_map[i][j]);
			if (j != i)
			{
				cInfo->dist.push_back({ j, dist_map[i][j] });
			}
		}

		//가까운 도시 순으로 정렬.
		std::sort(cInfo->dist.begin(), cInfo->dist.end(), [](std::pair<int, double>& lv, std::pair<int, double>& rv) {
			return lv.second < rv.second;
		});

		minDistFromCity[i] = cInfo->dist.front().second; //가장 가까운 곳을 지정.
		cityInfoList[i] = cInfo;
	}

	// find shortest path
	std::vector<bool> visited;
	for (int i = 0; i < N; i++)
		visited.push_back(false);

	for (int i = 0; i < N; i++)
	{
		visited[i] = true;
		CalcMinDist(visited, i, 0.0, N-1);
		visited[i] = false;
	}
	
	printf("%.10lf\n", min_dist);
	//clear memory
	for (int i = 0; i < N; i++)
	{
		if (cityInfoList[i] != nullptr)
		{
			delete cityInfoList[i];
			cityInfoList[i] = nullptr;
		}
	}
}

int main() 
{
	int problem_n;
	scanf("%d", &problem_n);

	for (int i = 0; i < problem_n; i++)
	{
		problem_solve();
	}
}

