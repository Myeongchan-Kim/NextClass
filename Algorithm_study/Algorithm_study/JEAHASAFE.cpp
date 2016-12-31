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

#define MAX_N 1000001

std::string current;
std::string next;

enum DIR {
	COLOCKWISE,
	REVERSWISE
};

std::vector<int> getPartialMatch(std::string& needle)
{
	std::vector<int> p = std::vector<int>(needle.length(), 0);
	p.reserve(needle.length());
	int begin = 1;
	int matched = 0;
	
	while (begin + matched < needle.length())
	{
		if (needle[begin + matched] == needle[matched])
		{
			++matched;
			p[begin + matched - 1] = matched;
		}
		else {
			if (matched == 0)
				begin++;
			else {
				begin += matched - p[matched - 1];
				matched = p[matched - 1];
			}
		}
	}

	return p;
}

int KMP_find_first(std::string & haystack, std::string& needle)
{
	int begin = 0;
	int matched = 0;
	std::vector<int> p = getPartialMatch(needle);

	while (begin <= haystack.length() - needle.length())
	{
		if (haystack[begin + matched] == needle[matched])
		{
			++matched;

			if (matched == needle.length()) return begin;
		}
		else {
			if (matched == 0)
			{
				++begin;
			}
			else {
				begin += matched - p[matched - 1];
				matched = p[matched - 1];
			}
		}

	}
}

int getRotation(DIR direction, std::string& source, std::string& target)
{
	std::string haystack;
	std::string needle;

	if (direction == COLOCKWISE)
	{
		haystack = target + target;
		needle = source;
	}
	else {
		haystack = source + source;
		needle = target;
	}

	int result = KMP_find_first(haystack, needle);
	
	return result;
}

void problem_solve()
{
	int N;
	scanf("%d", &N);

	std::cin >> current;

	int sum = 0;
	for (int i = 1; i < N + 1; i++)
	{
		std::cin >> next;

		DIR direction;
		if (i % 2 == 1)
			direction = COLOCKWISE;
		else
			direction = REVERSWISE;

		sum += getRotation(direction, current, next);

		current = next;
	}

	printf("%d\n", sum);
}


int main()
{
	int T;
	scanf("%d", &T);
	for (int i = 0; i < T; i++)
	{
		problem_solve();
	}
	return 0;
}

