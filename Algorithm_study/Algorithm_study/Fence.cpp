#include <iostream>
#include <vector>
using namespace std;

vector<int> fence;

int MaxRect(int startPos, int endPos)
{
	//	[startPos , endPos - 1] 범위 안에서 가장 큰 직사각형의 넓이
	if (startPos + 1 == endPos)
		return fence[startPos];
	
	int max = 0;

	int midPos = (endPos - startPos) / 2 + startPos;
	
	int leftMax = MaxRect(startPos, midPos);
	int rightMax = MaxRect(midPos, endPos);

	max = (leftMax > rightMax ? leftMax : rightMax);
	
	int startInter = midPos - 1;
	int finishInter = midPos;
	//printf("statPos=%d, endPos=%d, startInter=%d, finishInter=%d\n", startPos, endPos, startInter, finishInter);
	while (true)
	{
		//height 설정
		int height = (fence[startInter] < fence[finishInter] ? fence[startInter] : fence[finishInter]);

		//left expand
		while (startInter > startPos && fence[startInter - 1] >= height)
			startInter--;

		//right expand
		while (finishInter < endPos - 1 && fence[finishInter + 1] >= height)
			finishInter++;

		int InterRectSize = (finishInter + 1 - startInter) * height;
		//printf(" [%d, %d] height = %d, rect = %d\n", startInter, finishInter, height, InterRectSize);
		//set max;
		max = (max > InterRectSize ? max : InterRectSize);

		if (startInter == startPos && finishInter == endPos - 1)
			break;

		if (startInter == startPos)
		{
			finishInter++;
			continue;
		}
		else if (finishInter == endPos - 1)
		{
			startInter--;
			continue;
		}
		else if (fence[startInter - 1] > fence[finishInter + 1])
		{
			startInter--;
		}
		else
		{
			finishInter++;
		}
	}
	//printf("[%d, %d]curMax = %d\n",startPos, endPos, max);
	return max;
}

void problem_solve()
{
	int fenceCount = 0;
	scanf("%d", &fenceCount);
	fence.clear();
	for (int i = 0; i < fenceCount; i++)
	{
		int height = 0;
		scanf("%d", &height);
		fence.push_back(height);
	}

	int maxRect = MaxRect(0, fenceCount);
	printf("%d\n", maxRect);
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