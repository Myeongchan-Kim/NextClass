#include <iostream>
#include <vector>
using namespace std;

const int dx[8] = { +0, +1, +1, +1, +0, -1, -1, -1 };
const int dy[8] = { -1, -1, +0, +1, +1, +1, +0, -1 };
char board[5][5];

bool FindString(int x, int y, const string& str)
{
	if (x < 0 || x >= 5 || y < 0 || y >= 5)
		return false;

	if (board[x][y] != str[0])
		return false;

	if (str.size() == 1)
		return true;

	for (int dir = 0; dir < 8; dir++)
		if (FindString(x + dx[dir], y + dy[dir], str.substr(1)))
			return true;
	
	return false;
}

void Find()
{
	char tmp[10];
	cin >> tmp;
	string str(tmp);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (FindString(i, j, str))
			{
				cout << str.c_str() << " YES" << endl;
				return;
			}
		}
	}
	cout << str.c_str() << " NO" << endl;
}

void problem_solve()
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			board[5][5] = 0;

	char line[6];
	for (int i = 0; i < 5; i++)
	{
		cin >> line;
		for (int j = 0; j < 5; j++)
		{
			board[i][j] = line[j];
		}
	}

	int wordNum = 0;
	cin >> wordNum;
	for (int i = 0; i < wordNum; i++)
	{
		Find();
	}
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