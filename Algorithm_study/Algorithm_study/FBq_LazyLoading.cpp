#include <iostream>
#include <deque>
#include <algorithm>
#include <functional>

void problem_solve(int case_num)
{
	int N;
	scanf("%d", &N);

	std::deque<int> weights;

	for (int i = 0; i < N; i++)
	{
		int weight;
		scanf("%d", &weight);

		weights.push_back(weight);
	}

	std::sort(weights.begin(), weights.end(), std::greater<int>());
	int trip = 0;

	while (!weights.empty())
	{
		int top = weights.front(); // hevist one.
		int count = 1;
		weights.pop_front();
		while (!weights.empty() && top * count < 50)
		{
			weights.pop_back();
			count++;
		}

		if(top * count >= 50)
			trip++;
	}

	printf("Case #%d: %d\n", case_num, trip);
	// Case #1: 2
	// Case #3: 2
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