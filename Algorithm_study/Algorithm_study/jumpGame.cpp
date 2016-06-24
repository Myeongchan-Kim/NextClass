#include <iostream>
using namespace std;

int boardSize;
bool visitable[101][101] = { 0, };
int map[101][101] = { 0, };

void checkPoint(int x, int y)
{
	if (visitable[x][y] == true || x >= boardSize || y >= boardSize)
		return;
	visitable[x][y] = true;
	checkPoint(x + map[x][y], y);
	checkPoint(x, y + map[x][y]);
}

void problem_solve()
{
	cin >> boardSize;

	//√ ±‚»≠
	for (int i = 0; i < boardSize; i++)
		for (int j = 0; j < boardSize; j++)
		{
			visitable[i][j] = false;
			scanf("%d", &map[i][j]);
		}

	checkPoint(0, 0);

	if (visitable[boardSize - 1][boardSize - 1])
		cout << "YES" << endl;
	else
		cout << "NO" << endl;

	return;
}


int main()
{
	int N;
	cin >> N;

	for (int i = 0; i < N; i++)
		problem_solve();

	return  0;;
}
