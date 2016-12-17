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

#define MAX_N 500000000

std::queue<long long>generator;
std::queue<int>signals;

void clear(std::queue<int>& target)
{
	std::queue<int> empty;
	std::swap(target, empty);
}

void clear(std::queue<long long> target)
{
	std::queue<long long> empty;
	std::swap(target, empty);
}

void problem_solve()
{
	int K, N;
	scanf("%d %d", &K, &N);
	
	int sum = 0;
	int count = 0;
	clear(generator);
	clear(signals);

	long long seed = 1983;
	int signal = seed % 10000 + 1;
	
	for (int i = 0; i < N; i++)
	{
		sum += signal;
		signals.push(signal);
		seed = (seed * 214013 + 2531011) % (1ll << 32);
		signal = seed % 10000 + 1;
		

		while (sum > K && !signals.empty())
		{
			int old = signals.front();
			signals.pop();
			sum -= old;
		}

		if (sum == K)
		{
			count++;
		}
	}

	printf("%d\n", count);
}
int main()
{
	int c;
	scanf("%d", &c);

	for (int i = 0; i < c; i++)
	{
		problem_solve();
	}
	return 0;
}