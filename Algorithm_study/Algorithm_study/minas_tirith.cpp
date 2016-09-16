#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <deque>
#include <cmath>
#include <algorithm>

#define MAX_N 100
#define R (8.0)
#define INF 987654321

struct Circle {
	double x, y, r;
	double sRad, eRad;
	friend std::ostream& operator<<(std::ostream& os, Circle& c);

};

std::ostream& operator<<(std::ostream& os, Circle& c)
{
	os << "[Circle] x:" << c.x << " y:" << c.y << " r:" << c.r << " sRad:" << c.sRad << " eRad:" << c.eRad << "\tx2y2 =" << c.x*c.x + c.y*c.y;
	return os;
}

Circle* MakeCircle(double x, double y, double r)
{
	double centerAngle = atan2(y, x);
	double cos0 = ((2 * R * R) - r * r) / (2 * R * R);
	double theta = acos(cos0); // r^2 = R^2 + R^2 - 2rRcos0
	if (r > R * 2) theta = M_PI;

	Circle* newCircle = new Circle();
	newCircle->x = x;
	newCircle->y = y;
	newCircle->r = r;
	newCircle->sRad = centerAngle - theta;
	newCircle->eRad = centerAngle + theta;
	if (newCircle->eRad < 0) {
		newCircle->sRad += 2 * M_PI;
		newCircle->eRad += 2 * M_PI;
	}

	//std::cout << *newCircle << std::endl;
	return newCircle;
}

int GetMinValWithStartCicle(std::deque<Circle*>& cList)
{
	int count = 1;
	double startPos = cList[0]->sRad;
	double endPos = cList[0]->eRad;
	double maxEnd = -1.0;
	
	for (auto& c : cList)
	{
		//이전범위와 안겹치는 원이 나타나면.
		//겹치는 원들중의 최대 값으로 끝범위 설정하고 다시반복.
		if (c->sRad > endPos && maxEnd > c->sRad)
		{
			count++;
			endPos = maxEnd;
			maxEnd = -1.0;
		}
		//끝범위를 최대값으로 설정했는데도, 안 닿는 경우
		else if (c->sRad > endPos && maxEnd < c->sRad)
		{
			return INF; //실패
		}

		//현재 범위에 겹치면서, max보다 클 경우.
		if (c->sRad < endPos && c->eRad > endPos && c->eRad > maxEnd)
		{
			maxEnd = c->eRad;

			if (maxEnd > startPos + 2 * M_PI)
			{
				count++;
				endPos = maxEnd;
				break;
			}
			else 
			{
				continue;
			}
		}
	}

	if (endPos < startPos + 2 * M_PI)
		return INF;
	else
		return count;
}

int GetMinSolution(std::deque<Circle*>& cList)
{
	int minResult = INF;
	while(true)
	{
		if (cList[0]->sRad >= 0)
			break;

		int tmpRet = GetMinValWithStartCicle(cList);
		if (minResult > tmpRet)
			minResult = tmpRet;

		Circle* startCircle = cList[0];
		startCircle->sRad += 2 * M_PI;
		startCircle->eRad += 2 * M_PI;
		cList.pop_front();
		cList.push_back(startCircle);
	}

	return minResult;
}

void problem_solve()
{
	int n;
	scanf("%d", &n);

	std::deque<Circle*> cList;
	
	//생성
	for (int i = 0; i < n; i++)
	{
		double x, y, r;
		scanf("%lf %lf %lf", &y, &x, &r);
		cList.push_back(MakeCircle(x, y, r));
	}

	//시작점에 관해서 정렬
	auto compare = [](Circle* lv, Circle* rv) {
		return lv->sRad < rv->sRad;
	};
	std::sort(cList.begin(), cList.end(), compare);

	int result = GetMinSolution(cList);

	if (result == INF) printf("IMPOSSIBLE\n");
	else printf("%d\n", result);

	//삭제
	for (auto& circle : cList)
	{
		delete circle;
		circle = nullptr;
	}
	cList.clear();
}

int main() {
	int c;

	std::cin >> c;

	for (int i = 0; i < c; i++)
	{
		problem_solve();
	}
}