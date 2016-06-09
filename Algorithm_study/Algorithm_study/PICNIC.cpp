#include <iostream>
#include <vector>
using namespace std;

bool friendTable[10][10];
int totalStudent;

int SelectFriend(bool selected[10])
{
	bool allSelected = true;
	for (int i = 0; i < totalStudent; i++)
		if (selected[i] == false)
			allSelected = false;

	if (allSelected)
		return 1;

	int sum = 0;
	for (int i = 0; i < totalStudent; i++)
	{
		for (int j = i+1; j < totalStudent; j++)
		{
			if (selected[i] || selected[j])
				continue;
			if (friendTable[i][j])
			{
				selected[i] = true;
				selected[j] = true;
				sum += SelectFriend(selected);
				selected[i] = false;
				selected[j] = false;
			}
		}
	}

	return sum;
}

int calcCount()
{
	bool selected[10];
	for (int i = 0; i < 10; i++)
		selected[i] = false;

	int result = SelectFriend(selected);
	int permutation = 1;
	for (int i = 1; i <= totalStudent / 2; i++)
		permutation *= i;
	result /= permutation;
	return result;
}

void problem_solve()
{
	int coupleNum = 0;
	scanf("%d %d", &totalStudent, &coupleNum);

	//table init.
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			friendTable[i][j] = false;

	//make relation of freind table.
	for (int i = 0; i < coupleNum; i++)
	{
		int friend1;
		int friend2;
		cin >> friend1 >> friend2;
		friendTable[friend1][friend2] = true;
		friendTable[friend2][friend1] = true;
	}
	
	//calcluation.
	int result = calcCount();
	cout << result << endl;
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