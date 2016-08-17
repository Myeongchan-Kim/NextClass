#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

#define MAX_N 100
#define R (8.00000000000)
#define INF 987654321

struct Circle {
	double x;
	double y;
	double r;

	double sRad;
	double eRad;

	friend std::ostream& operator<<(std::ostream& os, Circle& c);
};

std::ostream& operator<<(std::ostream& os, Circle& c)
{
	os << "[Circle] x:" << c.x << " y:" << c.y << " r:" << c.r << " sRad:" << c.sRad << " eRad:" << c.eRad;
	return os;
}

Circle cPool[MAX_N + 1];
std::vector<Circle*> cList;

int findMinCover(Circle* startCircle)
{
	int result = 1;

	double startCover = startCircle->sRad;
	double endCover = startCircle->eRad;
	double maxCover = startCircle->eRad;

	for (auto& curCircle : cList)
	{
		if (curCircle->sRad > endCover)
		{
			// 시작점이 cover 범위를 벗어난 경우
			//제일 높은 값으로 갱신하고 1 증가시킴.
			endCover = maxCover; 
			result++;
			//std::cout << "renew endCover :" << endCover << std::endl;
		}
		//maxCover값은 계속 갱신.
		if (maxCover < curCircle->eRad)
		{
			maxCover = curCircle->eRad;
			//std::cout << "touch max : " << maxCover << std::endl;
		}
		if (maxCover >= startCover + 2 * M_PI)
		{
			result++;
			endCover = maxCover;
			return result;//시작점보다 높아졌으면 1 증가시키고 바로 종료.
		}
	}

	return INF; //한바퀴를 못돌았으면 INF 리턴
}

void problem_solve()
{
	int n;
	scanf("%d", &n);
	cList.clear();
	cList.reserve(n);
	for (int i = 0; i < n; i++)
	{
		scanf("%lf %lf %lf", &cPool[i].y, &cPool[i].x, &cPool[i].r);
		double theta = acos(1 - cPool[i].r * cPool[i].r / R / R / 2.0);
		double rDist = sqrt(cPool[i].x * cPool[i].x + (R - cPool[i].y)*(R - cPool[i].y));
		double cRad = acos(1 - rDist * rDist / R / R / 2.0); 
		cRad = (cPool[i].x < 0) ? (2 * M_PI - cRad) : (cRad);
		cPool[i].sRad = cRad - theta;
		cPool[i].eRad = cRad + theta;
		if (cPool[i].sRad < 2 * M_PI && cPool[i].eRad > 2 * M_PI)
		{
			cPool[i].sRad -= 2 * M_PI;
			cPool[i].eRad -= 2 * M_PI;
		}
		if (cPool[i].r > 16.000)
		{
			cPool[i].sRad = -0.1;
			cPool[i].eRad = M_PI * 2 + 0.1;
		}
		//std::cout << cPool[i] << std::endl;
		cList.push_back(&cPool[i]);
	}
	
	//시작점에 관해서 정렬
	auto compare = [](Circle* lv, Circle* rv) {
		return lv->sRad < rv->sRad;
	};
	std::sort(cList.begin(), cList.end(), compare);

	int minResult = INF;
	for (auto& pCir : cList)
	{
		//0.0 위치를 지나는 모든 원들을 기준으로 계산해보기
		if ( pCir->sRad < 0.0 && pCir->eRad > 0.0)
		{
			int result = findMinCover(pCir);
			if (result < minResult) minResult = result;
			//std::cout << result << " " << minResult << std::endl;
		}
	}
	if (minResult == INF) std::cout << "IMPOSSIBLE" << std::endl;
	else printf("%d\n", minResult);
	return;
}

int main() {
	int CASE;
	scanf("%d", &CASE);
	for (int i = 0; i < CASE; i++)
	{
		problem_solve();
	}
	return 0;
}