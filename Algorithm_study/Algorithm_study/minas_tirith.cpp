#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

#define MAX_N 100
#define R (8.0)
#define INF 987654321
#define PI 3.1415926535897931

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
	os << "[Circle] x:" << c.x << " y:" << c.y << " r:" << c.r << " sRad:" << c.sRad << " eRad:" << c.eRad << "\tx2y2 =" << c.x*c.x + c.y*c.y;
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
		if (curCircle == startCircle) continue;
		if (curCircle->sRad > endCover)
		{
			// �������� cover ������ ��� ���
			// ���ݱ��� endcover�߿� ���� ���� ������ �����ϰ� 1 ������Ŵ.
			endCover = maxCover; 
			result++;
			//std::cout << "renew endCover :" << endCover << std::endl;
		}
		//maxCover���� ��� ����.
		if (maxCover < curCircle->eRad)
		{
			maxCover = curCircle->eRad;
			//std::cout << "touch max : " << maxCover << std::endl;

			if (maxCover >= startCover + 2 * PI)
			{
				endCover = maxCover;
				result++;
				break; // ������ endcover�� �ѹ��� �� �������� ����.
			}
		}
	}

	if (endCover >= startCover + 2 * PI)
		return result;//���������� ���������� ��� ����.
	else 
		return INF; //�ѹ����� ���������� INF ����
}


void initCircleInfo(Circle* circle)
{
	double theta = acos(1 - circle->r * circle->r / R / R / 2.0);
	double rDist = sqrt(circle->x * circle->x + (R - circle->y)*(R - circle->y));
	double cRad = acos(1 - rDist * rDist / R / R / 2.0);
	cRad = (circle->x < 0) ? (2 * PI - cRad) : (cRad);
	circle->sRad = cRad - theta;
	circle->eRad = cRad + theta;
	if (circle->sRad < 2 * PI && circle->eRad > 2 * PI)
	{
		circle->sRad -= 2 * PI;
		circle->eRad -= 2 * PI;
	}
	if (circle->r >= 16.000000000)
	{
		circle->sRad = 0.0;
		circle->eRad = PI * 2;
	}

	//std::cout << *circle << std::endl;
	return;
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
		initCircleInfo(&cPool[i]);
		
		cList.push_back(&cPool[i]);
	}
	
	//�������� ���ؼ� ����
	auto compare = [](Circle* lv, Circle* rv) {
		return lv->sRad < rv->sRad;
	};
	std::sort(cList.begin(), cList.end(), compare);

	int minResult = INF;
	for (auto& pCir : cList)
	{
		//0.0 ��ġ�� ������ ��� ������ �������� ����غ���
		if ( pCir->sRad <= 0.0 && pCir->eRad >= 0.0)
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