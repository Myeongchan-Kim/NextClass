#include "MatrixMultiple.h"
#define MAX_VAL 987654321

int MatrixMultiple::CalcSmalistMul(int startId, int endId, Matrix * M)
{
	if (startId == endId)
		return 0;
	if (minTable[startId][endId] != -1)
		return minTable[startId][endId];

	int minVal = MAX_VAL;
	for (int endOfFirst = startId; endOfFirst < endId; endOfFirst++)
	{
		int val =
			CalcSmalistMul(startId, endOfFirst, M) +
			CalcSmalistMul(endOfFirst + 1, endId, M) +
			M[startId].row * M[endOfFirst].col * M[endId].col;
		if (minVal > val) minVal = val;
	}
	minTable[startId][endId] = minVal;
	return minVal;
}

int MatrixMultiple::CalcSmalistMulBottomUp(Matrix * M, int N)
{
	for (int startId = N - 1; startId > 0; startId--)
	{
		for (int endId = startId; endId < N; endId++)
		{
			if (endId == startId)
			{
				minTable[startId][endId] = 0;
			}
			else
			{
				int minVal = MAX_VAL;
				for (int endOfFirst = startId; endOfFirst < endId; endOfFirst++)
				{
					int val =
						minTable[startId][endOfFirst] +
						minTable[endOfFirst + 1][endId] +
						+M[startId].row * M[endOfFirst].col * M[endId].col;

					if (minVal > val) minVal = val;
				}
				minTable[startId][endId] = minVal;
			}// else
		}// endid
	}//startid
	return minTable[0][maxSize - 1];
}
