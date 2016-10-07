#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <memory.h>
#include <limits>
#include <bitset>

#define INF 987654321
#define MAX_SUB 12
#define MAX_SEME 10

int numSubject;
int numHaveTo;
int numSemester;
int maxSubject;
int preInfo[MAX_SUB];
int ciriculum[MAX_SEME];
int minSemester;

int cache[1 << MAX_SUB][MAX_SEME];

void addInfo(int& beforeInfo, int& newId)
{
	beforeInfo |= (1 << newId);
}

int CalcMinSeme(int beforeLearnSubject, int curSemester)
{
	if (std::bitset<32>(beforeLearnSubject).count() >= (unsigned int)numHaveTo)
		return 0;
	if (curSemester >= numSemester)
		return INF;

	if (cache[beforeLearnSubject][curSemester] >= 0)
		return cache[beforeLearnSubject][curSemester];

	int min = CalcMinSeme(beforeLearnSubject, curSemester + 1);

	int canLearn = 0;
	for (int i = 0; i < numSubject; i++)
	{
		if ((preInfo[i] & beforeLearnSubject) == preInfo[i])
			addInfo(canLearn, i);
	}
	canLearn &= ciriculum[curSemester];
	canLearn &= ~(beforeLearnSubject);

	for (int learn = canLearn; learn; learn = ((learn - 1) & canLearn))
	{
		if (std::bitset<32>(learn).count() > (unsigned int)maxSubject)
			continue;

		int totalLearn = beforeLearnSubject | learn;
		int ret = CalcMinSeme(totalLearn, curSemester + 1) + 1;
		//if (ret > INF) ret = INF;
		min = ret < min ? ret : min;
		//printf("learn: %d\n", learn);
	}

	cache[beforeLearnSubject][curSemester] = min;
	return min;
}

void problem_solve()
{
	//init
	minSemester = INF;
	for (int i = 0; i < MAX_SEME; i++)
		ciriculum[i] = 0;
	memset(cache, -1, sizeof(cache));


	scanf("%d %d %d %d", &numSubject, &numHaveTo, &numSemester, &maxSubject);

	//input preSub
	for (int i = 0; i < numSubject; i++)
	{
		preInfo[i] = 0; //init
		int numPre;
		scanf("%d", &numPre);
		for (int j = 0; j < numPre; j++)
		{
			int tmp;
			scanf("%d", &tmp);
			addInfo(preInfo[i], tmp);
		}
	}

	//input ciriculum
	for (int i = 0; i < numSemester; i++)
	{
		int subNum;
		scanf("%d", &subNum);
		
		for (int j = 0; j < subNum; j++)
		{
			int subId;
			scanf("%d", &subId);
			addInfo(ciriculum[i], subId);
		}
	}

	int result = CalcMinSeme(0, 0);
	if (result >= INF)
		printf("IMPOSSIBLE\n");
	else
		printf("%d\n", result);
}


int main()
{
	int numTestCase;
	scanf("%d", &numTestCase);

	for (int i = 0; i < numTestCase; i++)
		problem_solve();

	return 0;
}