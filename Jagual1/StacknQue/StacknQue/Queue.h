#pragma once
#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;


template <class T>
class Queue
{
private:
	T * list;
	int max;
	int enquePos;
	int dequePos;
	bool isFull();
	bool isEmpty();
	void doubling();

public:
	void	Enque(T element);
	T		Deque();
	int		size();

	Queue(int);
	~Queue();
};


template <class T>
Queue<T>::Queue(int l_size = 10) : max(l_size)
{
	enquePos = 0;
	dequePos = 0;
	list = new T[l_size];
}

template <class T>
Queue<T>::~Queue()
{
	delete[] list;
}

template <class T>
void Queue<T>::Enque(T element)
{
	if (isFull()) 
	{
		doubling();
	}
	list[enquePos] = element;

	enquePos++;
	if (enquePos >= max)
		enquePos /= max;

}

template <class T>
T Queue<T>::Deque()
{
	if (isEmpty())
		return NULL;

	T result = list[dequePos];

	dequePos++;
	if (dequePos >= max)
		dequePos /= max;

	return result;
}

template <class T>
bool Queue<T>::isFull()
{
	if ( (enquePos + 1 == dequePos) || (enquePos + 1 == dequePos + max))
	{
		return true;
	}
	return false;
}

template <class T>
bool Queue<T>::isEmpty()
{
	if (enquePos == dequePos)
	{
		cout << " Que is Empty." << endl;
		return true;
	}
	return false;
}


template <class T>
void Queue<T>::doubling()
{
	T* newList = new T[max * 2];

	if (dequePos < enquePos)
	{
		//just copy que
		for (int i = 0; i < enquePos; i++)
		{
			newList[i] = list[i];
		}
	}
	else {
		for (int i = 0; i < enquePos; i++)
		{
			newList[i] = list[i];
		}

		for (int i = dequePos; i < max; i++)
		{
			newList[i + max] = list[i];
		}
	}

	max *= 2;

	delete[] list;

	list = newList;
}

template <class T>
int Queue<T>::size()
{
	return max;
}