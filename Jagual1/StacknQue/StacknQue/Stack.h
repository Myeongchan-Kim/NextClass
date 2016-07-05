#pragma once
#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;

template <class T>
class Stack
{
private:
	T * list;
	int length;
	int max;
	void isFull();
	bool isEmpty();

public:
	void	push(T element);
	T		pop();
	int		size();

	Stack(int max);
	~Stack();
};







template <class T>
void Stack<T>::push(T element)
{
	// If stack is full , make it 2 times bigger.
	if (length >= max)
		isFull();

	list[length] = element;
	length++;
}

template <class T>
T Stack<T>::pop()
{
	if (isEmpty())
	{
		cout << "stack is empty." << endl;
		return NULL;
	}

	T element = list[length - 1];
	list[length - 1] = NULL;
	length--;
	return element;
}

template <class T>
int Stack<T>::size()
{
	return length;
}

template <class T>
Stack<T>::Stack(int l_size = 10)
{
	list = new T[l_size];
	max = l_size;
	length = 0;
}

template <class T>
Stack<T>::~Stack()
{
	delete[] list;
}

template <class T>
void Stack<T>::isFull()
{
	max *= 2;
	T* newList = new T[max]; //resize stack
	for (int i = 0; i < length; i++) // copy all elements
	{
		newList[i] = list[i];
	}
	delete list;
	list = newList;
}

template <class T>
bool Stack<T>::isEmpty()
{
	if (length <= 0)
		return true;
	else
		return false;
}

