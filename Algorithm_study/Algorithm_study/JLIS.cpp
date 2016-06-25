#include <iostream>
#include <vector>
#include <limits>       // std::numeric_limits
using namespace std;

vector<long long> Alist;
vector<long long> Blist;
long long resultTable[101][101] = { 0, };

int MaxJLIS(int offsetA, int offsetB)
{
	if (resultTable[offsetA][offsetB] != 0)
		return resultTable[offsetA][offsetB];

	long long largeVal = (Alist[offsetA] > Blist[offsetB] ? Alist[offsetA] : Blist[offsetB]);
	int Maxresult = 2;
	int result;
	for (int ai = offsetA + 1; ai < Alist.size(); ai++)
	{
		if (largeVal < Alist[ai])
		{
			result = 1 + MaxJLIS(ai, offsetB);
			if (Maxresult < result)
				Maxresult = result;
		}
	}

	for (int bi = offsetB + 1; bi < Blist.size(); bi++)
	{
		if (largeVal < Blist[bi])
		{
			result = 1 + MaxJLIS(offsetA, bi);
			if (Maxresult < result)
				Maxresult = result;
		}
	}

	resultTable[offsetA][offsetB] = Maxresult;
	return Maxresult;
}

void problem_solve()
{
	//initial
	Alist.clear();
	Blist.clear();
	for (int i = 0; i < 101; i++)
		for (int j = 0; j < 101; j++)
			resultTable[i][j] = 0;

	Alist.push_back(numeric_limits<int>::min());
	Blist.push_back(numeric_limits<int>::min());

	int aSize, bSize;
	scanf("%d %d",&aSize, &bSize);

	for (int i = 0; i < aSize; i++)
	{
		long long eleA;
		scanf("%lld", &eleA);
		Alist.push_back(eleA);
	}
	for (int i = 0; i < bSize; i++)
	{
		long long eleB;
		scanf("%lld", &eleB);
		Blist.push_back(eleB);
	}

	int result = MaxJLIS(0, 0);
	cout << result - 2 << endl;
}

int main()
{
	int N;
	cin >> N;
	for (int i = 0; i < N; i++)
		problem_solve();

	return 0;
}