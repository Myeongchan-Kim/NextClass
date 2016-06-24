#include <iostream>
using namespace std;

int triangleSize;
int num[101][101] = { 0, };
int rst[101][101] = { 0, };

int CalcMax(int x, int y)
{
	if (x == triangleSize - 1)
		return rst[x][y] = num[x][y];
	if (rst[x][y] != 0)
		return rst[x][y];

	int leftChild = CalcMax(x + 1, y) + num[x][y];
	int rightChild = CalcMax(x + 1, y + 1) + num[x][y];
	int maxVal = (leftChild > rightChild ? leftChild : rightChild);
	rst[x][y] = maxVal;
	return maxVal;
}

void problem_solve()
{
	cin >> triangleSize;

	for (int i = 0; i < triangleSize; i++)
		for (int j = 0; j <= i; j++)
			rst[i][j] = 0;

	for (int i = 0; i < triangleSize; i++)
		for (int j = 0; j <= i; j++)
			scanf("%d", &num[i][j]);

	int max = CalcMax(0, 0);
	cout << max << endl;
	return;
}


int main()
{
	int N;
	cin >> N;

	for (int i = 0; i < N; i++)
		problem_solve();

	return  0;;
}
