#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
#include <memory>

#define DIV 1000000007

int N, M;
std::vector<int> umbrellas;

std::map<std::pair<int, int>, unsigned long long> cache;
unsigned long long fact[2002] = {0,};

unsigned long long H(int n, int r)
{
	//return combination(n + r - 1, r);
	unsigned long long result = 1;
	int div = 1;
	for (int i = r + 1; i <= n + r - 1; i++)
	{
		result *= i;
		result /= div++;
		result %= DIV;
	}

	return result;
}

unsigned long long factorial(int n)
{
	if (fact[n] > 0)
		return fact[n];

	unsigned long long result = 1;
	for (int i = 1; i <= n; i++)
	{
		result *= i;
		result %= DIV;
	}

	fact[n] = result;
	return result;
}

unsigned long long calcCase(int remnants, int umCount)
{
	if (remnants < 0)
		return 0;
	auto c = cache.find({ umCount, remnants });
	if (c != cache.end())
		return c->second;

	//distribute remnants.
	unsigned long long distCase = H(umCount + 1, remnants);
	//printf("umCount:%d, remnats:%d, distCase:%llu\n",umCount, remnants, distCase);

	//calc factorial
	unsigned long long permuCase = factorial(umCount - 2);

	unsigned long long result = distCase * permuCase % DIV;

	cache[std::pair<int,int>({ umCount, remnants })] = result;
	return result;
}

void problem_solve(int case_num)
{
	umbrellas.clear();
	scanf("%d %d", &N, &M);

	int totalLen = 0;
	for (int i = 0; i < N; i++)
	{
		int R;
		scanf("%d", &R);
		umbrellas.push_back(R);
		totalLen += 2 * R;
	}

	unsigned long long result = 0;

	if (N >= 2)
	{
		for (int i = 0; i < N; i++)
		{
			int left = umbrellas[i];
			for (int j = 0; j < N; j++)
			{
				if (i == j)
					continue;

				int right = umbrellas[j];

				auto tmp = calcCase(M - 1 + left + right - totalLen, N);
				result += tmp;
				result %= DIV;
				//printf("M:%d left:%d right%d totalLen:%d tmp:%llu \n",M, left, right, totalLen,tmp);
			}
		}

	}
	else {
		result = M;
	}
	
	printf("Case #%d: %llu\n", case_num, result);
}

int main() {
	int T;
	scanf("%d", &T);
	for (int i = 0; i < T; i++)
	{
		problem_solve(i + 1);
	}
	return 0;
}