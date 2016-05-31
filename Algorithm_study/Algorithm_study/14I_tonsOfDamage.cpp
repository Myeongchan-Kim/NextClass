#include <iostream>
#include <unordered_map>
#include "time.h"

using namespace std;

double adt, adp, apt, app;
unsigned long long n;

unordered_map<unsigned long long, double> history;

unsigned long long index(unsigned long long ad, unsigned long long ap, unsigned long long n)
{
	unsigned long long _ad = ad;
	unsigned long long _ap = ap;
	unsigned long long _n = n;

	_ad <<= 35;
	_ap <<= 6;
	return _ad | _ap | _n;
}


double CalcExpect(unsigned long long ad, unsigned long long ap, unsigned long long n)
{
	if (n == 0)
		return 0.0;
	unsigned long long adapN = index(ad, ap, n);
	auto p = history.find(adapN);
	if (p != history.end())
	{
		return p->second;
	}

	double result =
		(CalcExpect(ad + 1, ap, n - 1) + (ad + 1) * ap) * adp +
		(CalcExpect(ad * 2, ap, n - 1) + (ad * 2) * ap) * adt +
		(CalcExpect(ad, ap + 1, n - 1) + ad * (ap + 1)) * app +
		(CalcExpect(ad, ap * 2, n - 1) + ad * (ap * 2)) * apt;


	history.insert({ adapN, result });
	return result;
}

void problem_solve()
{
	int ADT, ADP, APT, APP;
	scanf("%lld %d %d %d %d ", &n, &ADT, &ADP, &APT, &APP);
	adt = ADT / 100.0f;
	adp = ADP / 100.0f;
	apt = APT / 100.0f;
	app = APP / 100.0f;

	double result = CalcExpect(0ull, 0ull, n);
	printf("%lf\n", result);
}

int main()
{
	int N = 0;
	cin >> N;


	clock_t before;
	double  result;
	before = clock();

	for (int i = 0; i < N; i++)
	{
		problem_solve();
	}
	result = (double)(clock() - before) / CLOCKS_PER_SEC;

	printf("걸린시간은 %5.2f 입니다.\n", result);

	return 0;
}