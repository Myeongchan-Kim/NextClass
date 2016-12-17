#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <memory.h>
#include <limits>
#include <bitset>

#define INF 987654321
#define MAX_R 24
#define MAX_C 80

int status[MAX_R + 1][MAX_C + 1] = { 0, };
char input[MAX_R + 1][MAX_C + 1] = { 0, };
int row;
int col;

int check_02356789(int iPos, int jPos)
{
	int i = iPos;
	int j = jPos;

	//check below
	if(input[i+1][j] == '*')
		return check_
}

int check_14(int iPos, int jPos)
{
	int i = iPos;
	int j = jPos;
	// go down
	while (true)
	{
		status[i][j] = 2;
		
		if (input[i + 1][j] != '*' && input[i][j + 1] != '*')
			return 1;
		
		if (input[i + 1][j] != '*' && input[i][j + 1] == '*')
			return 4;
		i++;

		if (i > row)
		{
			return -INF;
		}
	}
	
}

int make_number() 
{
	char cur_char = input[0][0];

	//status 0: not checked , 1: now checking , 2: checked;
	
	int result = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (status[i][j] == 2)
				continue;
			
			if (input[i][j] != '*')
				continue;

			if (input[i][j + 1] == '*')
			{
				int num = check_02356789(i, j);
				result += num;
				status[i][j] = 2;
				return;
			}
			else {
				int num = check_14(i, j);
				result += num;
				status[i][j] = 2;
				return;
			}
		}
	}
	
	return result;
}

void problem_solve() 
{
	scanf("%d %d", &row, &col);
	for (int i = 0; i < row; i++)
	{
		scanf("%s", input[i]);
		input[i][col] = 0;
	}

	int result = 0;
	while (true)
	{
		result = make_number();
	}

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




