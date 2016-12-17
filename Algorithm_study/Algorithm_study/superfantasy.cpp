#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <memory.h>
#include <limits>
#include <bitset>
#include <string>

#define INF 987654321
char target[1000002] = { 0, };
char ppap[] = "pen-pineapple-apple-pen/";
char ppap2[] = "pen-pineapple-apple-pen/pen-pineapple-apple-pen/";

void problem_solv()
{
	long long int N, M, r0, c0, r, c, A, B;
	auto ret = scanf("%lld %lld %lld %lld %lld %lld %lld %lld", &N, &M, &r0, &c0, &r, &c, &A, &B);

	long long int deltaX = abs(r - r0);
	long long int deltaY = abs(c - c0);

	long long int Xtimes;
	long long int Ytimes;

	if (deltaX == 0 && A == 0)
		Xtimes = 0;
	else
		Xtimes = deltaX / A;

	if (deltaY == 0 && B == 0)
		Ytimes = 0;
	else
		Ytimes = deltaY / B;
	

	if (deltaX%A != 0)
		Xtimes++;
	if (deltaY%B != 0)
		Ytimes++;

	printf("%lld\n", Xtimes + Ytimes);
}

int main()
{
	
	int N;
	auto ret = scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		problem_solv();
	}
	return 0;
}