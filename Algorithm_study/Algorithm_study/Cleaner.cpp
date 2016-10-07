#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <limits>

#define INF 987654321
#define MAX_SIZE 7

int N;
int M;

int room[MAX_SIZE][MAX_SIZE] = {0,};
bool visitable[MAX_SIZE][MAX_SIZE];

int CountWay(int curTime, int startX, int startY, int endX, int endY)
{
	if (startX < 0 || startY < 0 || startX >= N || startY >= M)
		return 0;
	if (room[startX][startY] != -1 && room[startX][startY] != curTime)
		return 0;
	if (startX == endX && startY == endY && curTime == N * M - 1)
		return 1;

	int result = 0;

	int old = room[startX][startY];
	room[startX][startY] = curTime;

	result += CountWay(curTime + 1, startX + 1, startY, endX, endY);
	result += CountWay(curTime + 1, startX - 1 , startY, endX, endY);
	result += CountWay(curTime + 1, startX, startY + 1, endX, endY);
	result += CountWay(curTime + 1, startX, startY - 1, endX, endY);

	room[startX][startY] = old;

	return result;
}

void init_visitable()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			visitable[i][j] = false;
	for (int i = N; i < MAX_SIZE; i++)
		for (int j = M; j < MAX_SIZE; j++)
			visitable[i][j] = true;
}

void problem_solve()
{
	scanf("%d %d", &N, &M);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			scanf("%d", &room[i][j]);
		}
	}
	
	if (N % 2 == 0 && M % 2 == 0)
	{
		printf("0\n");
		return;
	}

	int result = CountWay(0, 0, 0, N-1, M-1);
	printf("%d\n", result);
}

int main()
{
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		problem_solve();
	}
	return 0;
}