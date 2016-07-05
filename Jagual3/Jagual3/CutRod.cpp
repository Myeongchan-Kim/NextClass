
int MaxPrice(int length, int* priceTable)
{
	if (length == 0)
		return 0;
	int maxResult = 0;
	int result = 0;
	for (int i = 1; i <= length; i++)
	{
		result = priceTable[i] + MaxPrice(length - i, priceTable);
		
		if (result > maxResult)
			maxResult = result;
	}

	return maxResult;
}