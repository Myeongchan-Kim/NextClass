#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <stack>
#define _USE_MATH_DEFINES
#include <math.h>
#include <memory.h>
#include <queue>

#define PI M_PI
struct Pair
{
	Pair() {}
	Pair(int s, int e, int w) : start(s), end(e), who(w) {}

	int start;
	int end;
	int who;
};

void solve()
{
	std::vector<Pair> pairs;
	int ac, aj;

	scanf("%d %d", &ac, &aj);

	int remains[2] = { 720, 720 };

	for (int i = 0; i < ac; i++)
	{
		int start, end;

		scanf("%d %d", &start, &end);

		pairs.emplace_back(start, end, 0);
		remains[0] -= end - start;
	}

	for (int i = 0; i < aj; i++)
	{
		int start, end;
		scanf("%d %d", &start, &end);

		pairs.emplace_back(start, end, 1);
		remains[1] -= end - start;
	}

	std::sort(pairs.begin(), pairs.end(), [](const Pair& l, const Pair& r)
	{
		return l.start < r.start;
	});


	for (int w = 0; w < 2; w++)
	{
		while (true)
		{
			int minGap = 987654321;
			int minIndex = -1;

			for (int i = 0; i < pairs.size(); i++)
			{
				if (pairs[i].who != w || pairs[(i + 1) % pairs.size()].who != w)
					continue;

				int gap = pairs[(i + 1) % pairs.size()].start - pairs[i].end;
				if (gap < 0) gap += 1440;

				if (gap <= remains[w] && gap < minGap)
				{
					minGap = gap;
					minIndex = i;
				}
			}

			if (minIndex == -1)
				break;

			remains[w] -= minGap;

			Pair newPair = pairs[minIndex];
			newPair.end = pairs[(minIndex + 1) % pairs.size()].end;

			if (minIndex != pairs.size() - 1)
			{
				pairs.erase(pairs.begin() + minIndex);
				pairs.erase(pairs.begin() + minIndex);
				pairs.push_back(newPair);
			}
			else
			{
				pairs.erase(pairs.begin() + minIndex);
				pairs.erase(pairs.begin());
				pairs.push_back(newPair);
			}

			std::sort(pairs.begin(), pairs.end(), [](const Pair& l, const Pair& r)
			{
				return l.start < r.start;
			});
		}
	}

	int count = 0;

	for (int i = 0; i < pairs.size(); i++)
	{
		int gap = pairs[(i + 1) % pairs.size()].start - pairs[i].end;

		if (gap < 0)gap += 1440;

		if (gap != 0)
		{
			Pair pair(pairs[i].end, pairs[(i + 1) % pairs.size()].start, (pairs[i].who + 1) % 2);
			pairs.push_back(pair);
			std::sort(pairs.begin(), pairs.end(), [](const Pair& l, const Pair& r)
			{
				return l.start < r.start;
			});
		}
	}

	for (int i = 0; i < pairs.size(); i++)
	{
		if (pairs[i].who != pairs[(i + 1) % pairs.size()].who)
			count++;
	}

	printf("%d\n", count);
}

int main()
{
	int T;

	scanf("%d", &T);

	for (int i = 1; i <= T; i++)
	{
		printf("Case #%d: ", i);
		solve();
	}

	return 0;
}