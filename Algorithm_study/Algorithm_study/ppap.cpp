#define _SCL_SECURE_NO_WARNINGS

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

void problem_solv()
{
	int sPos, ePos;
	char str[10002];

	scanf("%d %d %s", &sPos, &ePos, str);

	std::string fullstring = target;
	char buffer[1000000 + 2] = {0};

	fullstring.copy(buffer, ePos - sPos +1, sPos - 1);
	
	std::string targetStr = buffer;
	std::string srcStr = str;
	std::size_t found = 0;
	int count1 = 0;

	found = targetStr.find(srcStr);
	while (found != std::string::npos)
	{
		count1++;
		found = targetStr.find(srcStr, found + 1);
	}

	printf("%d\n", count1);
}

int main()
{
	for (int i = 0; i < 1000000 + 2; i++)
	{
		target[i] = ppap[i % 24];
	}

	
	problem_solv();
	
	return 0;
}