#include <iostream>
#include <vector>

using namespace std;

int N, L, R;
long long int resultTable[101][101][101];

long long int CalcBuildingComb(int curHeight, int leftRemain, int rightRemain)
{
	if (curHeight == 0)
	{
		if (leftRemain == 0 && rightRemain == 0)
			return 1;
		else
			return 0;
	}

	if (resultTable[curHeight][leftRemain][rightRemain] != -1)
		return resultTable[curHeight][leftRemain][rightRemain];

	long long int result = 0;
	if (leftRemain != 0)
	{
		result += CalcBuildingComb(curHeight - 1, leftRemain - 1, rightRemain);
		result %= 1000000007;
	}
	if (rightRemain != 0)
	{
		result += CalcBuildingComb(curHeight - 1, leftRemain, rightRemain - 1);
		result %= 1000000007;
	}
	
	result += CalcBuildingComb(curHeight - 1, leftRemain, rightRemain) * (N - curHeight - 1);
	result %= 1000000007;

	resultTable[curHeight][leftRemain][rightRemain] = result;
	return result;
}

int main()
{
	cin >> N >> L >> R;

	//reset
	for (int i = 0; i < 101; i++)
		for (int j = 0; j < 101; j++)
			for (int k = 0; k < 101; k++)
				resultTable[i][j][k] = -1;

	cout << CalcBuildingComb(N - 1, L - 1, R - 1) << endl;

	return 0;
}