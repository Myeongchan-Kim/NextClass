#include <iostream>
#include <vector>
using namespace std;

enum ORDER {
	LU,
	RU,
	LL,
	RL,
};

string Reversion(string& str)
{
	if (str[0] != 'x')
		return str;

	string tree[4];
	int startPos = 1;
	int nextPos = 2;

	for (int order = LU; order <= RL; order++)
	{
		for (int i = startPos; i < nextPos; i++)
		{
			if (str[i] == 'x')
				nextPos += 4;
		}
		tree[order] = str.substr(startPos, nextPos - startPos);
		startPos = nextPos;
		nextPos += 1;
	}

	for (int i = 0; i < 4; i++)
	{
		tree[i] = Reversion(tree[i]);
	}

	return "x" + tree[LL] + tree[RL] + tree[LU] + tree[RU];
}

void problem_solve()
{
	char inputString[1001];
	cin >> inputString;
	string inputStr = string(inputString);

	string result = Reversion(inputStr);

	cout << result.c_str() << endl;
}

int main()
{
	int N = 0;
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		problem_solve();
	}

	return 0;
}