#include <iostream>
#include <vector>

using namespace std;


struct Vilage
{
	vector<int> nearList;
};
//int edge[50][50];

Vilage vilageList[50];
int today;
int prisonId;
double probTable[101][50];

double CalcProbability(int day, int id)
{
	if (day == 0)
	{
		if (id == prisonId)
			return 1.0;
		else
			return 0.0;
	}

	if (probTable[day][id] >= 0)
		return probTable[day][id];


	double result = 0.0;
	for (auto& nearVId : vilageList[id].nearList)
	{
		result += CalcProbability(day - 1, nearVId) / vilageList[nearVId].nearList.size();
	}

	probTable[day][id] = result;
	return result;
}

void problem_solve()
{
	//reset
	for (int i = 0; i < 50; i++)
	{
		vilageList[i].nearList.clear();
	}
	for(int i = 0; i < 101; i++)
		for(int j = 0; j< 50; j++)
			probTable[i][j] = -1.0;

	
	int vilageNum;
	scanf("%d", &vilageNum);
	scanf("%d", &today);
	scanf("%d", &prisonId);

	for (int i = 0; i < vilageNum; i++)
	{
		for (int j = 0; j < vilageNum; j++)
		{
			int connected = 0;
			scanf("%d", &connected);
			if (connected == 1)
			{
				vilageList[i].nearList.push_back(j);
			}
				
		}
	}

	int outN;
	scanf("%d", &outN);
	for (int i = 0; i < outN; i++)
	{
		int vId;
		scanf("%d", &vId);
		printf("%.9f ", CalcProbability(today, vId));
	}
	printf("\n");
}

int main()
{
	int N = 0;
	cin >> N;

	for (int i = 0; i < N; i++)
	{
		problem_solve();
	}
	return 0;
}