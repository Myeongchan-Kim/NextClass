#define MAX 1000000
#include <iostream>
using namespace std;

int Fibonacci(int n)
{
	if (n == 0 || n == 1)
		return n;
	return Fibonacci(n - 1) + Fibonacci(n - 2);
}

int CallFiboTopdown(int n)
{
	int* res = new int[n + 1];
	for (int i = 0; i < n + 1; i++)
		res[i] = -1;

	int result = FiboTopdown(n, res);
	delete[] res;
	return result;
}

int FiboTopdown(int n, int * res)
{
	if (res[n] != -1)
		return res[n];

	if (n < 2)
		res[n] = n;
	else
		res[n] = FiboTopdown(n - 1, res) + FiboTopdown(n - 2, res);

	return res[n];
}

int FibonacciBottomup(int n)
{
	int* res = new int[n + 1];

	res[0] = 0;
	res[1] = 1;

	for (int i = 2; i < n + 1; i++)
	{
		res[i] = res[i - 1] + res[i - 2];
	}

	int result = res[n];
	delete[] res;
	return result;
}

int MyFibonacci(int n)
{
	if (n < 2)
		return n;
	 
	int fiboN_2 = 0;
	int fiboN_1 = 1;
	int result = 1;

	for (int i = 2; i < n; i++)
	{
		result = fiboN_1 + fiboN_2;
		fiboN_2 = fiboN_1;
		fiboN_1 = result;
	}

	return result;
}