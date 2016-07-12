#include <iostream>

struct Item
{
	int weight;
	int value;
};

int MaxKnapSack(Item* itemList, int curId, int remainWeight)
{
	if (curId < 0) return 0;
	auto& curItem = itemList[curId];
	
	int pickVal = 0;
	int noPickVal = 0;

	if (remainWeight >= curItem.weight)
		pickVal = curItem.value + MaxKnapSack(itemList, curId - 1, remainWeight);

	noPickVal = MaxKnapSack(itemList, curId - 1, remainWeight - curItem.weight);

	return (pickVal > noPickVal ? pickVal : noPickVal);
}

int MaxKnapSackBotup(Item* itemList, const int N, const int capacity)
{
	int** maxVal = new int*[capacity + 1];
	for (int i = 0; i <= capacity; i++)
	{
		maxVal[i] = new int[N + 1];
		maxVal[i][0] = 0;
	}

	for (int i = 0; i <= capacity; i++)
	{
		for (int j = 0; j <= N; j++)
		{
			int val = maxVal[i][j];
			if (maxVal[i][j + 1] < val)
				maxVal[i][j + 1] = val;
			
			int choiceWeight = i + itemList[j].weight; 
			int choiceVal = maxVal[i][j] + itemList[j].value;
			
			if (choiceWeight <= capacity && maxVal[choiceWeight][j + 1] < choiceVal)
				maxVal[choiceWeight][j + 1] = choiceVal;
		}
	}

	int result = maxVal[capacity][N];
	
	for (int i = 0; i <= capacity; i++)
		delete[] maxVal[i];
	delete[] maxVal;

	return result;
}