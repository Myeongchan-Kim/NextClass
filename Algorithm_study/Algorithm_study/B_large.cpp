#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <stack>
#include <math.h>
#include <memory.h>
#include <queue>

void solve(int c)
{
	int n;
	scanf("%d", &n);
	int u[6];

	for (int i = 0; i < 6; i++)
	{
		scanf("%d", &u[i]);
	}

	if (u[3] > u[0] || u[5] > u[2] || u[1] > u[4])
	{
		printf("IMPOSSIBLE\n");
		return;
	}

	u[0] -= u[3];
	u[2] -= u[5];
	u[4] -= u[1];

	int max = std::max({ u[0], u[2], u[4] });

	if (max > u[0] + u[2] + u[4] - max)
	{
		printf("IMPOSSIBLE\n");
		return;
	}

	if (u[0] == 0 && (u[2] > 0 || u[4] > 0) && u[3] != 0)
	{
		printf("IMPOSSIBLE\n");
		return;
	}

	if (u[2] == 0 && (u[0] > 0 || u[4] > 0) && u[5] != 0)
	{
		printf("IMPOSSIBLE\n");
		return;
	}

	if (u[4] == 0 && (u[0] > 0 || u[2] > 0) && u[1] != 0)
	{
		printf("IMPOSSIBLE\n");
		return;
	}

	std::string answer;

	std::vector<std::pair<int, char>> pairs = { { u[0], 'R' },{ u[2], 'Y' },{ u[4], 'B' } };

	std::sort(pairs.begin(), pairs.end(), [](auto a, auto b) { return a.first > b.first; });

	while (pairs[0].first > 0)
	{
		answer.push_back(pairs[0].second);
		pairs[0].first--;
	}

	int index = 1;
	while (pairs[1].first > 0)
	{
		answer.insert(answer.begin() + std::min((int)answer.size(), index), pairs[1].second);
		index += 2;
		pairs[1].first--;
	}

	index = 0;

	while (pairs[2].first > 0)
	{
		answer.insert(answer.begin() + answer.size() - index, pairs[2].second);
		index += 2;
		pairs[2].first--;
	}

	for (int i = 0; i < answer.size(); i++)
	{
		if (answer[i] == 'R')
		{
			while (u[3] > 0)
			{
				answer.insert(i + 1, "GR");
				u[3]--;
			}
		}
		if (answer[i] == 'Y')
		{
			while (u[5] > 0)
			{
				answer.insert(i + 1, "VY");
				u[5]--;
			}
		}
		if (answer[i] == 'B')
		{
			while (u[1] > 0)
			{
				answer.insert(i + 1, "OB");
				u[1]--;
			}
		}
	}

	while (u[3] > 0)
	{
		answer.insert(answer.size(), "GR");
		u[3]--;
	}

	while (u[5] > 0)
	{
		answer.insert(answer.size(), "VY");
		u[5]--;
	}

	while (u[1] > 0)
	{
		answer.insert(answer.size(), "OB");
		u[1]--;
	}

	for (int i = 0; i < answer.size(); i++)
	{
		auto now = answer[i];
		auto next = answer[(i + 1) % answer.size()];
		auto prev = answer[i > 0 ? i - 1 : answer.size() - 1];
		if (answer[i] == answer[(i + 1) % answer.size()])
		{
			printf("error case : %d\n", c);
			break;
		}

		if (now == 'O' && (next != 'B' || prev != 'B'))
		{
			printf("error case : %d\n", c);
			break;
		}

		if (now == 'G' && (next != 'R' || prev != 'R'))
		{
			printf("error case : %d\n", c);
			break;
		}

		if (now == 'V' && (next != 'Y' || prev != 'Y'))
		{
			printf("error case : %d\n", c);
			break;
		}
	}

	std::cout << answer << std::endl;
}

int main()
{
	int t;

	scanf("%d", &t);

	for (int i = 1; i <= t; i++)
	{
		printf("Case #%d: ", i);
		solve(i);
	}
}