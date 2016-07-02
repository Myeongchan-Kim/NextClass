#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

int resultTable[10][101][1025];

int addKey(int beforeKey , int newEle)
{
	int bit = 1;
	bit <<= newEle;
	return beforeKey | bit;
}

int CalcStair(int startNum, int alreadySelectedKey, int remainLength)
{
	if (startNum > 9 || startNum < 0)
		return 0;
	if (remainLength == 0)
	{
		if (alreadySelectedKey == 1023)
			return 1;
		else
			return 0;
	}
	if (resultTable[startNum][remainLength][alreadySelectedKey] != -1)
		return resultTable[startNum][remainLength][alreadySelectedKey];

	int upNum = startNum + 1;
	int downNum = startNum - 1;
	int result = 
		CalcStair(upNum, addKey(alreadySelectedKey, upNum), remainLength - 1) +
		CalcStair(downNum, addKey(alreadySelectedKey, downNum), remainLength - 1);

	result %= 1000000000;

	resultTable[startNum][remainLength][alreadySelectedKey] = result;
	return result;
}

int problemSolve(int N)
{
	int result = 0;
	for (int i = 1; i < 10; i++)
	{
		result += CalcStair(i, addKey(0, i), N - 1);
		result %= 1000000000;
	}
	return result;
}

int main()
{
	int N;
	cin >> N;

	//√ ±‚»≠
	for(int k = 0 ;k <10; k++)
		for (int i = 0; i < 101; i++)
			for (int j = 0; j < 1025; j++)
				resultTable[k][i][j] = -1;
	
	int result = problemSolve(N);

	cout << result << endl;
	return 0;
}