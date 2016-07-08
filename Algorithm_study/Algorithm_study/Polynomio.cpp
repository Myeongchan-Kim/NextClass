#include <iostream>
#include <vector>

using namespace std;
int resultTable[101][101];

int PolyCount(int beforeCount, int remainBlock)
{
	if (remainBlock == 0)
		return 1;

	if (resultTable[beforeCount][remainBlock] != -1)
		return resultTable[beforeCount][remainBlock];

	int totalCount = 0;
	for (int thisSelectBlockCount = 1; thisSelectBlockCount <= remainBlock; thisSelectBlockCount++)
	{
		int tmpResult = PolyCount(thisSelectBlockCount, remainBlock - thisSelectBlockCount) * (thisSelectBlockCount + beforeCount - 1);
		totalCount += tmpResult;
		totalCount %= 10000000;
	}
	
	resultTable[beforeCount][remainBlock] = totalCount;
	return totalCount;
}

int PolyCountStart(int blockNum)
{
	int result = 0;
	for (int startBlockNum = 1; startBlockNum <= blockNum; startBlockNum++)
	{
		int tmpResult = PolyCount(startBlockNum, blockNum - startBlockNum);;
		result += tmpResult;
		result %= 10000000;
	}

	return result;
}

void problem_solve()
{
	int blockNum = 0;
	cin >> blockNum;

	for (int i = 0; i < 101; i++)
		for (int j = 0; j < 101; j++)
			resultTable[i][j] = -1;

	cout << PolyCountStart(blockNum) << endl;
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