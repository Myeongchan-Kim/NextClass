#include <iostream>
#define MAX_R 10001
#define MAX_C 501

int R, C;
char map[MAX_R][MAX_C];

void fillMap(int * path, int len) 
{
	for (int j = 0; j < C; j++)
		map[path[j]][j] = 'x';
	/*for (int i = 0; i < R; i++)
		printf("%s\n", map[i]);
	printf("\n");*/
}

bool findPath(int curRow, int curCol, int* path)
{
	if (curRow < 0 || curRow >= R || curCol >= C)
		return false;
	if (map[curRow][curCol] == 'x')
		return false;

	if (curCol == C - 1)
	{
		path[C - 1] = curRow;
		return true;
	}

	if (findPath(curRow - 1, curCol + 1, path)) 
	{
		path[curCol] = curRow;
		return true;
	}
	map[curRow - 1][curCol + 1] = 'x';

	if (findPath(curRow, curCol + 1, path))
	{
		path[curCol] = curRow;
		return true;
	}
	map[curRow][curCol + 1] = 'x';
	
	if (findPath(curRow + 1, curCol + 1, path))
	{
		path[curCol] = curRow;
		return true;
	}
	map[curRow + 1][curCol + 1] = 'x';
	
	return false;
}

int findAndFill(int rowNum)
{
	int path[MAX_C];
	for (int i = 0; i < C; i++)
		path[i] = -1;

	int result = 0;
	if (findPath(rowNum, 0, path))
	{
		result = 1;
		fillMap(path, C);
		for (int i = 0; i < C; i++)
			path[i] = -1;
	}

	return result;
}

int main() 
{
	scanf("%d %d", &R, &C);
	for (int i = 0; i < R; i++)
	{
		scanf("%s", map[i]);
		for (int j = 0; j <= C; j++)
			if (map[i][j] == '\n')
				map[i][j] = '\0';
	}

	int count = 0;
	for (int i = 0; i < R; i++)
	{
		count += findAndFill(i);
	}

	printf("%d\n", count);
	return 0;
}