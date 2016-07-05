#include <iostream>
#include "Stack.h"
#include "Queue.h"
using namespace std;

int main()
{
	Stack<int> stack(5);

	for (int i = 1; i <= 7; i++)
	{
		stack.push(i);
	}
	
	for (int i = 7; i > 0; i--)
	{
		cout << "pop : " << stack.pop() << endl;
	}

	cout << "pop : " << stack.pop() << endl; //ERR! stack is already empty.
	
	Queue<double> que(5);
	for (int i = 1; i <= 7; i++)
	{
		que.Enque(i);
	}

	for (int i = 7; i > 0; i--)
	{
		cout << "deque : " << que.Deque() << endl;
	}

	cout << "deque : " << que.Deque() << endl; //ERR! stack is already empty.

	return 0;
}