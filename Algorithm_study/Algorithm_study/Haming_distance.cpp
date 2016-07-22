#include <iostream>

int DNA_length;
int str_length;
char str[1001][52];
char result[52];
char agct[] = "ACGT";
int resultNum = 0;

char maxChar(int count[4]) 
{
	int maxId = 0;
	for (int i = 0; i < 4; i++)
	{
		if (count[i] > count[maxId])
			maxId = i;
	}

	resultNum += DNA_length - count[maxId];
	return agct[maxId];
}

int main() 
{
	scanf("%d", &DNA_length);
	scanf("%d", &str_length);

	for (int i = 0; i < DNA_length; i++) 
	{
		scanf("%s\n", str[i]);
	}

	for (int charId = 0; charId < str_length; charId++)
	{
		int count[4] = { 0, };
		for (int i = 0; i < DNA_length; i++)
		{
			for (int cid = 0; cid < 4; cid++)
			{
				if (agct[cid] == str[i][charId])
				{
					count[cid]++;
					break;
				}
			}
		}
		
		result[charId] = maxChar(count);
	}

	result[str_length] = '\0';

	printf("%s\n%d\n", result, resultNum);
	return 0;
}