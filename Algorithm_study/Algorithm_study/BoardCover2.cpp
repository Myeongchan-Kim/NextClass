#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <limits>

#define INF 987654321
#define MAX_SIZE 10

struct Board
{
	static int H;
	static int W;
	bool info[MAX_SIZE][MAX_SIZE];
};

struct Block
{
	static int R;
	static int C;
	bool pieceInfo[MAX_SIZE][MAX_SIZE];
};

int Board::H = 0;
int Board::W = 0;
int Block::R = 0;
int Block::C = 0;

Block mainBlock = {};
Block blockList[4] = {};
Board board = {};

int GetMaxCoverCount()
{
	return 0;
}

void problem_solve()
{
	scanf("%d %d %d %d", &Board::H, &Board::W, &Block::R, &Block::C);
	char rowStr[MAX_SIZE+2];

	for (int i = 0; i < Board::H; i++)
	{
		scanf("%s\n", &rowStr);
		for (int j = 0; j < Board::W; j++)
		{
			if (rowStr[i] == '.')
				board.info[i][j] = true;
		}
	}

	for (int i = 0; i < Block::R; i++)
	{
		scanf("%s\n", &rowStr);
		for (int j = 0; j < Block::C; j++)
		{
			if (rowStr[i] == '.')
				mainBlock.pieceInfo[i][j] = true;
		}
	}

	int result = GetMaxCoverCount();

	printf("%d", result);
}

int main()
{
	int problem_N;

	scanf("%d", &problem_N);

	for (int i = 0; i < problem_N; i++)
	{
		problem_solve();
	}

	return 0;
}