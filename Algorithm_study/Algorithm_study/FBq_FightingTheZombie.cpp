#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
#include <memory>

struct Deal
{
	int min;
	int max;
};

double cache[22][10001];

void clearCahce()
{
	//clear cache;	
	for (int i = 0; i < 22; i++)
		for (int j = 0; j < 10001; j++)
			cache[i][j] = -1.0;
}

struct Spell
{
	std::vector<Deal> deals;
	int x;
	int y;
	int z;
	
	Spell(const int X,const int Y,const int Z) : x(X), y(Y), z(Z)
	{
		deals.clear();
		
		deals.push_back({ Z, Z });
		for (int i = 0; i < X; i++)
			deals.push_back({ 1, Y });
	
	}

	double calculDeathProb(int curDealIdx, int remainHP)
	{
		if (remainHP <= 0 || curDealIdx >= deals.size())
		{
			if (remainHP <= 0)
				return 1.0;
			else
				return 0.0;
		}
		if (cache[curDealIdx][remainHP] >= 0)
		{
			return cache[curDealIdx][remainHP];
		}

		Deal deal = deals[curDealIdx];
		double result = 0;

		for (int d = deal.min; d <= deal.max; d++)
		{
			result += calculDeathProb(curDealIdx + 1, remainHP - d);
		}
		result /= (double)(deal.max - deal.min + 1); // divide by count;

		cache[curDealIdx][remainHP] = result;
		return result;
	}
};

void problem_solve(int case_num)
{
	int H, S;
	scanf("%d %d\n", &H, &S);

	double maxProb = 0.0;

	for (int i = 0; i < S; i++)
	{
		char str[100] = { 0, };
		scanf("%s", str);
		std::string spell = std::string(str);
		
		int X, Y, Z=0;
		if (spell.find("+") != std::string::npos || spell.find("-") != std::string::npos)
		{
			sscanf(spell.c_str(), "%dd%d%d", &X, &Y, &Z);
		}
		else {
			sscanf(spell.c_str(), "%dd%d", &X, &Y);
		}
		//printf("Spell X:%d Y:%d Z:%d\n", X, Y, Z);
		
		clearCahce();
		Spell s = Spell(X, Y, Z);
		double result = s.calculDeathProb(0, H);
		
		if (maxProb < result)
			maxProb = result;

		//printf("This prob:%f\tMax prob :%f\n", result, maxProb);
	}

	printf("Case #%d: %f\n", case_num, maxProb);
	// Case #1: 1.000012
	// Case #3: 0.123413
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