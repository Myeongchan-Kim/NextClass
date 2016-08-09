#include <iostream>

int main() 
{
	int N, M;
	scanf("%d %d", &N, &M);

	if (N == 1)
	{
		printf("%d\n", 1);
		return 0;
	}

	if (N == 2)
	{
		if (M >= 7)
			printf("%d\n", 4);
		else
			printf("%d\n", (M+1)/2);
		return 0;
	}

	if (N >= 3)
	{
		if (M >= 6)
			printf("%d\n", M - 2);
		else if (M == 5)
			printf("%d\n", 4);
		else
			printf("%d\n", M);
		return 0;
	}

	return 0;
}