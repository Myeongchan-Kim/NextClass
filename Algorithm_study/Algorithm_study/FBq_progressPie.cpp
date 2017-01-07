#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <memory.h>
#include <limits>
#include <bitset>
#include <string>
#include <stack>
#include <queue>
#define PI 3.14159265358979323846

enum COLOR {
	BLACK = false,
	WHITE = true,
};

double sqrDist(double x1, double y1, double x2, double y2)
{
	double dx = x1 - x2;
	double dy = y1 - y2;
	return dx*dx + dy*dy;
}

double dist(double x1, double y1, double x2, double y2)
{
	return sqrt(sqrDist(x1, y1, x2, y2));
}

void problem_solve(int case_num)
{
	COLOR color = WHITE;

	int P, X, Y;
	scanf("%d %d %d", &P, &X, &Y);

	//cos2 rule
	double OtoC2 = 50 * 50;
	double CtoXY2 = sqrDist(X, Y, 50, 50);
	double OtoXY2 = sqrDist(X, Y, 50, 100);
	double e = .000001;

	double angleOfXY = 0.0;
	angleOfXY = acos((OtoC2 + CtoXY2 - OtoXY2) / 2.0 / sqrt(OtoC2) / sqrt(CtoXY2)) / PI * 180.0; 
	if (isnan(angleOfXY))
	{
		if (P == 100)
			color = BLACK;
		else
			color = WHITE;
	}
	else
	{
		angleOfXY = (X >= 50) ? angleOfXY : (360 - angleOfXY);
		double angleOfP = (double)P * 3.6;

		if (CtoXY2 > 50 * 50)
		{
			color = WHITE;
		}
		else if (angleOfXY < angleOfP)
		{
			color = BLACK;
		}

	}	
	
	printf("Case #%d: %s\n", case_num, color == WHITE ? "white" : "black");

	// Case #1: white
	// Case #3: black
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int i = 0; i < T; i++)
	{
		problem_solve(i + 1);
	}
	return 0;
}