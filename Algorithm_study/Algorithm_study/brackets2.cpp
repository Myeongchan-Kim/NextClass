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

int N;
std::map<char, char> symbList;

bool checkRightBracket(std::string& row)
{
	std::stack<char> charStack;
	for (auto iter = row.begin(); iter != row.end(); iter++)
	{
		char c = *iter;
		if (symbList.find(c) != symbList.end())
			charStack.push(c);
		else
		{
			char symbol = '\0';
			if (charStack.empty())
				return false;

			symbol = charStack.top();
			charStack.pop();

			auto result = symbList.find(symbol);
			if (c != result->second)
				return false;
		}
	}

	if (charStack.empty())
		return true;
	else
		return false;
}

void problem_solv()
{
	scanf("%d", &N);
	
	for (int i = 0; i < N; i++)
	{
		std::string row;
		std::cin >> row;

		if (checkRightBracket(row))
			printf("YES\n");
		else
			printf("NO\n");
	}
}

int main()
{

	symbList.insert({ '{', '}' });
	symbList.insert({ '[', ']' });
	symbList.insert({ '(', ')' });
	problem_solv();
	return 0;
}