#pragma once

class MatrixMultiple
{
public:

	struct Matrix {
		int row;
		int col;
		int** ele;
	};

	MatrixMultiple(const int maxSize) : maxSize(maxSize)
	{
		minTable = new int*[maxSize];
		for (int i = 0; i < maxSize; i++)
			minTable[i] = new int[maxSize];

		//init
		for (int i = 0; i < maxSize; i++)
			for (int j = 0; j < maxSize; j++)
				minTable[i][j] = -1;
	};

	~MatrixMultiple()
	{
		for (int i = 0; i < maxSize; i++)
			delete[] minTable[i];
		delete[] minTable;
	};

	const int maxSize;
	int** minTable;

	int CalcSmalistMul(int startId, int endId, Matrix* M);
	int CalcSmalistMulBottomUp(Matrix* M, int N);
};