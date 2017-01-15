#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
#include <memory>

int N, R;
std::vector<std::pair<int, int>> pointList;

void ShowGroup(std::vector<int>& group, std::string str)
{
	printf("Group:%s\n", str.c_str());
	for (auto id : group)
	{
		auto p = pointList[id];
		printf("\tp(%d) x:%d y:%d\n", id, p.first, p.second);
	}
}


void DivideGroup(
	std::vector<int>& circleGroup, std::vector<int>& restGroup, 
	std::pair<int,int>p1, std::pair<int,int>p2)
{
	double x1 = (double)p1.first;
	double x2 = (double)p2.first;
	double y1 = (double)p1.second;
	double y2 = (double)p2.second;

	double cx = x1 / 2.0 + x2 / 2.0 ;
	double cy = y1 / 2.0 + y2 / 2.0;;
	double r2 = ((x1 - x2) * (x1 - x2) + (y1 - y2)*(y1 - y2)) / 4.0;

	for (int i = 0; i < N; i++)
	{
		auto point = pointList[i];
		double x = (double)point.first;
		double y = (double)point.second;
		if ((x - cx) * (x - cx) + (y - cy)*(y - cy) <= r2 + 0.00001)
		{
			circleGroup.push_back(i);
		}
		else {
			restGroup.push_back(i);
		}
	}
}

int CountPoint(std::vector<int>&group, int topY, int botY, int leftX, int rightX)
{
	int count = 0;
	for (auto& i : group)
	{
		auto p = pointList[i];
		if (p.first <= rightX && p.first >= leftX && p.second <= topY && p.second >= botY)
			count++;
	}
	return count;
}

int GetMaxRect(std::vector<int>& group)
{
	int n = group.size();
	int maxResult = 1;
	for (auto& topId : group)
	{
		std::pair<int, int>&top = pointList[topId];
		
		for (auto& botId : group)
		{
			if (botId == topId)
				continue;

			std::pair<int, int>& bot = pointList[botId];
			int height = abs(top.second - bot.second);
			if (height > R)
				continue;

			for (auto& leftId : group)
			{
				std::pair<int, int>& left = pointList[leftId];

				if (left.first > top.first || left.first > bot.first)
					continue;
				if (left.second > top.second || left.second < bot.second)
					continue;

				for (auto& rightId : group)
				{
					std::pair<int, int>& right = pointList[rightId];
					if (right.first < top.first || right.first < bot.first)
						continue;
					if (right.second > top.second || right.second < bot.second)
						continue;
					int width = abs(left.first - right.first);
					if (width > R)
						continue;

					int count = CountPoint(group, top.second, bot.second, left.first, right.first);
					//printf("\tRect : topY:%d botY:%d leftX:%d rightX:%d count:%d\n", top.second, bot.second, left.first, right.first, count);

					maxResult = std::max(maxResult, count);
				}
			}
		}
	}

	return maxResult;
}

void problem_solve(int case_num)
{
	pointList.clear();

	scanf("%d %d", &N, &R);

	for (int i = 0; i < N; i++)
	{
		int X, Y;
		scanf("%d %d", &X, &Y);
		pointList.push_back({ X, Y });
	}

	int maxResult = 2;
	for (int i = 0; i < N; i++)
	{
		auto& p1 = pointList[i];
		for (int j = 0; j < N; j++)
		{
			if (i == j)
				continue;

			auto& p2 = pointList[j];
			std::vector<int> circleGroup;
			std::vector<int> restGroup;

			unsigned long long r_sqr = 
				(unsigned long long)(p1.first - p2.first) *(p1.first - p2.first)
				+ (unsigned long long)(p1.second - p2.second) * (p1.second - p2.second);
			if (r_sqr > (unsigned long long)R * (unsigned long long)R * 2)
				continue;

			DivideGroup(circleGroup, restGroup, p1, p2);
			
			//ShowGroup(circleGroup, "Circle");
			//ShowGroup(restGroup, "Rest");

			int maxCircle = GetMaxRect(circleGroup);
			//printf("Circle:%d\n", maxCircle);

			int maxRest = GetMaxRect(restGroup);
			//printf("Rest:%d\n", maxRest);

			maxResult = std::max(maxResult, std::max(maxCircle, 1) + std::max(maxRest, 1));
		}
	}

	printf("Case #%d: %d\n", case_num, maxResult);
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